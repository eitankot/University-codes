/*this program does commands in complax nubmers*/
#include "complex.h"
typedef	enum { False, True } Bool;
enum status { CHECK_COMMAND, FIRST_PARAM, SECOND_PARAM, THIRD_PARAM, AFTER, WAITING_FOR_COMMA };

enum erorr { NONE, UNDEFINED_COMMAND_NAME, UNDEFINED_COMPLEX_VARIABLE, INVALID_PARAMETER_NUM, MISSING_PARAMETER, EXTRANEOUS_TEXT_AFTER_END_OF_COMMAND, MULTIPLE_CONSECUTIVE_COMMAS, MISSING_COMMA, ILLEGAL_COMMA };

enum commands { UNDEFINED, ERROR, READ_COMP, PRINT_COMP, ADD_COMP, SUB_COMP, MULT_COMP_REAL, MULT_COMP_IMG, MULT_COMP_COMP, ABS_COMP, STOP };

/*global variables*/
char strNum[150];
int errorType = NONE;
complex firstParam;
double secondDoubleParam;
complex secondComplexParam;
double thirdParam;
complex A = { 'A',0,0 };
complex B = { 'B',0,0 };
complex C = { 'C',0,0 };
complex D = { 'D',0,0 };
complex E = { 'E',0,0 };
complex F = { 'F',0,0 };

/*main function*/
int main() {
	printf("please enter a command to start working.\n\n");
	checkSyntex();
	return 0;
}

/*checks if its a vallied command and return the command enum or an error.
@param stringName - the string to work with
@return an enum that represents the name of the command.*/
int checkIsVallidCommand(char stringName[]) {
	if (strcmp(stringName, "read_comp") == 0) {
		return READ_COMP;
	}
	else if (strcmp(stringName, "print_comp") == 0) {
		return PRINT_COMP;
	}
	else if (strcmp(stringName, "add_comp") == 0) {
		return ADD_COMP;
	}
	else if (strcmp(stringName, "sub_comp") == 0) {
		return SUB_COMP;
	}
	else if (strcmp(stringName, "mult_comp_real") == 0) {
		return MULT_COMP_REAL;
	}
	else if (strcmp(stringName, "mult_comp_img") == 0) {
		return MULT_COMP_IMG;
	}
	else if (strcmp(stringName, "mult_comp_comp") == 0) {
		return MULT_COMP_COMP;
	}
	else if (strcmp(stringName, "abs_comp") == 0) {
		return ABS_COMP;
	}
	else if (strcmp(stringName, "stop") == 0) {
		return STOP;
	}
	else {
		return ERROR;
	}
}

/*this function checks if its a number and returns it with a formal way
@param str[] the string to check if its a number
@return the number in a formal way.*/
int checknum(char str[]) {
	int len = 0;
	int i;
	int j = 0;
	strNum[0] = '\0';
	Bool hadntDot = True;
	while (str[len] != '\0')/*gets the length*/
	{
		len++;
	}

	for (i = 0; i < len; i++) {/*checks the number*/

		if (str[i] == '.' && hadntDot)
		{
			if (strNum[0] == '\0') {
				strNum[j++] = '0';
				strNum[j++] = '.';
				strNum[j++] = '0';
				strNum[j] = '\0';
			}
			else
			{
				strNum[j++] = '.';
				strNum[j] = '\0';
			}
			hadntDot = False;

		}
		else if (str[i] == '-' && strNum[0] == '\0'&& str[i + 1] != '\0') {
			strNum[j++] = '-';
			strNum[j] = '\0';
		}
		else if (isdigit(str[i])) {
			strNum[j++] = str[i];
			strNum[j] = '\0';
		}
		else {

			return False;
		}
	}
	return True;
}

