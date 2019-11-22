#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define NUM_HISTORY 4								// max number of commands tracked in history
#define MAX_CMD_LEN 100 							// maximum length of command strings

struct History {									// struct to track command history
	char command[NUM_HISTORY][MAX_CMD_LEN];			// circular array for commands history
	int count;										// current number of commands in history
	int cursor;										// cursor for circular array
} history;

void update_history(char buf[]) {
	strcpy(history.command[history.cursor], buf);	// add latest command to history
	history.cursor++;								// update cursor in circular array
	if (history.cursor >= NUM_HISTORY) {
		history.cursor = 0;							
	}
	if (history.count < NUM_HISTORY) {
		history.count++;							// track history count
	}			
}

void print_cmd_history() {
	printf("\nLast %d commands:\n", NUM_HISTORY);
	for (int i=0; i < history.count; i++) {			// print all commands stored in history
		history.cursor--;
		if (history.cursor < 0) {
			history.cursor = NUM_HISTORY -1;
		}
		printf("%s\n", history.command[history.cursor]);
	}
	printf("\n");
}

void list_to_terminal() { // Note: modified from list() function in "list.h"
   char path[100];
   getwd(path); // Gets the path to the current directory
   DIR *dir = opendir(path);
   if (dir == NULL) {
      printf("Error Directory couldn't be opened");
      return;
   }
   int totalBlockCount = 0;
   struct dirent *de;
   while((de = readdir(dir)) != NULL){ // While loop to read each file in the directory 
      char* fileName = de->d_name;
      if(strcmp(fileName, ".") != 0 && strcmp(fileName, "..") != 0 ){  // ignore . and .. 
         char filePath[1000]; 
         sprintf(filePath, "%s%s%s", path,"/",fileName); // Creating the filepath for each item
         struct stat fileInfo; // struct stat that store the files info
         stat(filePath, &fileInfo); // system call to get the information about the filepath provided         
         totalBlockCount += fileInfo.st_blocks; // keep count of total number of file system blocks
         formatString(stdout, fileInfo, fileName); // format the data in fileInfo and print to terminal
      }   
   }   
   fprintf(stdout,"total %d\n", totalBlockCount); // print the total block count of the directory to the terminal
   closedir(dir);
}

void exit_shell() {
	print_cmd_history();							// print command history to terminal
	list_to_terminal();								// print current directory to terminal
	printf("\nPress [Return] key to exit shell. ");	// ask for RETURN key
	while(getchar()!='\n'); 						// to clear stdin
	getchar(); 										// wait for RETURN
	printf("\n");
	exit(0);										// exit from shell process
}
