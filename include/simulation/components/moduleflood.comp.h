#ifndef MODULEFLOOD_COMP_H
#define MODULEFLOOD_COMP_H

#include <flowvr/app/components/module.comp.h>

using namespace flowvr::app;

namespace simulation
{

class ModuleFlood: public Module
{
public:
  ModuleFlood(const std::string &id);

  virtual Component * create() const;
};

inline ModuleFlood::ModuleFlood(const std::string &id):
  Module(id)
{
  setInfo("Flood simulation");
  addPort("dtmIn", INPUT);
  addPort("waterOut", OUTPUT);
}

inline Component * ModuleFlood::create() const
{
  return new ModuleFlood(getId());
}

}

#endif
