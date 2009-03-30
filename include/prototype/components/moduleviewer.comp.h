#ifndef MODULEVIEWER_COMP_H
#define MODULEVIEWER_COMP_H

#include <flowvr/app/components/module.comp.h>

using namespace flowvr::app;

namespace prototype
{

class ModuleViewer: public Module
{
public:
  ModuleViewer(const std::string &id);

  virtual Component * create() const;
};

inline ModuleViewer::ModuleViewer(const std::string &id_):
  Module(id_)
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
