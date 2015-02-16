#!/bin/bash
g++ -Wall -o ./move ./move.cpp Position.cpp Deplacement.cpp -lwiringPi
while [ 1 ]
do
sudo ./move
done