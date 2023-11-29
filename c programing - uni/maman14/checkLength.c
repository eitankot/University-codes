#include "asembler.h"

/*
checks the length of the file and reports if they are are above the limit.
@param char pathName[] - the path name to check.
@return true if all the lines are below the limit.

*/
int checkLengthOfFile(char pathName[]){
	FILE *fd;
	char oldPathName[strlen(pathName)]; /*starts to read the after macrofixer file*/
	strcpy(oldPathName, pathName);
	strcat(oldPathName, ".as");
	fd = fopen(oldPathName, "r");
	
	int counter = 0, line =1;
	int ch;
	while((ch=fgetc(fd))!=EOF){
		counter++;
		if(counter > MAX_PER_LINE-1){
			printf("error in line %d\t-length is more than a line can have.\n", line);
			return false;
		}
		if(ch == '\n'){
			line++;
			counter=0;
		}
	}
	fclose(fd);
	return true;
}

