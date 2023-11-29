#include "asembler.h"

/*
this code init the linked list
@param ptrBinaryD *hptr - the head of the linked list
@param unsigned int value - the value to enter into the linked list

*/
void initBinaryList(ptrBinaryD *hptr,int value){
	ptrBinaryD p1, p2;
	ptrBinaryD t;
	t = (ptrBinaryD)malloc(sizeof(binaryItems));
	if(!t){
		printf("cannot build list \n");
		exit(0);		
	}
	t->next = NULL;
	t->value = value;
	t->ARE = 4;
	t->zero=0;
	p1 = *hptr;
	while((p1)){
		p2=p1;
		p1=p1->next;
	}
	if(p1 == *hptr){
		*hptr = t;
		t->next = p1;
	}
	else{
		p2->next = t;
	}
}
/*
this code init the linked list
@param ptrBinaryOp *hptr - the head of the linked list
@param unsigned int value - the value to enter into the linked list
@param unsigned int ARE - the value to enter into the linked list

*/
void initOpBinaryList(ptrBinaryOp *hptr,unsigned int value, unsigned int ARE){
	ptrBinaryOp p1, p2;
	ptrBinaryOp t;
	t = (ptrBinaryOp)malloc(sizeof(binaryOpItems));
	if(!t){
		printf("cannot build list \n");
		exit(0);		
	}
	t->next = NULL;

	t->value = value;
	t->ARE = ARE;
	t->zero=0;
	p1 = *hptr;
	while((p1)){
		p2=p1;
		p1=p1->next;
	}
	if(p1 == *hptr){
		*hptr = t;
		t->next = p1;
	}
	else{
		p2->next = t;
	}
}


/*
this code init the linked list
@param ptrBinaryC *hptr - the head of the linked list
@param unsigned int destAddress - the value to enter into the linked list
@param unsigned int destAddress - the value to enter into the linked list
@param unsigned int destRegister - the value to enter into the linked list
@param unsigned int sourceAddress - the value to enter into the linked list
@param unsigned int sourceRegister - the value to enter into the linked list
@param unsigned int funct - the value to enter into the linked list
@param operand *operands - the value to enter into the linked list
@param unsigned int ARE - the value to enter into the linked list

*/
void initBinaryCodeList(ptrBinaryC *hptr,unsigned int destAddress ,unsigned int destRegister,unsigned int sourceAddress,unsigned int sourceRegister,unsigned int funct,unsigned int ARE, operand *operands){
	ptrBinaryC p1, p2;
	ptrBinaryC t;
	t = (ptrBinaryC)malloc(sizeof(binaryCodeItems));
	if(!t){
		printf("cannot build list \n");
		exit(0);		
	}

	t->next = NULL;
	if(operands->firstOperand == NONE){
		t=NULL;
	}
	else{

		t->destAddress=destAddress;
		t->destRegister=destRegister;
		t->sourceAddress=sourceAddress;
		t->sourceRegister=sourceRegister;
		t->ARE=ARE;
		t->funct = funct;
		t->zero=0;}
	p1 = *hptr;

	while((p1)){
		p2=p1;
		p1=p1->next;
	}
	if(p1 == *hptr){
		*hptr = t;
		if(t != NULL){
			t->next = p1;}
	}
	else{
		p2->next = t;

	}
	
}

/*
this code init the linked list
@param ptrSymbol *hptr - the head of the linked list
@param char dataName[] - the name of the label
@param char dataName[] - the value to enter into the linked list
@param int counter - the value to enter into the linked list
*/
void initLabel(ptrSymbol *hptr,char labelName[] ,char dataName[],int counter){
	ptrSymbol p1, p2;
	ptrSymbol t;
	t = (ptrSymbol)malloc(sizeof(symbolImage));
	if(!t){
		printf("cannot build list \n");
		exit(0);		
	}
	strcpy(t -> name,labelName);
	t->next = NULL;
	t->IC = counter;
	t ->baseAddress = counter- (counter%16);
	t ->offset = counter%16;
	if(strcmp(dataName, ".data")==0){
		t-> attribute = data;
	}
	else if(strcmp(dataName, ".code")==0){
		t-> attribute = code;
	}
	else if(strcmp(dataName, ".extern")==0)
	{
		t-> attribute = external;
	}
	else if(strcmp(dataName, ".entry")==0){
		t-> attribute = entry;
	}
	p1 = *hptr;
	while((p1)){
		p2=p1;
		p1=p1->next;
	}
	if(p1 == *hptr){
		*hptr = t;
		t->next = p1;
	}
	else{
		p2->next = t;
	}
}

