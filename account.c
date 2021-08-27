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
#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int SaveAllAccounts(struct AccountTicketingData* data)  // update all accounts to accounts.txt file
{
	FILE* fp = fopen("accounts.txt", "w");
	int i, count = 0;


	if (fp == NULL) {
		printf("accounts.txt doesn't exist!!\n");
		return -1;
	}
	else
	{
		for (i = 0; i < data->ACCOUNT_MAX_SIZE; i++)
		{
			if (data->accounts[i].accountNum != 0)
			{
				fprintf(fp, "%05d~%c~%s~%s~%s~%d~%lf~%s\n", data->accounts[i].accountNum, data->accounts[i].accountType, data->accounts[i].userLogin.nameOfuser, data->accounts[i].userLogin.loginName, data->accounts[i].userLogin.password, data->accounts[i].demoGraphic.birthYear, data->accounts[i].demoGraphic.houseHoldIncome, data->accounts[i].demoGraphic.country);
				count++;
			}
		}

		fclose(fp);
	}
	return count;
}
void displayAccountSummaryHeader(void)  //display account summary header
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

void displayAccountDetailHeader(void) //display account detail header
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account* ap) //display single account summary record
{
	printf("%05d %-9s %5d", ap->accountNum, ap->accountType == 'A' ? "AGENT" : "CUSTOMER", ap->demoGraphic.birthYear);
	putchar('\n');
}

void displayAccountDetailRecord(const struct Account* ap) //display single account detailed record
{
	int i;
	char hiddenpassword[9];

	for (i = 0; (hiddenpassword[i] = ap->userLogin.password[i]) != '\0'; i++) // changing every even-numbered character to *
	{
		if (i % 2 == 1)
			hiddenpassword[i] = '*';
	}



	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s", ap->accountNum, ap->accountType == 'A' ? "AGENT" : "CUSTOMER", ap->demoGraphic.birthYear, ap->demoGraphic.houseHoldIncome, ap->demoGraphic.country, ap->userLogin.nameOfuser, ap->userLogin.loginName, hiddenpassword);
	putchar('\n');

}

void displayAllAccountSummaryRecords(const struct Account* accountArray, int maxAccountNum) // display all account summary records
{
	int i;
	displayAccountSummaryHeader();
	for (i = 0; i < maxAccountNum; i++)
	{
		if (accountArray[i].accountNum > 0)
			displayAccountSummaryRecord(&accountArray[i]);
	}
}

void displayAllAccountDetailRecords(const struct Account* accountArray, int maxAccountNum) // display all account detailed records
{
	int i;
	displayAccountDetailHeader();
	for (i = 0; i < maxAccountNum; i++)
	{
		if (accountArray[i].accountNum > 0)
			displayAccountDetailRecord(&accountArray[i]);
	}
}

void getAccount(struct Account* ap) // get account information with typed account number
{
	printf("Account Data: New Record\n");
	printf("----------------------------------------\n");
	printf("Enter the account number: ");
	ap->accountNum = getPositiveInteger();
	putchar('\n');
	printf("Enter the account type (A=Agent | C=Customer): ");
	ap->accountType = getCharOption("AC");
	printf("\n");
}

void getAccountwithNum(struct Account* ap, int accountNum) // get account information with given account number by parameter
{
	ap->accountNum = accountNum;
	printf("New Account Data (Account#:%05d)\n", ap->accountNum);
	printf("----------------------------------------\n");
	printf("Enter the account type (A=Agent | C=Customer): ");
	ap->accountType = getCharOption("AC");
	printf("\n");
}

void getUserLogin(struct UserLogin* ulp) // get userlogin information
{
	printf("User Login Data Input\n");
	printf("----------------------------------------\n");
	getUserId(ulp->loginName, 1, 10);
	printf("Enter the display name (30 chars max): ");
	getCString(ulp->nameOfuser, 1, 30);
	getUserPw(ulp->password, 8, 8);
	printf("\n");
}

