#ifndef FLOWVR_THREAD_H
#define FLOWVR_THREAD_H

class FlowVR;
class DTM;
class Water;

#include <QtCore>

class FlowVRThread: public QThread
{
  Q_OBJECT

public:
  FlowVRThread(DTM *dtm, Water *water);
  virtual ~FlowVRThread();

  void run();

  void sendDTM();
  void getWater();

private:
  FlowVR *m_flowvr;

  DTM *m_dtm;
  Water *m_water;

signals:
  void updated();
};

#endif
