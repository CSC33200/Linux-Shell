#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h> 
#include "tree.h"
#include "list.h"
#include "path.h"
#include "exit.h"

#define clear() printf("\033[H\033[J") 

int main() {
	//initialize the shell
	clear();
	char username[100];
	printf("Enter username: ");
	scanf("%s", username);
	sleep(1);
	clear();
	
	//list of commands
	char* ListOfOwnCmds[4];
	ListOfOwnCmds[0] = "tree"; 
	ListOfOwnCmds[1] = "list"; 
	ListOfOwnCmds[2] = "path"; 
	ListOfOwnCmds[3] = "exit"; 	
	
	while(1) {
		//get curent working directory
		char cwd[1000];
		getcwd(cwd, sizeof(cwd));
		
		//get the command from the user
		char buf[100]; 
		printf("\n%s@%s>> ", username, cwd);
		scanf("%s", buf);
						
		//match the command with the one that the user entered
		int cmd = 4;
		for(int i=0; i<4; i++) {
			if(strcmp(ListOfOwnCmds[i],buf) == 0) {
				cmd = i;
				update_history(buf); // if a command is entered save it to history for exit function
				break;
			}
		}
		
		//choose the command to run
		switch(cmd) {
			case 0:
				tree();
				break;
			case 1:
				list();
				break;
			case 2:
				path();
				break;
			case 3:
				exit_shell();
				break;
			case 4:
				printf("Use a valid command");
				break;
		}
	}	

	return 0;
}