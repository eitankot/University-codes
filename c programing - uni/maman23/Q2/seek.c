#include "seek.h"
void checkFiles(int limit, char *files[],int seekIndex);
/*
this main function gets the arguments and checks if they are fine to use on the file and calles the filechecker.
@param argc the number of arguments that called into the function.
@param argv - a pointer into a list of the arguments. 
*/
int main(int argc, char *argv[]){
	char tmpString [100];
	tmpString[0] = '\0';
	int seekIndex;
	
	printf("calculating the index in the selected files\n");
	if(argc < 3){/*if there are less than 3 parameters that means if there are less than the number to seek the code name and one file*/
		printf("there is less parameters than needed.\n");
		exit(0);
	}
	sscanf(argv[1],"%d %s", &seekIndex, tmpString);/*seperates the string from the number*/
	if(seekIndex <= 0 || tmpString[0]!='\0' ){/*checks if the index is more than 0 and without a string that its not a number*/
		printf("invallied index please, please enter a number that is greater than 0.\n");
		exit(0);
	}
	checkFiles(argc, argv,seekIndex-1);
	return 1;
}

/*
this function checks all the files and seeks into the selcted index or prints an error if it can't.
@param limit the number of arguments that called into the function.
@param files - a pointer into a list of the arguments. 
@param seekIndex - the index that we need to seek and get the char.
*/
void checkFiles(int limit, char *files[],int seekIndex){
	FILE *fd;
	int i;
	char ch;
	int endPosition;
	
	for(i = 2; i<limit; i++){/*checks all the files in the code*/
		if(!(fd = fopen(files[i],"r"))){/*checks if it can open the file*/
			printf("can't open the file\n the name of the file %s\n", files[i]);
		}
		else{
			fseek(fd, 0, SEEK_END);/*finds the end of the file*/
			endPosition = ftell(fd);
			
			fseek(fd, seekIndex, SEEK_SET);/*find the char in the index of the file.*/
			if(seekIndex >= endPosition)/*checks if the position of the end is lower than the seek that we wanted to do*/
			{
				printf("the character index is lower than the index that you entered, please try a lower index.\n");
			}
			else{/*if we can do the seek*/
				ch = fgetc(fd);
				printf("\nin file number #%d the char is: %d\n",i-1,ch);
			}
			fclose(fd);
		}
	}
}
