#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
git clone git://git.drogon.net/wiringPi $DIR
g++ -Wall -o ./move ./move.cpp Position.cpp Deplacement.cpp -lwiringPi
while [ 1 ]
do
sudo ./move
done
