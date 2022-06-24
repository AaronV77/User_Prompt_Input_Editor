/*-------------------------------------------------------------------
Author: Aaron Anthony Valoroso
Date: March 3rd, 2018
License: BSD-3-Clause
Email: valoroso99@gmail.com
--------------------------------------------------------------------*/
#include "Utilities.h"

const char* MONTHS[] = {
  "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December"
};

std::string utili::convert_number_to_letter(int incomingNumber) {
	std::string output = "";
	return (output += incomingNumber);
}

std::string utili::date(int number) {
	/*-------------------------------------------------------------------
	Note: This method will take in a number and display either just the day
	* of the month, the year, the month of the year, the time of day, the 
	* whole date, or the whole date and time. This is done by using the time.h
	* header file to access the structs that are made within the system to grab
	* the information on the time, date, month, and year.
	--------------------------------------------------------------------*/	
    time_t     currentTime = time(0);
    struct tm  tstruct;
	struct tm* timeinfo;
    char       buf[80];

	time(&currentTime);
	timeinfo = localtime(&currentTime);
	tstruct = *localtime(&currentTime);
    strftime(buf, sizeof(buf), "%X", &tstruct);
    
    std::string time = buf;
    std::string day = std::to_string(timeinfo->tm_mday);
    std::string month = MONTHS[timeinfo->tm_mon];
	std::string year = std::to_string(timeinfo->tm_year + 1900);
	std::string output = "";

	if (number == 1) {
		return month + " " + day + ", " + year;
	} else if (number ==2) {
		std::string currentTime;
		currentTime += time[0];
		currentTime += time[1];
		time += " ";
		if (std::stoi(currentTime) >= 12)
			time += "PM";
		else
			time += "AM";
			
		return time;
	}
	
	return output;
}

std::vector<std::string> utili::directory_contents(std::string directoryPath, std::vector<std::string> contents) {
	/*------------------------------------------------------------------
	Note: This method takes in a string / path and looks into that directory
	of which the path is associated to.It then grabs all the files within that
	directory and puts them into a vector. How this method works is by opening
	the directory up and reading each entry in the directory, and then puts 
	it into the vector. This method was last updated on 2/18/2018.
	--------------------------------------------------------------------*/	
	DIR * dir;
	dirent * entry;	
	if (directoryPath.size() > 0)
		dir = opendir(directoryPath.c_str());
	else 
		dir = opendir(".");

	if (dir == NULL)  
		return contents;
	
	while ((entry = readdir(dir)))
		contents.push_back(entry->d_name);

	return contents;
	
}

std::string utili::fileInformation(std::string pathName) {
	/*------------------------------------------------------------------
	Note: This method takes in a string / path and looks at the file / folder
	that the path is pointing to and get the information of it. How this 
	method works is by opening up the file struct, and then building the 
	string of permissions. This method was last updated on 2/18/2018.
	--------------------------------------------------------------------*/	
	struct group *grp;
	struct passwd *pwd;
	struct stat fileStruct;
	stat(pathName.c_str(), &fileStruct);
	std::string fileInfo = "";
	mode_t perm = fileStruct.st_mode;
	
	grp = getgrgid(fileStruct.st_gid);
	pwd = getpwuid(fileStruct.st_uid );
	
	fileInfo = (perm & S_IFDIR) ? 'd' : '-';
	fileInfo += (perm & S_IRUSR) ? 'r' : '-';
	fileInfo += (perm & S_IWUSR) ? 'w' : '-';
	fileInfo += (perm & S_IXUSR) ? 'x' : '-';
	fileInfo += (perm & S_IRGRP) ? 'r' : '-';
	fileInfo += (perm & S_IWGRP) ? 'w' : '-';
	fileInfo += (perm & S_IXGRP) ? 'x' : '-';
	fileInfo += (perm & S_IROTH) ? 'r' : '-';
	fileInfo += (perm & S_IWOTH) ? 'w' : '-';
	fileInfo += (perm & S_IXOTH) ? 'x' : '-';
	fileInfo += " ";
	fileInfo += static_cast<std::string>(grp->gr_name);
	fileInfo += " ";
	fileInfo += static_cast<std::string>(pwd->pw_name);
	fileInfo += " "; 
	
	return fileInfo;
}

std::vector<std::string> utili::get_environment(char * envp[], std::vector<std::string> environment) {
	/*------------------------------------------------------------------
	Note: This method takes in the current environment that is given, 
	and puts the contents into a vector. How this works is by looping 
	through the given environment arrray, and getting each variable and
	value. Then stores each part into the array separately. This method
	was last updated on 2/18/2018.
	--------------------------------------------------------------------*/		
    int i = 0; 
    bool variableFound = false;
    bool equalSignFound = false;
   	std::string str = "";
    std::string command = "";
    std::string value = "";

    while(envp[i] != NULL) {
        str = envp[i];
        for (int a = 0; a < str.size(); ++a) {
            if (str[a] == '=') {
                equalSignFound = true;
            } else {
                if (equalSignFound == false) {
                    command += str[a];
                } else {
                    value += str[a];
                }
            }
        }
        environment.push_back(command);
        environment.push_back(value);
        equalSignFound = false;
        command = "";
        value = "";
        i++;
    }
	return environment;
}

bool utili::isDirectory(std::string incomingPath) {
	struct stat fileStruct;
	lstat(incomingPath.c_str(), &fileStruct);
	if ((fileStruct.st_mode & S_IFMT) == S_IFDIR)
		return true;

	return false;
}

