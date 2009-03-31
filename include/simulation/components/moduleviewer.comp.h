#ifndef MODULEVIEWER_COMP_H
#define MODULEVIEWER_COMP_H

#include <flowvr/app/components/module.comp.h>

using namespace flowvr::app;

namespace simulation
{

class ModuleViewer: public Module
{
public:
  ModuleViewer(const std::string &id);

  virtual Component * create() const;
};

inline ModuleViewer::ModuleViewer(const std::string &id):
  Module(id)
{
  setInfo("OpenGL viewer");

  addPort("waterIn", INPUT);
  addPort("dtmOut", OUTPUT);
}

inline Component * ModuleViewer::create() const
{
  return new ModuleViewer(getId());
}

}

#endif
