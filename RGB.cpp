#include <cmath>

#include "RGB.h"

float RGB::GetDistanceTo(const RGB& rhs) const {
    int delX = p[0]-rhs.p[0];
    int delY = p[1]-rhs.p[1];
    int delZ = p[2]-rhs.p[2];
    
    return sqrt(delX*delX+delY*delY+delZ*delZ);
}

void RGB::SetChannel(int ch, unsigned char val){
    p[ch] = val;
}

unsigned char RGB::GetChannel(int ch) const {
    return p[ch];
}