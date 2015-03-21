
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>


using namespace std;


int main(int argc, char **argv)
{
    string cmd="(empty)";
    if(argc != 2){
        cout << "incorrect no. of arguments" << "\n";
        cmd="0.5 0 0 1 0 0 2 0 0 0 2.5 0 0 0 4 0 0.5 0 0 0";
        exit(1);
    }
    else cmd = argv[1];
    
    cout << "Running cmd : " << cmd << "\n";
    
    char * pch;
    pch=strtok((char*)cmd.c_str()," ");
    float a=0;
    float b=0;
    
    while (pch!=NULL)
    {
        a=atof(pch); //to float;
        pch=strtok(NULL," ");
        b=atof(pch); //to float;

        if(pch[0] == 'x') cout << "Magnet ON" << "\n";
        else if(pch[0] == 'y') cout << "Magnet OFF" << "\n";
        else cout << "Going to : " << a << " - " << b << "\n";

        pch=strtok(NULL," ");
    }


    return 0;
}