bool utili::isFile(std::string incomingPath) {
	struct stat fileStruct;
	lstat(incomingPath.c_str(), &fileStruct);
	if ((fileStruct.st_mode & S_IFMT) == S_IFLNK) {
		return true;
	} else if (! access(incomingPath.c_str(), X_OK) && ((fileStruct.st_mode & S_IFMT) == S_IFREG)) {
		return true;
	} else if ((fileStruct.st_mode & S_IFMT) == S_IFREG) {
		return true;
	}	

	return false;
}

int utili::isNumber(std::string incomingString) {
	/*------------------------------------------------------------------
	Note: This method takes an incoming string and checks to see if it
	is a number. This method was last updated on 2/18/2018.
	--------------------------------------------------------------------*/		
	int counter = 0;
	int size = incomingString.size();
	
	if (size > 0) {
		for (int i = 0;  i < size; i++) {
			if (isdigit(incomingString[i]))
				counter++;
		}
		
		if (counter == size)
			return 1;
		else
			return 0;
	} else {
		return 0;
	}
		
}

void utili::print_content(std::vector<std::string> content) {
	/*------------------------------------------------------------------
	Note: This method takes in a vector and prints it to the terminal with
	adaqute padding on either side of the text. How this method works is by
	getting the screen size first, then setting a padding on either side of 
	the text to the indent. Now we will use that iterator later on to make
	sure that we don't exceed that indent. So then we loop through the vector,
	tokening up the that part and then looping through each token. I keep track
	of the size of each token so that when our iterator gets to the size of
	our indent or exceeds it, we just do a newline. There is also another 
	feature, of manually adding new lines to the output when "newline" is
	the token. This method was last updated on 2/18/2018.
	--------------------------------------------------------------------*/		
	int columns = screen_size();
	int indent = ((columns / 10) - 10);
	int iterator = 0;
	std::string input = "";

	if (indent < 0)
		indent = 0;

	for (int i = 0; i < content.size(); i++) {
		std::istringstream iss (content[i]);
		while (iss >> input) {
			if (input == "newLine") {
				iterator = 0;
				std::cout << std::endl;
			} else {
				if (iterator == 0) {
					std::cout << std::string(indent, ' ');
					std::cout << input << ' ';
					iterator = input.size() + indent + 1;
				} else if ((input.size()+iterator) < (columns - indent)) {
					iterator += input.size();
					iterator += 1;
					std::cout << input << ' ';
				} else {
					iterator = 0;
					std::cout << std::endl;
					std::cout << std::string(indent, ' ');
					std::cout << input << ' ';
					iterator = input.size() + indent + 1;
				}
			}	
		}
	}
	std::cout << std::endl;
}

void utili::print_string(std::string incomingString) {
	/*------------------------------------------------------------------
	Note: This method takes in a vector and prints it to the terminal with
	adaqute padding on either side of the text. How this method works is by
	getting the screen size first, then setting a padding on either side of 
	the text to the indent. Now we will use that iterator later on to make
	sure that we don't exceed that indent. So then we loop through the string,
	tokening up the that part and then I keep track of the size of each token 
	so that when our iterator gets to the size of our indent or exceeds it, 
	we just do a newline. This method was last updated on 2/18/2018.
	--------------------------------------------------------------------*/		
	int columns = screen_size();
	int indent = ((columns / 10) - 10);
	int iterator = 0;
	std::string input = "";

	if (indent < 0)
		indent = 0;

	std::istringstream iss (incomingString);
	while (iss >> input) {
		if (input.size() > 100) {
			for (int i = 0; i < input.size(); i++) {
				if (iterator == 0) {
					std::cout << std::string(indent, ' ');
					std::cout << input[i];
					iterator = indent + 1;
				} else if ((1 + iterator) < (columns - indent)) {
					iterator += 1;
					std::cout << input[i];
				} else {
					iterator = 0;
					std::cout << std::endl;
					std::cout << std::string(indent, ' ');
					std::cout << input[i];
					iterator = indent + 1;
				}
			}
		} else {
			if (iterator == 0) {
				std::cout << std::string(indent, ' ');
				std::cout << input << ' ';
				iterator = input.size() + indent + 1;
			} else if ((input.size()+iterator) < (columns - indent)) {
				iterator += input.size();
				iterator += 1;
				std::cout << input << ' ';
			} else {
				iterator = 0;
				std::cout << std::endl;
				std::cout << std::string(indent, ' ');
				std::cout << input << ' ';
				iterator = input.size() + indent + 1;
			}
		}	
	}
	std::cout << std::endl;

	return;
}

std::string utili::remove_spaces(std::string incomingString) {
	/*------------------------------------------------------------------
	Note: This method takes in the a string and space characters from it.
	How this method works is by looping through the given string and checking
	to see if any given character has a value equale to 32. This method 
	was last updated on 2/18/2018.
	--------------------------------------------------------------------*/		
	std::string output = "";
	for (int i = 0; i < incomingString.size(); ++i) {
		if (incomingString[i] != 32)
			output += incomingString[i];
	}
	return output;
}

std::string utili::remove_special_characters(std::string incomingString) {
	/*------------------------------------------------------------------
	Note: This method takes in the a string and removes all the forign 
	characters from it. How this method works is by looping through
	the given string and checking to see if any given character has a value
	lower than 32. All weird keys are below the value 32, and are not added
	to the string. This method was last updated on 2/18/2018.
	--------------------------------------------------------------------*/		
	std::string output = "";
	for (int i = 0; i < incomingString.size(); ++i) {
		if (incomingString[i] >= 32) 
			output += incomingString[i];
	}
	return output;
}

int utili::screen_size() {
	/*------------------------------------------------------------------
	Note: This method gets the screen size of the current terminal window.
	How this method works is by opening the terminal struct and gets the 
	information about the window size in columns. This method was last 
	updated on 2/18/2018.
	--------------------------------------------------------------------*/		
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return w.ws_col;
}





