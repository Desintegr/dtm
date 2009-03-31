#ifndef CAMERA_H
#define CAMERA_H

#include "point3d.h"

#include <QtCore>

class DTM;

class Camera
{
public:
  /**
   * Constructeur de caméra et initialise la position de la caméra
   */
  Camera(const DTM *dtm);

  /**
   * Déplacement relatif de la souris
   *
   * @param x déplacement relatif horizontal de la souris
   * @param y déplacement relatif vertical de la souris
   */
  void mouseMove(const int x, const int y);

  /**
   * Change l'état d'une touche du clavier
   *
   * @param key touche
   * @param state vrai : touche pressée,
   *              faux : touche relachée
   */
  void keyPress(const int key, const bool state);

  /**
   * Changement de position de la molette
   *
   * @param dir vrai vers le haut
   *            faux vers le bas
   */
  void wheel(const bool dir);

  /**
   * Repositionnement de la caméra
   */
  void look() const;

  /**
   * Déplacement de la caméra
   *
   * @param step étape du déplacement
   */
  void animate(const uint step);

  /**
   * Réinitialisation de l'état des touches du clavier
   */
  void clearKeyStates();

private:
  /**
   * Recalcule les vecteurs de placement de caméra à partir des angles
   */
  void vectorFromAngles();

private:
  static const float PI = 3.1415926535;
  static const float SENSITIVITY = 0.2;
  static const float SPEED = 0.05;
  static const uint BOOST = 10;
  static const uint WHEELTIME = 250;

  const DTM *m_dtm;

  Point3d m_position;
  Point3d m_target;
  Point3d m_forward;
  Point3d m_left;

  float m_phi;
  float m_theta;

  QHash<const int, bool> m_keystates;

  bool m_wheelactive;
  uint m_wheeltime;
  int m_wheeldir;
};

#endif
