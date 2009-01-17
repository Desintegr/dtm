#ifndef DTM_H
#define DTM_H

#include <QtOpenGL>

#include <QString>

class DTM {

  private:
    int m_ncols;
    int m_nrows;
    int m_xllcorner;
    int m_yllcorner;
    int m_cellsize;
    int m_nodata;

    int m_nvertices;
    float* m_vertices;

    int m_nindexes;
    GLuint* m_indexes;

  public:
    DTM();
    ~DTM();

    void load(QString filename);

    void draw();

    void test();

};

#endif
