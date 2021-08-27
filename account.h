// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Junwoo Lee
//  Student ID    : 124395203
//  Student Email : jlee648@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#ifndef ACCOUNT_H_
#define ACCOUNT_H_


struct Demographic
{
	int birthYear;
	double houseHoldIncome;
	char country[31];
	
};

struct UserLogin
{
	char nameOfuser[31];
	char loginName[11];
	char password[9];
};

struct Account
{
	int accountNum;
	char accountType; 
	struct UserLogin userLogin;
	struct Demographic demoGraphic;
};
struct AccountTicketingData;
int SaveAllAccounts(struct AccountTicketingData* data);
void displayAccountSummaryHeader(void);
void displayAccountDetailHeader(void);
void displayAccountSummaryRecord(const struct Account* ap);
void displayAccountDetailRecord(const struct Account* ap);
void displayAllAccountSummaryRecords(const struct Account* accountArray, int maxAccountNum);
void displayAllAccountDetailRecords(const struct Account* accountArray, int maxAccountNum);
void getAccount(struct Account* ap);
void getAccountwithNum(struct Account* ap, int accountNum);
void getUserLogin(struct UserLogin* ulp);
void getDemographic(struct Demographic* dp);
void getUserId(char* id, int from, int to);
void getUserPw(char* pw, int from, int to);
void getCountry(char* country, int from, int to);
int loadAccounts(struct Account* accounts, int sizeOfAccounts);
int archiveAccount(struct Account account);
int countArchivedAccounts(void);
#endif