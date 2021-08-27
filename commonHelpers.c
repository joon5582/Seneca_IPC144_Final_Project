// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Junwoo Lee
//  Student ID    : 124395203
//  Student Email : jlee648@myseneca.ca
//  Course Section: NBB
// ===================================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "commonHelpers.h"


int currentYear(void) //return current year
{
	time_t currentTime = time(NULL); return localtime(&currentTime)->tm_year + 1900;
}

void clearStandardInputBuffer(void) //clear standard buffer
{
	while (getchar() != '\n') {
		; // On purpose: do nothing 
	}
}

int getInteger(void) //get integer from user
{
	int value;
	char newline;
	int flag = 0;
	do
	{
		newline = '\0';
		scanf("%d%c", &value, &newline);
		if (newline == '\n')
			flag = 1;
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	} while (flag == 0);
	return value;
}

int getPositiveInteger(void) //get positive integer from user
{
	int value;
	char newline;
	int flag = 0;
	do
	{
		newline = '\0';
		scanf("%d%c", &value, &newline);
		if (newline == '\n')
		{
			flag = 1;
			if (value <= 0)
			{
				printf("ERROR: Value must be a positive integer greater than zero: ");
				flag = 0;
			}
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	} while (flag == 0);
	return value;
}
int getPositiveOrZeroInteger(void) //get positive integer or 0 from user
{
	int value;
	char newline;
	int flag = 0;
	do
	{
		newline = '\0';
		scanf("%d%c", &value, &newline);
		if (newline == '\n')
		{
			flag = 1;
			if (value < 0)
			{
				printf("ERROR: Value must be positive or zero: ");
				flag = 0;
			}
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	} while (flag == 0);
	return value;
}

double getDouble(void) //get double number(real number) from user
{
	double value;
	char newline;
	int flag = 0;
	do
	{
		newline = '\0';
		scanf("%lf%c", &value, &newline);
		if (newline == '\n')
			flag = 1;
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	} while (flag == 0);
	return value;
}


double getPositiveDouble(void) //get positive double number from user
{
	double value;
	char newline;
	int flag = 0;
	do
	{
		newline = '\0';
		scanf("%lf%c", &value, &newline);
		if (newline == '\n')
		{
			flag = 1;
			if (value <= 0)
			{
				printf("ERROR: Value must be a positive double floating-point number: ");
				flag = 0;
			}
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	} while (flag == 0);
	return value;
}

int getIntFromRange(int from, int to) //get int with range from user
{
	int value;
	char newline;
	int flag = 0;
	do
	{
		newline = '\0';
		scanf("%d%c", &value, &newline);

		if (newline == '\n')
		{
			flag = 1;
			if (value < from || value> to)
			{
				printf("ERROR: Value must be between %d and %d inclusive: ", from, to);
				flag = 0;
			}
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	} while (flag == 0);
	return value;
}


char getCharOption(const char str[]) //prompt user to input char included in parameter string
{
	char inputChar,newline;
	int flag= 0;
	
	do
	{
		newline = '\0';
		flag = 0;
		scanf("%c%c", &inputChar,&newline);
		if (newline == '\n')
		{
			if (strchr(str, inputChar))
				flag = 1;
		}	
					
		else
		{
			clearStandardInputBuffer();			
		}		
		if (flag == 0)
			printf("ERROR: Character must be one of [%s]: ", str);

	} while (flag == 0);
	return inputChar;
}

void getCString(char* str, int from, int to) //prompt user to input string including white space
{
	char inputString[1000] = { 0 };
	
	int flag, length;

	do
	{
		
		flag = 0;
		length = 0;
		scanf(" %[^\n]%*c", (char*)&inputString);
		length = strlen(inputString);
				
		if (from == to)
		{
			if (length != from)
				printf("ERROR: String length must be exactly %d chars: ", from);
			else
				flag = 1;
		}
		else
		{		
			if (length < from)
				printf("ERROR: String length must be between %d and %d chars: ", from, to);
			else if (length > to)
				printf("ERROR: String length must be no more than %d chars: ", to);
			else
				flag = 1;
			

		}

	} while (flag == 0);
	strcpy(str, inputString);
	
	
}