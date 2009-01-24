#ifndef DTM_H
#define DTM_H

#include <QString>

class QTextStream;

class Point3d;

class DTM {

  public:
    DTM(QString fileName);

    inline uint ncols() const {
      return m_ncols;
    }

    inline uint nrows() const {
      return m_nrows;
    }

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
    Point3d* m_vertices;

    uint m_nindexes;
    uint* m_indexes;

    uint m_nnormals;
    Point3d* m_normals;

    uint m_ntextures;
    float* m_textures;

    enum Buffers {
      VERTICES,
      NORMALS,
      INDEXES,
      TEXTURES
    };
    uint m_buffers[4];

  private:
    void initVertices(QTextStream& in);
    void initIndexes();
    void initNormals();
    void initTextures();
    void initVBO();
    void free();

};

#endif
