#ifndef LINKED_L
#define LINKED_L

#include <stdio.h>      // printf
#include <stdlib.h>     // calloc
#include <string.h>     // strcpy

//----------------------------------------------------------------------------------
// Function Name: 
// Function Notes:
//    - 
//----------------------------------------------------------------------------------
typedef struct Linked_List_Node { 
    char * string;
    int string_size;
    struct Linked_List_Node * next;
    struct Linked_List_Node * past;
}Linked_List_Node;

//----------------------------------------------------------------------------------
// Function Name: 

// Function Notes:
//    - 
//----------------------------------------------------------------------------------
typedef struct Linked_List {
    int list_length;
    Linked_List_Node * front, * rear;
}Linked_List;

int ll_debugger_flag = 0;

//----------------------------------------------------------------------------------
// Function Name: 
// Function Input Variables:
//    - 
// Function Return Value:
//    - Successful:
//    - Error:
// Function Notes:
//    - 
//----------------------------------------------------------------------------------
void vec_push(Linked_List ** list, char * string) {
    if (ll_debugger_flag) printf("Entering the vec_push function\n");

    Linked_List_Node * temp = calloc(1, sizeof(Linked_List_Node));
    temp->string = calloc((strlen(string) + 1), sizeof(char));
    strcpy(temp->string, string);
    temp->string_size = strlen(string);
    temp->next = NULL;
    temp->past = NULL;
    
    if (!*list) 
    {
        *list = calloc(1, sizeof(Linked_List));
        (*list)->front = (*list)->rear = temp;
    }
    else 
    {
        (*list)->rear->next = temp;
        temp->past = (*list)->rear;
        (*list)->rear = temp;
    }

    (*list)->list_length++;

    if (ll_debugger_flag) printf("Leaving the vec_push function\n");
    return;
}

//----------------------------------------------------------------------------------
// Function Name: 
// Function Input Variables:
//    - 
// Function Return Value:
//    - Successful:
//    - Error:
// Function Notes:
//    - 
//----------------------------------------------------------------------------------
void vec_pop(Linked_List ** list) {
    if (ll_debugger_flag) printf("Entering the vec_pop function\n");

    // Note: Check to see if the list is either empty or not initialized.
    if (!(*list) || !(*list)->front) 
    {
        printf("ERROR: The linked list is empty...\n");
        if (ll_debugger_flag) printf("Leaving the vec_cleanup function\n");
        return;
    }

    // Note: Point the linked lists main rear pointer to the second to last node within the linked list.
    (*list)->rear = (*list)->front->past;
    // Note: Allocate the second to last node next pointer to NULL.
    (*list)->front->past->next = NULL;
    // Note: Deallocate the string pointer within the linked list node.
    free((*list)->front->string);
    // Note: Deallocate the linked list node entirely. 
    free((*list)->front);

    if (ll_debugger_flag) printf("Leaving the vec_pop function\n");
    return;
}

//----------------------------------------------------------------------------------
// Function Name: 
// Function Input Variables:
//    - 
// Function Return Value:
//    - Successful:
//    - Error:
// Function Notes:
//    - 
//----------------------------------------------------------------------------------
void vec_remove(Linked_List ** list, char * string, int number_of_nodes) {
    if (ll_debugger_flag) printf("Entering the vec_pop function\n");

    // Note: Check to see if the list is either empty or not initialized.
    if (!(*list) || !(*list)->front) {
        printf("ERROR: The linked list is empty...\n");
        if (ll_debugger_flag) printf("Leaving the vec_cleanup function\n");
        return;
    }

    // Note: Check to make sure that the position of the linked list node is within the linked list.
    if (number_of_nodes > ((*list)->list_length - 1) || number_of_nodes < 0) {
        printf("ERROR: The number of nodes given is either greater than the list size or smaller than zero.\n");
        return;
    }

    int list_iterator = 0;
    Linked_List_Node * past = NULL;
    Linked_List_Node * current = NULL;

    // Note: Check to see if the user wants to start from the front of the linked list.
    if (!strcmp(string, "front")) 
    {
        // Note: Grab the first node within the linked list.
        current = (*list)->front;
    }
    // Note: Check to see if the user wants to start from the rear of the linked list.
    else if (!strcmp(string, "rear")) 
    {
        // Note: Grab the last node within the linked list.
        current = (*list)->rear;
    }

    // Note: Loop throug the linked list.
    while (current) 
    {
        // Note: Check to see if we have traversed the correct number of nodes within the linked list.
        if (list_iterator == number_of_nodes) 
        {
            // Note: Remove the leading node from the linked list.
            if (list_iterator == 0 && !strcmp(string, "front")) 
            {
                // Note: Change the main pointer of the linked lists front pointer to the next node.
                (*list)->front = current->next;
                // Note: Chang the next nodes past pointer to NULL.
                current->next->past = NULL;
            } 
            // Note: Remove the trailing node from the linked list.
            else if (((list_iterator == ((*list)->list_length - 1)) && 
                     (!strcmp(string, "front"))) || 
                     ((list_iterator == 0) &&
                     (!strcmp(string, "rear")))
                    ) 
            {
                // Note: Make the second from the rear's node, and set it's next pointer to NULL.
                (*list)->rear->past->next = NULL;
                // Note: Set the main linked list rear pointer to the second to last node.
                (*list)->rear = (*list)->rear->past;
            } 
            // Note: Removing a node from the middle of the linked list.
            else 
            {
                // Note: Set the past's nodes next pointer to the next in line node.
                past->next = current->next;
                // Note: Set the next in line node past pointer to past node.
                current->next->past = past->next;
            }

            // Note: Deallocate the string within the node.
            free(current->string);
            // Note: Deallocate the linked list node.
            free(current);
            break;
        }

        past = current;

        if (!strcmp(string, "front"))
        {
            // Note: Grab the next node within the linked list.
            current = current->next;
        }
        else if (!strcmp(string, "rear"))
        {
            // Note: Grab the previous node within the linked list.
            current = current->past;
        }
        
        list_iterator++;
    }

    if (ll_debugger_flag) printf("Leaving the vec_pop function\n");
    return;
}

