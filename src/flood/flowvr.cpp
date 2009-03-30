#include "flowvr.h"

FlowVR::FlowVR():
  m_waterOut(NULL),
  m_dtmIn(NULL),
  m_module(NULL)
{
}

FlowVR::~FlowVR()
{
  delete m_waterOut;
  delete m_dtmIn;

  if(m_module != NULL)
    m_module->close();

  delete m_module;
}

bool FlowVR::init()
{
  // initialisation des ports FlowVR
  m_waterOut = new flowvr::OutputPort("waterOut");
  m_dtmIn = new flowvr::InputPort("dtmIn");

  std::vector<flowvr::Port *> ports;
  ports.push_back(m_waterOut);
  ports.push_back(m_dtmIn);

  // initialisation du ModuleAPI FlowVR
  m_module = flowvr::initModule(ports);

  return m_module;
}
