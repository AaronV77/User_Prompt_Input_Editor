#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <termios.h>

#include <linux/input.h>

#include "lookup_table.h"

#define LEFT_SHIFT_KEY 42
#define RIGHT_SHIFT_KEY 54

Linux_Keys * get_value(int key) {
    // Get the starting point into the lookup table to start looping at.
    Linux_Keys key_stroke[1] = {{key}};
    // Use bsearch algorithm to find the correct key that was pressed in the lookup table.
    Linux_Keys * lookup_key = bsearch(key_stroke, linux_lookup_table, sizeof(linux_lookup_table) / sizeof(linux_lookup_table[0]), sizeof(linux_lookup_table[0]), compare_keys);
    // Return the lookup key.
    return lookup_key ? lookup_key : NULL;
}

int main(int argc, char *argv[])
{
    FILE* fd;
    Linux_Keys * lookup_key = NULL;
    int key_stuck_array[255];
    struct input_event event;
    struct termios oldattr, newattr;

    memset(key_stuck_array, 0, sizeof(key_stuck_array));

    if (!(fd = fopen("/dev/input/event2", "rb"))) {
        perror("ERROR: Couldn't open input device");
        return 1;
    }
    
    // Keep grabbing the user's input forever.
    while(1) {
        // Reset the event structure that was grabbed previously.
        memset(&event, 0, sizeof(event));

        // The 1 is for the STDIN file descriptor.
        // Get the current terminal setting for standard in.
		tcgetattr(0, &oldattr);
        // Save the settings to a new terminal variable for restoring later.			
		newattr = oldattr;
        // Turn off the echo feature and have the line editing to still occur.
		newattr.c_lflag &= ~( ICANON | ECHO );
        // Set the new settings to the terminal.
		tcsetattr(0, TCSANOW, &newattr);
        
        // Read from the keyboard device file for the given event structure size.
		size_t bytes = fread(&event, sizeof(event), 1, fd);
        if (bytes == 0) {
            printf("ERROR: There was an issue with the fread function call...\n");
            return 1;
        }	

        // Restore the old terminal setting for printing output.
		tcsetattr(0, TCSANOW, &oldattr);

        // Only process key events that occur in the keyboard input file.
        if (event.type == 1) {
            // Find the key that matches the keycode, if no match is found a NULL is given.
            if (!(lookup_key = get_value(linux_lookup_table[event.code].key_code))) {
                printf("\nERROR: There was an issue with the pressed key code...\n");
                return 1;
            }

            // If the event value from the keyboard is a key being unpressed.
            if (event.value == 0) 
            {
                // If a key was being pressed down continously, put the key state back to false.
                key_stuck_array[lookup_key->key_code] = 0;
            }
            // If the event value from the keyboard is a key being pressed.
            else if (event.value == 1 || key_stuck_array[lookup_key->key_code])
            {
                // Make sure that the value to the look up table contains astring.
                if (lookup_key->key_value || lookup_key->key_shift_value) {
                    // If either the left or right shift key is being pressed down continously.
                    if (key_stuck_array[LEFT_SHIFT_KEY] || key_stuck_array[RIGHT_SHIFT_KEY])
                    {
                        // Check that there is a shift value in the table, and print the key's shifted value.
                        if (lookup_key->key_shift_value) {
                            printf("%c", lookup_key->key_shift_value);
                            fflush(stdout);
                        }
                    }
                    else
                    {
                        // Check that there is a normal value in the table, and print the key's value.
                        if (lookup_key->key_value) {
                            printf("%c", lookup_key->key_value);
                            fflush(stdout);
                        }
                    }

                    // Prime the key stuck array with the key being pressed.
                    key_stuck_array[lookup_key->key_code] = 1;
                // Check for either shift key being pressed down and prime the array for it being pressed already.
                } else if (event.code == 42 || event.code == 54) {
                    key_stuck_array[lookup_key->key_code] = 1;
                } 
            }
        }

        fflush(stdin);
    }
    
    // Close the input device file.
    fclose(fd);

    return 0;
}
