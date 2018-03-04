/*-------------------------------------------------------------------
Author: Aaron Anthony Valoroso
Date: March 3rd, 2018
License: BSD-3-Clause
Email: valoroso99@gmail.com
--------------------------------------------------------------------*/
#include <termios.h>
#include <vector>
#include "Utilities.h"

std::string autoComplete(std::string theCommands, bool mySwitch);
int getche(void);

int main (int argc, char * argv[], char *envp[]) {					
	/*-------------------------------------------------------------------------------------------------------
	Note: This program does all the necessary functionality to be able to update the terminal screen and the
    underlying variables to edit incoming input for an application. How this code works, is by first displaying
    the basic prompt, then getting the terminal settings, copying them, and then shutting off the echo feature
    for when I type. I do this so that I don't get two letters when I type, and allow the program to read my
    input. After that a method called getche() will capture my keystroke. Please read the method note, for how
    it works, but that method will return a number of what keyboard button I pressed. I then run that number 
    through a switch looking to see what key was pressed. I am not going to get specific on what the switch does
    because there are already alot of comments made within it, but I look for the enter, tab, delete, backspace,
    home, end, insert, and then the four arrow keys. Everything else is sent to the default, but now is good to
    mention that there are two main variables within the main. They are theCommands and LeftAndRightIterator, the
    first one is a string for holding everything that the user types, and the other is for keeping track of where
    the cursor is in the input. Why I have these two variables is because if I edit the string variable the terminal
    screen will not update as well. I have to update it manually to stay up-to-date with the string variable.
    You will see what I mean later on. In the default section there are two options, if the cursor is at the end of the 
    input then I can just add the new characters to the screen, else if the character is in the middle of the input.
    Now if the cursor is in the middle of the input, I basically have to make sure that where the character is being
    inserted in the input moves all the characters on the screen over one. This give room for the new character,
    but I also have to update the string variable. Please read the comments on the side of the code because they 
    give a better description of what I am doing at each point! This method was last updated on 3/3/2018.
	---------------------------------------------------------------------------------------------------------*/
	char path[256];
	int characterNumber = 0;																					//Used to store the ascii value of the character from the keyboard.
	int LeftAndRightIterator = 1;																				//Used to keep track of where the cursor is on the screen.
	int UpAndDownIterator = 0;																					//Used to keep track of where the system is in the commands vector.
	int size = 0;
	bool tabPressed = false;
	bool quoteFound = false;																					//Used to stop store characters in the "theCommands" variable.
	std::string theCommands = "";																				//Used to store the whole incoming input from the user besides if there is a quote.
    std::string input = "";
    std::string lastItem = "";
    std::string storage = "";
    std::vector<std::string> incomingCommands;																	//Used to store the incoming commands from the user and will be checked.
	struct termios oldattr, newattr;																			//Setup terminal variables.
	
    std::cout << "Basic Prompt: ";															

	while (1) {																									//Loop for indeffinately.
		tcgetattr(STDIN_FILENO, &oldattr);																		//Get the terminal setting for standard in.				
		newattr = oldattr;																						//Save the settings to a different terminal variable.
		newattr.c_lflag &= ~( ICANON | ECHO );																	//Turn off the echo feature and line editing to still occur.
		tcsetattr(STDIN_FILENO, TCSANOW, &newattr);																//Set the new settings to the terminal.
		characterNumber = getche();																				//Retrieve the character that was typed and send back the ascii value.
		tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);																//Set the terminal to the old settings.
		switch(characterNumber) {
            case 9:																			//When a tab was pressed.
                // **** I commented this section out like I mentioned in the README.md file, because
                // I felt like this would not be needed if you were not building a shell. If feel like
                // you could use it just uncomment the code and give it a go!                
                
                // if (tabPressed == false) {
                //     theCommands = autoComplete(theCommands, false);
                //     tabPressed = true;
                //     LeftAndRightIterator = theCommands.size() + 1;
                // } else {
                //     autoComplete(theCommands, true);
                //     std::cout << "Basic Prompt: ";
                // }
                break;
            case 10:																	    //When an enter key was pressed.
                if (theCommands != "") {																		//Make sure that the char pointer is not empty / NULL.
                    //  **** When entered is hit, is where you can add the hook up to your application.
                    // When the user hits the enter key, it will send the string to your application,
                    // and then your application can do whatever it wants with the out going string.
                    std::cout << "This is what the end result is: " << theCommands << std::endl;
                    incomingCommands.push_back(theCommands);													//Store the old commands in this vector.				
                    tabPressed = false;
                }
                std::cout << "Basic Prompt: ";
                UpAndDownIterator = incomingCommands.size();													//Set the up and down iterator to zero.
                LeftAndRightIterator = 1;																		//Reset the iterator for back and forth to zero.
                theCommands = "";																				//Reset the variable.
                break;
            case 127:																        //Backspace character.
                if (LeftAndRightIterator > 1) {																	//Delete the characters in the pointer, but no further than what was typed.
                    tabPressed = false;
                    printf("\b \b");																			//Delete thee character before the cursor on the screen.
                    int endOfString = (theCommands.size()+1);													//Store thee size of the original string with one extra character for the iterator.
                    theCommands.erase(theCommands.begin()+(LeftAndRightIterator - 2));							//Erase the character from the string.
                    if (endOfString != LeftAndRightIterator) {													//If the cursor is not at the end of the string.
                        LeftAndRightIterator--;																	//Subtract from the left and right iterator because our cursor moves over one when we delete the character.
                        int i = 0;																				//With so many for loops just create one iterator variable.
                        int shift = (endOfString - LeftAndRightIterator);										//Get our shift which is just the different from the back of the string to where the cursor is at on the string.
                        for (i = 0; i < shift; ++i) {															//Move the cursor to the end of the string, so that we can delete everything on the screen.
                            printf ("\033[C");																	//Function call to move the cursor on the screen to the right.		
                            LeftAndRightIterator++;																//Keep track of moving our iterator.
                        }
                        for (i = 0; i < (theCommands.size() + 1); ++i) {										//Since our string is one less character it still has a space on the terminal display, so we can delete everything on the terminal screen.
                            printf("\b \b");																	//Delete the characters on the screen.
                            LeftAndRightIterator--;																//Move our iterator with the loop.
                        }
                        std::cout << theCommands;																//Reprint our new string on the screen. This will push our cursor to the end of the string.
                        LeftAndRightIterator = (theCommands.size() + 1);										//So lets save where our new iterator lies on the screen.

                        for (i = 0; i < (shift - 1); ++i) {														//Loop to move our cursor on the letter we were on originally.
                            printf("\033[D");																	//Move the cursor to the left.
                            LeftAndRightIterator--;																//Move our iterator with the loop.
                        }
                    } else {
                        LeftAndRightIterator--;																	//Since we are at the end our string we can just delete the character both on the screen and string.
                    }											
                }
                break;
            case 150:																        //Insert Key
                // Not implemented.
                break;
            case 153:																        //Delete key.
				size = theCommands.size() - (LeftAndRightIterator - 1);
				for (int i = 0; i < size; ++i) {																//Move the cursor to the end of the string, so that we can delete everything on the screen.
					printf ("\033[C");																			//Function call to move the cursor on the screen to the right.		
					LeftAndRightIterator++;																		//Keep track of moving our iterator.
				}
				for (int d = 0; d < theCommands.size(); d++) {													//Loop through the number of characters currently being typed.
					printf("\b \b");																			//Deletes a character on the current line and moves the pointer back one.
					LeftAndRightIterator--;																		//Decrement the left and right iterator.
				}
				theCommands = "";																				//Reset the input stream.
                break;
            case 195:															        	//Up arrow key	
                // **** I commented this section out like I mentioned in the README.md file, because
                // I felt like this would not be needed if you were not building a shell. If feel like
                // you could use it just uncomment the code and give it a go!
                
                // UpAndDownIterator--;																			//Decrement the iterator.
                // if (UpAndDownIterator >= 0 && incomingCommands.size() != 0) {									//Check to make sure the iterator is above  0.
                //     tabPressed = false;
                //     printf("%c[2K", 27);																		//Clear the current terminal line.
                //     std::cout << "\r";																		    //This carriage return will keep the prompt from shifting over.
                //     std::cout << "Basic Prompt: ";
                //     std::cout  << incomingCommands[UpAndDownIterator]; 											//Reset the output and pring the colored prompt and print out the previous command.
                //     theCommands = incomingCommands[UpAndDownIterator];											//Reset the input string with the previous command.
                //     LeftAndRightIterator = theCommands.size() + 1;												//Reset the left and right iterator so that the cursor doesn't move past the commmand.
                // } else {
                //     UpAndDownIterator = 0;																		//Reset the iterator to zero.
                // }
                break;
            case 198:																        //Down arrow key
                // **** I commented this section out like I mentioned in the README.md file, because
                // I felt like this would not be needed if you were not building a shell. If feel like
                // you could use it just uncomment the code and give it a go!
               
                // UpAndDownIterator++;																			//Increment the iterator.
                // if (UpAndDownIterator < incomingCommands.size() && incomingCommands.size() != 0) {				//If the up and down iterator is less than the size of the vector minus 1, and if the vector size is not equal to zero.
                //     tabPressed = false;
                //     printf("%c[2K", 27);																		//Clear the printed terminal line.
                //     std::cout << "\r";																			//This carriage return will keep the prompt from shifting over.
                //     std::cout << "Basic Prompt: ";
                //     std::cout  << incomingCommands[UpAndDownIterator]; 											//Reset the output and pring the colored prompt and print out the previous command.
                //     theCommands = incomingCommands[UpAndDownIterator];											//Reset the input string with the previous command.
                //     LeftAndRightIterator = theCommands.size() + 1;												//Reset the left and right iterator so that the cursor doesn't move past the commmand.
                // } else {																						//If we hit the very top of the vector then we want to clear the termina input just like bash.
                //     if (theCommands.size() > 0) {
                //         for (int i = LeftAndRightIterator; i < (theCommands.size()+1); ++i)	{
                //             printf("\033[C"); 
                //             LeftAndRightIterator++;
                //         }
                //         for (int d = 0; d < theCommands.size(); d++) {											//Loop through the number of characters currently being typed.
                //             printf("\b \b");																	//Deletes a character on the current line and moves the string back one.
                //             LeftAndRightIterator--;																//Decrement the left and right iterator.
                //         }
                //         theCommands = "";	
                //     }																							//Reset the input string.
                //     UpAndDownIterator = incomingCommands.size();												//Reset the iterator to the size of the vector.
                // } 
                break;
            case 201:																        //Right arrow key.
                if (LeftAndRightIterator < (theCommands.size()+1)) {											//If the iterator is not going past the current string.	
                    printf("\033[C"); 																			//Move the cursor to the right by one.	
                    LeftAndRightIterator++;																		//Increment the iterator.
                }	
                break;
            case 204:																        //Left arrow key.
                if (LeftAndRightIterator > 1) {																	//If the iterator is less than or equal to the vector size and is greater than zero.												
                    printf("\033[D");																			//Move the cursor to the left by one.
                    LeftAndRightIterator--;																		//Decrment the iterator.
                }	 
                break;
            case 210:																        //End key.
                size = theCommands.size() - (LeftAndRightIterator - 1);                                         //Get the number of times we have to move the cursor to the right.
                if (size != 0) {                                                                                //If the cursor is not already at the end of the string.
                    for (int i = 0; i < size; i++) {                                                            //Move the cursor x many times over.
                        printf("\033[C");
                        LeftAndRightIterator++;
                    }
                }
                break;
            case 216:															        	//Home key.
                size = (LeftAndRightIterator - 1);
                for (int i = 0; i < size; i++) {
                    printf("\033[D");
                    LeftAndRightIterator--;
                }	
                break;
            default:
                if (characterNumber < 195 || characterNumber > 204) {
                    tabPressed = false;
                    if ((theCommands.size()+1) != LeftAndRightIterator) {										//If the cursor is not at the end of the string.
                        std::string str = utili::convert_number_to_letter(characterNumber);						//Convert the character number into an actual letter.															
                        theCommands.insert((LeftAndRightIterator - 1), str);									//Insert the letter into our string.
                        int shift = (theCommands.size() - LeftAndRightIterator);								//Get our shift which is just the different from the back of the string to where the cursor is at on the string.
                        int i = 0;																				//Since there are more than one for loop, lets just create one variable.
                        for (i = 0; i < shift; ++i) {															//Loop to move the cursor to the end of the string.
                            printf("\033[C");																	//Move the cursor to the left.
                            LeftAndRightIterator--;																//Move the iterator to the right.
                        }	
                        for (i = 0; i < theCommands.size(); ++i) {												//Loop to delete the whole command off the screen.
                            printf("\b \b");																	//Delete a character off the screen.
                            LeftAndRightIterator--;
                        }
                        std::cout << theCommands;																//Print the updated string. This will put the cursor at the end of the string.
                        LeftAndRightIterator = (theCommands.size()+1);											//Set our iterator to the end of the string.
                        
                        for (i = 0; i < shift; ++i) {															//Loop to move the cursor to where we left off on the string.
                            printf("\033[D");																	//Move the cursor to the left.
                            LeftAndRightIterator--;																//Move our iterator in.
                        }
                    } else {
                        theCommands += characterNumber;															//Add the character to the input string.
                        LeftAndRightIterator++;																	//Move the iterator with the incoming character.
                    }
                }
                break;
        }

		if (incomingCommands.size() > 100)																		//If there are more than 100 elements in the vector.
			incomingCommands.erase(incomingCommands.begin()+50);												//Delete the first half of the vector.

		characterNumber = 0;																					//Reset the character number.
	}

	return 0;
}

