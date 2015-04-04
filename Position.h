#ifndef POSITION_H
#define POSITION_H

#define SIZE_SQUARE_MM 40
#define SIZE_STEP_MM 0.34
#define SIZE_DIAG_STEP_MM 0.95


using namespace std;

class Position
{
	public:
	float x;
	float y;
	int isEM;
	
	Position();
	Position(float a, float b);
    Position(int em_state);
    bool isEMCommand();
};


#endif
