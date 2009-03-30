#include "flood.h"

#include "flowvr.h"

Flood::Flood(QString fileName):
  m_timer(new QTimer(this)),
  m_flowvr(new FlowVR())
{
  if(!m_flowvr->init()) {
    std::cerr << "Error: cannot initialize FlowVR ports" << std::endl;
    exit(EXIT_FAILURE);
  }

  getDTM();
  readSources(fileName);

  m_water = new float[m_nrows * m_ncols];
  for(index_t i = 0; i < m_nrows; ++i)
    for(index_t j = 0; j < m_ncols; ++j) {
      const index_t k = i * m_ncols + j;
      m_water[k] = 0;
    }

  connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
  m_timer->start(200);
}

Flood::~Flood()
{
  delete m_flowvr;

  delete m_dtm;
  delete m_water;

  delete m_timer;
}

void Flood::getDTM()
{
  // réception du nombre de lignes

  if(m_flowvr->module()->wait()) {
    flowvr::Message nrowsMsg;
    m_flowvr->module()->get(m_flowvr->dtmIn(), nrowsMsg);

    memcpy(&m_nrows, nrowsMsg.data.readAccess(), sizeof(size_t));
  }

  // réception du nombre de colonnes

  if(m_flowvr->module()->wait()) {
    flowvr::Message ncolsMsg;
    m_flowvr->module()->get(m_flowvr->dtmIn(), ncolsMsg);

    memcpy(&m_ncols, ncolsMsg.data.readAccess(), sizeof(size_t));
  }

  // réception du terrain

  if(m_flowvr->module()->wait()) {
    flowvr::Message dtmMsg;
    m_flowvr->module()->get(m_flowvr->dtmIn(), dtmMsg);

    const size_t size = m_nrows * m_ncols;
    m_dtm = new float[size];
    memcpy(m_dtm, dtmMsg.data.readAccess(), size * sizeof(float));
  }
}

void Flood::readSources(QString fileName)
{
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    std::cerr << "Warning: error while reading water source file" << std::endl;

  int x;
  int y;

  // TODO 0 en trop
  QTextStream in(&file);
  while(!in.atEnd()) {
    in >> x;
    in >> y;
    m_sources.append(x * m_ncols + y);
  }

  file.close();
}

void Flood::update()
{
  for(index_t i = 1; i < m_nrows; ++i)
    for(index_t j = 1; j < m_ncols; ++j) {
      const index_t k = i * m_ncols + j;
      if(m_water[k] != 0) {
        index_t k2 = 0;

        for(int c = 0; c < 4; ++c) {
          switch(c) {
            case 0:
              k2 = (i - 1) * m_ncols + j;
              break;
            case 1:
              k2 = i * m_ncols + (j - 1);
              break;
            case 2:
              k2 = (i + 1 ) * m_ncols + j;
              break;
            case 3:
              k2 = i * m_ncols + ( j + 1);
              break;
          }

          const float v = m_dtm[k] + m_water[k];
          const float v2 = m_dtm[k2] + m_water[k2];

          if(v > v2) {
            const float e = std::min(m_water[k], v - v2);

            m_water[k] -= e;
            m_water[k2] += e;
          }
      }
    }
  }

  fill();
  sendWater();
}

void Flood::fill()
{
  foreach(int k, m_sources)
     m_water[k] += 1;
}

void Flood::sendWater() const
{
  const size_t size = m_nrows * m_ncols * sizeof(float);

  flowvr::MessageWrite waterMsg;

  waterMsg.data = m_flowvr->module()->alloc(size);
  memcpy(waterMsg.data.writeAccess(), m_water, size);

  m_flowvr->module()->put(m_flowvr->waterOut(), waterMsg);
}
