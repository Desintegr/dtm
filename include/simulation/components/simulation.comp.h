#include <flowvr/app/core/component.h>

using namespace flowvr::app;

namespace simulation
{

class simulation: public Composite
{
public:
  simulation(const std::string &id);

  virtual Component * create() const;
  virtual void execute();
};

inline simulation::simulation(const std::string &id):
  Composite(id, "simulation")
{
}

inline Component * simulation::create() const
{
  return new simulation(getId());
};

}
