#ifndef LIGHT_H
#define LIGHT_H

class DTM;

class Light
{
public:
  /**
   * Constructeur de lumière
   *
   * @param dtm le terrain
   */
  Light(const DTM *dtm);

private:
  /**
   * Place la lumière
   */
  void set();

private:
  float m_position[4];

  const DTM *m_dtm;
};

#endif
