#include "asembler.h"
/*
gets the number of the command name to put in the binary code.
@param char commandName[] - the command name to check
@return the number to put in the binary code.
*/
unsigned int getNumberOfCommand(char commandName[]){
	if(strcmp(commandName, "mov")==0)
		return 1;
	else if(strcmp(commandName, "cmp")==0)
		return 2;
	else if(strcmp(commandName, "add")==0)
		return 4;
	else if(strcmp(commandName, "sub")==0)
		return 4;
	else if(strcmp(commandName, "lea")==0)
		return 16;
	else if(strcmp(commandName, "clr")==0)
		return 32;
	else if(strcmp(commandName, "not")==0)
		return 32;
	else if(strcmp(commandName, "inc")==0)
		return 32;
	else if(strcmp(commandName, "dec")==0)
		return 32;
	else if(strcmp(commandName, "jmp")==0)
		return 512;
	else if(strcmp(commandName, "bne")==0)
		return 512;
	else if(strcmp(commandName, "jsr")==0)
		return 512;
	else if(strcmp(commandName, "red")==0)
		return 4096;
	else if(strcmp(commandName, "prn")==0)
		return 8192;
	else if(strcmp(commandName, "rts")==0)
		return 16384;
	else
		return 32768;
	
}

/*
gets the funct to put in the binary code.
@param char commandName[] - the command name to check
@return the number to put in the binary code.
*/
unsigned int getFunct(char commandName[]){
	if(strcmp(commandName, "add")==0 || strcmp(commandName, "clr")==0 || strcmp(commandName, "jmp")==0)
		return 10;
	else if(strcmp(commandName, "sub")==0 || strcmp(commandName, "not")==0 || strcmp(commandName, "bne")==0)
		return 11;
	else if(strcmp(commandName, "inc")==0 || strcmp(commandName, "jsr")==0)
		return 12;
	else if(strcmp(commandName, "dec")==0)
		return 13;
	else
		return 0;
}

/*
builds the binary code of the command.
@param char commandName[] - the command name to check
@param ptrBinaryOp *tmpBinaryHead - the head of the linked list
@param ptrBinaryOp ptrBinaryC *tmpSecondBinaryHead - the head of the linked list
@param operand *operands - the operand parameters
@return the number to put in the binary code.
*/
void buildBinaryCode(char commandName[] ,ptrBinaryOp *tmpBinaryHead,ptrBinaryC *tmpSecondBinaryHead, operand *operands){
	unsigned int num = getNumberOfCommand(commandName);/*creating the binary code*/
	initOpBinaryList(tmpBinaryHead, num,4);
	unsigned int funct = getFunct(commandName);/*creating the second binary code*/
	unsigned int firstOp, secondOp, ARE;
	ARE = 4;
	if(operands->secondOperand != NONE){/*creating the address to use in the code*/
		if(operands->firstOperand == immediateOp){
			firstOp = 0;}
		else if(operands->firstOperand == NONE)
			firstOp = 0;
		else if(operands->firstOperand == directOp || operands->firstOperand == unidentified)
			firstOp = 1;
		else if(operands->firstOperand == indexOp )
			firstOp = 2;
		else{
			firstOp = 3;
		}
		if(operands->secondOperand == immediateOp)
			secondOp = 0;
		else if(operands->secondOperand == directOp ||  operands->secondOperand == unidentified)
			secondOp = 1;
		else if(operands->secondOperand == indexOp )
			secondOp = 2;
		else{
			secondOp = 3;
		}
		initBinaryCodeList(tmpSecondBinaryHead, secondOp,operands->sourceRegister , firstOp, operands->destRegister, funct, ARE, operands);
	}
	else{
		if(operands->firstOperand == immediateOp){
			firstOp = 0;}
		else if(operands->firstOperand == NONE)
			firstOp = 0;
		else if(operands->firstOperand == directOp || operands->firstOperand == unidentified)
			firstOp = 1;
		else if(operands->firstOperand == indexOp )
			firstOp = 2;
		else{
			firstOp = 3;
		}
		initBinaryCodeList(tmpSecondBinaryHead, firstOp,operands->destRegister , 0,0, funct, ARE, operands);/*creating the second binary code*/
	}

}

/*
sets the otherBinary word to the correct place in the linked code list
@param ptrBinaryOp *otherBinaryWord - the other binary head linked list to place in the selected place.
@param ptrBinaryOp ptrCode *codeHead - the code head linked list to enter the binary word to.
@param int IC - the corrent ic .

*/
void getAndInitCodeLinked(ptrBinaryOp *otherBinaryWord, ptrCode *codeHead, int IC){
	if(otherBinaryWord !=NULL){
		ptrCode p1 = *codeHead;
		ptrCode p2;
		while(p1->next != NULL){
			p2=p1;
			p1=p1->next;
			if((p1->IC)>IC){/*is the ic is bigger than the selected.*/
				p2->otherBinaryWord = *otherBinaryWord;
				return;
			}
		}
	}
}
