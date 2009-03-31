#ifndef WATER_H
#define WATER_H

#include <QtCore>

typedef unsigned int index_t;
typedef unsigned int size_t;

class DTM;
class Point3d;

class Water: public QObject
{
  Q_OBJECT

public:
  /**
   * Constructeur d'eau
   *
   * @param dtm le terrain
   */
  Water(DTM *dtm);

  /**
   * Destructeur d'eau
   */
  virtual ~Water();

  /**
   * Retourne les données de l'eau
   */
  float * values() const;

  /**
   * Retourne les somments de l'eau
   */
  Point3d * vertices() const;

  /**
   * Dessine l'eau
   */
  void draw() const;

public slots:
  /**
   * Met à jour le VBO des sommets de l'eau
   */
  void updateVBO();

private:
  DTM *m_dtm;

  size_t m_ncols;
  size_t m_nrows;
  size_t m_nvertices;
  size_t m_nindices;

  float *m_values;

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
};

inline float * Water::values() const
{
  return m_values;
}

inline Point3d* Water::vertices() const
{
  return m_vertices;
}

#endif
