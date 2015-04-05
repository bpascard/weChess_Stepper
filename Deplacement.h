#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "Position.h"
using namespace std;

class Deplacement
{

   public:
   float dx;
   float dy;
   int nb_step;
   int reste;
   double distance_mm;
   
   Deplacement();
   
   Deplacement(float a, float b, int n);
   
   void computeFromPos(Position a, Position b);
};
   
#endif
