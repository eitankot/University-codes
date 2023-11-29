#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size 80
/* initilazer*/
char pop(char stack[]);
char peek(char stack[]);
void push(char stack[], char ch);
int isEmpty(char stack[]);
int checkStack(char stack [], char c, int blankLine);
int leftSlashState(char c,int state);
int InComment(char c,int state);
int RightStar(char c, int state);
int inString(char c, int state);			
int checkState(char c,int state);

void checker();

/* global variable for the stack and the special brakets. */
int top = -1;
int specialBrakets = 0;/* counter of the special brakets*/

typedef	enum {False,True} Bool;
enum status{OUT,IN_STRING,LEFT_SLASH,IN_COMMENT,RIGHT_STAR};

char pop(char stack[]){/* this func pops the last item in the stack*/
	int data;
	
   	if(!isEmpty(stack)) {
      		data = stack[top];
      		top = top - 1;   
      		return data;
   	} 
	else {
		return '\0';
	}
}

char peek(char stack[])/* this func look at the last item in the stack*/
{
	return stack[top];
}

void push(char stack[], char ch)/* this func push the item to the last place in the stack*/
{
	stack[++top] = ch;
	stack[top+1] = '\0';
	
}

int isEmpty(char stack[])/* this checks if the stack is empty*/
{
	return top == -1;
}

int main() 
{
	printf("Please enter a code line to check if the brackets are orderly\n it will get into the checker until you press ctrl+d or the text file will get to EOF.\n");
	checker();
	return 0;
}

int checkState(char c,int state){
	if(c  =='/')/* all the conditions to change the state or add normal brakets.*/
		state=LEFT_SLASH;
	else if(c =='\"')
		state = IN_STRING;
	else
		state = OUT;
	return state;
}

int leftSlashState(char c, int state){
	putchar(c);
	if(c=='*')
		state = IN_COMMENT;
	else if (c == '/'){
		state = LEFT_SLASH;
	}
	else{
		state = OUT;
	}
	return state;
}
int InComment(char c,int state){
	putchar(c);
	if(c=='*')
		state= RIGHT_STAR;
	return state;
}

int RightStar(char c, int state){
	putchar(c);
	if(c=='/')
		state = OUT;
	return state;
}

int inString(char c, int state){
	if(c=='\"')
		state = OUT;
	putchar(c);
	return state;
}

int checkStack(char stack [], char c, int blankLine)
{
	if(c =='(')
		push(stack,'(');
	else if(c =='[')
		push(stack,'[');
	else if(c ==')')
	{
		if (peek(stack) == '('){
			pop(stack);
		}
		else{
			return False;
		}
	}
	else if(c ==']')
	{
		if (peek(stack) == '['){
			pop(stack);			
		}
		else{
			return False;
		}
	}
	if(c == '{'){
		push(stack,'{');}
	if(c == '}'){
		if(blankLine == True){
			if(specialBrakets > 0)
				specialBrakets--;
			else
				return False;
			}
			else{
				if (peek(stack) == '{'){
					pop(stack);	
				}
				else{
					return False;
				}
			}
	}
	return True;
}

void checker()
{
	int c;/* the char*/
	int state = OUT;/* the state of the checker*/
	char stack[size];
	Bool tmpLineFine;
	Bool isFine = True;
	Bool lineFine = True;
	Bool blankLine = True;	
	Bool isFirst = True;


	while((c=getchar()) != EOF)
		switch(state){
			case OUT:/* Normal case*/
			
				if(c == '\n')/* if its the end of the line*/
				{
					if(!(isEmpty(stack))){
						if (blankLine == True && peek(stack)== '{')
							specialBrakets++;
						else
							lineFine = False;
					memset(stack, 0, size);
					top = -1;
					}
					if(lineFine)
						puts(" OK");
					else{
						isFine = False;
						lineFine = True;
						puts(" Not");}
					isFirst = True;
					blankLine = True;			
				}
				putchar(c);

				if(c != ' ' && c != '\t' && c!='\n'){
					if ((c == '{' || c == '}')&& isFirst){
						isFirst = False;}
					else{
						blankLine = False;
						isFirst = False;}
				}
				state = checkState(c, state);				
				
				tmpLineFine =  checkStack(stack, c, blankLine);
				if(lineFine == False || tmpLineFine == False){
					lineFine = False;
				}
				break;	
			
			case LEFT_SLASH:/* left slash status*/
				state = leftSlashState(c, state);
				break;
			case IN_COMMENT:/* in comment status*/
				state = InComment(c, state);
				break;
			case RIGHT_STAR:/* right statr status*/
				state = RightStar(c, state);
				break;
			case IN_STRING:/* in string status*/
				state = inString(c, state);
				break;
		}
	if(isFine && specialBrakets == 0)/* check if the total code is ok*/
		printf("The code in total is OK");
	else
		printf("The code in total is Not ok");
}





