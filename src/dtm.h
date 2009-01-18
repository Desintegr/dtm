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
    int m_nodata;

    uint m_nvertices;
    float* m_vertices;

    uint m_nindexes;
    uint* m_indexes;

    enum Buffers {
      VERTICES,
      INDEXES
    };
    uint m_buffers[2];

  public:
    DTM();
    ~DTM();

    void load(QString filename);

    void draw() const;

    void test();
    void initVBO();

};

#endif
