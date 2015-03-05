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
	bool isEM;
	
	Position();
	Position(float a, float b);
	Position(float a, float b, bool em_state);
};


#endif