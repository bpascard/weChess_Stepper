#!/bin/bash

cd /home/pi/Desktop/wechess/wechess_stepper/

g++ -Wall -o ./move ./move.cpp Position.cpp Deplacement.cpp -lwiringPi

while [ 1 ]
do
a=$RANDOM
b=$RANDOM
let "a %= 8"
let "b %= 8"
let "a += 2"
let "b += 2"
sudo ./move "$a $b"
done