/*checks if its a vallied parameter to get for the specific command.
@param str[] - the string to work with and check
@param paramState - the state the function called from
@param commandName - the name of the command to check
@return a value that matches the command name and the state the is currently in.*/
int isValliedParam(char str[], int paramState, int commandName) {
	char **stoped = NULL;

	if (commandName == READ_COMP) {/* if its the command read_comp */
		if (paramState == FIRST_PARAM) {/*first param*/
			if (strcmp(str, "A") == 0)
				firstParam = A;
			else if (strcmp(str, "B") == 0)
				firstParam = B;
			else if (strcmp(str, "C") == 0)
				firstParam = C;
			else if (strcmp(str, "D") == 0)
				firstParam = D;
			else if (strcmp(str, "E") == 0)
				firstParam = E;
			else if (strcmp(str, "F") == 0)
				firstParam = F;
			else {
				if (errorType == NONE)
					errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			}
		}
		else if (paramState == SECOND_PARAM) {/*second param*/

			if (checknum(str))
				secondDoubleParam = strtod(strNum, stoped);
			else {
				if (errorType == NONE)
					errorType = INVALID_PARAMETER_NUM;
				return False;
			}
		}
		else if (paramState == THIRD_PARAM) {/*third param*/
			if (checknum(str))
				thirdParam = strtod(strNum, stoped);
			else {
				if (errorType == NONE)
					errorType = INVALID_PARAMETER_NUM;
				return False;
			}
		}
	}
	else if (commandName == PRINT_COMP) {/*print comp*/
		if (paramState == FIRST_PARAM) {/* first param*/
			if (strcmp(str, "A") == 0)
				firstParam = A;
			else if (strcmp(str, "B") == 0)
				firstParam = B;
			else if (strcmp(str, "C") == 0)
				firstParam = C;
			else if (strcmp(str, "D") == 0)
				firstParam = D;
			else if (strcmp(str, "E") == 0)
				firstParam = E;
			else if (strcmp(str, "F") == 0)
				firstParam = F;
			else {
				if (errorType == NONE)
					errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			};
		}
	}
	else if (commandName == ADD_COMP) {/*add comp*/
		if (paramState == FIRST_PARAM) {/*first param*/
			if (strcmp(str, "A") == 0)
				firstParam = A;
			else if (strcmp(str, "B") == 0)
				firstParam = B;
			else if (strcmp(str, "C") == 0)
				firstParam = C;
			else if (strcmp(str, "D") == 0)
				firstParam = D;
			else if (strcmp(str, "E") == 0)
				firstParam = E;
			else if (strcmp(str, "F") == 0)
				firstParam = F;
			else {
				if (errorType == NONE)
					errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			}
		}
		else if (paramState == SECOND_PARAM) {/*second param*/
			if (strcmp(str, "A") == 0)
				secondComplexParam = A;
			else if (strcmp(str, "B") == 0)
				secondComplexParam = B;
			else if (strcmp(str, "C") == 0)
				secondComplexParam = C;
			else if (strcmp(str, "D") == 0)
				secondComplexParam = D;
			else if (strcmp(str, "E") == 0)
				secondComplexParam = E;
			else if (strcmp(str, "F") == 0)
				secondComplexParam = F;
			else {
				errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			}
		}
	}
	else if (commandName == SUB_COMP) {/*sub comp */
		if (paramState == FIRST_PARAM) {/*first param */
			if (strcmp(str, "A") == 0)
				firstParam = A;
			else if (strcmp(str, "B") == 0)
				firstParam = B;
			else if (strcmp(str, "C") == 0)
				firstParam = C;
			else if (strcmp(str, "D") == 0)
				firstParam = D;
			else if (strcmp(str, "E") == 0)
				firstParam = E;
			else if (strcmp(str, "F") == 0)
				firstParam = F;
			else {
				if (errorType == NONE)
					errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			}
		}
		else if (paramState == SECOND_PARAM) {/*second param*/
			if (strcmp(str, "A") == 0)
				secondComplexParam = A;
			else if (strcmp(str, "B") == 0)
				secondComplexParam = B;
			else if (strcmp(str, "C") == 0)
				secondComplexParam = C;
			else if (strcmp(str, "D") == 0)
				secondComplexParam = D;
			else if (strcmp(str, "E") == 0)
				secondComplexParam = E;
			else if (strcmp(str, "F") == 0)
				secondComplexParam = F;
			else {
				if (errorType == NONE)
					errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			}
		}
	}
	else if (commandName == MULT_COMP_REAL) {/*mult comp by real num*/
		if (paramState == FIRST_PARAM) {/*first param*/
			if (strcmp(str, "A") == 0)
				secondComplexParam = A;
			else if (strcmp(str, "B") == 0)
				secondComplexParam = B;
			else if (strcmp(str, "C") == 0)
				secondComplexParam = C;
			else if (strcmp(str, "D") == 0)
				secondComplexParam = D;
			else if (strcmp(str, "E") == 0)
				secondComplexParam = E;
			else if (strcmp(str, "F") == 0)
				secondComplexParam = F;
			else {
				if (errorType == NONE)
					errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			}
		}
		else if (paramState == SECOND_PARAM) {/*second param*/
			if (checknum(str))
				secondDoubleParam = strtod(strNum, stoped);
			else {
				if (errorType == NONE)
					errorType = INVALID_PARAMETER_NUM;
				return False;
			}
		}
	}
	else if (commandName == MULT_COMP_IMG) {/*mult comp by imnagenary num*/
		if (paramState == FIRST_PARAM) {/*first param*/
			if (strcmp(str, "A") == 0)
				secondComplexParam = A;
			else if (strcmp(str, "B") == 0)
				secondComplexParam = B;
			else if (strcmp(str, "C") == 0)
				secondComplexParam = C;
			else if (strcmp(str, "D") == 0)
				secondComplexParam = D;
			else if (strcmp(str, "E") == 0)
				secondComplexParam = E;
			else if (strcmp(str, "F") == 0)
				secondComplexParam = F;
			else {
				if (errorType == NONE)
					errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			};
		}
		else if (paramState == SECOND_PARAM) {/*second param*/
			if (checknum(str))
				secondDoubleParam = strtod(strNum, stoped);
			else {
				if (errorType == NONE)
					errorType = INVALID_PARAMETER_NUM;
				return False;
			}
		}
	}
	else if (commandName == MULT_COMP_COMP) {/*mult comp by comp*/
		if (paramState == FIRST_PARAM) {/*first param*/
			if (strcmp(str, "A") == 0)
				firstParam = A;
			else if (strcmp(str, "B") == 0)
				firstParam = B;
			else if (strcmp(str, "C") == 0)
				firstParam = C;
			else if (strcmp(str, "D") == 0)
				firstParam = D;
			else if (strcmp(str, "E") == 0)
				firstParam = E;
			else if (strcmp(str, "F") == 0)
				firstParam = F;
			else {
				if (errorType == NONE)
					errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			}
		}
		else if (paramState == SECOND_PARAM) {/*second param*/
			if (strcmp(str, "A") == 0)
				secondComplexParam = A;
			else if (strcmp(str, "B") == 0)
				secondComplexParam = B;
			else if (strcmp(str, "C") == 0)
				secondComplexParam = C;
			else if (strcmp(str, "D") == 0)
				secondComplexParam = D;
			else if (strcmp(str, "E") == 0)
				secondComplexParam = E;
			else if (strcmp(str, "F") == 0)
				secondComplexParam = F;
			else {
				if (errorType == NONE)
					errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			}
		}
	}
	else if (commandName == ABS_COMP) {/*check abs*/
		if (paramState == FIRST_PARAM) {/*first param*/
			if (strcmp(str, "A") == 0)
				firstParam = A;
			else if (strcmp(str, "B") == 0)
				firstParam = B;
			else if (strcmp(str, "C") == 0)
				firstParam = C;
			else if (strcmp(str, "D") == 0)
				firstParam = D;
			else if (strcmp(str, "E") == 0)
				firstParam = E;
			else if (strcmp(str, "F") == 0)
				firstParam = F;
			else {
				if (errorType == NONE)
					errorType = UNDEFINED_COMPLEX_VARIABLE;
				return False;
			}
		}
	}
	else
		return False;
	return True;
}

