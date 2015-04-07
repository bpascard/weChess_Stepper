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
   unsigned int nb_step_X;
   unsigned int nb_step_Y;
   unsigned int pas_restant_X;
   unsigned int pas_restant_Y;
   
   Deplacement();
   
   void computeFromPos(Position a, Position b);
};
   
#endif
