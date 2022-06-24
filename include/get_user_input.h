#ifndef GUI_H
#define GUI_H

#include <string.h>
#include <sys/time.h>

#include <termios.h>
#include <linux/input.h>

#include "astring.h"
#include "dir_utility.h"
#include "lookup_table.h"
#include "key_functions.h"

//----------------------------------------------------------------------------------
// Function Name: get_directory_contents
// Function Input Variables:
// Function Return Value:
//  - Successful:
//  - Error:
//----------------------------------------------------------------------------------
char * determine_keyboard_source() {
    // Note: This linked list will hold all the files in the /dev/input/by-path directory.
    Linked_List * dev_input_file_list = NULL;
    // Note: Store the full path to the keyboard dev input file.
    char * keyboard_dev_input_file = NULL;

    // Grab the directory of /dev/input/by-path
    dev_input_file_list = get_directory_contents("/dev/input/by-path/");
    
    // Note: Check to see if the linked list has contents
    if (dev_input_file_list) {
        // Note: Start looping through the linked list from the front.
        Linked_List_Node * temp = dev_input_file_list->front;
        // Note: Loop through the linked list looking for the keyboard dev file.
        for (int i = 0; i < dev_input_file_list->list_length; i++) {
            // Note: Look for the kdb and platform in the file name for the correct keyboard dev file.
            if (strstr(temp->string, "kbd")) {
                if (strstr(temp->string, "platform")) {
                    printf("Found the keyboard device: %s\n", temp->string);
                    // Note: Create a new string to hold the whole absolute path to the keyboard dev file.
                    keyboard_dev_input_file = calloc((strlen("/dev/input/by-path/") + strlen(temp->string) + 1), sizeof(char));
                    strcpy(keyboard_dev_input_file, "/dev/input/by-path/");
                    strcat(keyboard_dev_input_file, temp->string);
                }
            }
            // Note: Grab the next node in the linked list.
            temp = temp->next;
        }
    } else {
        // Note: If there are no contents within the linked list.
        return NULL;
    }

    return keyboard_dev_input_file;
}

//----------------------------------------------------------------------------------
// Function Name: grab_user_input_from_getchar
// Function Input Variables:
// Function Return Value:
//  - Successful:
//  - Error:
//----------------------------------------------------------------------------------
unsigned char grab_user_input_from_getchar(FILE * fd) {
    char c, character;
    int key, savedChar;
	int specialCharacterSwitch = 0;
	int characterIterator = 0;
	int savedCharacter = 0;

    Linux_Keys * lookup_key = NULL;
    struct termios oldattr, newattr;
    
    // Note: Get the current terminal setting for standard in.
    tcgetattr(0, &oldattr);
    // Note: Save the settings to a new terminal variable for restoring later.			
    newattr = oldattr;
    // Note: Turn off the echo feature and have the line editing to still occur.
    newattr.c_lflag &= ~( ICANON | ECHO );
    // Note: Set the new settings to the terminal.
    tcsetattr(0, TCSANOW, &newattr);

    // Note: Read from Standard In. 
    read(0, &c, 1);
    key = c;

    // Note: Check to see if we have found either an escape key or function key.
    if (c == 27) {
        fd_set set;
        struct timeval timeout;
        
        // Note: Intialize the set structure to zero.
        FD_ZERO(&set);
        // Note: Open the set structure for the Standard In file descriptor.
        FD_SET(0, &set);
        // Note: Set our time out to zero for an immediate response.
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        // Note: Check to see if there is any more incoming characters into Standard In.
        int selret = select(1, &set, NULL, NULL, &timeout);

        // Note: If the value is 1 then there is more input coming being written to Standard In. 
        if (selret == 1) {
            // Note: Loop at least three times for the function keys. There are two different kinds.
            // Note: 3: HOME, END, ARROW
            // Note: 4: PAGE UP / DOWN, INSERT, DELETE
            for (int i = 0; i < 3; i++) {
                // Note: Grab the next character of the function key.
                read(0, &c, 1);
                key = c;

                // Note: We don't care about the second character for either function key kind, but the third 
                // - character we do. 
                if (i == 1) {
                    // Note: The 3 char return function key all have a third character value greater than 60. 
                    if (key > 60) {
                        // Note: Multiply the third character value by 3 to make a unique character number for 
                        // - the switch statement.
                        key = key * 3;
                        // Note: Break out of the loop because we are done.
                        break;
                    // Note: The 4 char return function key will another value after the third so we need to save 
                    // - the number for later. Again multiply it by 3 to make a unique number.
                    } else {
                        savedChar = key * 3;
                    }
                // Note: Once we hit the last number, reset the c variable to the saved third value of the function key.
                } else if (i == 2) {
                    key = savedChar;
                }
            }
        // Note: There was an error with reading the file descriptor.
        } else if (selret == -1) {
            printf("ERROR: Something went wrong with the select function on the STDIN file descriptor...");
        // Note: There is no more characters coming into Standard In and we found and escape key.
        } else {
            key = 27;
        }
        character = key;
    } else {
        // Note: If you got the backspace character.
        if (key == 127) {
            character = 14;
        }
        else
        {
            character = key;
        }
    }
    
    // Note: Restore the old terminal setting for printing output.
    tcsetattr(0, TCSANOW, &oldattr);
        
	return character;
}

