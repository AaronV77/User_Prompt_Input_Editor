# User-Prompt-Input-Editor

This program is designed for people to take and implement into their own software application. This software basically grabs user input and allows the user to modify it like while using the Bash shell. There is no tab auto complete, command history, or of the Bash shortcuts. The advantage of this system is that the system will try and grab input from the user from two different locations. If there is no sudo or root access then the getchar function will be used but if you do have access then the system will grab the input from the keyboard input dev file. With getchar you get limited input values from the keyboard but with the input file you have the ability to get every key. 
<br>
<br>
## Prerequisites

### Red Hat: 
- Type: yum install gcc-c++ make

## Compiling:

To compile the program, run make in the parent directory of the repo.

## Running:

To run the program, type make run in the parent directory of the repo.
<br>
<br>
# Author: Aaron A. Valoroso

## Inspiring Quotes

I can't change the direction of the wind, but I can adjust my sails to always reach my destination.
- Jimmy Dean