void getDemographic(struct Demographic* dp) // get demographic information
{
	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");


	printf("Enter birth year (current age must be between 18 and 110): ");
	dp->birthYear = getIntFromRange(currentYear() - 110, currentYear() - 18);

	printf("Enter the household Income: $");
	dp->houseHoldIncome = getPositiveDouble();
	getCountry(dp->country, 1, 30);
	printf("\n");
}

void getUserId(char* id, int from, int to) // get User id excluding whitespace
{
	int flag, i;
	do
	{
		flag = 1;
		printf("Enter user login (10 chars max): ");
		getCString(id, from, to);
		for (i = 0; id[i] != '\0'; i++)
		{
			if (isspace(id[i]))
			{
				printf("ERROR:  The user login must NOT contain whitespace characters.\n");
				flag = 0;
				break;
			}
		}
	} while (flag == 0);
}

void getUserPw(char* pw, int from, int to) //get user password with verification
{
	int flag, i, digit, lower, upper, punct;
	do
	{
		digit = 0;
		lower = 0;
		upper = 0;
		punct = 0;
		flag = 1;
		printf("Enter the password (must be 8 chars in length): ");
		getCString(pw, from, to);
		for (i = 0; pw[i] != '\0'; i++)
		{

			if (isdigit(pw[i]))
				digit++;
			if (islower(pw[i]))
				lower++;
			if (isupper(pw[i]))
				upper++;
			if (pw[i] == '!' || pw[i] == '@' || pw[i] == '#' || pw[i] == '$' || pw[i] == '%' || pw[i] == '^' || pw[i] == '&' || pw[i] == '*')
				punct++;
		}

		if (digit < 2 || lower < 2 || upper < 2 || punct < 2)
		{
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
			flag = 0;
		}
	} while (flag == 0);
}

void getCountry(char* country, int from, int to) // get country from user and convert it to capital alphabet
{
	int i;

	printf("Enter the country (30 chars max.): ");
	getCString(country, from, to);
	for (i = 0; country[i] != '\0'; i++)
	{
		if (islower(country[i]))
			country[i] = toupper(country[i]);
	}
}

int loadAccounts(struct Account* accounts, int sizeOfAccounts) // load accounts from accounts.txt
{ 

	FILE* fp = fopen("accounts.txt", "r");
	int i, count = 0;


	if (fp == NULL) {
		printf("account.txt doesn't exist!!\n");
		return -1;
	}
	else
	{
		for (i = 0; i < sizeOfAccounts && !feof(fp); i++)
		{
			if (fscanf(fp, "%d~%c~%[^~]~%[^~]~%[^~]~%d~%lf~%[^\n]%*c", &accounts[i].accountNum, &accounts[i].accountType, accounts[i].userLogin.nameOfuser, accounts[i].userLogin.loginName, accounts[i].userLogin.password, &accounts[i].demoGraphic.birthYear, &accounts[i].demoGraphic.houseHoldIncome, accounts[i].demoGraphic.country) == 8)
				count++;
		}
		fclose(fp);
	}

	return count;

}

int archiveAccount(struct Account account) // archive single account to accounts_arc.txt
{
	FILE* fp = fopen("accounts_arc.txt", "a");

	if (fp == NULL) {
		printf("accounts_arc.txt doesn't exist!!\n");
		return -1;
	}
	else
	{
		fprintf(fp, "%05d~%c~%s~%s~%s~%d~%lf~%s\n", account.accountNum, account.accountType, account.userLogin.nameOfuser, account.userLogin.loginName, account.userLogin.password, account.demoGraphic.birthYear, account.demoGraphic.houseHoldIncome, account.demoGraphic.country);
		fclose(fp);
	}

	return 0;

}

int countArchivedAccounts(void) //count archived accounts in accounts_arc.txt
{
	int accountNum = 0, count = 0;
	FILE* fp = fopen("accounts_arc.txt", "r");
	if (fp == NULL) {
		printf("accounts_arc.txt doesn't exist!!\n");
		return -1;
	}
	else
	{
		while (fscanf(fp, "%d%*[^\n]%*c", &accountNum)==1)
		{
			count++;
		}
		fclose(fp);
	}
	return  count;
}