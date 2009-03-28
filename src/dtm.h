#ifndef DTM_H
#define DTM_H

#include <QString>

class QTextStream;

class Point3d;

class DTM
{
public:
  DTM(QString fileName);
  ~DTM();

  uint ncols() const;
  uint nrows() const;

  float minz() const;

  Point3d* vertices() const;

  void draw() const;

private:
  uint m_ncols;
  uint m_nrows;
  uint m_xllcorner;
  uint m_yllcorner;
  uint m_cellsize;
  float m_nodata;

  float m_minz;

  uint m_nvertices;
  uint m_nindices;

  Point3d* m_vertices;
  uint* m_indices;
  Point3d* m_normals;
  float* m_textures;

  enum Buffers
  {
    VERTICES,
    NORMALS,
    INDICES,
    TEXTURES
  };
  uint m_buffers[4];

private:
  void initVertices(QTextStream& in);
  void initIndices();
  void initNormals();
  void initTextures();
  void initVBO();
  void free();
};

inline uint DTM::ncols() const
{
  return m_ncols;
}

inline uint DTM::nrows() const
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