//----------------------------------------------------------------------------------
// Function Name: grab_user_input_from_dev_file
// Function Input Variables:
// Function Return Value:
//  - Successful:
//  - Error:
//----------------------------------------------------------------------------------
unsigned char grab_user_input_from_dev_file(FILE * fd) {

    unsigned char character = 0;
    Linux_Keys * lookup_key = NULL;
    struct input_event event;
    struct termios oldattr, newattr;

    int key_stuck_array[255];

    // Note: Initialize the data structure to zero's.
    memset(key_stuck_array, 0, sizeof(key_stuck_array));

    // Note: Get the current terminal setting for standard in.
    tcgetattr(0, &oldattr);
    // Note: Save the settings to a new terminal variable for restoring later.			
    newattr = oldattr;
    // Note: Turn off the echo feature and have the line editing to still occur.
    newattr.c_lflag &= ~( ICANON | ECHO );
    // Note: Set the new settings to the terminal.
    tcsetattr(0, TCSANOW, &newattr);

    // Note: Loop until a printable character can be found.
    while(1) 
    {
        // Note: Reset the event structure that was grabbed previously.
        memset(&event, 0, sizeof(event));
        
        // Note: Read from the keyboard device file for the given event structure size.
        size_t bytes = fread(&event, sizeof(event), 1, fd);
        if (bytes == 0) 
        {
            printf("ERROR: There was an issue with the fread function call...\n");
            return 0;
        }	

        // Note: Only process key events that occur in the keyboard input file.
        if (event.type == 1) 
        {
            // Note: Find the key that matches the keycode, if no match is found a NULL is given.
            if (!(lookup_key = get_linux_value(linux_lookup_table[event.code].key_code))) {
                printf("\nERROR: There was an issue with the pressed key code...\n");
                return 0;
            }

            // Note: If the event value from the keyboard is a key being unpressed.
            if (event.value == 0) 
            {
                // Note: If a key was being pressed down continously, put the key state back to false.
                key_stuck_array[lookup_key->key_code] = 0;
            }

            // Note: If the event value from the keyboard is a key being pressed and or held.
            else if (event.value == 1 || key_stuck_array[lookup_key->key_code])
            {
                // Note: Make sure that the value to the look up table contains astring.
                if (lookup_key->key_value) 
                {
                    // Note: If either the left or right shift key is being pressed down continously.
                    if (key_stuck_array[LEFT_SHIFT_KEY] || key_stuck_array[RIGHT_SHIFT_KEY])
                    {
                        // Note: Check that there is a shift value in the table, and print the key's shifted value.
                        if (lookup_key->key_shift_value) 
                        {
                            character = lookup_key->key_shift_value;
                            break;
                        // Note: If there is a string value for a code but no shift value then just continue.
                        } else 
                        {
                            continue;
                        }
                    }
                    else
                    {
                        // Note: Check that there is a normal value in the table, and print the key's value.
                        if (lookup_key->key_value) 
                        {
                            character = lookup_key->key_value;
                            break;
                        }
                    }
                    // Note: Prime the key stuck array with the key being pressed.
                    key_stuck_array[lookup_key->key_code] = 1;
                }
                // Note: Check for either shift key being pressed down and prime the array for it being pressed already.
                else if (event.code == 42 || event.code == 54) 
                {
                    key_stuck_array[lookup_key->key_code] = 1;
                }
                else
                {
                    // Note: Convert the key codes from the linux input number to ascii.
                    switch(lookup_key->key_code) 
                    {
                        case 1:
                            // Escape
                            character = 27;
                            break;
                        case 14:
                            // Backspace
                            character = 14;
                            break;
                        case 15:
                            // Tab
                            character = 9;
                            break;
                        case 28:
                            // Enter
                            character = 10;
                            break;
                        case 102:
                            // Home 
                            character = 216;
                            break;
                        case 103:
                            // Arrow Up
                            character = 195;
                            break;
                        case 104:
                            // Page Up
                            character = 159;
                            break;
                        case 105:
                            // Arrow Left
                            character = 201;
                            break;
                        case 106:
                            // Arrow Right
                            character = 204;
                            break;
                        case 107:
                            // End 
                            character = 210;
                            break;
                        case 108:
                            // Arrow Down
                            character = 198;
                            break;
                        case 109:
                            // Page Down
                            character = 162;
                            break;
                        case 110:
                            // Insert
                            character = 150;
                            break;
                        case 111:
                            // Delete
                            character = 153;
                            break;
                    }
                    break;
                }           
            }
        }
    }

    // Note: Restore the old terminal setting for printing output.
    tcsetattr(0, TCSANOW, &oldattr);

    return character;
}

