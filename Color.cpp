#include "Color.h"

Color::Color(float r_p, float g_p, float b_p, float a_p){
    r = r_p;
    g = g_p;
    b = b_p;
    a = a_p;
}


Color Color::operator * (const float k){
    return Color(r * k, g * k, b * k);
}


Color Color::operator * (const Color c){
    return Color(r * c.r, g * c.g, b * c.b);
}

Color Color::operator + (const Color c){
    return Color(r + c.r, g + c.g, b + c.b);
}

Color Color::operator = (const Color c){
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;

    return *this;
}

Color Color::operator *= (const Color c){
    r *= c.r;
    g *= c.g;
    b *= c.b;

    return *this;
}

Color Color::operator *= (const float k){
    r *= k;
    g *= k;
    b *= k;

    return *this;
}

Color Color::operator += (const Color c){
    r += c.r;
    g += c.g;
    b += c.b;

    return *this;
}

Color Color::cap(){
    if(r > 1){
        r = 1;
    }
    if(g > 1){
        g = 1;
    }
    if(b > 1){
        b = 1;
    }

    return *this;
}
