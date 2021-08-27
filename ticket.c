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
#include "ticket.h"
#include "account.h"
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#include <stdio.h>
#include <string.h>



int SaveAllTickets(struct AccountTicketingData* data) //update all tickets to tickets.txt file
{
	FILE* fp = fopen("tickets.txt", "w");
	int i, j, count = 0;


	if (fp == NULL) {
		printf("tickets.txt doesn't exist!!\n");
		return -1;
	}
	else
	{

		for (i = 0; i < data->TICKET_MAX_SIZE; i++)
		{
			if (data->tickets[i].numberOfticket != 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|", data->tickets[i].numberOfticket, data->tickets[i].customerAccountNumber, data->tickets[i].ticketStatusIndicator, data->tickets[i].subjectLine, data->tickets[i].numOfmessageCounter);
				for (j = 0; j < data->tickets[i].numOfmessageCounter; j++)
				{
					fprintf(fp, "%c|%s|%s|", data->tickets[i].messages[j].accountType, data->tickets[i].messages[j].nameOfuser, data->tickets[i].messages[j].messageDetail);
				}
				fputc('\n', fp);
				count++;
			}
		}

		fclose(fp);
	}
	return count;
}

int archiveClosedTickets(struct AccountTicketingData* data) //archive all closed tickets to tickets_arc.txt file
{
	FILE* fp = fopen("tickets_arc.txt", "a");
	int i, j, count = 0;


	if (fp == NULL) {
		printf("tickets_arc.txt doesn't exist!!\n");
		return -1;
	}
	else
	{

		for (i = 0; i < data->TICKET_MAX_SIZE; i++)
		{
			if (data->tickets[i].numberOfticket != 0 && data->tickets[i].ticketStatusIndicator == 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|", data->tickets[i].numberOfticket, data->tickets[i].customerAccountNumber, data->tickets[i].ticketStatusIndicator, data->tickets[i].subjectLine, data->tickets[i].numOfmessageCounter);
				for (j = 0; j < data->tickets[i].numOfmessageCounter; j++)
				{
					fprintf(fp, "%c|%s|%s|", data->tickets[i].messages[j].accountType, data->tickets[i].messages[j].nameOfuser, data->tickets[i].messages[j].messageDetail);
				}
				fputc('\n', fp);
				data->tickets[i].numberOfticket = 0;
				count++;
			}
		}

		fclose(fp);
	}
	return count;
}

void openMessages(const struct Ticket* ticket) //display all messages of the ticket given by parameter
{
	int i;
	const struct Message* messages;
	messages = ticket->messages;
	printf("================================================================================\n");
	printf("%06d (%s) Re: %s\n", ticket->numberOfticket, ticket->ticketStatusIndicator ? "ACTIVE" : "CLOSED", ticket->subjectLine);
	printf("================================================================================\n");

	for (i = 0; messages[i].accountType != 0 && i < MESSAGE_SIZE; i++)
	{
		printf("%s (%s):\n", messages[i].accountType == 'C' ? "CUSTOMER" : "AGENT", messages[i].nameOfuser);
		printf("   %s\n", messages[i].messageDetail);
		putchar('\n');
		if ((i + 1) % 5 == 0) //for every five messages, pause execution.
			pauseExecution();


	}

	if (i % 5 != 0)
		pauseExecution();

}

void displayTicketsHeader(void) //display ticket header for agent's menu
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayCustomerTicketsHeader(void) //display ticket header for customer's menu
{
	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
}

