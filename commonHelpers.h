// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Junwoo Lee
//  Student ID    : 124395203
//  Student Email : jlee648@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_
#define _CRT_SECURE_NO_WARNINGS
int currentYear(void); 
void clearStandardInputBuffer(void);
int getInteger(void);
int getPositiveInteger(void);
int getPositiveOrZeroInteger(void);
int getIntFromRange(int from, int to);
double getDouble(void);
double getPositiveDouble(void);
char getCharOption(const char str[]);
void getCString(char* str , int from, int to);

#endif