//----------------------------------------------------------------------------------
// Function Name: process_user_input
// Function Input Variables:
// Function Return Value:
//  - Successful:
//  - Error:
//----------------------------------------------------------------------------------
int process_user_input(unsigned char (*function_ptr)(FILE * fd), FILE * fd)
{
    int saving_locker = 0;
    int cursor_position = 1;
    int executed_commands_iterator = 0;
    unsigned char character = 0;
    string * user_input = salloc(256, 1);
    string * saving_user_input = salloc(256, 1);
    Linked_List * executed_commands = NULL;

    while (1) 
    {
        character = function_ptr(fd);

        switch (character)
        {
            case 9:
                printf("\n Tab\n");
                break;
            case 10:
                printf("\n");
                // Note: Add the input from the user into the linked list for the history.
                vec_push(&executed_commands, user_input->array);
                // Note: Reset the linked list to the normal amount since the user entered a new command.
                executed_commands_iterator = executed_commands->list_length;
                // Note: Increment the iterator of the linked list for the current position in the linked list.
                executed_commands_iterator++;
                // Note: Reset the string for new input.
                sclear(&user_input);
                // Note: Reset the cursor position to one, and reset.
                cursor_position = 1;
                // Note:
                sclear(&saving_user_input);
                // Note: 
                saving_locker = 0;
                break;
            case 14:
                cursor_position = backspace_key_press(&user_input, cursor_position);
                break;
            case 27:
                printf("\n Escape\n");
                break;
            case 150:
                printf("\n Insert\n");
                break;
            case 153:
                cursor_position = delete_key_press(&user_input, cursor_position);   
                break;
            case 159:
                printf("\n Page Up\n");
                break;
            case 162:
                printf("\n Page Down\n");
                break;
            case 195:
                // Note: Check to see if the save buffer is currently empty and the locker for the saved buffer is open.
                if (saving_user_input->current_num_col == 0 && saving_locker == 0) 
                {
                    // Note: Check to see if the user has entered anything on the screen.
                    if (user_input->current_num_col == 0) 
                    {
                        // Note: Lock the mechanism that saves input into the save buffer.
                        saving_locker = 1;
                    }
                    else
                    {
                        // Note: Save the input that the user was typing onto the screen into the saved buffer.
                        sadd(&saving_user_input, "string", user_input->array);
                    }
                }

                // Note: Check to see if there are any more previous commands left.
                if (executed_commands_iterator >= 2)
                {
                    // Note: Subtract one from the linked list iterator to get the previous command that was executed.
                    executed_commands_iterator--;

                    arrow_up_key_press(&user_input, &executed_commands, executed_commands_iterator, cursor_position);

                    // Note: Save the new cursor position for the new command on the screen.
                    cursor_position = user_input->current_num_col + 1;
                }

                break;                
            case 198:
                // Note: Check to see if there are any more next commands left.
                if (executed_commands_iterator < executed_commands->list_length)
                {
                    // Note: Add one from the linked list iterator to get the next command that was executed.
                    executed_commands_iterator++;

                    arrow_down_key_press(&user_input, &executed_commands, executed_commands_iterator, cursor_position);

                    // Note: Save the new cursor position for the new command on the screen.
                    cursor_position = user_input->current_num_col + 1;
                }
                else
                {
                    // Note: Check to see if the saved input buffer has anything in it.
                    if (saving_user_input->current_num_col > 0)
                    {
                        // Note: Clear the selected command off of the screen.
                        clear_string_from_screen(user_input, cursor_position);
                        // Note: Clear the input buffer.
                        sclear(&user_input);
                        // Note: Add the previoius command to the string datastructure.
                        sadd(&user_input, "string", saving_user_input->array);
                        // Note: Print the previous command onto the screen.
                        printf("%s", user_input->array);
                    }
                    else
                    {
                        // Note: Clear the selected command off of the screen.
                        clear_string_from_screen(user_input, cursor_position);
                        // Note: Clear the input buffer.
                        sclear(&user_input);                        
                    }
                }

                break;    
            case 201:
                cursor_position = arrow_right_key_press(user_input, cursor_position);     
                break;
            case 204:
                cursor_position = arrow_left_key_press(cursor_position);         
                break;
            case 210:
                cursor_position = end_key_press(user_input, cursor_position);             
                break;
            case 216:
                cursor_position = home_key_press(cursor_position);            
                break;
            default:
                // Note: Check to see if the incoming character is a printable character.
                if (character > 31 && character < 127)
                {
                    // Note: Check to see if cursor isn't at the end of the string.
                    if (cursor_position < user_input->current_num_col + 1) 
                    {
                        // Note: Insert the incoming character into the string.
                        sinsert(&user_input, (cursor_position - 1), "char", character);

                        // Note: Determine how much the cursor has to move to get to the end of the string.
                        int shift = user_input->current_num_col - cursor_position + 1;

                        cursor_position = clear_string_from_screen(user_input, cursor_position);

                        // Note: Print the new string onto the screen.
                        printf("%s", user_input->array);

                        // Note: Set the cursor position to the end of the string.															
                        cursor_position = (user_input->current_num_col + 1);											
                        
                        // Note: Loop to move the cursor to where we left off on the string.
                        for (int i = 0; i < shift; ++i) 
                        {
                            // Note: Move the cursor to the left.
                            printf("\033[D");
                            //Note: Move the cursor position to where we were originally in.
                            cursor_position--;
                        }
                    }
                    else
                    {
                        // Note: Add the character to the user input string.
                        sadd(&user_input, "char", character);
                        // Note: Move the iterator with the incoming character.
                        cursor_position++;
                        // Note: Print the character to the end of the string.
                        printf("%c", character);
                    }
                }

                break;
        }

        // Note: Flush the standard out because there is no newline after the last printf.
        fflush(stdout);
    }

    // Note: When the program is exiting make sure to flush the standard input so it doesn't get repeated on the screen. 
    fflush(stdin);
    // Note: Cleanup the linked list of executed commands.
    vec_cleanup(&executed_commands);

    return 0;
}

#endif