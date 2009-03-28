#ifndef WATER_H
#define WATER_H

#include <QtCore>

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

  uint m_ncols;
  uint m_nrows;
  uint m_nvertices;
  uint m_nindices;

  float* z;

  Point3d* m_vertices;
  uint* m_indices;

  enum Buffers
  {
    VERTICES,
    INDICES,
  };
  uint m_buffers[2];

private:
  void initVertices();
  void initIndices();
  void initVBO();
  void free();
};

#endif