//----------------------------------------------------------------------------------
// Function Name: 
// Function Input Variables:
//    - 
// Function Return Value:
//    - Successful:
//    - Error:
// Function Notes:
//    - 
//----------------------------------------------------------------------------------
Linked_List_Node * vec_get(Linked_List ** list, char * string, int number_of_nodes) {
    if (ll_debugger_flag) printf("Entering the vec_get function\n");

    // Note: Check to see if the list is either empty or not initialized.
    if (!(*list) || !(*list)->front) {
        printf("ERROR: The linked list is empty...\n");
        if (ll_debugger_flag) printf("Leaving the vec_cleanup function\n");
        return NULL;
    }

    // Note: Check to make sure that the position of the linked list node is within the linked list.
    if (number_of_nodes > (*list)->list_length || number_of_nodes < 0) {
        printf("ERROR: The number of nodes given is either greater than the list size or smaller than zero (%d).\n", number_of_nodes);
        return NULL;
    }

    int list_iterator = 1;
    Linked_List_Node * current = NULL;

    // Note: Check to see if the user wants to start from the front of the linked list.
    if (!strcmp(string, "front")) 
    {
        // Note: Grab the first node within the linked list.
        current = (*list)->front;
    }
    // Note: Check to see if the user wants to start from the rear of the linked list.
    else if (!strcmp(string, "rear")) 
    {
        // Note: Grab the last node within the linked list.
        current = (*list)->rear;
    }

    // Note: Loop throug the linked list.
    while (current) 
    {
        // Note: Check to see if we have traversed the correct number of nodes within the linked list.
        if (list_iterator == number_of_nodes) 
        {
            break;
        }

        if (!strcmp(string, "front"))
        {
            // Note: Grab the next node within the linked list.
            current = current->next;
        }
        else if (!strcmp(string, "rear"))
        {
            // Note: Grab the previous node within the linked list.
            current = current->past;
        }
        
        list_iterator++;
    }

    if (ll_debugger_flag) printf("Leaving the vec_get function\n");

    return current;
}

//----------------------------------------------------------------------------------
// Function Name: 
// Function Input Variables:
//    - 
// Function Return Value:
//    - Successful:
//    - Error:
// Function Notes:
//    - 
//----------------------------------------------------------------------------------
void vec_cleanup(Linked_List ** list) {
    if (ll_debugger_flag) printf("Entering the vec_cleanup function\n");

    // Note: Check to see if the list is either empty or not initialized.
    if (!(*list) || !(*list)->front) {
        printf("ERROR: The linked list is empty...\n");
        if (ll_debugger_flag) printf("Leaving the vec_cleanup function\n");
        return;
    }

    Linked_List_Node * temp;
    while ((*list)->front) {
        temp = (*list)->front->next;
        free((*list)->front->string);
        free((*list)->front);
        (*list)->front = temp;
    }
    free(*list);

    if (ll_debugger_flag) printf("Leaving the vec_cleanup function\n");
    return;
}

//----------------------------------------------------------------------------------
// Function Name: 
// Function Input Variables:
//    - 
// Function Return Value:
//    - Successful:
//    - Error:
// Function Notes:
//    - 
//----------------------------------------------------------------------------------
void vec_listall(Linked_List * list) {
    if (ll_debugger_flag) printf("Entering the vec_listall function\n");

    // Note: Check to see if the list is either empty or not initialized.
    if (!list || !list->front) {
        printf("ERROR: The linked list is empty...\n");
        if (ll_debugger_flag) printf("Leaving the vec_listall function\n");
        return;
    }

    Linked_List_Node * temp = list->front;
    while (temp) {
        printf("%s\n", temp->string);
        temp = temp->next;
    }

    if (ll_debugger_flag) printf("Leaving the vec_listall function\n");
    return;
}

//----------------------------------------------------------------------------------
// Function Name: 
// Function Input Variables:
//    - 
// Function Return Value:
//    - Successful:
//    - Error:
// Function Notes:
//    - 
//----------------------------------------------------------------------------------
void linked_list_debugger() {
    ll_debugger_flag = 1;
    return;
}

#endif
