#ifndef METAMODULEVIEWER_COMP_H
#define METAMODULEVIEWER_COMP_H

#include "simulation/components/moduleviewer.comp.h"

#include <flowvr/app/components/metamoduleflowvr-run-ssh.comp.h>

using namespace flowvr::app;

namespace simulation
{

class MetaModuleViewer: public MetaModuleFlowvrRunSSH<ModuleViewer>
{
public:
  MetaModuleViewer(const std::string &id);

  virtual Component * create() const;
};

inline MetaModuleViewer::MetaModuleViewer(const std::string &id):
  MetaModuleFlowvrRunSSH<ModuleViewer>(id, CmdLine("viewer data/512.grd"))
{
  getRun()->openDisplay(":0");
}

inline Component * MetaModuleViewer::create() const
{
  return new MetaModuleViewer(getId());
}

}

#endif
