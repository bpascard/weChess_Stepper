#include <stdlib.h>
#include <iostream>
#include "Deplacement.h"
#include "Position.h"
#include <math.h>
using namespace std;


   
   Deplacement::Deplacement()
   {
    dx=0;
    dy=0;
    nb_step=0;
    distance_mm=0;
    reste=0;
   };
   
   Deplacement::Deplacement(float a, float b, int n)
   {
    dx=a;
    dy=b;
    nb_step=n;
    reste=n;
    distance_mm=sqrtf(dx*dx+dy*dy);
   };
   
   void Deplacement::computeFromPos(Position a, Position b){
		this->dx=b.x-a.x;
		this->dy=b.y-a.y;
		cout << "origine x/y : " << a.x <<"/"<<a.y << "\narrivée x/y :" << b.x << "/" <<b.y << "\n"; 
		
		
		this->distance_mm = (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
		this->distance_mm = sqrtf(distance_mm);
		this->distance_mm = ceil(distance_mm * SIZE_SQUARE_MM);
		if(!dx || !dy) this->nb_step = distance_mm / SIZE_STEP_MM;
		else this->nb_step = distance_mm / SIZE_DIAG_STEP_MM;
		cout << "Distance en mm : " << this->distance_mm << "\n";
   };
   
   
