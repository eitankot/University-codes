#include "asembler.h"
/*
gets the number for the immidiate address
@param char str[] - the string to check
@param int i - index to check from.
*/
unsigned int getNum(char str[], int i){
	int j,k=0;
	char tmpStr[MAX_PER_LINE];
	unsigned int num;
	tmpStr[0] = '\0';
	for(j=i; j<strlen(str); j++){
		if(str[j]==' ' || str[j]=='\t' || str[j]=='\n'|| str[j]==','){
			j=j;
		}
		else{
			tmpStr[k] = str[j];
			tmpStr[k+1] = '\0';
			k++;
		}
	}
	num=atoi(tmpStr);
	return num;
}

/*
gets the label before the brackets
@param char tmpStr[] - the string to check
@param labelName - the label name.
*/
void getBeforeBrackets(char tmpStr[],char labelName[]){
	int i, k=0;
	for(i=0; strlen(tmpStr); i++){
		if(tmpStr[i] == ' ' || tmpStr[i] == '\n' || tmpStr[i] == '\t' || tmpStr[i] == ','){}
		else if(tmpStr[i]=='['){
			return;
		}
		else{
			labelName[k] = tmpStr[i];
			labelName[k+1] = '\0';
			k++;
		}
	}
}

/*
gets the base if the symbol
@param char labelName[] - the label name
@param ptrSymbol *symbolHead - the head of the linked list.
@return a number that represents the base.
*/
int getBase(char labelName[],ptrSymbol *symbolHead){
	ptrSymbol p1 = *symbolHead;
	while(p1){
		if(strcmp(p1->name, labelName)==0){
			return p1->baseAddress;}
		p1=p1->next;
	}
	return 0;
}
/*
gets the offset if the symbol
@param char labelName[] - the label name
@param ptrSymbol *symbolHead - the head of the linked list.
@return a number that represents the offset.
*/
int getOffset(char labelName[],ptrSymbol *symbolHead){
	ptrSymbol p1 = *symbolHead;
	while(p1){
		if(strcmp(p1->name, labelName)==0){
			return p1->offset;}
		p1=p1->next;
	}
	return 0;
}

/*
checks if the label is in the external list.
@param char labelName[] - the label name
@param ptrExternal *hptr - the head of the linked list.
@return true if its in the external list
*/
int isExternalWritten(char labelName[], ptrExternal *hptr){
	ptrExternal p1 = *hptr;
	while(p1){
		if(strcmp(p1->name, labelName)==0){
			return true;}
		p1=p1->next;
	}
	return false;
}
/*
checks if its a direct register.
@param char str[] - the register name
@return true if its a direct register
*/
int directChecker(char str[]){
	char commandNameList[][5] = {"r0","r1", "r2", "r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15"};
	int commandNameListLen = 16;
	int i;
	for(i=0; i<commandNameListLen ;i++){
		if(strcmp(commandNameList[i], str)== 0){
			return true;}
	}
	return false;
}

/*
builds the other binary word that left after the first move.
@param char commandName[] - the command name
@param char line[] - the line of the code.
@param int i - the index to start read from.
@param int IC - the IC
@param int lineOfCode - the line in the code.
@param ptrBinaryOp *otherBinaryWord - the head linked list of the other binary word.
@param ptrSymbol  *symbolHead- the head linked list of the symbol list.
@param ptrExternal *ExternHead - the head linked list of external list.
@param ptrValExt *ExternValHead - the head linked list of external val list.
@return true if there is no errors.
*/
int buildOtherBinary(char commandName[],char line[],int i, int IC,int lineOfCode,ptrBinaryOp *otherBinaryWord, ptrSymbol  *symbolHead,ptrExternal *ExternHead, ptrValExt *ExternValHead){
	int j, k=0, counter=0;
	int hadComma = true;
	int hadWritten = false;
	unsigned int tmpNum;
	char tmpStr[MAX_PER_LINE];
	char labelName[MAX_LABEL];
	tmpStr[0] = '\0';
	labelName[0] = '\0';
	for(j=i; j<strlen(line); j++){	
		if(hadComma){
			if(line[j]== ' ' || line[j]== '\t' || line[j]== '\n' || line[j]==','){/*if its a while space*/
					if(tmpStr[0]== '#'){/*immiditate address*/
						if(counter<1){
							counter++;
						}
						counter++;
						tmpNum = getNum(tmpStr, 1);
						initOpBinaryList( otherBinaryWord,tmpNum, 4);/*creates the binary list*/
						 
					}
					else if(hasBrackets(tmpStr)){/*checks direct index register*/
						getBeforeBrackets(tmpStr,labelName);
						if(isLabelInSymbol(labelName, symbolHead)){
							if(counter<1){
								counter++;
							}
							counter+=2;
							if(isLabelExternal(labelName, symbolHead)){/*checks if its an external label*/
								initlinkedValExt(ExternValHead, IC+counter-1);
								initlinkedExtern(ExternHead, labelName ,ExternValHead);
								initOpBinaryList(otherBinaryWord, getBase(labelName, symbolHead), 1);/*creates the binary list*/
								initOpBinaryList(otherBinaryWord,getOffset(labelName, symbolHead),1);/*creates the binary list*/
							}
							else{/*normal label*/
								initOpBinaryList(otherBinaryWord, getBase(labelName, symbolHead), 2);/*creates the binary list*/
								initOpBinaryList(otherBinaryWord,getOffset(labelName, symbolHead),2);}/*creates the binary list*/
						}
						else{
							printf("error in line %d\t-The label does not exits.\n", lineOfCode);
							return false;
						}
								
					}
					else if(strlen(tmpStr) > 0){
						if(directChecker(tmpStr)){/*check if its a direct register*/
							if(counter<1){
								counter++;}
						}
						else{
							if(isLabelInSymbol(tmpStr, symbolHead)){/*check if its a synbol*/
								if(counter<1){
								counter++;
								}
								counter+=2;
								if(isLabelExternal(tmpStr, symbolHead)){/*checks if its an external label*/

										initlinkedValExt(ExternValHead, IC+counter-1);
										initlinkedExtern(ExternHead, tmpStr ,ExternValHead);
										initOpBinaryList(otherBinaryWord, getBase(tmpStr, symbolHead), 1);/*creates the binary list*/
										initOpBinaryList(otherBinaryWord,getOffset(tmpStr, symbolHead),1);/*creates the binary list*/
									}
								else{/*normal label*/
								initOpBinaryList(otherBinaryWord, getBase(tmpStr, symbolHead), 2);/*creates the binary list*/
								initOpBinaryList(otherBinaryWord,getOffset(tmpStr, symbolHead),2);}/*creates the binary list*/
							}
							else{
								printf("error in line %d\t-The label does not exits.\n", lineOfCode);
								return false;
							}
						}
					}
					if(line[j]==','){/*if it starts another word*/
						hadWritten = false;
					}
					else if(line[j]=='\n'){/*if its the end of the list*/
						return true;
						
					}
					else{/*if its a white space without nothing*/
						if(hadWritten){
							hadComma=false;}
					}
					tmpStr[0] = '\0';
					k=0;
				}
			else{/*normal char*/
				hadWritten = true;
				tmpStr[k] = line[j];
				tmpStr[k+1] = '\0';
				k++;
			}
		}
		else{/*without comma*/
			if(line[j]== ' ' || line[j]== '\t' || line[j]== '\n'){
				if(line[j]== '\n'){
						return true;
				}
			}
			else if(line[j]== ','){
				hadComma = true;
				hadWritten = false;
				}
		}
	}
	return -1;
}
