#ifndef DTM_H
#define DTM_H

#include <QString>

class Point3d;

class QTextStream;

typedef uint size_t;
typedef uint index_t;

class DTM
{
public:
  DTM(QString fileName);
  virtual ~DTM();

  size_t ncols() const;
  size_t nrows() const;

  float minz() const;

  Point3d * vertices() const;

  void draw() const;

private:
  size_t m_ncols;
  size_t m_nrows;
  size_t m_xllcorner;
  size_t m_yllcorner;
  size_t m_cellsize;
  float m_nodata;

  float m_minz;

  size_t m_nvertices;
  size_t m_nindices;

  Point3d *m_vertices;
  index_t *m_indices;
  Point3d *m_normals;
  float *m_textures;

  enum Buffers
  {
    VERTICES,
    NORMALS,
    INDICES,
    TEXTURES
  };
  index_t m_buffers[4];

private:
  void initVertices(QTextStream& in);
  void initIndices();
  void initNormals();
  void initTextures();
  void initVBO();
  void free();
};

inline size_t DTM::ncols() const
{
  return m_ncols;
}

inline size_t DTM::nrows() const
{
  return m_nrows;
}

inline Point3d* DTM::vertices() const
{
  return m_vertices;
}

inline float DTM::minz() const
{
  return m_minz;
}

#endif
