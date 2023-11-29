#include "asembler.h"
/*
this code transforms a number into a binary code.
@param unsigned int k - the number to transform
@return a number that represents the binary code of the number.
*/
unsigned int binToUnsigned(unsigned int k) {
    if (k == 0) return 0;/*base of the recurtion*/
    if (k == 1) return 1;
    return (k % 2) + 10 * binToUnsigned(k / 2);/*step of the recurtion*/
}

/*
this code checks if the string of the code is direct register.
@param char str[] - the string to check if its a direct register.
@param operand *operands - the operands to set the register if its a register.
@return true if its the string is a register.
*/
int isDirect(char str[], operand *operands){
	char commandNameList[][5] = {"r0","r1", "r2", "r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15"};
	int commandNameListLen = 16;
	unsigned int num;
	int i;
	for(i=0; i<commandNameListLen ;i++){
		if(strcmp(commandNameList[i], str)== 0){/*if the string is a register*/
			num= i;
			if(operands->firstOperand == NONE){/*sets the value of the register*/
				operands->destRegister = num;
			}
			else{
				operands->sourceRegister = num;
			}
			return true;}
	}
	return false;
}

/*
this function checks if there is only numbers or white spaces in the string.
@param char str[] - the string to check if it has only white spaces.
@param operand *operands - the operands to set the register if its a register.
@return true if its the string has only numbers.
*/
int checkOnlyNum(char str[], int i){
	int j;
	int isLast = false;
	int isFirst = true;
	int hadOnlyPlusOrMinus = false;
	for(j=i; j<strlen(str); j++){/*checks the string*/
		if(!(isdigit(str[j]))){
			if (str[j] == ' ' || str[j] == '\n' || str[j] == '\t'){/*white space*/
				if(isFirst == false){
					isLast = true;
			}
			}
			else if(isFirst && (str[j]=='-' || str[j]=='+')){/*special char that its not a number but its ok to use at the start*/
				isFirst = false;
				hadOnlyPlusOrMinus =true;
			}
			else{
				return false;}
		}
		else{/*a number*/
			if(isLast){
				return false;				
			}
			hadOnlyPlusOrMinus = false;
			isFirst = false;
		}
	}
	if(hadOnlyPlusOrMinus){/*checks if its a fine number*/
		return false;
	}
	return true;
}

/*
this code checks if the string of the code is index register.
@param char str[] - the string to check if its a index register.
@param int i - the index to start the checking from.
@param operand *operands - the operands to set the register if its a register.
@return true if its the string is a index register.
*/
int checkDirectIndex(char str[], int i, operand *operands){
	int j,l;
	unsigned int num;
	int isLast = false;
	int isFirst = true;
	int hadCloseBraket = false;
	
	char directsList[][5] = {"r10", "r11", "r12", "r13", "r14", "r15"};/*the allowed registers*/
	
	int k=0;
	char tmpStr[MAX_PER_LINE];
	tmpStr[0] = '\0';
	for(j=i; j<strlen(str); j++){/*moves on the str*/
		if(str[j]==' ' || str[j]=='\t' || str[j]=='\n'){/*white space*/
			if(!isFirst){
				if(hadCloseBraket){
					isLast=true;}
				else{
					return false;
				}
			}
		}
		else if(str[j]==']'){/*if it had closed brackets*/
			if(!hadCloseBraket)
				hadCloseBraket = true;
			else{
				return false;
			}
		}
		else{/*a normal char*/
			if(isLast || hadCloseBraket){
				return false;
			}
		tmpStr[k]=str[j];
		tmpStr[k+1]='\0';
		k++;
		isFirst = false;
		}
	}
	if(hadCloseBraket){/*checks if there its an allowed register*/
		for(l=0; l<=5; l++){
			if(strcmp(tmpStr, directsList[l])==0){
				num= l+10;
				if(operands->firstOperand == NONE){
					operands->destRegister = num;
					 return true;
				}
				else{
					operands->sourceRegister = num;
					return true;
				}
			}
		}
		return false;}
	else{
		return false;
	}
}

