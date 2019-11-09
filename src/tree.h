#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void tree() {
    char dirname[128] = "./Dir0";
    char *path = dirname;
    //sytem call to create Dir0
    int check = mkdir(path, 0700);

    if(!check) {
        //Dir0 created

        //change working directory to Dir0
        chdir(path);
        //create 3 empty text files 
        FILE *fp = fopen("t1.txt", "w+");
        FILE *fp2 = fopen("t2.txt", "w+");
        FILE *fp3 = fopen("t3.txt", "w+");

        if(!fp && !fp2 && !fp3) {
            printf("Error in file creation\n");
        }
        //close all the files
        fclose(fp);
        fclose(fp2);
        fclose(fp3);

        char dirname[128] = "./Dir1";
        char *path = dirname;
        //sytem call to create Dir1
        mkdir(path, 0700);
    } else {
        //Dir0 already existed
        printf("%s unable to create %s\n", dirname);
    }
}
