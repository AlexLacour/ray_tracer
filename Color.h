#ifndef __COLOR_H
#define __COLOR_H

class Color
{
    public:
        float r;
        float g;
        float b;
        float a;

        Color(float r_p=0.0, float g_p=0.0, float b_p=0.0, float a_p=1.0);
        ~Color(){}

        Color cap();

        Color operator * (const float k);
        Color operator * (const Color c);
        Color operator + (const Color c);
        Color operator = (const Color c);
        Color operator *= (const Color c);
        Color operator += (const Color c);
        Color operator *= (const float k);
};

#endif
