/*
this code creates a matrix and checks if its a magic cube.
*/
#include "data.h"

int getMatrix(int mat[][N]);
void printMat(int mat[][N]);
int checkIfMatIsMagic(int mat[][N]);


typedef	enum {False,True} Bool;
enum status{OUT,IN_NUMBER,MINUS};

/*
this function prints the matrix.
@param mat [][] - the matrix to print.
*/
void printMat(int mat[][N]){
	int i,j;
	printf("\n");
	for(i=0; i<N; i++){
		for(j=0; j<N;j++)
			printf("%d\t",mat[i][j]);
		printf("\n");}
}
/*
this is the main function of the code.
*/
int main(){
	int mat[N][N];
	Bool fineSquare;
	printf("\nplease enter a matrix with %d rows and %d columns \n",N,N);
	fineSquare = getMatrix(mat);
	if(fineSquare == False){
		return 0;	
	}
	printMat(mat);
	if(checkIfMatIsMagic(mat)){
		printf("The matrix is a magic cube.");
	}
	else{
		printf("The matrix is not a magic cube.");
	}
	return 0;
}

/*
this function gets the matrix and create a matrix by the user and check that the matrix has only number in it.
@param mat [][] - the matrix that to create and check about.
@return if the matrix includes only numbers and if its a full matrix.
*/
int getMatrix(int mat[][N]){
	int c;
	int state = OUT;
	int counter = 0;
	
	int fineSquare = True;

	char tmpString[100] = "";
	char tmpChar[2] = {'0','\0'};

	int i = 0;
	int j = 0;

	while((c=getchar()) != EOF){
		switch(state){
			case OUT:
			{
				if(c == ' ' || c == '\n' || c == '\t'){
					state = OUT;
				}
				else if(isdigit(c) || c == '-'){
					if(c == '-'){
						state = MINUS;
					}
					else{
						state = IN_NUMBER;}
					tmpChar[0] = c;
					strcat(tmpString, tmpChar);}
				else{
					printf("\nThere is a char that is not a number in the magic square. \n the program has been stopped from acting\n");
					fineSquare = False;
					return fineSquare;
					}
				break;}
			case IN_NUMBER:{
				if(c == ' ' || c == '\n' || c == '\t'){
					
					if(j == N){
						j = 0;
						i++;
						if(i ==N ){
							printf("\nThere are more numbers to fill the magic square. \n the program has been stopped from acting\n");
							fineSquare = False;
							return fineSquare;}
						else{
						mat[i][j++] = atoi(tmpString);}
						
					}
					
					else
						mat[i][j++] = atoi(tmpString);
						counter++;
						tmpString[0] = '\0';		
						state = OUT;
					}
					
				else if(isdigit(c)){/* checks if its a digit*/
					tmpChar[0] = c;
					strcat(tmpString, tmpChar);
				}
				else{/* if there is a char in the matrix */
					printf("\nThere is a char that is not a number in the magic square. \n the program has been stopped from acting\n");
					fineSquare = False;
					return fineSquare;
				}
					
				break;
			}
			case MINUS:{
				if(isdigit(c)){/* checks if its a digit*/
					tmpChar[0] = c;
					strcat(tmpString, tmpChar);
					state = IN_NUMBER;}
				else{
					printf("\nThere is a char that is not a number in the magic square. \n the program has been stopped from acting\n");
					fineSquare = False;
					return fineSquare;
				}
			}
		}
		
	}
	if(counter < N*N){
		printf("\nThere are less numbers to fill the magic square. \n the program has been stopped from acting\n");
		fineSquare = False;
		return fineSquare;
	}
	return fineSquare;
}

/*
this function gets the matrix check if there are only positive numbers and no duplicates.
@param mat [][] - the matrix to check if there is a duplicate or only positive.
@return true if the matrix include only posivitve numbers and so duplicates
*/
int checkPosAndDup(int mat[][N]){
	int tmpArr[N*N];
	int i,j,k=0;
	for(i=0; i<N; i++){/* creates a array with all of the numbers*/
		for(j=0; j<N; j++){
			tmpArr[k++] = mat[i][j];}
	}
	for(i = 0; i<N*N; i++){/* checks the all of the numbers are positive*/
		if(tmpArr[i] <= 0)
			return False;}
	for(i=0; i<N*N; i++){/* checks if there is not duplicates in the matrix*/
		for(j=0; j<i; j++){
			if(tmpArr[i] == tmpArr[j])
				return False;}
	}
	return True;
}

/*
this function gets the matrix and check if all the rows have the same number.
@param mat [][] - the matrix.
@return true if all the rows have the same number
*/
int checkRows(int mat[][N]){
	int SUM_MAGIC = (N*((N*N)+1))/2;
	int sum=0;
	int i,j;
	for(i=0; i<N; i++){/* checks the all of the rows*/
		for(j=0; j<N; j++){
			sum += mat[i][j];
		}
		if(sum != SUM_MAGIC){
			return False;}
		sum=0;
	}
	return True;
}

/*
this function gets the matrix and check if all the columns have the same number.
@param mat [][] - the matrix.
@return true if all the columns have the same number
*/
int checkColumns(int mat[][N]){
	int SUM_MAGIC = (N*((N*N)+1))/2;
	int sum=0;
	int i,j;
	for(j=0; j<N; j++){/* checks the all of the columns*/
		for(i=0; i<N; i++){
			sum+= mat[i][j];
		}
		if(sum != SUM_MAGIC){
			return False;}
		sum=0;
	}
	return True;
}

/*
this function gets the matrix and check if all the main diagonals have the same number.
@param mat [][] - the matrix to check
@return true if all the main diagonals have the same number
*/
int checkMainDiagonals(int mat[][N]){
	int SUM_MAGIC = (N*((N*N)+1))/2;
	int sum=0;
	int i,j=N-1;
	for(i=0; i<N;i++){/* checks the first diagonal*/
		sum+= mat[i][i];
	}
	if(sum != SUM_MAGIC){
		return False;
	}
	sum=0;
	for(i=0; i<N;i++){/* checks the second diagonal*/
		sum+= mat[i][j];
		j--;
	}
	if(sum != SUM_MAGIC){
		return False;
	}
	return True;
}

/*
this function gets the matrix and checks if the matrix is a magic cube.
@param mat [][] - the matrix to check.
@return true if the matrix is a magic cube
*/
int checkIfMatIsMagic(int mat[][N]){
	Bool isMagic = True;
	if(!( checkPosAndDup(mat) )){
		isMagic = False;}
	if (!(checkRows(mat))){
		isMagic = False;}
	if (!(checkColumns(mat))){
		isMagic = False;}
	if (!(checkMainDiagonals(mat))){
		isMagic = False;}
	return isMagic;

}

