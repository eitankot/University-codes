/*this code is the mathematical side of the command prompt of complex nubmers*/
#include "complex.h"

/*changes the complex variable by entering 2 double numbers
@param compNum - the complex nubmer to change
@param num1 - the real number of the complex num
@param num2 - the inmaginary nubmer of the complex num
@return sets the complex number to the numbers that given by the user*/
complex read_comp(complex compNum, double num1, double num2){
	compNum.realNumber = num1;
	compNum.imagneryNumber = num2;
	return compNum;
}

/*prints the complex num
@param compNUm - the num to print*/
void print_comp(complex compNum){
	if((compNum.realNumber == 0 && compNum.imagneryNumber == 0 )|| compNum.imagneryNumber == 0)
	{
		printf("%f\n", compNum.realNumber);
	}
	else if(compNum.realNumber == 0 && compNum.imagneryNumber != 0 )
	{
		printf("(%f)i\n", compNum.imagneryNumber);
	}
	else{
		printf("%f + (%f)i\n",compNum.realNumber ,compNum.imagneryNumber);
	}
}

/*adds two complex numbers and prints the result
@param compNum1 - the first complex num to add
@param compNum2 - the second complex num to add*/
void add_comp(complex compNum1, complex compNum2)
{
	complex tmpComp;
	tmpComp.realNumber = compNum1.realNumber + compNum2.realNumber;
	tmpComp.imagneryNumber = compNum1.imagneryNumber + compNum2.imagneryNumber;
	print_comp(tmpComp);
}

/*subs two complex numbers and prints the result
@param compNum1 - the first complex num to sub from
@param compNum2 - the second complex num to sub with*/
void sub_comp(complex compNum1, complex compNum2){
	complex tmpComp;
	tmpComp.realNumber = compNum1.realNumber - compNum2.realNumber;
	tmpComp.imagneryNumber = compNum1.imagneryNumber - compNum2.imagneryNumber;
	print_comp(tmpComp);
}

/*mults the complex num by a real number
@param compNum1 - the complex number that gets multiplied
@param realNum - the number that you multiply with*/
void mult_comp_real(complex compNum1, double realNum){
	complex tmpComp;
	tmpComp.realNumber = compNum1.realNumber * realNum;
	tmpComp.imagneryNumber = compNum1.imagneryNumber * realNum;
	print_comp(tmpComp);
}

/*mults the complex num by a imaginary number
@param compNum1 - the complex number that gets multiplied
@param imgNum - the number that you multiply with*/
void mult_comp_img(complex compNum1, double imgNum){
	complex tmpComp;
	tmpComp.realNumber = compNum1.imagneryNumber * (imgNum*(-1));
	tmpComp.imagneryNumber = compNum1.realNumber * imgNum;
	print_comp(tmpComp);
}

/*mults the complex num by a complex number
@param compNum1 - the complex number that gets multiplied
@param compNum2 - the complex that you multiply with*/
void mult_comp_comp(complex compNum1, complex compNum2){
	complex tmpComp;
	tmpComp.realNumber = (compNum1.realNumber * compNum2.realNumber) - compNum1.imagneryNumber * compNum2.imagneryNumber;
	tmpComp.imagneryNumber = (compNum1.realNumber * compNum2.imagneryNumber) + compNum1.imagneryNumber * compNum2.realNumber;
	print_comp(tmpComp);
}

/*checks the abs of the complex number.
@param compNum1 - the complex number to check his abs*/
void abs_comp(complex compNum1){
	double number;
	number = sqrt(pow(compNum1.realNumber,2) + pow(compNum1.imagneryNumber,2));
	printf("%f\n",number);
}