/*
this code checks if the string a allowed operands for the command.
@param char str[] - the string to check.
@param operand *operands - the operands to check if the operands are allowed.
@return true if its the string has allowed operands for the selected command.
*/
int checkLegalOperands(char str[], operand *operands){
	if(strcmp(str, "mov")==0){/*checks every command*/
		if(operands->firstOperand == NONE || operands->secondOperand == NONE){
			return false;}
		if(operands->secondOperand == immediateOp){
			return false;
		}
		return true;
	}
	else if(strcmp(str, "cmp")==0){
		if(operands->firstOperand == NONE || operands->secondOperand == NONE){
			return false;}
		return true;
	}
	else if(strcmp(str, "add")==0){
		if(operands->firstOperand == NONE || operands->secondOperand == NONE){
			return false;}
		if(operands->secondOperand == immediateOp){
			return false;
		}
		return true;
	}
	else if(strcmp(str, "sub")==0){
		if(operands->secondOperand == NONE || operands->firstOperand == NONE){
			return false;}
		if(operands->secondOperand == immediateOp ){
			return false;
		}
		return true;
	}
	else if(strcmp(str, "lea")==0){
		if(operands->firstOperand == immediateOp|| operands->firstOperand ==registerDirectOp || operands->firstOperand == NONE){
			return false;
		}
		if(operands->secondOperand == immediateOp || operands->secondOperand == NONE){
			return false;
		}
			return true;
	}
	else if(strcmp(str, "clr")==0){
		if(operands->secondOperand != NONE || operands->firstOperand == NONE){
			return false;}
		if(operands->firstOperand == immediateOp)
			return false;
		return true;
	}
	else if(strcmp(str, "not")==0){
		if(operands->secondOperand != NONE || operands->firstOperand == NONE){
			return false;}
		if(operands->firstOperand == immediateOp)
			return false;
		return true;
	}
	else if(strcmp(str, "inc")==0){
		if(operands->secondOperand != NONE || operands->firstOperand == NONE){
			return false;}
		if(operands->firstOperand == immediateOp)
			return false;
		return true;
	}
	else if(strcmp(str, "dec")==0){
		if(operands->secondOperand != NONE || operands->firstOperand == NONE){
			return false;}
		if(operands->firstOperand == immediateOp)
			return false;
		return true;
	}
	else if(strcmp(str, "jmp")==0){
		if(operands->secondOperand != NONE || operands->firstOperand == NONE){
			return false;}
		if(operands->firstOperand == immediateOp || operands->firstOperand == registerDirectOp)
			return false;
		return true;
	}
	else if(strcmp(str, "bne")==0){
		if(operands->secondOperand != NONE || operands->firstOperand == NONE){
			return false;}
		if(operands->firstOperand == immediateOp || operands->firstOperand == registerDirectOp)
			return false;
		return true;
	}
	else if(strcmp(str, "jsr")==0){
		if(operands->secondOperand != NONE || operands->firstOperand == NONE){
			return false;}
		if(operands->firstOperand == immediateOp || operands->firstOperand == registerDirectOp)
			return false;
		return true;
	}
	else if(strcmp(str, "red")==0){
		if(operands->secondOperand != NONE || operands->firstOperand == NONE){
			return false;}
		if(operands->firstOperand == immediateOp)
			return false;
		return true;
	}
	else if(strcmp(str, "prn")==0){
		if(operands->secondOperand != NONE || operands->firstOperand == NONE){
			return false;}
		return true;
	}
	else if(strcmp(str, "rts")==0){
		if(operands->secondOperand != NONE || operands->firstOperand != NONE){
			return false;}
		return true;
	}
	else{
		if(operands->secondOperand != NONE || operands->firstOperand != NONE){
			return false;}
		return true;
	}
}

/*
this code checks if the string has an opening bracket.
@param char str[] - the string to check.
@return true if there is a bracket
*/
int hasBrackets(char str[]){
	int i;
	for(i=0; i<strlen(str); i++){/*moves on the string and checks*/
		if(str[i]=='['){
			return true;
		}
	}
	return false;
}
/*
this code checks if the gets the index of the bracket.
@param char str[] - the string to check.
@return a number that represents the index if there is a bracket or 0 if there is none.
*/
int getIndexOfBracket(char str[]){
	int i;
	for(i=0; i<strlen(str); i++){
		if(str[i]=='['){
			return i+1;
		}
	}
	return 0;
}

