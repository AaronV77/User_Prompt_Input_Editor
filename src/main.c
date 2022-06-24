#include <stdio.h>

#include "get_user_input.h"

int main(int argc, char *argv[])
{
    FILE * fd = NULL;
    unsigned char (*function_ptr)(FILE * fd) = NULL;

    char * keyboard_dev_input_file = determine_keyboard_source();

    // Note: See if the program can find the keyboard dev file.
    if (keyboard_dev_input_file) 
    {
        // Note: Try to open the keyboard dev file for reading.
        if (!(fd = fopen(keyboard_dev_input_file, "rb"))) 
        {
            perror("ERROR: Couldn't open input device");
            printf("Starting to capture keyboard input with getch()...\n");
            // Note: If not successful, lets just read from getch() function.
            function_ptr = &grab_user_input_from_getchar;
        } 
        else 
        {
            printf("Starting to capture keyboard input...\n");
            // Note: If successful, lets read from the dev input file.
            function_ptr = &grab_user_input_from_dev_file;
        }
    } 
    else 
    {
        printf("Starting to capture keyboard input with getch()...\n");
        // Note: If not successful, lets just read from getch() function.
        function_ptr = &grab_user_input_from_getchar;
    }

    // Note: Pass the funtion pointer to start getting input from the user.
    process_user_input(*function_ptr, fd); 


    if (keyboard_dev_input_file) 
        free(keyboard_dev_input_file);

    if (fd)
        fclose(fd);

    return 0;
}
