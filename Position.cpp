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

Position::Position(float a, float b, int em_state){
	x=a;
	y=b;
	isEM=em_state;
}

Position::Position(bool em_state){
    isEM=em_state;
}