/*this function prints the error that happend.
@param errorType - the name of the error*/
void printError(int errorType) {
	if (errorType == UNDEFINED_COMMAND_NAME) {
		printf("Undefined command name\n\n");
	}
	else if (errorType == UNDEFINED_COMPLEX_VARIABLE) {
		printf("Undefined complex variable\n\n");
	}
	else if (errorType == INVALID_PARAMETER_NUM) {
		printf("Invalid parameter – not a number\n\n");
	}
	else if (errorType == MISSING_PARAMETER) {
		printf("Missing parameter \n\n");
	}
	else if (errorType == EXTRANEOUS_TEXT_AFTER_END_OF_COMMAND) {
		printf("Extraneous text after end of command \n\n");
	}
	else if (errorType == MULTIPLE_CONSECUTIVE_COMMAS) {
		printf("Multiple consecutive commas \n\n");
	}
	else if (errorType == MISSING_COMMA) {
		printf("Missing comma\n\n");
	}
	else if (errorType == ILLEGAL_COMMA) {
		printf("Illegal comma\n\n");
	}
}

/*this function changes the real variabel and sets the command of the read_comp*/
void getCompRead() {
	/*checks what is the variabel to read.*/
	if (firstParam.name == 'A') {

		A = read_comp(A, secondDoubleParam, thirdParam);
		firstParam = A;
	}
	else if (firstParam.name == 'B') {
		B = read_comp(B, secondDoubleParam, thirdParam);
		firstParam = B;
	}
	else if (firstParam.name == 'C') {
		C = read_comp(C, secondDoubleParam, thirdParam);
		firstParam = C;
	}
	else if (firstParam.name == 'D') {
		D = read_comp(D, secondDoubleParam, thirdParam);
		firstParam = D;
	}
	else if (firstParam.name == 'E') {
		E = read_comp(E, secondDoubleParam, thirdParam);
		firstParam = E;
	}
	else if (firstParam.name == 'F') {
		F = read_comp(F, secondDoubleParam, thirdParam);
		firstParam = F;
	}

}

