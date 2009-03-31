#ifndef FLOWVR_THREAD_H
#define FLOWVR_THREAD_H

#include "flowvr.h"

#include <QtCore>

class DTM;
class Water;

class FlowVRThread: public QThread
{
  Q_OBJECT

public:
  /**
   * Constructeur du module threadé FlowVR
   *
   * @param dtm le terrain
   * @param water l'eau
   */
  FlowVRThread(const DTM *dtm, const Water *water);

  /**
   * Destrcuteur du module threadé FlowVR
   */
  virtual ~FlowVRThread();

protected:
  /**
   * Lance le thread
   */
  void run();

private:
  /**
   * Envoie le terrain au module d'inondation
   */
  void sendDTM();

  /**
   * Reçoit les données d'eau du module d'inondation
   */
  void getWater();


private:
  FlowVR m_flowvr;

  const DTM *m_dtm;
  const Water *m_water;

signals:
  void updated();
};

#endif
