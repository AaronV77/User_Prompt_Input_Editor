# Thursday

This project started in a Linux Programming class my Junior year of college. I was fascinated with Bash and wanted to create my own Linux shell. I used this project to direct my willingness to learn more about how both Bash and the underlying operating system works. At the time I did not know how to read the Bash C language code, so I did what I could in C++ and went from there. Yes I know that the languages are similiar, but have you seen a professional C developer code (It's NUTS!). Now I am not saying I copied the code in anyway, I took the features I knew and implemented them the way I thought they would have been implemented.

Over the next few years I spent months on adding features to make this application more usuable in everyday life, and to make my job easier while having to work in the terminal! The goal for Thursday is to make it a full fledge shell out of it. You are probably asking yourself, "I thought it was a shell"? And you are right, but Thursday works and acts like a real shell. The program currently works on top of Bash, I ran into issues trying to have the program run stand alone off of Bash. Hey its a learning process! But in the mean time I will figure that out and how to use all these GitHub features.

If you have made it this far into the description than a round of appluase for you. By now you are wondering why you are still reading this and why you should use Thursday when there are so many other already working shells? Well you should use Thursday as a shell and help contribute to the project because I want this shell to take all the best features from every shell into one and make everyone's life easier! Also I want to create proper doucmentation so that beginners have some starting point for learnign about Linux shells. Hopefully that it will encourage them to learn more about low level applications and program!

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. Make sure that the system is compatable with your environment, if it doesn't then please post an issue and I will correct it accordinly. For any other questions or concerns, consult the Wiki in GitHub. I have put up documents for the application there and hopefully that will answer your questions, if not send me a message!

## Warnings

I have only tested the system on the latest release of Mac which is “High Sierra”, Centos 7, and Ubuntu 16.04. 

Lastly the commands that I have created within the system override the Linux versions. For example, the command "find" in Thursday will not take the same arguments as the comand "find" in a normal Linux Terminal. If you need help using the commands then execute the "commands" command in Thursday and it will help you figure out what each command needs inorder to run. Not all the command are different from the Linux versions, some are needed so that the system has an idea of where the user is going and wants to do.

Here is a list of Thursday's commands:

back
bash
cd
color
commands
compress
cp
date
debug
decompress
decrypt
encrypt
exit
find
getenv
hd
help
info
ls
mv
pid
ppid
printenv
prompt
rm
search
setenv
time
uid
unsetenv
usage
wd

## Prerequisites

The only thing that you should need to get this project off the ground and into your computer is c++ 11 (wouldn't hurt to the latest), and the latest version of gcc. Below are what commands you need to run.

### Ubuntu: 
- Type: sudo apt-get install build-essential 
- Type: sudo apt-get install g++
- Type: sudo apt-get install gcc-4.9 g++-4.9

### Red Hat: 
- Type: yum install gcc-c++ kernel-devel make
- Type: yum groupinstall “Development Tools”
- Type: yum install gcc-c++

###	Mac:
- Make sure that your XCode installation is up-to-date. 
- Hopefully that in your XCode installation it will update the gcc compiler, if not use google.

## Installing

To install the system, just run the setup.sh script in the base directory of Thursday. This should get you going and running. From there go into the build directory that is created from the script and execute the Thurs file. For more information please consult the wiki.


## Updating

To update the system just run the update script and it should update your system to the new repository. For more information please consult the wiki.


# Author: Aaron A. Valoroso


## Inspiring Quotes

 The programmers of tomorrow are the wizards of the future. You're going to look like you have magic  powers compared to everybody else.
 
 - Gabe Newell
   
  When 99% of people doubt your idea, you're either gravely wrong or about to make history.
  
   - Scott Belsky

  Most good programmers do programming not because they expect to get paid or get adulation by the publicc, but because it is fun to       program.

   - Linux Torvalds
