#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "Position.h"
using namespace std;

class Deplacement
{

   public:
   float dx;
   float dy;
   int reste;
   int nb_step_X;
   int nb_step_Y;
   int pas_restant_X;
   int pas_restant_Y;
   
   Deplacement();
   
   void computeFromPos(Position a, Position b);
};
   
#endif
