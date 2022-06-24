/*-------------------------------------------------------------------
Author: Aaron Anthony Valoroso
Date: January 30th, 2022
License: None
Email: valoroso99@gmail.com
--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

int getche(void);

int main(int argc, char ** args, char ** envp) {

    int characterNumber = 0;
    struct termios oldattr, newattr;

	while (1) {
		tcgetattr(0, &oldattr);								//Get the terminal setting for standard in.				
		newattr = oldattr;								    //Save the settings to a different terminal variable.
		newattr.c_lflag &= ~( ICANON | ECHO );				//Turn off the echo feature and line editing to still occur.
		tcsetattr(0, TCSANOW, &newattr);					//Set the new settings to the terminal.
		characterNumber = getche();							//Retrieve the character that was typed and send back the ascii value.
		printf("HERE: %d\n", characterNumber);
		tcsetattr(0, TCSANOW, &oldattr);	
    }

    return 0;
}

int getche(void) {
	/*-------------------------------------------------------------------
	Note: This method is to capture the keystrokes of the user and process them
    so that they can be sent back to the main. How this method works is by looping
    through the incoming numbers, some keys have more than one number associated 
    to them. If the key is either an enter key, space, or alphabetic character
    I print and return the number to the main. If it is not one of the previous
    characters then we are looking at an arrow, home, and end key
    that return three numbers. The delete and home key return 4 numbers. So the 
    third number is the most important one that I need and since it falls within
    the alphabetic character values, I multiply the number by 3. This allows
    me to get a new number with no issues. This method was last updated on
    3/3/2018. 
	--------------------------------------------------------------------*/	
	char c;
	int specialCharacterSwitch = 0;
	int characterIterator = 0;
	int savedCharacter = 0;

	while (c = getchar()) {
        // If more than one number hasn't been output from the given keyboard key.
		if (!specialCharacterSwitch) {
            // If the value from the key is any upper / lower case letter, or newline.
			if ((c >= 32 && c <= 126) || c == 10) {
                // Print the key onto the terminal.
				// printf("%c",c);
				return c;
            // If any value from the key is a backspace or tab.
			} else if (c == 9 || c == 127 ) {
				return c;
            // Anything else, more than one number will be outputted. 	
			} else {
				specialCharacterSwitch = 1;
				characterIterator++;
			}
        // If we have found a specail key that returns more than one number.
		} else {
            // Increment the number of numbers that have been outputted since we've already found one.
			characterIterator++;
            // The third number is the descriptor key of what the key that was actually pressed.
			if (characterIterator == 3) {
                // If the key is either the del, insert, home, or end key.
				if (c == 51 || c == 50 || c == 53 || c == 54) {
                    // Save the number output since there is still one more number that will be outputted by the getchar.
					savedCharacter =  c * 3;
				} else {
					return c * 3;
				}
			} else if (characterIterator == 4) {
				return savedCharacter;
			}
		}
	}
	return -1;
}