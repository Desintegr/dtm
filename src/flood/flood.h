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
  Flood(QString fileName);
  virtual ~Flood();

public slots:
  void update();

private:
  void getDTM();
  void readSources(QString fileName);
  void fill();
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
