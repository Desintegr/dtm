#ifndef FLOWVR_H
#define FLOWVR_H

#include <flowvr/module.h>

class FlowVR
{
public:
  /**
   * Constructeur de module FlowVR d'inondation
   */
  FlowVR();

  /**
   * Destructeur de module FlowVR d'inondation
   */
  virtual ~FlowVR();

  /**
   * Retourne le port de sortie waterOut
   *
   * Ce port est utilisé pour envoyer les données de l'inondation
   */
  flowvr::OutputPort * waterOut() const;

  /**
   * Retourne le port d'entrée dtmIn
   *
   * Ce port est utilisé pour recevoir les données du terrain
   */
  flowvr::InputPort * dtmIn() const;

  /**
   * Retourne le ModuleAPI FlowVR
   */
  flowvr::ModuleAPI * module() const;

  /**
   * Initialise les ports FlowVR du module
   * @return vrai si les ports sont initialisés correctement
   */
  bool init();

private:
  flowvr::OutputPort *m_waterOut;
  flowvr::InputPort *m_dtmIn;

  flowvr::ModuleAPI *m_module;
};

inline flowvr::OutputPort * FlowVR::waterOut() const
{
  return m_waterOut;
}

inline flowvr::InputPort * FlowVR::dtmIn() const
{
  return m_dtmIn;
}

inline flowvr::ModuleAPI * FlowVR::module() const
{
  return m_module;
}

#endif