/*
this code init the linked list
@param ptrData *hptr - the head of the linked list
@param int count - the value to enter into the linked list
@param int L - the value to enter into the linked list
@param ptrBinaryD *bptr - the value to enter into the linked list
*/
void initlinkedData(ptrData *hptr,int count, int L, ptrBinaryD *bptr ){
	ptrData p1, p2;
	ptrData t;
	t = (ptrData)malloc(sizeof(dataImage));
	if(!t){
		printf("cannot build list \n");
		exit(0);		
	}
	t->next = NULL;
	t->IC = count;
	t-> headBinary = *bptr;
	p1 = *hptr;
	while((p1)){
		p2=p1;
		p1=p1->next;
	}
	if(p1 == *hptr){
		*hptr = t;
		t->next = p1;
	}
	else{
		p2->next = t;
	}
}
/*
this code init the linked list
@param ptrValExt *hptr - the head of the linked list
@param int IC - the value to enter into the linked list
*/
void initlinkedValExt(ptrValExt *hptr,int IC){
	ptrValExt p1, p2;
	ptrValExt t;
	t = (ptrValExt)malloc(sizeof(valueExt));
	if(!t){
		printf("cannot build list \n");
		exit(0);		
	}
	t->next = NULL;
	t->base = IC;
	t-> offset = IC+1;
	p1 = *hptr;
	while((p1)){
		p2=p1;
		p1=p1->next;
	}
	if(p1 == *hptr){
		*hptr = t;
		t->next = p1;
	}
	else{
		p2->next = t;
	}
}

/*
this code init the linked list
@param ptrExternal *hptr - the head of the linked list
@param char name[] - the name to enter into the linked list
@param ptrValExt *Extptr - the binary code val of the external.
*/
void initlinkedExtern(ptrExternal *hptr,char name[], ptrValExt *Extptr ){
	ptrExternal p1, p2;
	ptrExternal t;
	t = (ptrExternal)malloc(sizeof(externImage));
	if(!t){
		printf("cannot build list \n");
		exit(0);		
	}
	t->next = NULL;
	strcpy(t->name,name);
	t-> headExt = *Extptr;
	p1 = *hptr;
	while((p1)){
		p2=p1;
		p1=p1->next;
	}
	if(p1 == *hptr){
		*hptr = t;
		t->next = p1;
	}
	else{
		p2->next = t;
	}
}

/*
this code init the linked list
@param ptrCode *hptr - the head of the linked list
@param int count - the value to enter into the linked list
@param int L - the value to enter into the linked list
@param int ptrBinaryC *secondBinaryPtr - the binary word to enter.
@param int ptrBinaryOp *firstBinaryPtr - the binary word to enter.
*/
void initlinkedCode(ptrCode *hptr,int count, int L, ptrBinaryC *secondBinaryPtr ,ptrBinaryOp *firstBinaryPtr){
	ptrCode p1, p2;
	ptrCode t;
	t = (ptrCode)malloc(sizeof(codeImage));
	if(!t){
		printf("cannot build list \n");
		exit(0);		
	}
	t->next = NULL;
	t->IC = count;
	t-> firstBinaryWord = *firstBinaryPtr;
	t-> secondBinaryWord = *secondBinaryPtr;
	t->otherBinaryWord = NULL;
	t->L=L;
	p1 = *hptr;
	while((p1)){
		p2=p1;
		p1=p1->next;
	}
	if(p1 == *hptr){
		*hptr = t;
		t->next = p1;
	}
	else{
		p2->next = t;
	}
}
