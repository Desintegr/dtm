#ifndef LIGHT_H
#define LIGHT_H

class DTM;

class Light {

  public:
    Light(DTM* dtm);

    void set();

  private:
    float m_position[4];

    DTM* m_dtm;

};

#endif
