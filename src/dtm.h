#ifndef DTM_H
#define DTM_H

#include <QtOpenGL>

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
    GLuint* m_indexes;

  public:
    DTM();
    ~DTM();

    void load(QString filename);

    void draw() const;

    void test();

};

#endif
