#include "asembler.h"
/*
gets the count of all the command lines.
@param ptrCode *codeHead - the code head linked list .
@return the count of all command lines

*/
int getCommandCount(ptrCode *codeHead){
	ptrCode p1 = *codeHead;
	ptrBinaryOp p2 = NULL;
	ptrBinaryC p3 = NULL;
	 ptrBinaryOp p4 = NULL;
	int count=0;
	while(p1){/* moves on all the command nodes*/
		p2 = p1->firstBinaryWord;
		while(p2){/*reads the first word count*/
			count++;
			p2 = p2->next;
		}
		p3 = p1->secondBinaryWord;
		while(p3){/*reads the second word count*/
			count++;
			p3 = p3->next;
		}
		p4 = p1->otherBinaryWord;
		while(p4){/*reads the other words count*/
			count++;
			p4 = p4->next;
		}
		p1=p1->next;
	}
	return count;
}

/*
gets the count of all the data lines.
@param ptrData *dataHead - the data head linked list .
@return the count of all data lines

*/
int getDataCount(ptrData *dataHead){
	ptrData p1 = *dataHead;
	ptrBinaryD p2 = NULL;
	int count=0;
	while(p1){/* moves on all the data nodes*/
		p2 = p1->headBinary;
		while(p2){/*reads the binary line count*/
			count++;
			p2 = p2->next;
		}
		p1=p1->next;
	}
	return count;
}

