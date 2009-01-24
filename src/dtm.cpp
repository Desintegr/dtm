#include "dtm.h"

#define GL_GLEXT_PROTOTYPES

#include <cfloat>

#include <QtOpenGL>
#include <QtCore>

#include "point3d.h"

DTM::DTM(QString fileName) {
  QFile file(fileName + ".grd");

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

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
  initIndexes();
  initNormals();
  initTextures();
  initVBO();
  free();

  file.close();
}

void DTM::initVertices(QTextStream& in) {
  m_minz = FLT_MAX;

  m_nvertices = m_nrows*m_ncols;
  m_vertices = new Point3d[m_nvertices];

  for(uint i=0; i<m_nrows; i++)
    for(uint j=0; j<m_ncols; j++) {
      const uint k = i*m_ncols+j;

      m_vertices[k].setX(i);
      m_vertices[k].setY(j);
      float z;
      in >> z;
      m_vertices[k].setZ(z);

      if(z!=m_nodata && z<m_minz)
        m_minz = z;
    }

  // remplacement des nodata par la valeur minimale de z
  for(uint i=0; i<m_nrows; i++)
    for(uint j=0; j<m_ncols; j++) {
      const uint k = i*m_ncols+j;
      if(m_vertices[k].z()==m_nodata)
        m_vertices[k].setZ(m_minz);
    }
}


void DTM::initIndexes() {
  m_nindexes = 3*2*(m_nrows-1)*(m_ncols-1);
  m_indexes = new uint[m_nindexes];

  for(uint i=0; i<m_nrows-1; i++)
    for(uint j=0; j<m_ncols-1; j++) {
      const uint k = (i*(m_ncols-1)+j)*6;

      m_indexes[k] = i*m_ncols+j;
      m_indexes[k+1] = (i+1)*m_ncols+j;
      m_indexes[k+2] = i*m_ncols+j+1;

      m_indexes[k+3] = (i+1)*m_ncols+j+1;
      m_indexes[k+4] = (i+1)*m_ncols+j;
      m_indexes[k+5] = i*m_ncols+j+1;
    }
}

void DTM::initNormals() {
  m_nnormals = m_nrows*m_ncols;
  m_normals = new Point3d[m_nnormals];

  for(uint i=0; i<m_nrows-1; i++)
    for(uint j=0; j<m_ncols-1; j++) {
      const uint k = (i*(m_ncols-1)+j)*6;

      Point3d p1, p2, p3;

      p1 = m_vertices[(i+1)*m_ncols+j] - m_vertices[i*m_ncols+j];
      p2 = m_vertices[i*m_ncols+j+1] - m_vertices[i*m_ncols+j];
      p3 = p1.cross(p2);

      m_normals[m_indexes[k]] += p3;
      m_normals[m_indexes[k+1]] += p3;
      m_normals[m_indexes[k+2]] += p3;

      p1 = m_vertices[i*m_ncols+j+1] - m_vertices[(i+1)*m_ncols+j+1];
      p2 = m_vertices[(i+1)*m_ncols+j] - m_vertices[(i+1)*m_ncols+j+1];
      p3 = p1.cross(p2);

      m_normals[m_indexes[k+3]] += p3;
      m_normals[m_indexes[k+4]] += p3;
      m_normals[m_indexes[k+5]] += p3;
    }

  for(uint i=0; i<m_nnormals; i++)
    m_normals[i].normalize();
}

void DTM::initTextures() {
  m_ntextures = 2*m_nrows*m_ncols;
  m_textures = new float[m_ntextures];

  for(uint i=0; i<m_nrows; i++)
    for(uint j=0; j<m_ncols; j++) {
      const uint k = (i*m_ncols+j)*2;

      m_textures[k] = m_vertices[(i*m_ncols+j)].y()/(m_ncols-1);
      m_textures[k+1] = m_vertices[(m_nrows*m_ncols)-(i*m_ncols+j)].x()/(m_nrows-1);
    }
}

void DTM::DTM::initVBO() {
  glGenBuffers(4, m_buffers);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[VERTICES]);
  glBufferData(GL_ARRAY_BUFFER, m_nvertices*sizeof(Point3d), m_vertices, GL_STATIC_DRAW);
  glVertexPointer(3, GL_FLOAT, 0, 0);
  glEnableClientState(GL_VERTEX_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[NORMALS]);
  glBufferData(GL_ARRAY_BUFFER, m_nnormals*sizeof(Point3d), m_normals, GL_STATIC_DRAW);
  glNormalPointer(GL_FLOAT, 0, 0);
  glEnableClientState(GL_NORMAL_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[TEXTURES]);
  glBufferData(GL_ARRAY_BUFFER, m_ntextures*sizeof(float), m_textures, GL_STATIC_DRAW);
  glTexCoordPointer(2, GL_FLOAT, 0, 0);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDEXES]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nindexes*sizeof(uint), m_indexes, GL_STATIC_DRAW);
}

void DTM::free() {
  delete[] m_vertices;
  delete[] m_normals;
  delete[] m_indexes;
  delete[] m_textures;
}

void DTM::draw() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[INDEXES]);
  glDrawElements(GL_TRIANGLES, m_nindexes, GL_UNSIGNED_INT, 0);
}
