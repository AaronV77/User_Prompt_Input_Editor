#ifndef DU_H
#define DU_H

#include <stdio.h>      // printf(), fprintf(), fclose(), fopen(), FILE
#include <stdlib.h>     // strtol()
#include <string.h>     // strlen()
#include <unistd.h>     // access(), X_OK
#include <sys/stat.h>   // struct stat, lstat(), chmod()

#include <dirent.h>

#include "linked_list_utility.h"

int du_debugger_flag = 0;

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
int is_dir(char * path) 
{

    if (du_debugger_flag) printf("Entering is_dir function.\n");

	struct stat fileStruct;
	lstat(path, &fileStruct);

	if ((fileStruct.st_mode & S_IFMT) == S_IFDIR) {
        if (du_debugger_flag) printf("Leaving is_dir function.\n");
		return 1;
    }

    if (du_debugger_flag) printf("Leaving is_dir function.\n");
	
    return 0;
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
int is_file(char * path) 
{
    if (du_debugger_flag) printf("Entering is_file function.\n");
	
    struct stat fileStruct;
	lstat(path, &fileStruct);
	if (((fileStruct.st_mode & S_IFMT) == S_IFLNK) ||
        ((fileStruct.st_mode & S_IFMT) == S_IFREG) ||
        ((!access(path, X_OK)) && ((fileStruct.st_mode & S_IFMT) == S_IFREG))) {
        if (du_debugger_flag) printf("Leaving is_file function.\n"); 
		return 1;
    }

    if (du_debugger_flag) printf("Leaving is_file function.\n");

	return 0;
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
int change_permissions(char * path, char * permissions) 
{
    if (du_debugger_flag) printf("Entering change_permissions function.\n");
    
    int i = strtol(permissions, 0, 8);
    if (chmod(path,i) < 0) {
        printf("ERROR: There was an issue with changing '%s' permissions...\n", path);
        if (du_debugger_flag) printf("Leaving change_permissions function.\n");
        return 1;
    }

    if (du_debugger_flag) printf("Leaving change_permissions function.\n");

    return 0;
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
int create_file(char * path, char * contents, char * permissions) {
    
    if (du_debugger_flag) printf("Entering create_file function.\n");
    
    if (is_file(path) || is_dir(path)) {
        printf("ERROR: The file to be created '%s', already exists...\n", path);
        if (du_debugger_flag) printf("Leaving create_file function.\n");
        return 1;
    }

    FILE *fp;
    fp  = fopen (path, "w");
    if (!fp) {
        printf("ERROR: The file '%s' could not be created...\n", path);
        if (du_debugger_flag) printf("Leaving create_file function.\n");
        return 1;
    }

    if (contents) {
        if (strlen(contents) > 0)
            fprintf(fp, "%s", contents);
    }
    fclose (fp);

    if (strlen(permissions) > 0 && strlen(permissions) < 5)
        change_permissions(path, permissions);

    if (du_debugger_flag) printf("Leaving create_file function.\n");
    
    return 0;
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
Linked_List * get_directory_contents(char * path) 
{

    if (du_debugger_flag) printf("Entering get_directory_contents function.\n");

    // Note: Check to see if the path is not empty and not NULL.
    if (path && strlen(path)) {
        // Note: Check to see if the path is a directory.
        if (!is_dir(path)) {
            printf("ERROR: The incoming path is not a directory...\n");
            if (du_debugger_flag) printf("Leaving get_directory_contents function.\n");
            return NULL;
        }
    // Note: The path was empty or NULL.
    } else {
        printf("ERROR: The incoming path pointer is either empty or NULL...\n");
        if (du_debugger_flag) printf("Leaving get_directory_contents function.\n");
        return NULL;
    }

    struct dirent * directory_struct;
    Linked_List * directory_contents = NULL;
    DIR * directory_ptr = NULL;

    // Note: Open the directory for reading.
    directory_ptr = opendir(path);

    // Note: Check to see if the directory is capable of being read.
    if (!directory_ptr)
    {
        printf("ERROR: Unable to open the following directory: %s\n", path);
        if (du_debugger_flag) printf("Leaving get_directory_contents function.\n");
        return 0;
    }

    // Note: Loop through the opened directory for reading.
    while ((directory_struct = readdir(directory_ptr)) != NULL)
    {
        // Note: Ignore the . and .. directories. 
        if (strcmp(directory_struct->d_name, ".") && strcmp(directory_struct->d_name, "..")) {
            // Note: Add the file / directory to the linked list. 
            vec_push(&directory_contents, directory_struct->d_name);
        }
    }

    // Note: Check to see if there was anything added to the linked list.
    if (!directory_contents->list_length) {
        printf("WARNING: The directory was empty...\n");
        if (du_debugger_flag) printf("Leaving get_directory_contents function.\n");
        return NULL;
    }

    if (du_debugger_flag) printf("Leaving get_directory_contents function.\n");

    return directory_contents;
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
void directory_utility_debugger() 
{
	du_debugger_flag = 1;
	return;
}

#endif