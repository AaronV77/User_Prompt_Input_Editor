/*-------------------------------------------------------------------
Author: Aaron Anthony Valoroso
Date: March 3rd, 2018
License: BSD-3-Clause
Email: valoroso99@gmail.com
--------------------------------------------------------------------*/
#ifndef UTIL_H
#define UTIL_H

#include <dirent.h>
#include <grp.h>
#include <iostream>
#include <pwd.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <vector>

namespace utili {   
    static const int MAX_SIZE = 256;
	static char path[MAX_SIZE];
    /*Methods*/
    /*-------------------------------------------------------------------------------------------*/
    std::string convert_number_to_letter(int incomingNumber);
    std::string	date(int number);   
    std::vector<std::string> directory_contents(std::string directoryPath, std::vector<std::string> contents);
    std::string fileInformation(std::string pathName);
    std::vector<std::string> get_environment(char **, std::vector<std::string> environment);
    bool isDirectory(std::string incomingPath);
    bool isFile(std::string incomingPath);
    int isNumber(std::string incomingString);
    void print_content(std::vector<std::string> content);
    void print_string(std::string incomingString);
    std::string remove_spaces(std::string incomingString);
    std::string remove_special_characters(std::string incomingString);
    int screen_size();
};
#endif
