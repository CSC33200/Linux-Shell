#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void path() {
    //find th current path
   char cwd[100000];
   getcwd(cwd, sizeof(cwd));
   printf("Current working dir: %s\n", cwd);

   //open file t2.txt and write the current path into it
   FILE *fptr;
   fptr = fopen("t2.txt", "w+");
   if(fptr == NULL)
   {
      printf("Unable to open t2.txt\n");   
            
   }

   fprintf(fptr,"%s",cwd);
   fclose(fptr);

   //rename to file t2.txt to path-info.txt
   char oldname1[] = "t2.txt";
   char newname1[] = "path-info.txt";
   if(rename(oldname1, newname1)==1){
       printf("fail to renamed t2.txt to path-info.txt\n");
   }

  //concatenate path-info.txt and tree.txt into t3.txt
  //open two file for read
   FILE *fp1 = fopen("tree.txt", "r"); 
   FILE *fp2 = fopen("path-info.txt", "r");  
   //open the file for write
   FILE *fp3 = fopen("t3.txt", "w"); 

   char c; 
  
   if (fp1 == NULL || fp2 == NULL || fp3 == NULL) 
   { 
         printf("Could not open files\n"); 
        
   } 
  
   // Copy contents of first file to file3.txt 
   while ((c = fgetc(fp1)) != EOF) 
      fputc(c, fp3); 
  
   // Copy contents of second file to file3.txt 
   while ((c = fgetc(fp2)) != EOF) 
      fputc(c, fp3); 
  
   fclose(fp1); 
   fclose(fp2); 
   fclose(fp3); 

   //rename t3.txt to log.txt
   char oldname2[] = "t3.txt";  
   char newname2[] = "log.txt";
   rename(oldname2, newname2);
    if(rename(oldname2, newname2)==1){
       printf("fail to renamed t3.txt to log.txt\n");
   }

   remove("tree.txt");
   remove("path-info.txt");
}