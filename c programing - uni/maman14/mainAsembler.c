#include "asembler.h"

/*
this is the main function of the code.
@param int argc - the number of arguments.
@param char *argv[] - the list of parameters.
@return 0 if the code did not crush.
*/
int main(int argc, char *argv[]){
	if(argc <= 1){/*if there is no path file to use*/
		printf("error, there is no files selected.");
		exit(0);
	}
	int i;
	FILE *fd;
	char pathName [100];
	char tmpPathName [100];
	for(i=1; i<argc;i++){/*moves on all the files*/
		strcpy(pathName,argv[i]);
		strcpy(tmpPathName,argv[i]);
		strcat(tmpPathName, ".as");
		if(!(fd = fopen(tmpPathName,"r"))){/*if the file does not exists*/
			printf("can't use the selected file name(%s).\n", argv[i]);
			
		}
		else{
			printf("File:%s\n", pathName);/*starts to move on the file*/
			macroFixer(pathName);
			firstMove(pathName);
			printf("Done:%s\n", pathName);
			fclose(fd);
		}
	}
	return 0;
}
