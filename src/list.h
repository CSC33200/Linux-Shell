#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

// Formats the timespect to a readable string in a date time format 
char* formatTime(struct timespec time){
   char formatedDate[100];
   strftime(formatedDate, 100 , "%b %d %y %R ", gmtime(&time.tv_sec));
   return formatedDate;
}

// Format the struct stat with a file name and outputs to the file provided 
char* formatString(FILE* output, struct stat buffer, char* name){
   
   fprintf(output,"%d ",buffer.st_nlink);
   fprintf(output,"%s ", getpwuid(buffer.st_uid)->pw_name);
   fprintf(output,"%s ",getgrgid(buffer.st_gid)->gr_name);
   fprintf(output,"%d ",buffer.st_size);
   fprintf(output,"%s ",formatTime(buffer.st_mtim));
   fprintf(output,"%s\n",name);

}

void list() {

   printf("\033c"); // Clear the terminal screen

   char path[100];
   getwd(path); // Gets the path to the current directory

   DIR *dir = opendir(path);

   if (dir == NULL) {
      printf("Error Directory couldn't be opened");
      return;
   }

   // Get the t1 file and open it
   FILE *t1; 
   t1 = fopen("t1.txt", "w");

   if(t1 == NULL) {
      printf("Couldn't open t1.txt\n");   
      closedir(dir);
      return;
   }

   int totalBlockCount = 0;
   struct dirent *de;

   while((de = readdir(dir)) != NULL){ // While loop to read each file in the directory 
      char* fileName = de->d_name;

      if(strcmp(fileName, ".") != 0 && strcmp(fileName, "..") != 0 ){  // ignore . and .. 

         // Creating the filepath for each item
         char filePath[1000]; 
         sprintf(filePath, "%s%s%s", path,"/",fileName);

         struct stat fileInfo; // struct stat that store the files info
         stat(filePath, &fileInfo); // system call to get the information about the filepath provided
         
         totalBlockCount += fileInfo.st_blocks; // keep count of total number of file system blocks

         // format the data in fileInfo and print to terminal and t1.txt
         formatString(stdout, fileInfo, fileName); 
         formatString(t1, fileInfo, fileName); 
      }
   
   }

   // print the total block count of the directory to the terminal and t1.txt
   fprintf(stdout,"total %d\n", totalBlockCount); 
   fprintf(t1,"total %d\n", totalBlockCount); 
      
   fclose(t1); 

   if( rename("t1.txt", "tree.txt") == 1 ) { // rename the file t1.txt to tree.txt print if it failed
       printf("Failed to renamed t1.txt to log.txt\n");
   }

   closedir(dir); 
}
