#include "Position.h"

using namespace std;


Position::Position(){
	x=0;
	y=0; 	
	isEM=0;
};

Position::Position(float a, float b){
	x=a;
	y=b;
	isEM=0; 	
};

Position::Position(int em_state){
	isEM=em_state;
}

bool Position::isEMCommand(){
    if(isEM==1 || isEM==-1) return true;
    return false;
}