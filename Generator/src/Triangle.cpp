#include "../include/Triangle.h"
#include "iostream"

Triangle::Triangle() {
    indexP1=0;
    indexP2=0;
    indexP3=0;
}

Triangle::Triangle(int indexP1G,int indexP2G,int indexP3G) {
    indexP1=indexP1G;
    indexP2=indexP2G;
    indexP3=indexP3G;
}