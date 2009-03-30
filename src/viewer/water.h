#ifndef WATER_H
#define WATER_H

#include <QtCore>

typedef unsigned int index_t;
typedef unsigned int size_t;

class FlowVR;
class DTM;
class Point3d;

class Water: public QObject
{
  Q_OBJECT

public:
  Water(DTM *dtm);
  virtual ~Water();

  void draw() const;

  void run();

  float * z() const;
  Point3d * vertices() const;

public slots:
  void update();

private:
  DTM *m_dtm;

  size_t m_ncols;
  size_t m_nrows;
  size_t m_nvertices;
  size_t m_nindices;

  float *m_z;

  //FlowVR *m_flowvr;

  //QTimer *m_timer;

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

  //void fill();
};

inline float * Water::z() const
{
  return m_z;
}

inline Point3d* Water::vertices() const
{
  return m_vertices;
}


#endif
