#ifndef DTM_H
#define DTM_H

#include <QtCore>

typedef unsigned int size_t;
typedef unsigned int index_t;

class Point3d;

class DTM
{
public:
  /**
   * Constructeur de terrain à partir d'un fichier
   *
   * @param filename le nom du fichier
   */
  DTM(const QString &filename);

  /**
   * Destructeur de terrain
   */
  virtual ~DTM();

  /**
   * Retourne le nombre de colonnes du terrain
   */
  size_t ncols() const;

  /**
   * Retourne le nombre de lignes du terrain
   */
  size_t nrows() const;

  /**
   * Retourne la hauteur la plus basse du terrain
   */
  float minZ() const;

  /**
   * Retourne les sommets du terrain
   */
  Point3d * vertices() const;

  /**
   * Dessine le terrain
   */
  void draw() const;

private:
  /**
   * Initialise les sommets du terrain
   */
  void initVertices(QTextStream &in);

  /**
   * Initialise les index du terrain
   */
  void initIndices();

  /**
   * Initialise les normales du terrain
   */
  void initNormals();

  /**
   * Initialise les textures du terrain
   */
  void initTextures();

  /**
   * Initialise les VBO pour le terrain
   */
  void initVBO();

  /**
   * Libère les ressources qui ne sont plus utilisées après constructions du
   * terrain
   */
  void free();

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
};

inline size_t DTM::ncols() const
{
  return m_ncols;
}

inline size_t DTM::nrows() const
{
  return m_nrows;
}

inline Point3d * DTM::vertices() const
{
  return m_vertices;
}

inline float DTM::minZ() const
{
  return m_minz;
}

#endif