/*
this code checks if the operand is allowed to be with the selcted command.
@param char commandName[] - the command name.
@param char line[] - the line of the code
@param int i - the index to start from.
@param int lineOfCode - the line in the file of the code
@param operand *operands - the operands to set and return to the main part.
@return the number of operand or -1 if an error happned/
*/
int checkOperands(char commandName[],char line[],int i,int lineOfCode, operand *operands){
	int j, k=0;/*creating parameters*/
	int hadComma = true;
	int hadWritten = false;
	
	char tmpStr[MAX_PER_LINE];
	tmpStr[0] = '\0';
	typeOfVariant operation = NONE;
	
	int counter = 1;
	for(j=i; j<strlen(line); j++){	/*moves on the line*/
		if(hadComma){
			if(line[j]==','){/*checks llegal comma*/
				if(!hadWritten){
					printf("error in line %d\t-illegal comma.\n", lineOfCode);
					return -1;}
			}
			if(line[j]== ' ' || line[j]== '\t' || line[j]== '\n' || line[j]==','){/*if there is a white space or a comma*/
					if(tmpStr[0]== '#'){/*if its immidiate operand*/
						if(checkOnlyNum(tmpStr, 1)){
							operation = immediateOp;
							if(counter<2){/*add to the counter of operands*/
								counter++;
							}
							counter++;}
						else{
							printf("error in line %d\t-in immediate address you need to enter only numbers.\n", lineOfCode);
							return -1;
						}
					}
					else if(hasBrackets(tmpStr)){/*checks if its index operand*/
						if(checkDirectIndex(tmpStr, getIndexOfBracket(tmpStr), operands)){
							
							operation = indexOp;
							if(counter<2){/*add to the counter of operands*/
								counter++;
							}
							counter+=2;}	
						else{
							printf("error in line %d\t-in index address you need to enter only numbers.\n", lineOfCode);
							return -1;
						}
					}
					else if(strlen(tmpStr) > 0){
						if(isDirect(tmpStr, operands)){/*if its a direct register*/
							operation = registerDirectOp;
							if(counter<2){/*add to the counter of operands*/
								counter++;}
						}
						else{
							operation = unidentified;/*there is a chance that its a symbol*/
							if(counter<2){/*add to the counter of operands*/
								counter++;
							}
							counter+=2;
						}
					}
					if(operation != NONE){/*changes the operation to the selected operand*/
						if(operands->firstOperand == NONE){
							operands->firstOperand = operation;
						}
						else if(operands->secondOperand == NONE){
							operands->secondOperand = operation;
						}
						else{
							printf("error in line %d\t-to many arguments in the operand.\n", lineOfCode);
							return -1;
						}
					}/*if its a comma*/
					if(line[j]==','){
						hadWritten = false;
					}
					else if(line[j]=='\n'){/*if the code ended here*/
						if(checkLegalOperands(commandName, operands) && (hadWritten==true ||  operands->firstOperand == NONE)){
							return counter;
						}
						else{
							if(hadWritten==false && operands->firstOperand != NONE){
								printf("error in line %d\t-illegal comma.\n", lineOfCode);
							}
							else{
								printf("error in line %d\t-there are less operands then needed to the selected command.\n", lineOfCode);}
							return -1;
						}
						
					}
					else{/*if there is a white space*/
						if(hadWritten){
							hadComma=false;}
					}
					operation = NONE;
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
		else{/*if it have not got comma*/
			if(line[j]== ' ' || line[j]== '\t' || line[j]== '\n'){/*if its a white space*/
				if(line[j]== '\n'){/*if its the end to the line*/
					if(checkLegalOperands(commandName, operands)){
						return counter;}
					else{
						printf("error in line %d\t-there are more or less operands then needed to the selected command.\n", lineOfCode);
						return -1;
					}
				}
			}
			else if(line[j]== ','){/*if its a comma*/
				hadComma = true;
				hadWritten = false;
				}
			else{/*other char than white space and comma*/

				printf("error in line %d\t-missing comma.\n", lineOfCode);
				return -1;
			}
		}
	}
	return -1;
}
/*
checks if its a vallied command name
@param char str[] - the command name to check
@return true if its a vallied command name.
*/
int checkValliedCommand(char str[]){
	char commandNameList[][5] = {"mov","cmp","add","sub","lea","clr","not","inc","dec","jmp","bne","jsr","red", "prn" , "rts", "stop"};
	int commandNameListLen = 16;
	int i;
	for(i=0; i<commandNameListLen; i++){
		if(strcmp(commandNameList[i], str)== 0){
			return true;}
	}
	return false;
}
