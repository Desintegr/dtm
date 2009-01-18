#include "dtm.h"

#include <QtCore>

DTM::DTM() {
}

DTM::~DTM() {
  delete[] m_vertices;
  delete[] m_indexes;
}

void DTM::load(QString filename) {
  QFile file(filename);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QTextStream in(&file);

  QString null;

  in >> null; in >> m_ncols;
  in >> null; in >> m_nrows;
  in >> null; in >> m_xllcorner;
  in >> null; in >> m_yllcorner;
  in >> null; in >> m_cellsize;
  in >> null; in >> m_nodata;

  int k;

  m_nvertices = m_nrows*m_ncols;
  m_vertices = new float[3*m_nvertices];

  k = 0;
  for(uint i=0; i<m_nrows; i++)
    for(uint j=0; j<m_ncols; j++) {
      m_vertices[k] = i;
      m_vertices[k+1] = j;
      in >> m_vertices[k+2];
      k += 3;
    }

  m_nindexes = 2*(m_nrows-1)*(m_ncols-1);
  m_indexes = new GLuint[3*m_nindexes];

  k = 0;
  for(uint i=0; i<m_nrows-1; i++)
    for(uint j=0; j<m_ncols-1; j++) {
      m_indexes[k] = i*m_ncols+j;
      m_indexes[k+1] = (i+1)*m_ncols+j;
      m_indexes[k+2] = i*m_ncols+j+1;

      m_indexes[k+3] = (i+1)*m_ncols+j+1;
      m_indexes[k+4] = (i+1)*m_ncols+j;
      m_indexes[k+5] = i*m_ncols+j+1;

      k += 6;
    }

  file.close();
}

#include <QtDebug>
void DTM::test() {
  //qDebug() << m_ncols;
  //qDebug() << m_nrows;
  //qDebug() << m_xllcorner;
  //qDebug() << m_yllcorner;
  //qDebug() << m_cellsize;
  //qDebug() << m_nodata;

  //qDebug() << "";

  //for(int i=0; i<3*m_nvertices; i++)
  //  qDebug() << m_vertices[i];


  //for(int i=0; i<3*m_nindexes; i++)
  //  qDebug() << m_indexes[i];

}

void DTM::draw() const {
  glColor3f(1,1,1);
  glEnableClientState(GL_VERTEX_ARRAY);
  glPolygonMode(GL_FRONT,GL_LINE);
  glPolygonMode(GL_BACK,GL_LINE);
  glVertexPointer(3, GL_FLOAT, 0, m_vertices);
  glDrawElements(GL_TRIANGLES, 3*m_nindexes, GL_UNSIGNED_INT, m_indexes);
}
