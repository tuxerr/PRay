#ifndef DEF_COLOR
#define DEF_COLOR

class Color {
 private :
  float r;
  float g;
  float b;
 public :
  Color(float grey);
  Color(float r, float g, float b);
  float getR();
  float getG();
  float getB();
};

#endif
