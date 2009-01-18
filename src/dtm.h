#ifndef DTM_H
#define DTM_H

#include <QString>

class DTM {

  private:
    uint m_ncols;
    uint m_nrows;
    uint m_xllcorner;
    uint m_yllcorner;
    uint m_cellsize;
    float m_nodata;

    float minz;
    float maxz;

    uint m_nvertices;
    float* m_vertices;

    uint m_ncolors;
    float* m_colors;

    uint m_nindexes;
    uint* m_indexes;

    enum Buffers {
      VERTICES,
      COLORS,
      INDEXES
    };
    uint m_buffers[3];

  public:
    DTM();
    ~DTM();

    void load(QString filename);
    void initVBO();
    void draw() const;

};

#endif
