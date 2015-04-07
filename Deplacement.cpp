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
    nb_step_X=0;
    nb_step_Y=0;
    pas_restant_X=0;
    pas_restant_Y=0;
   };
   
   void Deplacement::computeFromPos(Position a, Position b){
		this->dx=b.x-a.x;
		this->dy=b.y-a.y;
		cout << "origine x/y : " << a.x <<"/"<<a.y << "\narrivée x/y :" << b.x << "/" <<b.y << "\n"; 
		cout << "dx : " << this->dx;
		cout << "\ndy : " << this->dy;
		
    //
    double distance_mm_X = abs(this->dx) * SIZE_SQUARE_MM;
    double distance_mm_Y = abs(this->dy) * SIZE_SQUARE_MM;

    this->pas_restant_X = distance_mm_X / SIZE_STEP_MM;
    this->pas_restant_Y = distance_mm_Y / SIZE_STEP_MM;
    this->nb_step_X = this->pas_restant_X;
    this->nb_step_Y = this->pas_restant_Y;
    /*
		this->distance_mm = (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
		this->distance_mm = sqrtf(distance_mm);
		this->distance_mm = ceil(distance_mm * SIZE_SQUARE_MM);
		if(!dx || !dy) this->nb_step = distance_mm / SIZE_STEP_MM;
		else this->nb_step = distance_mm / SIZE_DIAG_STEP_MM;
    */
		cout << "Distance en mm (X) : " << distance_mm_X << "\n";
    cout << "Distance en mm (Y) : " << distance_mm_Y << "\n";
   };
   
   
