#ifndef DEF_AMBIENTLIGHT
#define DEF_AMBIENTLIGHT

class AmbientLight {
 private :
  float intensity;
  float r;
  float g;
  float b;
 public :
  AmbiantLight (float intensity, float color);
  AmbiantLight (float intensity, float r, float g, float b);
  float getIntensity();
  float getR();
  float getG();
  float getB();
};

#endif
