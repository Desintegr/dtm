#ifndef FLOOD_H
#define FLOOD_H

#include <QtCore>

typedef unsigned int index_t;
typedef unsigned int size_t;

class FlowVR;

class Flood: public QObject
{
  Q_OBJECT

public:
  /**
   * Constructeur du module d'inondation
   *
   * Lit un fichier en entrée contenant les sources de l'inondation
   * Format du fichier : deux entiers par ligne correspondant au point x et y
   *
   * @param le nom du fichier contenant les sources
   */
  Flood(const QString &filename);

  /**
   * Destructeur du module d'inondation
   */
  virtual ~Flood();

private slots:
  /**
   * Mise à jour des niveaux de l'eau
   */
  void update();

private:
  /**
   * Récupère le terrain à partir du module viewer
   */
  void getDTM();

  /**
   * Lit le fichier contenant les sources
   *
   * @param filename le nom du fichier contenant les sources
   */
  void readSources(const QString &filename);

  /**
   * Remplit d'eau les différentes sources
   */
  void fill();

  /**
   * Envoie les niveaux de l'eau à module viewer
   */
  void sendWater() const;

private:
  QTimer *m_timer;
  FlowVR *m_flowvr;

  size_t m_nrows;
  size_t m_ncols;

  float *m_dtm;
  float *m_water;

  QList<int> m_sources;
};

#endif
