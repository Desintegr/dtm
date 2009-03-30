#ifndef FLOWVR_H
#define FLOWVR_H

#include <flowvr/module.h>

class FlowVR
{
public:
  /**
   * Constructeur du module FlowVR de visualisation
   */
  FlowVR();

  /**
   * Destructeur du module FlowVR de visualisation
   */
  virtual ~FlowVR();

  /**
   * Retourne le port de sortie dtmOut
   *
   * Ce port est utilisé pour envoyer les données du terrain
   */
  flowvr::OutputPort * dtmOut() const;

  /**
   * Retourne le port d'entrée waterIn
   *
   * Ce port est utilisé pour recevoir les données de l'inondation
   */
  flowvr::InputPort * waterIn() const;

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