/* this function gets from the user input and checks if its a command that can be done*/
void checkSyntex() {
	/*pre set of variabels*/
	int c;
	int state = CHECK_COMMAND;
	int commandName = UNDEFINED;
	int isWritten = False;
	int hadComma = False;

	int hadSpace = False;
	int writtenBefore = False;

	int doubleComma = False;
	char tmpString[150] = "";
	int i = 0;

	/*loop to check every char.*/
	while ((c = getchar()) != EOF) {
		putchar(c);
		switch (state) {
		case CHECK_COMMAND: {/*the first stage checks the command name and check if its a real one.*/
			if (c == ',') {
				if (errorType == NONE)
					errorType = ILLEGAL_COMMA;
			}
			if (c == '\n' || c == ' ' || c == '\t') {/* that means that the command name is done*/
				if (isWritten) {
					commandName = checkIsVallidCommand(tmpString);
					if (commandName != ERROR) {

						if (c == '\n') {/* checks if there is missing parameters*/
							if (commandName == ABS_COMP || commandName == PRINT_COMP || commandName == ADD_COMP || commandName == SUB_COMP || commandName == MULT_COMP_REAL || commandName == MULT_COMP_IMG || commandName == MULT_COMP_COMP || commandName == READ_COMP) {
								if (errorType == NONE)
									errorType = MISSING_PARAMETER;
							}
							if (errorType != NONE) {
								printError(errorType);
								errorType = NONE;
								tmpString[0] = '\0';
								i = 0;
								isWritten = False;
								commandName = UNDEFINED;
								state = CHECK_COMMAND;
								break;;
							}
							if (commandName == STOP) {/*check if its a command that needs to stop right now and it does that also.*/
								printf("the program has been stoped.\n");
								exit(0);
							}
						}
						/*moves to the next stage*/
						state = FIRST_PARAM;
						tmpString[0] = '\0';
						i = 0;
						isWritten = False;
						writtenBefore = False;
						hadComma = True;
						break;

					}
					else {/*if there is an error*/
						if (errorType == NONE)
							errorType = UNDEFINED_COMMAND_NAME;
						if (c == '\n') {
							printError(errorType);
							errorType = NONE;
							tmpString[0] = '\0';
							i = 0;
							isWritten = False;
							writtenBefore = False;
							commandName = UNDEFINED;
							state = CHECK_COMMAND;
						}

					}
				}
			}
			else {/*add to the list if there is no keyword to move to the next level*/
				if (isWritten)
					writtenBefore = True;
				isWritten = True;
				tmpString[i] = c;
				tmpString[i + 1] = '\0';
				i++;
			}
			break;
		}
		case FIRST_PARAM: {/*gets the first parameter*/
			if (c == ',' || c == '\n') {/*checks the keyword to move to the next parameter or end the command*/
				if (isWritten)
				{
					if (isValliedParam(tmpString, FIRST_PARAM, commandName) && errorType == NONE && !(hadComma)) {/*checks if its a vallied command*/
						if (c == '\n' && (commandName == ABS_COMP || commandName == PRINT_COMP)) {/*check if the command name equals to this 2 and stop if it need to*/
							if (commandName == ABS_COMP) {
								abs_comp(firstParam);
							}
							else if (commandName == PRINT_COMP) {
								print_comp(firstParam);
							}
							tmpString[0] = '\0';
							i = 0;
							commandName = UNDEFINED;
							state = CHECK_COMMAND;
							hadComma = False;
							isWritten = False;
							writtenBefore = False;
							break;


						}
						if (c == ',') {/*double comma checker*/
							if (doubleComma) {
								if (errorType == NONE) {
									errorType = MULTIPLE_CONSECUTIVE_COMMAS;
									break;
								}
							}
							else
								doubleComma = True;
						}
						if (c == ',' && (commandName == ABS_COMP || commandName == PRINT_COMP)) {/*error checker*/
							if (errorType == NONE)
								errorType = EXTRANEOUS_TEXT_AFTER_END_OF_COMMAND;
							break;
						}
						/*moves to the next level*/
						state = SECOND_PARAM;
						hadComma = True;
						tmpString[0] = '\0';
						i = 0;
						isWritten = False;
						writtenBefore = False;


					}
					else {/*error checker of commas or missing parameters*/
						if (errorType == NONE && c == ',' && hadComma)
							errorType = MULTIPLE_CONSECUTIVE_COMMAS;
						else if (errorType == NONE && c == '\n' && !hadComma)
							errorType = MISSING_COMMA;
						else if (errorType == NONE)
							errorType = MISSING_PARAMETER;

					}
				}
			}
			else if (c == ' ' || c == '\t') {/*blank spaces checker*/
				hadSpace = True;/*check if a space was there*/
			}
			else {
				writtenBefore = isWritten;/*checks the last time of the is written before this time*/
				if (isWritten && writtenBefore && hadSpace) {
					if (errorType == NONE)
						errorType = MISSING_COMMA;
				}
				isWritten = True;
				hadComma = False;
				hadSpace = False;
				doubleComma = False;
				tmpString[i] = c;
				tmpString[i + 1] = '\0';
				i++;
			}
			if (commandName == STOP) {/*if the stop happend without enter before.*/
				if (isWritten == False) {
					printf("the program has been stoped.\n");
					exit(0);
				}
				else {
					if (errorType == NONE)
						errorType = EXTRANEOUS_TEXT_AFTER_END_OF_COMMAND;
					printError(errorType);
					errorType = NONE;
					tmpString[0] = '\0';
					i = 0;
					isWritten = False;
					writtenBefore = False;
					commandName = UNDEFINED;
					state = CHECK_COMMAND;
					break;
				}
			}
			if (c == '\n') {/*error checker*/
				if (commandName == ADD_COMP || commandName == SUB_COMP || commandName == MULT_COMP_REAL || commandName == MULT_COMP_IMG || commandName == MULT_COMP_COMP || commandName == READ_COMP) {
					if (errorType == NONE)
						errorType = MISSING_PARAMETER;
				}
				if (errorType != NONE) {
					printError(errorType);
					errorType = NONE;
					tmpString[0] = '\0';
					i = 0;
					isWritten = False;
					writtenBefore = False;
					commandName = UNDEFINED;
					state = CHECK_COMMAND;
					break;
				}
			}
			break;
		}
		case SECOND_PARAM: {/*the second parameter checker*/
			if (c == '\n' || c == ',') {/*key word*/
				if (isWritten)
				{
					if (isValliedParam(tmpString, SECOND_PARAM, commandName) && errorType == NONE && !(hadComma)) {/*checks if its a vallied parameter*/
						if (c == '\n') {
							/*checks if its a command that need to be stoped*/
							if (commandName == ADD_COMP || commandName == SUB_COMP || commandName == MULT_COMP_REAL || commandName == MULT_COMP_IMG || commandName == MULT_COMP_COMP) {
								if (commandName == ADD_COMP) {
									add_comp(firstParam, secondComplexParam);
								}
								else if (commandName == SUB_COMP) {

									sub_comp(firstParam, secondComplexParam);
								}
								else if (commandName == MULT_COMP_REAL) {
									mult_comp_real(firstParam, secondDoubleParam);
								}
								else if (commandName == MULT_COMP_IMG) {
									mult_comp_img(firstParam, secondDoubleParam);
								}
								else if (commandName == MULT_COMP_COMP) {
									mult_comp_comp(firstParam, secondComplexParam);
								}
								tmpString[0] = '\0';
								i = 0;
								commandName = UNDEFINED;
								hadComma = True;
								state = CHECK_COMMAND;
								isWritten = False;
								writtenBefore = False;
								break;
							}

						}
						if (c == ',') {/*double comma checker*/
							if (doubleComma) {
								if (errorType == NONE) {
									errorType = MULTIPLE_CONSECUTIVE_COMMAS;
									break;
								}
							}
							else
								doubleComma = True;
						}
					}/*check if the commands that need to be stoped are not stoped by comma*/
					if (c == ',' && (commandName == ADD_COMP || commandName == SUB_COMP || commandName == MULT_COMP_REAL || commandName == MULT_COMP_IMG || commandName == MULT_COMP_COMP)) {
						errorType = EXTRANEOUS_TEXT_AFTER_END_OF_COMMAND;
					}
					state = THIRD_PARAM;

					tmpString[0] = '\0';
					i = 0;
					isWritten = False;
					writtenBefore = False;

				}
				else {/*error checker*/

					tmpString[0] = '\0';
					if (errorType == NONE && c == ',' && hadComma)
						errorType = MULTIPLE_CONSECUTIVE_COMMAS;
					else if (errorType == NONE && c == '\n' && !hadComma)
						errorType = MISSING_COMMA;
					else if (errorType == NONE) {
						errorType = MISSING_PARAMETER;

					}
				}
			}
			else if (c == ' ' || c == '\t') {/*black space checker*/
				hadSpace = True;/*checks if space was there*/
			}
			else {/*checks if there is no missing commas and adds to the list the character here.*/
				writtenBefore = isWritten;
				if (isWritten && writtenBefore && hadSpace) {
					if (errorType == NONE)
						errorType = MISSING_COMMA;
				}
				isWritten = True;
				hadComma = False;
				hadSpace = False;
				doubleComma = False;
				tmpString[i] = c;
				tmpString[i + 1] = '\0';
				i++;
			}
			if (commandName == ABS_COMP || commandName == PRINT_COMP) {/*checks again if this commands are here.*/

				if (isWritten == False) {
					if (commandName == ABS_COMP) {
						abs_comp(firstParam);
					}
					else if (commandName == PRINT_COMP) {
						print_comp(firstParam);
					}
					tmpString[0] = '\0';
					i = 0;
					commandName = UNDEFINED;
					state = CHECK_COMMAND;
					isWritten = False;
					writtenBefore = False;
					break;
				}
				else {

					if (errorType == NONE)
						errorType = EXTRANEOUS_TEXT_AFTER_END_OF_COMMAND;
					printError(errorType);
					errorType = NONE;
					tmpString[0] = '\0';
					i = 0;
					isWritten = False;
					writtenBefore = False;
					commandName = UNDEFINED;
					state = CHECK_COMMAND;
					break;
				}
			}
			if (c == '\n') {/*error checker*/
				if (commandName == READ_COMP) {
					if (errorType == NONE)
						errorType = MISSING_PARAMETER;
				}
				if (errorType != NONE) {
					printError(errorType);
					errorType = NONE;
					tmpString[0] = '\0';
					i = 0;
					isWritten = False;
					writtenBefore = False;
					commandName = UNDEFINED;
					state = CHECK_COMMAND;
					break;
				}
			}
			break;
		}
		case THIRD_PARAM: {/*third param checker*/

			if (c == '\n') {/*checks the keyword*/
				if (isWritten)
				{

					if (isValliedParam(tmpString, THIRD_PARAM, commandName) && errorType == NONE) {/*checks if its vallied parameter*/

						if (c == '\n') {/*checks if its a the command read_comp*/

							if (commandName == READ_COMP) {
								getCompRead();

								tmpString[0] = '\0';
								i = 0;
								commandName = UNDEFINED;
								hadComma = True;
								state = CHECK_COMMAND;
								isWritten = False;
								writtenBefore = False;
								break;
							}

						}
						/*moves to the last stage in case something happend and it missed it*/
						state = AFTER;
						tmpString[0] = '\0';
						i = 0;
						isWritten = False;
						writtenBefore = False;
					}
					else {/*error checker*/
						if (errorType == NONE)
							errorType = MISSING_PARAMETER;
						tmpString[0] = '\0';
					}
				}
			}
			else if (c == ' ' || c == '\t') {/*blank space checker*/
				state = THIRD_PARAM;
			}
			else {/*comma error checker*/
				if (errorType == NONE) {
					if (c == ',' && isWritten) {
						errorType = EXTRANEOUS_TEXT_AFTER_END_OF_COMMAND;
					}
					else if (c == ',' && !isWritten) {
						errorType = ILLEGAL_COMMA;
					}
				}
				if (isWritten)/*adds to the list to work with it*/
					writtenBefore = False;
				isWritten = True;
				tmpString[i] = c;
				tmpString[i + 1] = '\0';
				i++;

			}
			if (c != ' ' && c != '\t') {/*checks incase it missed it last time*/
				if (commandName == ADD_COMP || commandName == SUB_COMP || commandName == MULT_COMP_REAL || commandName == MULT_COMP_IMG || commandName == MULT_COMP_COMP) {
					if (c != '\n') {
						if (errorType == NONE)
							errorType = EXTRANEOUS_TEXT_AFTER_END_OF_COMMAND;

						printError(errorType);
						errorType = NONE;
						tmpString[0] = '\0';
						i = 0;
						isWritten = False;
						writtenBefore = False;
						commandName = UNDEFINED;
						state = CHECK_COMMAND;
						break;
					}
					if (commandName == ADD_COMP) {
						add_comp(firstParam, secondComplexParam);
					}
					else if (commandName == SUB_COMP) {

						sub_comp(firstParam, secondComplexParam);
					}
					else if (commandName == MULT_COMP_REAL) {
						mult_comp_real(firstParam, secondDoubleParam);
					}
					else if (commandName == MULT_COMP_IMG) {
						mult_comp_img(firstParam, secondDoubleParam);
					}
					else if (commandName == MULT_COMP_COMP) {
						mult_comp_comp(firstParam, secondComplexParam);
					}

					tmpString[0] = '\0';
					i = 0;
					commandName = UNDEFINED;
					state = CHECK_COMMAND;
					isWritten = False;
					writtenBefore = False;
					break;
				}
			}
			if (c == '\n') {/*error checker*/
				if (errorType != NONE) {
					printError(errorType);
					errorType = NONE;
					tmpString[0] = '\0';
					i = 0;
					isWritten = False;
					writtenBefore = False;
					commandName = UNDEFINED;
					state = CHECK_COMMAND;
					break;
				}
			}
			break;
		}
		case AFTER: {/*checker in case it moved by to many parameters by read_comp and etc*/

			if (c == '\n') {/*checks it the command was right*/
				if (commandName == READ_COMP)
					getCompRead();
				tmpString[0] = '\0';
				i = 0;
				commandName = UNDEFINED;
				state = CHECK_COMMAND;
				isWritten = False;
				writtenBefore = False;
				break;
			}
			else {/* checks if there was to many parameters to work*/
				if (c != ' ' && c != '\t') {
					if (errorType == NONE)
						errorType = EXTRANEOUS_TEXT_AFTER_END_OF_COMMAND;
					printError(errorType);
					errorType = NONE;
					isWritten = False;
					writtenBefore = False;
					tmpString[0] = '\0';
					i = 0;
					commandName = UNDEFINED;
					state = CHECK_COMMAND;
					break;
				}
			}
		}
		}
	}/*it the program has not been stoped right it prints that.*/
	printf("The program has not been stoped right.");
}
