#ifndef DTM_H
#define DTM_H

#include <QString>

class Point3d;

class DTM {

  public: // TODO
    uint m_ncols;
    uint m_nrows;
    uint m_xllcorner;
    uint m_yllcorner;
    uint m_cellsize;
    float m_nodata;

    float minz;
    float maxz;

    uint m_nvertices;
    Point3d* m_vertices;

    uint m_ncolors;
    float* m_colors;

    uint m_nindexes;
    uint* m_indexes;

    uint m_nnormals;
    Point3d* m_normals;

    enum Buffers {
      VERTICES,
      //COLORS,
      NORMALS,
      INDEXES
    };
    uint m_buffers[3];

  public:
    DTM();

    void load(QString filename);
    void initVBO();
    void draw();

    void affiche_normales(int);

};

#endif
