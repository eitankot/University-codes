#include "asembler.h"

#define MAX_LINES_PER_MACRO 6

enum status {noMacro, trigeredMacro, copyingMacro};

typedef struct linkedMacro * ptr;/*the linked macro list*/
typedef struct linkedMacro{
	char macroName [MAX_PER_LINE];
	char macroContext[MAX_LINES_PER_MACRO][MAX_PER_LINE];
	ptr next;
}item;


ptr macroHead = NULL;
/*prototype of the functions*/
void printToFileTheMacro(char tmpStr[],FILE *fileToWork);
int vallidMacroName(char str[], ptr *hptr);
void initMacroName(char str[], ptr *hptr);
ptr findMacro(char str[],ptr macro, ptr *hptr);
void addLineToMacro(char tmpStr[], ptr *hptr);
void normalPrintToFile(char tmpStr[], FILE *fileToWork);

/*checks is its a macro thats in the macro list
@param char str[] - the string to check if its in the macro list.
@param ptr *hptr - the head of the macro list.
@return true if its in the macro list
*/
int vallidMacroName(char str[], ptr *hptr){
	ptr cur = *hptr;
	while(cur != NULL){
		if(strcmp(str, cur->macroName)==0){
			return true;
		}
		cur = cur->next;
	}
	return false;
	
}
/*add to the macro list the macro name
@param char str[] - the name of the macro.
@param ptr *hptr - the head of the macro list.
*/
void initMacroName(char str[],ptr *hptr){
	ptr p1, p2;
	ptr t;
	t = (ptr)malloc(sizeof(item));
	if(!t){
		printf("cannot build list \n");
		exit(0);		
	}
	strcpy(t -> macroName,str);
	t->next = NULL;
	p1 = *hptr;
	while((p1)){/*moves on the macro to fined the last part of it*/
		p2=p1;
		p1=p1->next;
	}
	if(p1 == *hptr){
		macroHead = t;
		t->next = p1;
	}
	else{
		p2->next = t;
	}
}

/*finds the macro with the same name.
@param char str[] - the name to fined the macro.
@param ptr macro - the macro to set into when it finds the name.
@param ptr *hptr - the head of the macro list.
@return the macro node of the selected name.
*/
ptr findMacro(char str[],ptr macro,ptr *hptr){
	ptr cur = *hptr;
	while(cur != NULL){
		if(strcmp(str, cur->macroName)==0){
			macro = cur;
		}
		cur = cur->next;
	}
	return macro;
}

/*prints to file the macro
@param char tmpStr[] - the name of the macro to change.
@param FILE *fileToWork - file to work with and print into it.
*/
void printToFileTheMacro(char tmpStr[], FILE *fileToWork){
	int i;
	ptr macro = (ptr)malloc(sizeof(item));
	macro = findMacro(tmpStr, macro, &macroHead);
	for(i=0; i< MAX_LINES_PER_MACRO; i++){
		if(macro->macroContext[i][0] != '\0'){
			fprintf(fileToWork, "%s\n", macro->macroContext[i]);
		}
	}

}


/*adds a line to the macro content
@param char tmpStr[] - the line to add.
@param ptr *hptr - the head of the macro file.
*/
void addLineToMacro(char tmpStr[], ptr *hptr){
	ptr cur = *hptr;
	while(cur->next != NULL){
			cur= cur->next;}
	int i;
	for(i=0; i<MAX_LINES_PER_MACRO; i++){
		if(cur->macroContext[i][0] == '\0'){
			strcpy(cur->macroContext[i], tmpStr );
			return;
		}
	}
}
/*prints to file in normal way
@param char tmpStr[] - the line to add.
@param FILE *fileToWorkr - file to work with and print into it.
*/
void normalPrintToFile(char tmpStr[], FILE *fileToWork){
	fprintf(fileToWork, "%s", tmpStr);
}

/*fixes the macro and turns the asembly code to be without macros
@param char pathName - the path to work with.

*/
void macroFixer(char pathName[])
{

	FILE *fd, *fileToWork;/*creates the files to work with*/
	char oldPathName[strlen(pathName)]; 
	char newPathName[strlen(pathName)];
	strcpy(oldPathName, pathName);
	strcpy(newPathName, pathName);
	strcat(oldPathName, ".as");
	strcat(newPathName, ".am");
	fd = fopen(oldPathName, "r");
	fileToWork = fopen(newPathName, "w");
	
	
	int i,j;
	
	char line[MAX_PER_LINE];
	char tmpStr[MAX_PER_LINE];

	
	int state = noMacro;

	tmpStr[0] = '\0';
	line[0] = '\0';
	while(fgets(line, MAX_PER_LINE, fd) != NULL)/*reads the line of the file*/
	{
		tmpStr[0] = '\0';
		j=0;
		for(i=0; i<strlen(line); i++){/*reads text line char by char*/
			switch(state){
			
			case noMacro:{/*no macro*/
				if(line[i] == ' ' || line[i] == '\t' || line[i] == '\n'){/*if its a white space*/
					
					if(vallidMacroName(tmpStr, &macroHead)){/*if it was a macro that created before*/
						printToFileTheMacro(tmpStr, fileToWork);
					}
					else if(strcmp(tmpStr, "macro")==0){/*if its createing a new macro*/
						
						state= trigeredMacro;
						j = 0;
					}
					else{/*a normal white space*/
						tmpStr[j] = line[i];
						tmpStr[j+1] = '\0';
						normalPrintToFile(tmpStr ,fileToWork);
					}
					tmpStr[0] = '\0';
					j=0;
				
				}
				else{/*not a white space*/

					tmpStr[j] = line[i];
					tmpStr[j+1] = '\0';
					j++;
				}
				break;

			}
			case copyingMacro:{/*copying the macro*/
				if(line[i] == '\n'){
					if(strcmp(tmpStr, "endm")==0){/*checks if its the end of the macro*/

						state = noMacro;
					}
					else{/*add the line to the macro*/

						addLineToMacro(tmpStr, &macroHead);
					}
					tmpStr[0] = '\0';
				}
				else{/*normal char*/
					tmpStr[j] = line[i];
					tmpStr[j+1] = '\0';
					j++;
				}
			break;	
			}
			case trigeredMacro:{/*copying the macro name*/
				if(line[i] == '\n'){/*add the macro name to the linked list*/
					initMacroName(tmpStr, &macroHead);
					tmpStr[0] = '\0';
					state = copyingMacro;
				}
				else{/*adds to the name*/
					tmpStr[j] = line[i];
					tmpStr[j+1] = '\0';
					j++;
				}
			break;
			}
			
			}
		}
	}

	fclose(fd);/*closes the file*/
	fclose(fileToWork);
}
