#ifndef KF_H
#define KF_H

#include "astring.h"

int end_key_press(string * user_input, int cursor_position) 
{
    // Note: Get the number of times we have to move the cursor to the right.
    int size = user_input->current_num_col - (cursor_position - 1);
    // Note :Make sure that we are not already at the end of the string.                                      
    if (size) 
    {
        // Note: Move the cursor (size) many times to the right.
        for (int i = 0; i < size; i++)
        {
            // Note: Move the cursor on the screen one step to the right.
            printf("\033[C");
        }
        cursor_position = user_input->current_num_col + 1;
    }

    return cursor_position;
}

int clear_string_from_screen(string * user_input, int cursor_position)
{
    cursor_position = end_key_press(user_input, cursor_position);
    
    // Note: Loop to remove all the characters off the screen.
    for (int i = 0; i < (user_input->current_num_col + 1); ++i) 
    {
        printf("\b \b");
        cursor_position--;
    }

    return cursor_position;
}

int move_cursor_far_right(string * user_input)
{
    // Note: Loop through the passed in string.
    for (int i = 0; i < (user_input->current_num_col + 1); ++i)
    {
        // Note: Move the cursor one space to the right.
        printf("\033[C");
    }

    return user_input->current_num_col;
}

int new_line_key_press() {

    return 0;
}

int arrow_up_key_press(string ** user_input, Linked_List ** executed_commands, int linked_list_iterator, int cursor_position)
{
    // Note: Get the node from the linked list that the user is looking for.
    Linked_List_Node * node = vec_get(executed_commands, "front", linked_list_iterator);

    if (node)
    {
        // Note: Clear the current contents from the screen.
        clear_string_from_screen((*user_input), cursor_position);

        sclear(user_input);

        // Note: Add the previoius command to the string datastructure.
        sadd(user_input, "string", node->string);
        
        // Note: Print the previous command onto the screen.
        printf("%s", (*user_input)->array);
    }

    return 0;
}

int arrow_down_key_press(string ** user_input, Linked_List ** executed_commands, int linked_list_iterator, int cursor_position) 
{
    // Note: Get the node from the linked list that the user is looking for.
    Linked_List_Node * node =  vec_get(executed_commands, "front", linked_list_iterator);

    if (node)
    {
        // Note: Clear the current contents from the screen.
        clear_string_from_screen((*user_input), cursor_position);

        sclear(user_input);

        // Note: Add the previoius command to the string datastructure.
        sadd(user_input, "string", node->string);
        
        // Note: Print the previous command onto the screen.
        printf("%s", (*user_input)->array);
    }

    return 0;
}

int arrow_left_key_press(int cursor_position) 
{
    // Note: Check to see if the cursor is at the end of the screen already.
    if (cursor_position > 1) 
    {
        // Note: Move the cursor one space to the left.
        printf("\033[D");
        // Note: Increment the cursor iterator.
        cursor_position--;
    }

    return cursor_position;
}

int arrow_right_key_press(string * user_input, int cursor_position) 
{
    // Note: Check to see if the cursor hasn't exceeded the 1+ past the current line.
    if (cursor_position < (user_input->current_num_col + 1)) 
    {
        // Note: Move the cursor one space to the right.
        printf("\033[C");
        // Note: Increment the cursor iterator.
        cursor_position++;
    }

    return cursor_position;
}

int page_up_key_press() 
{
    return 0;
}

int page_down_key_press() 
{
    return 0;
}

int home_key_press(int cursor_position) 
{
    // Note: Get the number of times we have to move the cursor to the right.
    int size = cursor_position - 1;
    // Note :Make sure that we are not already at the end of the string.                                      
    if (size) 
    {
        // Note: Move the cursor (size) many times to the right.
        for (int i = 0; i < size; i++)
        {
            // Note: Move the cursor on the screen one step to the left.
            printf("\033[D");
        }
        cursor_position = 1;
    }

    return cursor_position;
}

int insert_key_press() 
{
    return 0;
}

int backspace_key_press(string ** user_input, int cursor_position) 
{
    int old_cursor_position = 0;

    // Note: Delete the characters in the pointer, but no further than what was typed.
    if (cursor_position > 1) 
    {
        // Note: Delete the character before the cursor on the screen.
        printf("\b \b");
        
        // Note: Store the size of the original string with one extra character for the cursor position.
        int end_of_string = (*user_input)->current_num_col + 1;

        // Note: Erase the character from the string with minus two (Null terminator and One Base).
        schar_single_delete(user_input, (cursor_position - 2));

        // Note: If the cursor is not at the end of the string.
        if (end_of_string != cursor_position) 
        {
            // Note: Decrement the cursor iterator once due to the deletion of the character from the screen.
            // Note: Decrement the cursor iterator once due to the deletion of the character from the string.
            // Note: We have to do the subtraction by 2 for getting the cursor to the end of the original string
            //       - size and counter act the string shortening on us in the mean time.
            cursor_position -= 2;

            // Note: Save the cursor position because we will lose it in the clearing of the string from the screen function.
            old_cursor_position = cursor_position;
            
            cursor_position = clear_string_from_screen((*user_input), cursor_position);            

            // Note: We subtract the original cursor position from the end of the string. We have to subtract one 
            //       - from the end of the string variable due to it being the original size + 1 for the cursor position.
            //       - Remember this was done to check to see if we were at the end of the string. Then we have to subtract
            //       - everything by one because of over compensating the subtraction to be able to delete everything off 
            //       - of the screen. By subtacting one from the value we are actually move the cursor to the right versas
            //       - the left when looking at the algorithm. 
            int shift = ((end_of_string - 1) - old_cursor_position) - 1;

            // Note: Reprint our new string on the screen. This will push our cursor to the end of the string.
            printf("%s", (*user_input)->array);

            // Note: So lets save where our new iterator lies on the screen.
            cursor_position = (*user_input)->current_num_col + 1;

            // Note: Loop to move the cursor position to the left on the letter we were on originally.
            for (int i = 0; i < shift; ++i) 
                cursor_position = arrow_left_key_press(cursor_position);
        } 
        else 
        {
            // Note: Since we are at the end our string we can just delete the character both on the screen and string.
            cursor_position--;																	    
        }											
    }

    return cursor_position;
}

int delete_key_press(string ** user_input, int cursor_position) 
{
    // Note: Check to see if we are at the end of the string.
    if (cursor_position <= (*user_input)->current_num_col) 
    {
        // Note: Store the size of the original string with one extra character for the iterator.
        int end_of_string = (*user_input)->current_num_col + 1;

        // Note: Erase the character from the string with minus two (Null terminator).
        schar_single_delete(user_input, cursor_position);

        // Note: Subtract from the left and right iterator because our cursor moves over one when we delete the character.
        cursor_position--;

        // Note: Get our shift which is just the different from the back of the string to where the cursor is at on the string.
        int shift = (end_of_string - cursor_position - 2);

        cursor_position = clear_string_from_screen((*user_input), cursor_position);

        // Note: Reprint our new string on the screen. This will push our cursor to the end of the string.
        printf("%s", (*user_input)->array);

        // Note: So lets save where our new iterator lies on the screen.
        cursor_position = (*user_input)->current_num_col + 1;

        // Note: Loop to move the cursor position to the left on the letter we were on originally.
        for (int i = 0; i < shift; ++i)
        {
            cursor_position = arrow_left_key_press(cursor_position);
        }
    }

    return cursor_position;
}

#endif