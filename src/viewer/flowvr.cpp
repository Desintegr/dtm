#include "flowvr.h"

FlowVR::FlowVR():
  m_dtmOut(NULL),
  m_waterIn(NULL),
  m_module(NULL)
{
}

FlowVR::~FlowVR()
{
  delete m_dtmOut;
  delete m_waterIn;

  if(m_module != NULL)
    m_module->close();

  delete m_module;
}

bool FlowVR::init()
{
  m_dtmOut = new flowvr::OutputPort("dtmOut");
  m_waterIn = new flowvr::InputPort("waterIn");

  std::vector<flowvr::Port*> ports;
  ports.push_back(m_dtmOut);
  ports.push_back(m_waterIn);

  m_module = flowvr::initModule(ports);

  return m_module;
}
