
#include <stdlib.h>
#include "Position.h"
#include "Deplacement.h"
#include "wiringPi.h"
#include <vector>
#include <string>
#include <cstring>
#include <iostream>

// wiringPi 0-6 -> GPIO 17,18,21,22,23,24,25

#define STEP_X 0 //BCM_GPIO 17
#define DIR_X 1 //BCM_GPIO 18
#define STEP_Y 3 //BCM_GPIO 22
#define DIR_Y 4 //BCM_GPIO 23
#define SLEEP 2 //
#define EM_PIN 5 
//#define MS1 
//#define MS2 

using namespace std;


vector<Position> position_parser(string cmd)
{
	vector<Position> pos_list;
	char * pch;
	pch=strtok((char*)cmd.c_str()," ");
	float a=0;
	float b=0;
	bool magnetState=0;
	
	while (pch!=NULL)
	{
		a=atof(pch); //to float;
		pch=strtok(NULL," ");
	    b=atof(pch); //to float;

	    if(a == 'x' && b =='x'){
	    	magnetState=1;
	    }
	    else if(a == 'y' && b == 'y'){
	    	magnetState=0;
	    }

	    Position pos(a,b,magnetState);
		pos_list.push_back(pos);
		cout << "Go to " << a << ":" << b << "magnet "<< magnetState << "\n";
		pch=strtok(NULL," ");
	}
	
	return pos_list;
}


void init_step()
{
	//pas
	pinMode(STEP_X, OUTPUT); 
	pinMode(STEP_Y, OUTPUT);  
	//direction
	pinMode(DIR_X, OUTPUT);
	pinMode(DIR_Y, OUTPUT);
	//sleep
	pinMode(SLEEP, OUTPUT);
	
	//electro-magnet
	pinMode(EM_PIN, OUTPUT);
	
	digitalWrite(DIR_X,LOW);
	digitalWrite(DIR_Y,HIGH);
	digitalWrite(SLEEP,HIGH);
	delay(500);
}

void end_step(){
	digitalWrite(SLEEP,LOW);
}

void step(int num_pin)
{
	digitalWrite(num_pin,HIGH);
	delayMicroseconds(2000);
	digitalWrite(num_pin,LOW);
	delayMicroseconds(2000);
}

void set_dir(int num_pin, int d){
	if(d>0) digitalWrite(num_pin,HIGH);
	else if(d<0) digitalWrite(num_pin,LOW);
	cout << "d" << num_pin << ":" << d << "\n";
}

int main(int argc, char **argv)
{
	if( wiringPiSetup()==-1)
	{	exit(1);
	}

	/*
	init_step();
	while(1){
		digitalWrite(EM_PIN,HIGH);
		delay(500);
		digitalWrite(EM_PIN,LOW);
		delay(500);
	}
	*/

	string cmd="";
    if(argc != 2){
        cout << "incorrect no. of arguments" << "\n";
        cmd="0.5 0 0 1 0 0 2 0 0 0 2.5 0 0 0 4 0 0.5 0 0 0";
        exit(1);
    }
	else cmd = argv[1];
	
	init_step();
	


    Position current;
	Position next;
	Deplacement deplacement;
	vector<Position> pos_list;

	pos_list=position_parser(cmd);
	int nb_positions = pos_list.size();
	cout << nb_positions << " positions\n";
	for(int i=0; i<nb_positions; i++){
		next = pos_list.at(i);
		deplacement.computeFromPos(current,next);
		
		set_dir(DIR_X,deplacement.dx);
		set_dir(DIR_Y,deplacement.dy);
		delayMicroseconds(1000);
		cout << deplacement.nb_step << " pas\n";
		for(int x=0; x<deplacement.nb_step;x++){
			if(deplacement.dx){
				step(STEP_X);
				//cout << "step!\n";
				
			}
			if(deplacement.dy){
				step(STEP_Y);
			}
			
		}

		cout << "---------------------\n";
		if(next.isEM==1) digitalWrite(EM_PIN,HIGH);
			else 
		current = next; digitalWrite(EM_PIN,LOW);
		delay(500);

	}
	end_step();
	return 0;
}


