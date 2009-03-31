#include "dtm.h"

#include "point3d.h"

#define GL_GLEXT_PROTOTYPES

#include <QtOpenGL>

#include <iostream>

#include <cfloat>

DTM::DTM(const QString &filename)
{
  QFile file(filename + ".grd");

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    std::cerr << "Error: unable to read grid file" << std::endl;
    exit(EXIT_FAILURE);
  }

  // lecture des informations sur le terrain
  QTextStream in(&file);

  QString null;

  in >> null;
  in >> m_ncols;
  in >> null;
  in >> m_nrows;
  in >> null;
  in >> m_xllcorner;
  in >> null;
  in >> m_yllcorner;
  in >> null;
  in >> m_cellsize;
  in >> null;
  in >> m_nodata;

  initVertices(in);
  initIndices();
  initNormals();
  initTextures();
  initVBO();
  free();

  file.close();
}

DTM::~DTM()
{
  delete[] m_vertices;
}

void DTM::draw() const
{
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[NORMALS]);
  glNormalPointer(GL_FLOAT, 0, 0);
  glEnableClientState(GL_NORMAL_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[TEXTURES]);
  glTexCoordPointer(2, GL_FLOAT, 0, 0);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[VERTICES]);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glEnableClientState(GL_VERTEX_ARRAY);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDICES]);

  glDrawElements(GL_TRIANGLES, m_nindices, GL_UNSIGNED_INT, 0);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDisable(GL_LIGHTING);
  glDisable(GL_LIGHT0);
}

void DTM::initVertices(QTextStream& in)
{
  m_minz = FLT_MAX;

  m_nvertices = m_nrows * m_ncols;
  m_vertices = new Point3d[m_nvertices];

  // lecture des données du terrain
  for(index_t i = 0; i < m_nrows; ++i)
    for(index_t j = 0; j < m_ncols; ++j) {
      const index_t k = i * m_ncols + j;

      m_vertices[k].setX(i);
      m_vertices[k].setY(j);
      float z;
      in >> z;
      m_vertices[k].setZ(z);

      // calcul du z minimum
      if(z != m_nodata && z < m_minz)
        m_minz = z;
    }

  // remplacement des nodata par le z minimum
  for(index_t i = 0; i < m_nrows; ++i)
    for(index_t j = 0; j < m_ncols; ++j) {
      const index_t k = i * m_ncols + j;
      if(m_vertices[k].z() == m_nodata)
        m_vertices[k].setZ(m_minz);
    }
}

void DTM::initIndices()
{
  m_nindices = 3 * 2 * (m_nrows - 1) * (m_ncols - 1);
  m_indices = new index_t[m_nindices];

  for(index_t i = 0; i < m_nrows - 1; ++i)
    for(index_t j = 0; j < m_ncols - 1; ++j) {
      const index_t k = 3 * 2 * (i * (m_ncols - 1) + j);

      // triangle 1
      m_indices[k] = i * m_ncols + j;
      m_indices[k + 1] = (i + 1) * m_ncols + j;
      m_indices[k + 2] = i * m_ncols + j + 1;

      // triangle 2
      m_indices[k + 3] = (i + 1 ) * m_ncols + j + 1;
      m_indices[k + 4] = (i + 1) * m_ncols + j;
      m_indices[k + 5] = i * m_ncols + j + 1;
    }
}

void DTM::initNormals()
{
  m_normals = new Point3d[m_nvertices];

  for(index_t i = 0; i < m_nrows - 1; ++i)
    for(index_t j = 0; j < m_ncols - 1; ++j) {
      const index_t k = 3 * 2 * (i * (m_ncols - 1) + j);

      Point3d p1;
      Point3d p2;
      Point3d p3;

      // triangle 1
      p1 = m_vertices[(i + 1) * m_ncols + j] - m_vertices[i * m_ncols + j];
      p2 = m_vertices[i * m_ncols + j + 1] - m_vertices[i * m_ncols + j];
      p3 = p1.cross(p2);

      m_normals[m_indices[k]] += p3;
      m_normals[m_indices[k + 1]] += p3;
      m_normals[m_indices[k + 2]] += p3;

      // triangle 2
      p1 = m_vertices[i * m_ncols + j + 1] - m_vertices[(i + 1) * m_ncols + j + 1];
      p2 = m_vertices[(i + 1) * m_ncols + j] - m_vertices[(i + 1) * m_ncols + j + 1];
      p3 = p1.cross(p2);

      m_normals[m_indices[k + 3]] += p3;
      m_normals[m_indices[k + 4]] += p3;
      m_normals[m_indices[k + 5]] += p3;
    }

  for(index_t i = 0; i < m_nvertices; ++i)
    m_normals[i].normalize();
}

void DTM::initTextures()
{
  m_textures = new float[2 * m_nvertices];

  for(index_t i = 0; i < m_nrows; ++i)
    for(index_t j = 0; j < m_ncols; ++j) {
      const index_t k = 2 * (i * m_ncols + j);

      // coordonnée x de la texture
      m_textures[k] = m_vertices[(i * m_ncols + j)].y() / (m_ncols - 1);

      // coordonnée y de la texture
      m_textures[k + 1] = m_vertices[(m_nrows * m_ncols) - (i * m_ncols + j)].x() / (m_nrows - 1);
    }
}

void DTM::initVBO()
{
  glGenBuffers(4, m_buffers);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[VERTICES]);
  glBufferData(GL_ARRAY_BUFFER, m_nvertices * sizeof(Point3d), m_vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[NORMALS]);
  glBufferData(GL_ARRAY_BUFFER, m_nvertices * sizeof(Point3d), m_normals, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[TEXTURES]);
  glBufferData(GL_ARRAY_BUFFER, 2 * m_nvertices * sizeof(float), m_textures, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDICES]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nindices * sizeof(index_t), m_indices, GL_STATIC_DRAW);
}

void DTM::free()
{
  delete[] m_normals;
  delete[] m_indices;
  delete[] m_textures;
}
