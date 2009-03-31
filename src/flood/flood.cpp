#include "flood.h"

Flood::Flood(const QString &filename)
{
  if(!m_flowvr.init()) {
    std::cerr << "Error: cannot initialize FlowVR ports" << std::endl;
    exit(EXIT_FAILURE);
  }

  getDTM(); // lecture du terrain
  readSources(filename); // lecture des sources

  // initialisation des niveaux de l'eau à 0
  m_water = new float[m_nrows * m_ncols];
  for(index_t i = 0; i < m_nrows; ++i)
    for(index_t j = 0; j < m_ncols; ++j) {
      const index_t k = i * m_ncols + j;
      m_water[k] = 0;
    }

  // met les niveaux de l'eau au timeout du timer
  connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
  m_timer.start(100); // lancement de l'itération de mise à jour
}

Flood::~Flood()
{
  delete m_dtm;
  delete m_water;
}

void Flood::getDTM()
{
  // réception du nombre de lignes
  if(m_flowvr.module()->wait()) {
    flowvr::Message nrowsMsg;
    m_flowvr.module()->get(m_flowvr.dtmIn(), nrowsMsg);

    memcpy(&m_nrows, nrowsMsg.data.readAccess(), sizeof(size_t));
  }

  // réception du nombre de colonnes
  if(m_flowvr.module()->wait()) {
    flowvr::Message ncolsMsg;
    m_flowvr.module()->get(m_flowvr.dtmIn(), ncolsMsg);

    memcpy(&m_ncols, ncolsMsg.data.readAccess(), sizeof(size_t));
  }

  // réception du terrain
  if(m_flowvr.module()->wait()) {
    flowvr::Message dtmMsg;
    m_flowvr.module()->get(m_flowvr.dtmIn(), dtmMsg);

    const size_t size = m_nrows * m_ncols;
    m_dtm = new float[size];
    memcpy(m_dtm, dtmMsg.data.readAccess(), size * sizeof(float));
  }
}

void Flood::readSources(const QString &fileName)
{
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    std::cerr << "Warning: error while reading water sources file" << std::endl;

  int x;
  int y;

  QTextStream in(&file);
  while(!in.atEnd()) {
    in >> x;
    in >> y;
    in.skipWhiteSpace();
    m_sources.append(x * m_ncols + y);
  }

  file.close();
}

void Flood::fill()
{
  // augmente l'eau de 1 pour chaque source
  foreach(int k, m_sources)
     m_water[k] += 1;
}

void Flood::sendWater() const
{
  static const size_t size = m_nrows * m_ncols * sizeof(float);

  // envoie des niveaux de l'eau
  flowvr::MessageWrite waterMsg;

  waterMsg.data = m_flowvr.module()->alloc(size);
  memcpy(waterMsg.data.writeAccess(), m_water, size);

  m_flowvr.module()->put(m_flowvr.waterOut(), waterMsg);
}

void Flood::update()
{
  for(index_t i = 0; i < m_nrows; ++i)
    for(index_t j = 0; j < m_ncols; ++j) {
      const index_t k = i * m_ncols + j;
      if(m_water[k] != 0) { // ne fait rien si le niveau d'eau est nul
        index_t k2 = 0;

        for(int c = 0; c < 4; ++c) { // dans les quatre directions
          switch(c) {
            case 0:
              if(i == 0)
                continue;

              k2 = (i - 1) * m_ncols + j;
              break;

            case 1:
              if(j == 0)
                continue;

              k2 = i * m_ncols + (j - 1);
              break;

            case 2:
              if(i == m_nrows - 1)
                continue;

              k2 = (i + 1) * m_ncols + j;
              break;

            case 3:
              if(j == m_ncols - 1)
                continue;

              k2 = i * m_ncols + (j + 1);
              break;
          }

          const float v = m_dtm[k] + m_water[k];
          const float v2 = m_dtm[k2] + m_water[k2];

          if(v > v2) {
            // calcul du trop plein
            const float e = std::min(m_water[k], v - v2);

            m_water[k] -= e;
            m_water[k2] += e;
          }
      }
    }
  }

  fill(); // remplit les sources
  sendWater(); // envoie les niveaux d'eau
}