void displayCustomerTicketsRecord(const struct AccountTicketingData* accountTicketingDataArray, const struct Account* ap) // display customer's (given by 2nd parameter) all tickets
{
	int i;
	struct Ticket tempTicket;
	for (i = 0; i < accountTicketingDataArray->TICKET_MAX_SIZE; i++)
	{
		tempTicket = accountTicketingDataArray->tickets[i];
		if (tempTicket.numberOfticket != 0 && tempTicket.customerAccountNumber == ap->accountNum)
		{
			printf("%06d %-6s %-30s    %2d\n", tempTicket.numberOfticket, tempTicket.ticketStatusIndicator ? "ACTIVE" : "CLOSED", tempTicket.subjectLine, tempTicket.numOfmessageCounter);
		}
	}
	printf("------ ------ ------------------------------ --------\n");
}
void displayNewTicketsRecord(const struct AccountTicketingData* accountTicketingDataArray)
{ //display all new tickets (ACTIVE and having only singlge message)
	int i;
	struct Ticket tempTicket;

	for (i = 0; i < accountTicketingDataArray->TICKET_MAX_SIZE; i++)
	{
		tempTicket = accountTicketingDataArray->tickets[i];

		if (tempTicket.numberOfticket != 0 && tempTicket.ticketStatusIndicator == 1 && tempTicket.numOfmessageCounter == 1)
		{
			printf("%06d %05d %-15s %-6s %-30s    %2d\n", tempTicket.numberOfticket, tempTicket.customerAccountNumber, tempTicket.messages[0].nameOfuser, "ACTIVE", tempTicket.subjectLine, tempTicket.numOfmessageCounter);
		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}
void displayActiveTicketsRecord(const struct AccountTicketingData* accountTicketingDataArray)
{ //display all active tickets
	int i;
	struct Ticket tempTicket;
	for (i = 0; i < accountTicketingDataArray->TICKET_MAX_SIZE; i++)
	{
		tempTicket = accountTicketingDataArray->tickets[i];

		if (tempTicket.numberOfticket != 0 && tempTicket.ticketStatusIndicator == 1)
		{
			printf("%06d %05d %-15s %-6s %-30s    %2d\n", tempTicket.numberOfticket, tempTicket.customerAccountNumber, tempTicket.messages[0].nameOfuser, "ACTIVE", tempTicket.subjectLine, tempTicket.numOfmessageCounter);
		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}
void displayClosedTicketsRecord(const struct AccountTicketingData* accountTicketingDataArray)
{ //display all closed tickets
	int i;
	struct Ticket tempTicket;

	for (i = 0; i < accountTicketingDataArray->TICKET_MAX_SIZE; i++)
	{
		tempTicket = accountTicketingDataArray->tickets[i];

		if (tempTicket.numberOfticket != 0 && tempTicket.ticketStatusIndicator == 0)
		{
			printf("%06d %05d %-15s %-6s %-30s    %2d\n", tempTicket.numberOfticket, tempTicket.customerAccountNumber, tempTicket.messages[0].nameOfuser, "CLOSED", tempTicket.subjectLine, tempTicket.numOfmessageCounter);
		}
	}
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}
void getTicketwithNum(struct Ticket* tp, int ticketNum, const struct Account* ap)
{ //create ticket with given number(by 2nd parameter)
	tp->customerAccountNumber = ap->accountNum;
	tp->numberOfticket = ticketNum;
	tp->numOfmessageCounter = 0;
	tp->ticketStatusIndicator = 1;
	strcpy(tp->messages[0].nameOfuser, ap->userLogin.nameOfuser);
	printf("New Ticket (Ticket#:%06d)\n", tp->numberOfticket);
	printf("----------------------------------------\n");
	printf("Enter the ticket SUBJECT (30 chars. maximum): ");
	getCString(tp->subjectLine, 1, 30);
	putchar('\n');
	writeMessageBycustomer(tp);
	putchar('\n');
}

void writeMessageBycustomer(struct Ticket* tp)
{ //write message on ticket for customer
	if (tp->numOfmessageCounter >= MESSAGE_SIZE)
	{
		printf("ERROR: Message limit has been reached, call ITS Support!\n");

	}
	else
	{
		struct Message* message;
		message = &(tp->messages[tp->numOfmessageCounter]);
		message->accountType = 'C';
		strcpy(message->nameOfuser, tp->messages[0].nameOfuser);
		printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
		getCString(message->messageDetail, 1, 150);
		(tp->numOfmessageCounter)++;

	}
}

void writeMessageByagent(struct Ticket* tp, const struct Account* ap)
{ //write message on ticket for agent
	if (tp->numOfmessageCounter >= MESSAGE_SIZE)
	{
		printf("ERROR: Message limit has been reached, call ITS Support!\n");

	}
	else
	{
		struct Message* message;
		message = &(tp->messages[tp->numOfmessageCounter]);
		message->accountType = 'A';
		strcpy(message->nameOfuser, ap->userLogin.nameOfuser);
		printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
		getCString(message->messageDetail, 1, 150);
		(tp->numOfmessageCounter)++;

	}
}

int loadTickets(struct Ticket* tickets, int sizeOfTickets)
{ //load tickets from tickets.txt file
	FILE* fp = fopen("tickets.txt", "r");
	int i, j, count = 0;


	if (fp == NULL) {
		printf("tickets.txt doesn't exist!!\n");
		return -1;
	}
	else
	{
		for (i = 0; i < sizeOfTickets && !feof(fp); i++)
		{
			if (fscanf(fp, "%d|%d|%d|%[^|]|%d|", &tickets[i].numberOfticket, &tickets[i].customerAccountNumber, &tickets[i].ticketStatusIndicator, tickets[i].subjectLine, &tickets[i].numOfmessageCounter) == 5)
			{

				for (j = 0; j < tickets[i].numOfmessageCounter; j++)
				{
					fscanf(fp, "%c|%[^|]|%[^|]|", &tickets[i].messages[j].accountType, (char*)&tickets[i].messages[j].nameOfuser, tickets[i].messages[j].messageDetail);
				}
				count++;
			}
		}
		fclose(fp);
	}

	return count;
}
int archiveTicket(struct Ticket ticket)
{ //archive single ticekt to tickets_arc.txt
	FILE* fp = fopen("tickets_arc.txt", "a");
	int i;


	if (fp == NULL) {
		printf("tickets_arc.txt doesn't exist!!\n");
		return -1;
	}
	else
	{

		fprintf(fp, "%d|%d|%d|%s|%d|", ticket.numberOfticket, ticket.customerAccountNumber, ticket.ticketStatusIndicator, ticket.subjectLine, ticket.numOfmessageCounter);
		for (i = 0; i < ticket.numOfmessageCounter; i++)
		{
			fprintf(fp, "%c|%s|%s|", ticket.messages[i].accountType, ticket.messages[i].nameOfuser, ticket.messages[i].messageDetail);
		}
		fputc('\n', fp);
		fclose(fp);
	}
	return 0;
}

int countArchivedTickets(int* tc, int* mc)
{ //count archived tickets in tickets_arc.txt
	int ticketNum = 0, numOfMessage, ticketCount = 0, messageCount = 0;
	FILE* fp = fopen("tickets_arc.txt", "r");
	if (fp == NULL) {
		printf("tickets_arc.txt doesn't exist!!\n");
		return -1;
	}
	else
	{
		while (fscanf(fp, "%d|%*d|%*d|%*[^|]|%d|%*[^\n]%*c", &ticketNum, &numOfMessage) == 2)
		{
			ticketCount++;
			messageCount += numOfMessage;
		}
		*tc = ticketCount;
		*mc = messageCount;
		fclose(fp);
	}
	return 0;
}
