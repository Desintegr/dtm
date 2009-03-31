#include "flowvr_thread.h"

#include "dtm.h"
#include "water.h"
#include "point3d.h"

FlowVRThread::FlowVRThread(const DTM *dtm, const Water *water):
  m_dtm(dtm),
  m_water(water)
{
  if(!m_flowvr.init()) {
    std::cerr << "Error: cannot initialize FlowVR ports" << std::endl;
    exit(EXIT_FAILURE);
  }
}

FlowVRThread::~FlowVRThread()
{
}

void FlowVRThread::run()
{
  // envoie d'abord les données du terrain au module d'inondation
  sendDTM();

  // attend les données de l'inondation
  while(m_flowvr.module()->wait())
    getWater();

  // lance la boucle d'événements
  exec();
}

void FlowVRThread::sendDTM()
{
  // envoie le nombre de lignes
  flowvr::MessageWrite nrowsMsg;
  nrowsMsg.data = m_flowvr.module()->alloc(sizeof(size_t));
  size_t nrows = m_dtm->nrows();
  memcpy(nrowsMsg.data.writeAccess(), &nrows, sizeof(size_t));
  m_flowvr.module()->put(m_flowvr.dtmOut(), nrowsMsg);

  // envoie le nombre de colonnes
  flowvr::MessageWrite ncolsMsg;
  ncolsMsg.data = m_flowvr.module()->alloc(sizeof(size_t));
  size_t ncols = m_dtm->ncols();
  memcpy(ncolsMsg.data.writeAccess(), &ncols, sizeof(size_t));
  m_flowvr.module()->put(m_flowvr.dtmOut(), ncolsMsg);

  // envoie le terrain
  flowvr::MessageWrite dtmMsg;

  const size_t size = m_dtm->nrows() * m_dtm->ncols();
  float dtm[size];

  for(index_t i = 0; i < m_dtm->nrows(); ++i)
    for(index_t j = 0; j < m_dtm->ncols(); ++j) {
      const index_t k = i * m_dtm->ncols() + j;
      dtm[k] = m_dtm->vertices()[k].z();
    }

  const size_t size_alloc = size * sizeof(float);

  dtmMsg.data = m_flowvr.module()->alloc(size_alloc);
  memcpy(dtmMsg.data.writeAccess(), dtm, size_alloc);

  m_flowvr.module()->put(m_flowvr.dtmOut(), dtmMsg);
}

void FlowVRThread::getWater() {
  static const size_t size = m_dtm->nrows() * m_dtm->ncols() * sizeof(float);

  // reçoit les données de l'inondation
  flowvr::Message waterMsg;
  m_flowvr.module()->get(m_flowvr.waterIn(), waterMsg);

  memcpy(m_water->values(), waterMsg.data.readAccess(), size);

  for(index_t i = 0; i < m_dtm->nrows(); ++i)
    for(index_t j = 0; j < m_dtm->ncols(); ++j) {
      const index_t k = i * m_dtm->ncols() + j;
      if(m_water->values()[k] != 0)
        m_water->vertices()[k].setZ(m_dtm->vertices()[k].z() + m_water->values()[k]);
    }

  // signal de mise à jour pour la visualisation
  emit updated();
}
