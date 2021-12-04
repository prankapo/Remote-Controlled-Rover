# Remote Controlled Rover 
This is a rover I designed as a part of my final year Minor Project. Both hardware and software, except for the modules and boards available in the market, have been designed completely by me. Over here, I am going to describe this project in brief. 

## Structure of the rover 
The base of the rover is made using PVC pipes having a diameter of 2.22 cm. The diagram for the same is shown below: 
![Rough drawing of base of the rover](images/img1.png) 
On top this structure is fixed a 22.5cm x 12.5cm rectangular piece of hardened cardboard, from which four screws projecting upwards. This allows us to build various levels on top of this rover. Each level can contain its own specialised hardware. For the sake of keeping the centre of gravity of the rover as low as possible for stability reasons, the power source is kept on the lowest level. 

## Description of the software 
The software used in this project can be divided into two parts. 
1. Command interpreter (rpi/main.c): This is an interactive single command interpreter. It majorly consists of the code for a parser. It is written in C. This interpreter, along with shell scripts or python scripts executes various commands which has been entered by the user. For example, the script rpi/interface.py reads the strings that has been passed to it by the parser, sends them serially to Arduino Nano at /dev/ttyUSB0 where they are executed by the controller. The syntax of these commands is somewhat similar to the syntax of assembly instructions.
2. Source code for microcontroller (ardcon/ardcon.ino): Servo motors and motor driver are not controlled by the on-board computer (RPi 3B+) directly. The commands to control the motion of the rover via these motors is sent serially by RPi to Arduino Nano. The code running in Nano then executes these instructions and controls the motors accordingly. ardcon.ino contains string to float function which can translate a string to a floating point value of upto 2 decimal places.
