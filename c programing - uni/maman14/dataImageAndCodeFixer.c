#include "asembler.h"
/*
gets the next IC in the code list.
@param ptrCode *codeHead - the code head linked list .
@param int IC- the last IC.
@return the next IC in the code.

*/
int getIC(ptrCode *codeHead, int IC){
	ptrCode p1 = *codeHead;
	while(p1){
		if(IC<(p1->IC)){
			return p1->IC;
		}
		p1=p1->next;
	}
	return 0;
}


/*
checks if its a vallied label name.

@param ptrSymbol *hptr - the head of the linked list
@param char labelname[] - the label name to check
@param int line - the line of the code
@return true if its a vallied name.
*/
int isVallidLabelName(ptrSymbol *hptr, char labelname[], int line){
	char blockedList[][5] = {"r0","r1", "r2", "r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15","mov","cmp","add","sub","lea","clr","not","inc","dec","jmp","bne","jsr","red", "prn" , "rts", "stop"};
	ptrSymbol p1, p2;
	int i;
	int blockedListLen = 32;
	for(i=0; i<blockedListLen; i++){/*checks if its not a blocked name by registers or commands*/
		if(strcmp(blockedList[i], labelname)== 0){
			printf("error in line: %d\t- invallied name for the label.\n", line);
			return false;
		}
	}
	p1 = *hptr;
	while(p1){/*checks if its not a blocked name by other label that registered*/
		p2=p1;
		p1= p1->next;
		if(strcmp(p2->name, labelname)==0){
			printf("error in line: %d\t- invallied name for the label.\n", line);
			return false;
		}
	}
	return true;
}

/*
checks if its a vallied label name.
@param ptrData *dataHead - the head of the linked list
@param char dataName[] - the data name to check
@param int IC - the IC if the line
@param char line[] - the line of the text
@param int i - the index to start check from.
@param ptrBinaryD *tmpBinaryHead - the head of the linked list
@return a number that represents the number of line that we used in the text.
*/
int checkLengthOfData(ptrData *dataHead,char dataName [],int IC ,char line[],int i,ptrBinaryD *tmpBinaryHead){
	int j, counter =0;
	int c;
	char str[MAX_PER_LINE];
	if(strcmp(dataName, ".string")==0){/*if its a string command*/
		int hadApostrophe = false;
		int hadBeforeApostrophe = false;
		for(j=i; j<strlen(line); j++){
			if(line[j]=='"'){
				if(hadApostrophe){/*if it had apostrophe (")*/
					c = 0;
					counter++;
					initBinaryList(tmpBinaryHead, c);
					hadApostrophe = false;}
				else{
					if(!hadBeforeApostrophe){
						hadApostrophe = true;
						hadBeforeApostrophe = true;}
					else{
						return counter;}
				}
			}
			else if(hadApostrophe){/*in the string*/
				c = line[j];
				counter++;
				initBinaryList(tmpBinaryHead, c);
			}
			else if(line[j]== ' ' || line[j]== '\t' || line[j]== '\n'){/*white space*/
				if(line[j]== '\n'){
					if(tmpBinaryHead!=NULL){
						return counter;}
					else{
						return -1;
					}
				}
			}
			else{
				counter = -1;
				return counter;
			}
		}
	}
	else{
		int hadComma = true;
		int hadWritten = false;
		int k = 0;
		str[0] = '\0';
		for(j=i; j<strlen(line); j++){
			if(hadComma){
				if(!hadWritten && (line[j]=='+' || line[j]=='-')){/*if it a plus of minus*/
					hadWritten = true;
					if(line[j]=='-'){
						str[0] = '-';
						str[1] = '\0';
						k++;
					}
				}
				else if(isdigit(line[j])){/*if it a number*/
					hadWritten = true;
					str[k] = line[j];
					str[k+1] = '\0';
					k++;
				}
				else if(line[j]==','){/*if it comma*/
					if(((str[0] =='-' || str[0] =='+')&& str[1]=='\0')){
						return -1;}
					hadWritten = false;
					c = atoi(str);
					initBinaryList(tmpBinaryHead, c);
					counter++;
					k=0;
					str[0] = '\0';
				}
				else if(line[j]==' ' || line[j]=='\t' ){/*if it a white space*/
					if(hadWritten){
						hadComma = false;
						c = atoi(str);
						initBinaryList(tmpBinaryHead, c);
						k=0;
						str[0] = '\0';}
				}
				else if(line[j]=='\n'){/*if it the end of the line*/
					if(((str[0] =='-' || str[0] =='+')&& str[1]=='\0')){
						return -1;}
					if(tmpBinaryHead!=NULL && hadWritten){
						c = atoi(str);
						initBinaryList(tmpBinaryHead, c);
						counter++;
						return counter;}
					else{
						return -1;
					}
				}
				else{
					return -1;
				}
			}
			else{
				if(line[j]==','){/*if it a comma*/
					k=0;
					counter++;
					hadComma = true;
					hadWritten = false;
				}
				else if(line[j]=='\t' || line[j]==' ' ||line[j]== '\n'){/*if it the end of the line or white space*/
					k = 0;
					if(line[j]== '\n'){
						if(hadWritten){
							counter++;
							return counter;
						}
						else{
							return -1;
						}
					}
				}
				else{
					return -1;
				}
			}
		}
	}
	return -1;
}
