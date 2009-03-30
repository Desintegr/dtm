#ifndef METAMODULEFLOOD_COMP_H
#define METAMODULEFLOOD_COMP_H

#include "prototype/components/moduleflood.comp.h"

#include <flowvr/app/components/metamoduleflowvr-run-ssh.comp.h>

using namespace flowvr::app;

namespace prototype
{

class MetaModuleFlood: public MetaModuleFlowvrRunSSH<ModuleFlood>
{
public:
  MetaModuleFlood(const std::string &id);

  Component * create() const;
};

inline MetaModuleFlood::MetaModuleFlood(const std::string &id):
  MetaModuleFlowvrRunSSH<ModuleFlood>(id, CmdLine("flood data/64.water"))
{
}

inline Component * MetaModuleFlood::create() const
{
  return new MetaModuleFlood(getId());
}

}

#endif
