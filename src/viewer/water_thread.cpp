#include "flowvr_thread.h"

#include "flowvr.h"
#include "dtm.h"
#include "water.h"
#include "point3d.h"

FlowVRThread::FlowVRThread(DTM *dtm, Water *water):
  m_dtm(dtm),
  m_water(water)
{
  m_flowvr = new FlowVR();
  m_flowvr->init();
  if(!flowvr.init()) {
    std::cerr << "Error: cannot initialize FlowVR ports" << std::endl;
    exit(EXIT_FAILURE);
  }
}

FlowVRThread::~WaterThread()
{
  delete m_flowvr;
}

void FlowVRThread::run()
{
  sendDTM();

  while(m_flowvr->module()->wait())
    getWater();

  exec();
}

void FlowVRThread::sendDTM()
{
  // envoi du nombre de lignes

  flowvr::MessageWrite nrowsMsg;
  nrowsMsg.data = m_flowvr->module()->alloc(sizeof(size_t));
  size_t nrows = m_dtm->nrows();
  memcpy(nrowsMsg.data.writeAccess(), &nrows, sizeof(size_t));
  m_flowvr->module()->put(m_flowvr->dtmOut(), nrowsMsg);

  // envoi du nombre de colonnes

  flowvr::MessageWrite ncolsMsg;
  ncolsMsg.data = m_flowvr->module()->alloc(sizeof(size_t));
  size_t ncols = m_dtm->ncols();
  memcpy(ncolsMsg.data.writeAccess(), &ncols, sizeof(size_t));
  m_flowvr->module()->put(m_flowvr->dtmOut(), ncolsMsg);

  // envoi du terrain

  flowvr::MessageWrite dtmMsg;

  const size_t size = m_dtm->nrows() * m_dtm->ncols();
  float dtm[size];

  for(index_t i = 0; i < m_dtm->nrows(); ++i)
    for(index_t j = 0; j < m_dtm->ncols(); ++j) {
      const index_t k = i * m_dtm->ncols() + j;
      dtm[k] = m_dtm->vertices()[k].z();
    }

  const size_t size_alloc = size * sizeof(float);

  dtmMsg.data = m_flowvr->module()->alloc(size_alloc);
  memcpy(dtmMsg.data.writeAccess(), dtm, size_alloc);

  m_flowvr->module()->put(m_flowvr->dtmOut(), dtmMsg);
}

void FlowVRThread::getWater() {
  flowvr::Message waterMsg;
  m_flowvr->module()->get(m_flowvr->waterIn(), waterMsg);

  const size_t size = m_dtm->nrows() * m_dtm->ncols() * sizeof(float);

  memcpy(m_water->z(), waterMsg.data.readAccess(), size);

  for(index_t i = 0; i < m_dtm->nrows(); ++i)
    for(index_t j = 0; j < m_dtm->ncols(); ++j) {
      const index_t k = i * m_dtm->ncols() + j;
      if(m_water->z()[k] != 0)
        m_water->vertices()[k].setZ(m_dtm->vertices()[k].z() + m_water->z()[k]);
    }

  emit updated();
}

