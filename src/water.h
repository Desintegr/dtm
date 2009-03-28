#ifndef WATER_H
#define WATER_H

#include <QtCore>

typedef uint index_t;
typedef uint size_t;

class DTM;
class Point3d;

class Water: public QObject
{
  Q_OBJECT

public:
  Water(DTM *dtm);
  ~Water();

  void draw() const;

public slots:
  void update() const;

private:
  DTM *m_dtm;

  QTimer *timer;

  size_t m_ncols;
  size_t m_nrows;
  size_t m_nvertices;
  size_t m_nindices;

  float* z;

  Point3d* m_vertices;
  index_t* m_indices;

  enum Buffers
  {
    VERTICES,
    INDICES,
  };
  index_t m_buffers[2];

private:
  void initVertices();
  void initIndices();
  void initVBO();
  void free();
};

#endif
