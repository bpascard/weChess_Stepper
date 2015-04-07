
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
	int magnetState=0;
	Position pos;
	
	while (pch!=NULL)
	{
	    a=atof(pch); //to float;
	    pch=strtok(NULL," ");
	    b=atof(pch); //to float;

	    if(pch[0] =='x'){
	    	magnetState=1;
	    	pos = Position(magnetState);
	    }
	    else if(pch[0] == 'y'){
	    	magnetState=-1;
	    	pos = Position(magnetState);
	    }
	    else{
	    	pos = Position(a,b,magnetState);
	    	
	    }
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
	
	//wake up motors
	digitalWrite(SLEEP,HIGH);
	delay(500);
}

void end_step(){
	digitalWrite(SLEEP,LOW);
}

void step(int num_pin)
{
	digitalWrite(num_pin,LOW);
	delayMicroseconds(2000);
	digitalWrite(num_pin,HIGH);
	delayMicroseconds(2000);
}

void set_dir(int num_pin, float d){
	if(d>0) digitalWrite(num_pin,HIGH);
	else if(d<0) digitalWrite(num_pin,LOW);
	cout << "d" << num_pin << ":" << d << "\n";
}

int main(int argc, char **argv)
{
	if( wiringPiSetup()==-1)
		{	exit(1);
		}


/*	init_step();
    int k=0;
	while(k!=100){
        step(STEP_Y);
        k++;
	}
    end_step();
    return 0;*/
/*init_step();
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
	


	Position current(0.5,0.5);
	Position next;
	Deplacement deplacement;
	vector<Position> pos_list;

	pos_list=position_parser(cmd);
	int nb_positions = pos_list.size();
	cout << nb_positions << " positions\n";
	for(int i=0; i<nb_positions; i++){
		next = pos_list.at(i);
		
		//Commande EM
		if(next.isEMCommand()){
			if(next.isEM==1){
				digitalWrite(EM_PIN,HIGH);
				cout << "EM ON!\n";
			}
			else{
				digitalWrite(EM_PIN,LOW);
				cout << "EM OFF!\n";
			}
			delay(1000);
		}
		//Commande moteurs
		else{
			deplacement.computeFromPos(current,next);

			set_dir(DIR_X,-deplacement.dx);
			set_dir(DIR_Y,deplacement.dy);
			//delayMicroseconds(1000);
			cout << deplacement.nb_step_X << " pas (X)\n";
			cout << deplacement.nb_step_Y << " pas (Y)\n";
			while(deplacement.pas_restant_X>0 || deplacement.pas_restant_Y>0){
				if(deplacement.pas_restant_X>0){
					step(STEP_X);
					deplacement.pas_restant_X--;
					//cout << deplacement.pas_restant_X << " pas restant (X)\n";

				}
				if(deplacement.pas_restant_Y>0){
					step(STEP_Y);
					deplacement.pas_restant_Y--;
					//cout << deplacement.pas_restant_Y << " pas restant (Y)\n";
				}

			}

			cout << "---------------------\n";

			current = next;
		}
		
		delay(500);

	}
	end_step();
	return 0;
}


