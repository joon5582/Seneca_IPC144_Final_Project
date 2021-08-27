// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Junwoo Lee
//  Student ID    : 124395203
//  Student Email : jlee648@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_
#include "account.h"
#include "ticket.h"

struct AccountTicketingData
{
	struct Account* accounts;
	const int ACCOUNT_MAX_SIZE;
	struct Ticket* tickets;
	const int TICKET_MAX_SIZE;
};

void applicationStartup(struct AccountTicketingData accountTicketingDataArray[]);
int menuLogin(struct AccountTicketingData accountTicketingDataArray[]);
void menuAgent(struct AccountTicketingData accountTicketingDataArray[], const struct Account ap[]);
void menuCustomer(struct AccountTicketingData accountTicketingDataArray[], const struct Account ap[]);
void pauseExecution(void);
int findAccountIndexByAcctNum(int accountNum, const struct Account* accountArray, int maxAccountNum, unsigned int flag);
int findTicketIndexByTicketNum(int ticketNum, const struct Ticket* ticketArray, int maxTicketNum, unsigned int flag);
void updateTicketForAgent(struct Ticket* tp, const struct Account* ap);
void updateTicketForCustomer(struct Ticket* tp);
void updateAccount(struct Account* ap);
void updateUserLogin(struct UserLogin* ulp);
void updateDemographic(struct Demographic* dp);


#endif