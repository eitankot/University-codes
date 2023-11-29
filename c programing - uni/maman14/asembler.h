#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LABEL 32
#define MAX_PER_LINE 82

typedef	enum { false, true } Bool;/*enums*/
typedef	enum {external, code, entry, data} attributes;
typedef	enum {NONE, unidentified ,immediateOp, directOp, indexOp, registerDirectOp } typeOfVariant;
typedef	enum { unsignedVal, signedVal } typeOfVal;

typedef struct operand{/*global operand srtuct*/
	typeOfVariant firstOperand;
	unsigned int destRegister:4;
	typeOfVariant secondOperand;
	unsigned int sourceRegister:4;
}operand;

typedef struct linkedBinaryDataList * ptrBinaryD;/*linked list*/
typedef struct linkedBinaryDataList{
	int value: 16;
	unsigned int ARE: 3;
	unsigned int zero: 1;
	ptrBinaryD next;
}binaryItems;

typedef struct linkedBinaryOpList * ptrBinaryOp;/*linked list*/
typedef struct linkedBinaryOpList{
	unsigned int value: 16;
	unsigned int ARE: 3;
	unsigned int zero: 1;
	typeOfVal type;
	ptrBinaryOp next;
}binaryOpItems;

typedef struct linkedBinaryCodeList * ptrBinaryC;/*linked list*/
typedef struct linkedBinaryCodeList{
	unsigned int destAddress: 2;
	unsigned int destRegister: 4;
	unsigned int sourceAddress: 2;
	unsigned int sourceRegister:4;
	unsigned int funct:4;
	unsigned int ARE: 3;
	unsigned int zero: 1;
	ptrBinaryC next;
}binaryCodeItems;

typedef struct linkedData * ptrData;/*linked list*/
typedef struct linkedData{
	int IC;
	int L;
	ptrBinaryD headBinary;
	ptrData next;
}dataImage;


typedef struct linkedCode * ptrCode;/*linked list*/
typedef struct linkedCode{
	int IC;
	int L;
	ptrBinaryOp firstBinaryWord;
	ptrBinaryC secondBinaryWord;
	ptrBinaryOp otherBinaryWord;
	ptrCode next;
}codeImage;

typedef struct linkedSymbol * ptrSymbol;/*linked list*/
typedef struct linkedSymbol{
	char name[MAX_LABEL];
	int IC;
	int baseAddress;
	int offset;
	attributes attribute;
	ptrSymbol next;
}symbolImage;

/* externals*/
typedef struct linkedValueExtList * ptrValExt;/*linked list*/
typedef struct linkedValueExtList{
	int base;
	int offset;
	ptrValExt next;
}valueExt;

typedef struct linkedExternal * ptrExternal;/*linked list*/
typedef struct linkedExternal{
	char name[MAX_LABEL];
	ptrValExt headExt;
	ptrExternal next;
}externImage;

/*prototypes*/
int getIC(ptrCode *codeHead, int IC);
int checkLengthOfFile(char pathName[]);
void getAndInitCodeLinked(ptrBinaryOp *otherBinaryWord, ptrCode *codeHead, int IC);
void printObjectToFile(char pathName[], ptrCode *codeHead, ptrData *dataHead);
void getEnteries(char labelName[] ,char line[], int i);
int isVallidLabelExternal(char labelName[], ptrSymbol *hptr);
void getExternals(char labelName[] ,char line[], int i);
int isLabelExternal(char labelName[], ptrSymbol *hptr);
void initlinkedExtern(ptrExternal *hptr,char name[], ptrValExt *Extptr );
void initlinkedValExt(ptrValExt *hptr,int IC);
int isExternalWritten(char labelName[], ptrExternal *hptr);
void printExternals(char pathName[], ptrExternal *externalHead);
void printEnteries(char pathName[], ptrSymbol *symbolHead);
void initBinaryList(ptrBinaryD *hptr, int value);
void initOpBinaryList(ptrBinaryOp *hptr,unsigned int value, unsigned int ARE);
void initBinaryCodeList(ptrBinaryC *hptr,unsigned int destAddress ,unsigned int destRegister,unsigned int sourceAddress,unsigned int sourceRegister,unsigned int funct,unsigned int ARE, operand *operands);
void initLabel(ptrSymbol *hptr,char labelName[] ,char dataName[],int counter);
void initlinkedData(ptrData *hptr,int count, int L, ptrBinaryD *bptr );
void initlinkedCode(ptrCode *hptr,int count, int L, ptrBinaryC *secondBinaryPtr ,ptrBinaryOp *firstBinaryPtr);
unsigned int binToUnsigned(unsigned int i);
void macroFixer(char pathName[]);
void firstMove(char pathName[]);
int isVallidLabelName(ptrSymbol *hptr, char labelname[],  int line);
int checkLengthOfData(ptrData *dataHead,char str [],int IC ,char line[],int i,ptrBinaryD *tmpBinaryHead);
int checkValliedCommand( char str[]);
int checkOperands(char commandName[],char line[],int i, int lineOfCode, operand *operands);
void buildBinaryCode(char commandName[] ,ptrBinaryOp *tmpBinaryHead,ptrBinaryC *tmpSecondBinaryHead, operand *operands);
int hasBrackets(char str[]);
void secondMove(char pathName[],ptrData dataHead,ptrCode codeHead ,ptrSymbol  symbolHead );
int isLabelInSymbol(char labelName[], ptrSymbol *hptr);
void changeTypeToEntry(char labelName[], ptrSymbol *hptr);
int buildOtherBinary(char commandName[],char line[],int i,int IC,int lineOfCode,ptrBinaryOp *otherBinaryWord, ptrSymbol  *symbolHead,ptrExternal *ExternHead,  ptrValExt *ExternValHead);