/*
prints the data to the object file.
@param char pathName[] - the path to print to.
@param ptrCode *codeHead- the code head linked list
@param ptrData *dataHead - the data head linked list .

*/
void printObjectToFile(char pathName[], ptrCode *codeHead, ptrData *dataHead){
	FILE *fd;
	char newPathName[strlen(pathName)];/*creating the file*/
	strcpy(newPathName, pathName);
	strcat(newPathName, ".ob");
	fd= fopen(newPathName, "w");
	
	ptrCode p1 = *codeHead;
	ptrData p2 = *dataHead;
	
	ptrBinaryD ptrData;
	ptrBinaryOp ptrFirst;
	ptrBinaryC ptrSecond;
	ptrBinaryOp ptrOther;
	int firstNum, secondNum, thirdNum, fourthNum, fithNum;
	int counter, commandCount, dataCount;
	commandCount = getCommandCount(codeHead);
	dataCount = getDataCount(dataHead);
	fprintf(fd ,"%d %d\n", commandCount, dataCount);
	while(p1!=NULL || p2!=NULL){/*moving until nothing stays in both lists*/
		if(p1==NULL){/*if the code list is empty*/
			ptrData= p2->headBinary;
			counter = p2->IC;
			while(ptrData){
				firstNum = ((ptrData->zero)<<3)+ptrData->ARE;/*gets all the numbers to present by the values in the linked list*/
				secondNum=((ptrData->value)&61440)>>12;
				thirdNum=((ptrData->value)&3840)>>8;
				fourthNum=((ptrData->value)&240)>>4;
				fithNum =((ptrData->value)&15);
				fprintf(fd ,"%d\tA%x-B%x-C%x-D%x-E%x\n", counter,firstNum, secondNum, thirdNum, fourthNum, fithNum);/*prints the numbers to the file*/
				counter++;
				ptrData = ptrData->next;
			}
			p2 = p2->next;
		}
		else if(p2==NULL){/*if the data list is empty*/
			ptrFirst= p1->firstBinaryWord;/**/
			ptrSecond= p1->secondBinaryWord;
			ptrOther = p1->otherBinaryWord;
			counter = p1->IC;
			firstNum = ((ptrFirst->zero)<<3)+ptrFirst->ARE;/*gets all the numbers to present by the values in the linked list*/
			secondNum=(((ptrFirst->value)&61440)>>12);
			thirdNum=((ptrFirst->value)&3840)>>8;
			fourthNum=((ptrFirst->value)&240)>>4;
			fithNum =((ptrFirst->value)&15);
			fprintf(fd ,"%d\tA%x-B%x-C%x-D%x-E%x\n", counter,firstNum, secondNum, thirdNum, fourthNum, fithNum);/*prints the numbers to the file*/
			counter++;
			if(ptrSecond){
				firstNum = ((ptrSecond->zero)<<3)+ptrSecond->ARE;/*gets all the numbers to present by the values in the linked list*/
				secondNum=(ptrSecond->funct);
				thirdNum=(ptrSecond->sourceRegister);
				fourthNum=(((ptrSecond->sourceAddress)<<2)+(((ptrSecond->destRegister)&12)>>2));
				fithNum =((((ptrSecond->destRegister)&3)<<2)+((ptrSecond->destAddress)));
				fprintf(fd ,"%d\tA%x-B%x-C%x-D%x-E%x\n", counter,firstNum, secondNum, thirdNum, fourthNum, fithNum);/*prints the numbers to the file*/
				counter++;
			}
			while(ptrOther){
				firstNum = ((ptrOther->zero)<<3)+ptrOther->ARE;
				secondNum=((ptrOther->value)&61440)>>12;/*gets all the numbers to present by the values in the linked list*/
				thirdNum=((ptrOther->value)&3840)>>8;
				fourthNum=((ptrOther->value)&240)>>4;
				fithNum =((ptrOther->value)&15);
				fprintf(fd ,"%d\tA%x-B%x-C%x-D%x-E%x\n", counter,firstNum, secondNum, thirdNum, fourthNum, fithNum);/*prints the numbers to the file*/
				counter++;
				ptrOther = ptrOther->next;
			}
			p1 = p1->next;
		}
		else if((p1->IC)<(p2->IC)){/*if the IC in the code list is smaller than the data list */
			ptrFirst= p1->firstBinaryWord;
			ptrSecond= p1->secondBinaryWord;
			ptrOther = p1->otherBinaryWord;
			counter = p1->IC;
			firstNum = ((ptrFirst->zero)<<3)+ptrFirst->ARE;
			secondNum=(((ptrFirst->value)&61440)>>12);/*gets all the numbers to present by the values in the linked list*/
			thirdNum=((ptrFirst->value)&3840)>>8;
			fourthNum=((ptrFirst->value)&240)>>4;
			fithNum =((ptrFirst->value)&15);
			fprintf(fd ,"%d\tA%x-B%x-C%x-D%x-E%x\n", counter,firstNum, secondNum, thirdNum, fourthNum, fithNum);/*prints the numbers to the file*/
			counter++;
			if(ptrSecond){
				firstNum = ((ptrSecond->zero)<<3)+ptrSecond->ARE;/*gets all the numbers to present by the values in the linked list*/
				secondNum=(ptrSecond->funct);
				thirdNum=(ptrSecond->sourceRegister);
				fourthNum=(((ptrSecond->sourceAddress)<<2)+(((ptrSecond->destRegister)&12)>>2));
				fithNum =((((ptrSecond->destRegister)&3)<<2)+((ptrSecond->destAddress)));
				fprintf(fd ,"%d\tA%x-B%x-C%x-D%x-E%x\n", counter,firstNum, secondNum, thirdNum, fourthNum, fithNum);/*prints the numbers to the file*/
				counter++;
			}
			while(ptrOther){
				firstNum = ((ptrOther->zero)<<3)+ptrOther->ARE;
				secondNum=((ptrOther->value)&61440)>>12;/*gets all the numbers to present by the values in the linked list*/
				thirdNum=((ptrOther->value)&3840)>>8;
				fourthNum=((ptrOther->value)&240)>>4;
				fithNum =((ptrOther->value)&15);
				fprintf(fd ,"%d\tA%x-B%x-C%x-D%x-E%x\n", counter,firstNum, secondNum, thirdNum, fourthNum, fithNum);/*prints the numbers to the file*/
				counter++;
				ptrOther = ptrOther->next;
			}
			p1 = p1->next;
		}
		else{
			ptrData= p2->headBinary;
			counter = p2->IC;
			while(ptrData){
				firstNum = ((ptrData->zero)<<3)+ptrData->ARE;/*gets all the numbers to present by the values in the linked list*/
				secondNum=((ptrData->value)&61440)>>12;
				thirdNum=((ptrData->value)&3840)>>8;
				fourthNum=((ptrData->value)&240)>>4;
				fithNum =((ptrData->value)&15);
				fprintf(fd ,"%d\tA%x-B%x-C%x-D%x-E%x\n", counter,firstNum, secondNum, thirdNum, fourthNum, fithNum);/*prints the numbers to the file*/
				counter++;
				ptrData = ptrData->next;
			}
			p2 = p2->next;
		}
		
	}
}
