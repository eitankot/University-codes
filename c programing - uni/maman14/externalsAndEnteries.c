#include "asembler.h"
/*
this function prints the enteries to the function 
@param char pathName[] - the path to print the enteries
@param ptrSymbol *symbolHead - the head to the symbol linked list

*/
void printEnteries(char pathName[], ptrSymbol *symbolHead){
	FILE *fd;
	char newPathName[strlen(pathName)];
	strcpy(newPathName, pathName);
	strcat(newPathName, ".ent");
	fd = fopen(newPathName, "w");
	int hadEntry = false;
	
	ptrSymbol p1 = *symbolHead;
	while(p1){/* checks all the nodes in the list*/
		if(p1->attribute == entry){
			fprintf(fd, "%s,%d,%d\n",p1->name, p1->baseAddress, p1->offset);
			hadEntry = true;
		}
		p1 = p1->next;
	}
	fclose(fd);
	if(hadEntry){/* checks if it printed to the file entery*/
		return;
	}
	remove(newPathName);/* remove if its empty*/
}

/*
this function prints the externals to the function 
@param char pathName[] - the path to print the enteries
@param ptrExternal *externalHead - the head to the external linked list

*/
void printExternals(char pathName[], ptrExternal *externalHead){
	FILE *fd;
	char newPathName[strlen(pathName)];
	strcpy(newPathName, pathName);
	strcat(newPathName, ".ext");
	fd = fopen(newPathName, "w");
	
	int hadExternal = false;
	ptrExternal p1 = *externalHead;
	while(p1){/* checks all the nodes in the list*/
			fprintf(fd, "%s BASE: %d\n",p1->name, (p1->headExt)->base);
			fprintf(fd, "%s OFFSET: %d\n\n", p1->name, (p1->headExt)->offset);
			hadExternal = true;
			p1=p1->next;
		}
	fclose(fd);
	if(hadExternal==true){/* checks if it printed to the file external*/
		return;
	}
	remove(newPathName);/* remove if its empty*/
	
	
}

/*
this fucntion gets the external name to put in the symbol list.
@param char labelName[] - the label to save in.
@param char line[] - the line that we need to work on.
@param int i - the index to start with.

*/
void getExternals(char labelName[] ,char line[], int i){
	int j, k=0;
	labelName[0] = '\0';
	int hadWriten = false;
	int usedSpaceInWord= false;
	for(j=i; j<strlen(line); j++){/*moves from the index that gave.*/
		if(line[j]== ' '||line[j]== '\t'|| line[j]== '\n'){/*check if its a white space.*/
			if(hadWriten && (line[j]== ' ' || line[j]== '\t')){
				usedSpaceInWord=true;
			}
			else if(line[j]== '\n'){
				return;
			}
		}
		else{/*adds to the label name if its llegal*/
			if(!usedSpaceInWord){
				hadWriten=true;
				labelName[k]=line[j];
				labelName[k+1] ='\0';
				k++;}
			else{
				labelName[0]='\0';
				return;
			}
		}
	}
}

/*
this fucntion gets the enteries name to put in the symbol list.
@param char labelName[] - the label to save in.
@param char line[] - the line that we need to work on.
@param int i - the index to start with.

*/
void getEnteries(char labelName[] ,char line[], int i){
	int j, k=0;
	labelName[0] = '\0';
	int hadWriten = false;
	int usedSpaceInWord= false;
	for(j=i; j<strlen(line); j++){/*moves from the index that gave.*/
		if(line[j]== ' '||line[j]== '\t'|| line[j]== '\n'){/*check if its a white space.*/
			if(hadWriten && (line[j]== ' ' || line[j]== '\t')){
				usedSpaceInWord=true;
			}
			else if(line[j]== '\n'){
				return;
			}
		}
		else{/*adds to the label name if its llegal*/
			if(!usedSpaceInWord){
				hadWriten=true;
				labelName[k]=line[j];
				labelName[k+1] ='\0';
				k++;}
			else{
				labelName[0]='\0';
				return;
			}
		}
	}
}

/*
this fucntion checks if the label is in external linked list.
@param char labelName[] - the label to check.
@param ptrSymbol *hptr - the head of the symbol linked list.
@return - true if the symbol is in the list and external
*/
int isLabelExternal(char labelName[], ptrSymbol *hptr){
	ptrSymbol p1 = *hptr;
	while(p1){
		if(strcmp(p1->name, labelName)==0){
			if(p1->attribute==external){
				return true;
				}
		}
		p1=p1->next;
	}
	return false;
}

/*
this fucntion checks if the label is in symnol linked list.
@param char labelName[] - the label to check.
@param ptrSymbol *hptr - the head of the symbol linked list.
@return - true if the symbol is in the list
*/
int isLabelInSymbol(char labelName[], ptrSymbol *hptr){
	ptrSymbol p1 = *hptr;
	while(p1){
		if(strcmp(p1->name, labelName)==0){
			return true;}
		p1=p1->next;
	}
	return false;
}


/*
changes the type of the symbol to entry.
@param char labelName[] - the label to check.
@param ptrSymbol *hptr - the head of the symbol linked list.

*/
void changeTypeToEntry(char labelName[], ptrSymbol *hptr){
	ptrSymbol p1 = *hptr;
	while(p1){
		if(strcmp(p1->name, labelName)==0){
			p1->attribute=entry;}
		p1=p1->next;
	}
}

