#include "asembler.h"

operand operands = { NONE,0,NONE,0 };
/*
moves on all the file and checks if the whole file is fine to work with and makes the first and second move of the asembler.
@param char pathName[] - the path name to use.

*/
void firstMove(char pathName[]){
	FILE *fd;
	char oldPathName[strlen(pathName)]; /*starts to read the after macrofixer file*/
	strcpy(oldPathName, pathName);
	strcat(oldPathName, ".am");
	fd = fopen(oldPathName, "r");
	
	int errorType = false;/*creates the booleans*/
	int commentMode = false;
	int isWritten = false;
	
	char labelName[MAX_LABEL];
	int hasLabel = false;
	
	ptrData dataHead = NULL;/*sets all the linked lists*/
	ptrCode codeHead = NULL;
	ptrSymbol symbolHead = NULL;
	ptrBinaryD tmpBinaryHead;
	ptrBinaryC tmpSecondBinaryHead;
	ptrBinaryOp	tmpOpBinaryHead;
	
	ptrExternal externHead=NULL;
	ptrValExt ExternValHead;
	ptrBinaryOp	otherBinaryWord;
	
	int IC = 100;/*sets the parameters of the code*/
	int DC=0;
	int lineOfCode = 0;
	int L=0;
	
	char line[MAX_PER_LINE];
	char tmpStr[MAX_PER_LINE];
	
	int j,i;
	
	int sum = 0;
	
	tmpStr[0] = '\0';
	line[0] = '\0';
	if(!checkLengthOfFile(pathName)){/*return if there are an error*/
		fclose(fd);
		remove(oldPathName);
		return;
	}
	while(fgets(line, MAX_PER_LINE, fd) != NULL)/*moves on all the file.*/
	{
	
		tmpStr[0] = '\0';/*reset all the needed things for the run of the line*/
		labelName[0]='\0';
		j=0;
		lineOfCode++;
		L=0;
		isWritten = false;
		hasLabel = false;
		operands.firstOperand =NONE;
		operands.secondOperand =NONE;
		operands.destRegister = 0;
		operands.sourceRegister =0;
		tmpBinaryHead = NULL;
		tmpSecondBinaryHead = NULL;
		tmpOpBinaryHead = NULL;
		
		for(i=0; i<strlen(line); i++){/*moves on every char on the line*/
			if(!commentMode){/*checks if its not a commant mode*/
				if(line[i] == ';' && !isWritten){/*starts comment mode*/
					commentMode = true;
					tmpStr[0] = '\0';
					j=0;}
				else if(line[i]==':'){/*label mode*/
					hasLabel = true;
					if(strlen(tmpStr) > 31){/*checks if its a fine label*/
						printf("error in line %d\t-length is more than label can have.\n", lineOfCode);
						errorType = true;
						break;
					}
					else{
						strcpy(labelName , tmpStr);/*saves the label*/
					}
					tmpStr[0] = '\0';
					j=0;
				}
				else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'){/*check if its done to write the command/data/blank line*/
					if(strcmp(tmpStr, ".string") == 0 ||strcmp(tmpStr, ".data") == 0){/*if its a data command*/
						if(hasLabel){/*if a label was before*/
							if(!isVallidLabelName(&symbolHead ,labelName, lineOfCode)/*checks if its a vallied name for a label*/){
								printf("error in line %d\t-The label is already exists or it's a locked name.\n", lineOfCode);			
								errorType = true;
								break;}
							else{/*start to create the data*/
								initLabel(&symbolHead,labelName ,".data",IC);
								sum = checkLengthOfData(&dataHead, tmpStr ,IC , line, i, &tmpBinaryHead);
								if(sum == -1){
									printf("error in line %d\t-The data has a syntex error.\n", lineOfCode);			
									errorType = true;
									break;
								}
								initlinkedData(&dataHead,IC, sum, &tmpBinaryHead);
								DC+= sum;
								IC+= sum;
								
								break;
							}
						}
						else{/*if tere is no label before*/
							sum = checkLengthOfData(&dataHead,tmpStr ,IC , line, i, &tmpBinaryHead);/*check if the data has no errors there*/
							if(sum == -1){
									printf("error in line %d\t-The the data has a syntex error.\n", lineOfCode);			
									errorType = true;
									break;
							}
							initlinkedData(&dataHead,IC, sum, &tmpBinaryHead);/*creates the list*/
							DC+= sum;
							IC+= sum;
							break;
						}					
					}
					else if(strcmp(tmpStr, ".extern") == 0 ){/*extern move*/
						getExternals(labelName ,line, i);/*gets the external parameter*/
						if(labelName[0] == '\0'){/*if there are no parameter after the extern*/
							printf("error in line %d\t-you can't use this label name please try another one.\n", lineOfCode);
							errorType = true;
							break;
						}
						else if(!isVallidLabelName(&symbolHead ,labelName, lineOfCode)){/*checks if its a vallied name to use.*/
							errorType = true;
							break;
						}
						initLabel(&symbolHead,labelName ,".extern",0);/*creates the external value*/
						DC++;
						break;
					}
					else if(strcmp(tmpStr, ".entry") == 0){/*checks if its an entry*/
						break;
					}
					else{/*command mode or blank mode*/
						if(tmpStr[0] != '\0'){/*command mode*/
							if(hasLabel){/*checks if there is a label*/
								if(!isVallidLabelName(&symbolHead ,labelName, lineOfCode)){
									errorType = true;
									break;
								}
								initLabel(&symbolHead,labelName ,".code",IC);/*creates the label*/
							}
							if(!checkValliedCommand(tmpStr)){/*checks if its a vallied command*/
								printf("error in line %d\t-invallid command name.\n", lineOfCode);
								errorType = true;
								break;
							}
							else{
								L = checkOperands(tmpStr, line, i, lineOfCode, &operands);/*checks the amount of operands and sends an error if there are incorrect operand in the code*/
								if(L == -1){
									errorType = true;
									break;
								}

								buildBinaryCode(tmpStr ,&tmpOpBinaryHead, &tmpSecondBinaryHead, &operands); /*builds the binary code in the code list*/
								initlinkedCode(&codeHead, IC, L, &tmpSecondBinaryHead, &tmpOpBinaryHead);/*add to the code linked list the corrent code*/
								IC += L;
								break;
							}
						}/*blank line*/
						tmpStr[0] = '\0';
						j=0;
					}
				}
				else{/*if its not a white space or a special char*/
					isWritten = true;
					tmpStr[j]=line[i];
					tmpStr[j+1]='\0';
					j++;
				}
			}
			else{/*if its a comment mode*/
				if(line[i] == '\n'){
					commentMode = false;
				}
			}
		}
	}
	if(errorType){/*return if there are an error*/
		fclose(fd);
		remove(oldPathName);
		return;
	}
	/*second move*/
	IC = 0;/*init the paramerers*/
	lineOfCode = 0;	
	tmpStr[0] = '\0';
	line[0] = '\0';
	fseek(fd, SEEK_SET, 0);
	while(fgets(line, MAX_PER_LINE, fd) != NULL)/*reads the line*/
	{		
		tmpStr[0] = '\0';/*init the parameters in the line*/
		labelName[0]='\0';
		j=0;
		lineOfCode++;
		isWritten = false;
		otherBinaryWord =NULL;
		ExternValHead=NULL;
		for(i=0; i<strlen(line); i++){/*moves on every char in the line*/
			if(!commentMode){/*not a comment mode*/
				if(line[i] == ';' && !isWritten){/*checks if its a comment mode*/
					commentMode = true;
					tmpStr[0] = '\0';
					j=0;}
				else if(line[i]==':'){/*checks label*/
					tmpStr[0] = '\0';
					j=0;
				}
				else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'){/*checks white spaces*/
					if(strcmp(tmpStr, ".string") == 0 ||strcmp(tmpStr, ".data") == 0){/*if its a data line*/
						break;
					}
					else if(strcmp(tmpStr, ".extern") == 0 ){/*if its an external line*/
						break;
					}
					else if(strcmp(tmpStr, ".entry") == 0){/*if its an entry line*/
							getEnteries(labelName, line, i);/*get the entery name*/
							if(isLabelInSymbol(labelName, &symbolHead)){/*checks if its in hte list of symbols*/
								changeTypeToEntry(labelName, &symbolHead);/*changes the type of the entery*/
								break;
							}
							else{
								printf("error in line %d\t-entry is not registered.\n", lineOfCode);
								errorType = true;
								break;
							}
					}
					else{
						if(tmpStr[0] != '\0'){/*if its not a white space*/
							IC = getIC(&codeHead , IC);/*get the next IC*/
							buildOtherBinary(tmpStr, line, i, IC, lineOfCode , &otherBinaryWord, &symbolHead, &externHead, &ExternValHead);/*build the last part of the binary code of the code list*/
							getAndInitCodeLinked(&otherBinaryWord, &codeHead, IC);/*creates the last code of the code list*/
								break;
						}
						tmpStr[0] = '\0';
						j=0;
					}
				}
				else{/*not a white space or a special char*/
					isWritten = true;
					tmpStr[j]=line[i];
					tmpStr[j+1]='\0';
					j++;
				}
			}
			else{/*commant mode*/
				if(line[i] == '\n'){
					commentMode = false;
				}
			}
		}
	}
	if(errorType){/*return if there are an error*/
		fclose(fd);
		remove(oldPathName);
		return;
	}
	printObjectToFile(pathName, &codeHead, &dataHead);/*prints all the the selected files*/
	printExternals(pathName, &externHead);
	printEnteries(pathName, &symbolHead);
}
