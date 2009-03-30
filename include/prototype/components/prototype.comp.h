#include <flowvr/app/core/component.h>

using namespace flowvr::app;

namespace prototype
{

class prototype: public Composite
{
public:
  prototype(const std::string &id);

  virtual Component * create() const;
  virtual void execute();
};

inline prototype::prototype(const std::string &id):
  Composite(id, "prototype")
{
}

inline Component * prototype::create() const
{
  return new prototype(getId());
};

}
