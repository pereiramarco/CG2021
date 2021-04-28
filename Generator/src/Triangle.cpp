#include "../include/Triangle.h"
#include "iostream"

Triangle::Triangle(int indexP1G,int indexP2G,int indexP3G) {
    indexP1=indexP1G;
    indexP2=indexP2G;
    indexP3=indexP3G;
}

Triangle::Triangle(std::shared_ptr<Point3D> point11,std::shared_ptr<Point3D> point22,std::shared_ptr<Point3D> point33) {
    indexP1 = point11->index;
    indexP2 = point22->index;
    indexP3 = point33->index;
}