std::string autoComplete(std::string incomingTypedString, bool mySwitch) {
    /*-------------------------------------------------------------------
    Note: This method will auto complete the path that the user is trying to
    complete without knowing how to correctly spell the file or path. How this
    method works is by taking the incoming string and getting the last item / 
    token from it. From there I check to see if the path is going to be an absolute
    or relative path. Then I loop through the string character by character, and
    build the path staring with the first character. I want to make sure that 
    if the path is absolute that everything before what the user is trying to 
    auto complete is correct, and that I can get to the directory that they 
    want. If the user has typed more than one backslash together or if the path
    they they are trying to get too, does not exist then I print an error. If 
    there were no errors I get the contents of the directory that they are trying
    to get the file or folder from. Once I have the directory contents, I loop
    through the contents taking that last couple of characters that the user was 
    trying to auto complete with and check the same number of characters against
    the contents. If I find any matches I save them. Next, if the incoming switch
    is false, the user has only pressed the tab key once, else they pressed it 
    twice and are looking for the contents of the directory or matches they are 
    trying to auto complete with. If there are no items that were similar to 
    what the user was trying to auto complete to then we return. If there was one
    item that matched what the user was trying, then I print the different characters
    that don't match, and if what the user was trying to auto complete is a folder
    then add a back slash to it else return the new string. If there is more than one
    saved item item, then we have to auto complete to where ever the saved items
    differ from each other. After that we print the characters, and return the new
    string. Lastly, if the user has already pressed the tab once and wants to display
    the contents of the directory or what they are trying to auto complete then that
    happens last. This is done by just looping through the contents of the directory,
    or saved items from within the algorithm. This method was last updated on 3/3/2018.
	--------------------------------------------------------------------*/
    // const int MAX_SIZE = 256;
	// char path[MAX_SIZE];
    // bool warning_flag = false;
    // bool backslash_found_flag = false;
    // bool absolute_path_flag = false;
    // int iteration_counter = 0;
    // std::string token = "";
    // std::string storage = "";
    // std::string last_item_token = "";
    // std::string constructed_test_path = "";
    // std::string constructed_saved_path = "";
    // std::string temp_input = "";
    // std::string comparisonCharacters = "";
    // std::vector<std::string> directory_contents;
    // std::vector<std::string> saved_items;


    // std::istringstream iss (incomingTypedString);
    // while (iss >> temp_input) {
    //     if (iss.eof()) {
    //         last_item_token = temp_input;
    //     } else {
    //         storage += temp_input;
    //         storage += " ";
    //     }	
    // }

	// if (last_item_token[0] == '/')
	// 	absolute_path_flag = true;

    // for (int a = 0; a < last_item_token.size(); a++) {
    //     if (last_item_token[a] == '/') {
    //         if (a == 0)
    //             constructed_test_path += last_item_token[a];

    //         if (backslash_found_flag == false) {
    //             backslash_found_flag = true;
    //         } else {
    //             std::cout <<  std::endl << "\t\t The path is inccorect." << std::endl;
    //             home.PromptDisplay();
    //             std::cout << incomingTypedString;
    //             return incomingTypedString;
    //         }

    //         constructed_test_path += token;

    //         if (utili::isDirectory(constructed_test_path) == true) {
    //             if (token.size() > 0) {
    //                 constructed_saved_path += token;
    //                 constructed_saved_path += "/";
    //                 constructed_test_path += "/";
    //             } else {
    //                 constructed_saved_path += "/";
    //             }
    //             token = "";
    //         } else {
    //             if (warning_flag == false) {
    //                 warning_flag = true;
    //             } else {
    //                 std::cout <<  std::endl << "\t\t The path is inccorect." << std::endl;
    //                 std::cout << "Basic Prompt: ";
    //                 std::cout << incomingTypedString;
    //                 return incomingTypedString;
    //             }
    //         }
    //     } else {
    //         if (warning_flag == true) {
    //             std::cout <<  std::endl << "\t\t The path is inccorect." << std::endl;
    //             std::cout << "Basic Prompt: ";
    //             std::cout << incomingTypedString;
    //             return incomingTypedString;
    //         }
    //         backslash_found_flag = false;
    //         token += last_item_token[a];
    //     }

    // }

    // if (absolute_path_flag == false) {
    //     temp_input = getcwd(path, MAX_SIZE);
    //     temp_input += '/';
    //     temp_input += constructed_saved_path;
    //     constructed_saved_path = temp_input;
    // }

    // directory_contents = utili::directory_contents(constructed_saved_path, directory_contents);
    // if (directory_contents.size() > 0) {
    //     for (int b = 0; b < directory_contents.size(); b++) {
    //         temp_input = directory_contents[b];
    //         for (int c = 0; c < token.size(); c++)
    //             comparisonCharacters += temp_input[c];

    //         if (token == comparisonCharacters) {
    //             saved_items.push_back(directory_contents[b]);
    //         }
    //         comparisonCharacters = "";
    //     }
    // }

    // if (mySwitch == false) {
    // 	if (saved_items.size() == 0) {
    //         return incomingTypedString;
    //     } else if (saved_items.size() == 1) {
	// 		for (int d = 0; d < saved_items[0].size(); d++) {
	// 			if (token[d] != saved_items[0][d])
    //                 std::cout << saved_items[0][d];
	// 		}

    //         constructed_saved_path += saved_items[0];

    //         if (utili::isDirectory(constructed_saved_path) == true) {
    //             std::cout << "/";
    //             return storage + constructed_saved_path + "/";	
    //         } else {
    //             return storage + constructed_saved_path;
    //         }
	// 	} else if (saved_items.size() > 0) {
	// 		std::string exampleSearch = saved_items[0];
	// 		std::string foundSearch = "";
	// 		bool searchTest = false;

	// 		for (int e = 0; e < saved_items[0].size(); e++) {
	// 			for (int f = 0; f < saved_items.size(); f++) {
	// 				if (saved_items[f][e] != exampleSearch[e]) {
	// 					searchTest = true;
	// 					break;
	// 				}
	// 			}
	// 			if (searchTest == true) {
	// 				break;
	// 			} else {
	// 				if (e <= incomingTypedString.size()) {
	// 					if (exampleSearch[e] != token[e]) {
	// 						foundSearch += exampleSearch[e];
    //                     }
	// 				} else {
	// 					foundSearch += exampleSearch[e];
	// 				}
	// 			}
	// 		}
	// 		std::cout << foundSearch;
	// 		return incomingTypedString + foundSearch;
	// 	}
    // } else {
	// 	int temp_size = 0;
    //     bool nothing_found = false;
    //     if (saved_items.size() > 0) 
    //         temp_size = saved_items.size();
    //     else if (directory_contents.size() > 0) 
    //         temp_size = directory_contents.size();
    //     else   
    //         nothing_found = true;

    //     if (nothing_found == false) {
    //         std::cout << std::endl;
    //         for (int g = 0; g < temp_size; g++) {
    //             if ((g % 4) == 0)
    //                 std::cout << std::endl;

    //             if (saved_items.size() > 0) 
    //                 std::cout << std::setw(40) << std::left <<  saved_items[g];
    //             else   
    //                 std::cout << std::setw(40) << std::left <<  directory_contents[g];
                
    //         }
    //         std::cout << std::endl << std::endl;
    //     }

	// 	return incomingTypedString;
    // }

	return "";
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
	char c;																										//Used to store the character coming in.
	bool specialCharacterSwitch = false;
	int characterIterator = 0;																					//Some keys will output 3 or 4 charactes.
	int savedCharacter = 0;

	while ((c = getchar())) {																					//Loop through getting characters.
		if (specialCharacterSwitch == false) {
			if ((c >= 32 && c <= 126) || c == 10) {																//If the letter is between what we want and can easily process.
				printf("%c",c);																					//Just print the letter out and return.
				return c;
			} else if (c == 9 || c == 127 ) {																	//Return the backspace and tab character, but don't print them.
				return c;		
			} else {
				specialCharacterSwitch = true;																	//Set our switch to true.
				characterIterator++;																			//Start our iterator.
			}
		} else {
			characterIterator++;																				//If we already found the start to one of our special keys with more than one output then increment.
			if (characterIterator == 3) {																		//With keys that have more than one output the, the third number is the descriptor key.
				if (c == 51 || c == 50) {																		//Looking at del and insert
					savedCharacter =  c * 3;																	//Save the character since we can't return it until we get all the incoming numbers from the key.
				} else {
					return c * 3;
				}
			} else if (characterIterator == 4) {																//If the key outputs four numbers then we can ignore the last number.
				return savedCharacter;
			}
		}
	}
	return -1;
}

