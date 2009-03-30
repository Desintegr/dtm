#ifndef FLOWVR_H
#define FLOWVR_H

#include <flowvr/module.h>

class FlowVR
{
public:
  FlowVR();
  virtual ~FlowVR();
  bool init();

  flowvr::OutputPort * dtmOut() const;
  flowvr::InputPort * waterIn() const;

  flowvr::ModuleAPI * module() const;

private:
  flowvr::OutputPort *m_dtmOut;
  flowvr::InputPort *m_waterIn;

  flowvr::ModuleAPI *m_module;
};

inline flowvr::OutputPort * FlowVR::dtmOut() const
{
  return m_dtmOut;
}

inline flowvr::InputPort * FlowVR::waterIn() const
{
  return m_waterIn;
}

inline flowvr::ModuleAPI * FlowVR::module() const
{
  return m_module;
}

#endif
