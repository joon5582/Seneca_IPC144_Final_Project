// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Junwoo Lee
//  Student ID    : 124395203
//  Student Email : jlee648@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#ifndef TICKET_H
#define TICKET_H
#define MESSAGE_SIZE 20
#include "account.h"

struct Message
{
	char accountType;
	char nameOfuser[31];
	char messageDetail[151];
};

struct Ticket
{
	int numberOfticket;
	int customerAccountNumber;
	int ticketStatusIndicator;
	char subjectLine[31];
	int numOfmessageCounter;
	struct Message messages[MESSAGE_SIZE];
};
struct AccountTicketingData;

int SaveAllTickets(struct AccountTicketingData* data);
int archiveClosedTickets(struct AccountTicketingData* data);
void openMessages(const struct Ticket* ticket);
void displayTicketsHeader(void);
void displayCustomerTicketsHeader(void);
void displayCustomerTicketsRecord(const struct AccountTicketingData* accountTicketingDataArray, const struct Account* ap);
void displayNewTicketsRecord(const struct AccountTicketingData* accountTicketingDataArray);
void displayActiveTicketsRecord(const struct AccountTicketingData* accountTicketingDataArray);
void displayClosedTicketsRecord(const struct AccountTicketingData* accountTicketingDataArray);
void getTicketwithNum(struct Ticket* tp, int ticketNum, const struct Account* ap);
void writeMessageBycustomer(struct Ticket* tp);
void writeMessageByagent(struct Ticket* tp, const struct Account* ap);
int loadTickets(struct Ticket* tickets, int sizeOfTickets);
int archiveTicket(struct Ticket ticket);
int countArchivedTickets(int* tc, int* mc);
#endif
