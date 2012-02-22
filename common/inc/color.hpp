#ifndef DEF_COLOR
#define DEF_COLOR

class Color {
private :
    float r;
    float g;
    float b;

public :
    Color(float grey =1);
    Color(float r, float g, float b);
    float getR();
    float getG();
    float getB();
    Color merge(Color color);
};

#endif
