#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


typedef struct complex {
	char name;
	double realNumber;
	double imagneryNumber;
}complex;


complex read_comp(complex compNum, double num1, double num2);
void print_comp(complex compNum);
void add_comp(complex compNum1, complex compNum2);
void sub_comp(complex compNum1, complex compNum2);
void mult_comp_real(complex compNum1, double realNum);
void mult_comp_img(complex compNum1, double imgNum);
void mult_comp_comp(complex compNum1, complex compNum2);
void abs_comp(complex compNum1);
void checkSyntex();

