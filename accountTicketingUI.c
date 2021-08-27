// ===================================================================================
//  Assignment: 2 
//  Milestone : 4
// ===================================================================================
//  Student Name  : Junwoo Lee
//  Student ID    : 124395203
//  Student Email : jlee648@myseneca.ca
//  Course Section: NBB
// ===================================================================================

#include "accountTicketingUI.h"
#include "account.h"
#include "commonHelpers.h"
#include <stdio.h>
#include <string.h>

void applicationStartup(struct AccountTicketingData accountTicketingDataArray[]) //start application with menuLogin
{
	menuLogin(accountTicketingDataArray);
}

int menuLogin(struct AccountTicketingData accountTicketingDataArray[]) // Login menu function
{
	int selectnum, flag, isFound = -1, attemptsRemaining;
	char yesno;
	char tempLogin[31];
	char tempPW[31];
	struct Account* ap = NULL;
	do
	{
		flag = 0;
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n");
		putchar('\n');
		printf("Selection: ");
		selectnum = getIntFromRange(0, 1);
		putchar('\n');
		if (selectnum == 1)  // login to system. user enter account number, userLogin(id) and password 
		{
			attemptsRemaining = 3; //give user up to 3 attempts
			do
			{
				printf("Enter the account#: ");
				isFound = findAccountIndexByAcctNum(0, (const struct Account*)accountTicketingDataArray->accounts, accountTicketingDataArray->ACCOUNT_MAX_SIZE, 1);
				printf("User Login    : ");
				getCString(tempLogin, 0, 30);
				printf("Password      : ");
				getCString(tempPW, 0, 30);
				if (isFound == -1 || strcmp(tempLogin, accountTicketingDataArray->accounts[isFound].userLogin.loginName) || strcmp(tempPW, accountTicketingDataArray->accounts[isFound].userLogin.password)) //verify account information
				{
					printf("INVALID user login/password combination! [attempts remaining:%d]\n", --attemptsRemaining); // if user input didn't correctly matched, display error messages with remaining attempts
					putchar('\n');
				}
				else
					break; // if user input matched, break loop
			} while (attemptsRemaining > 0);

			if (attemptsRemaining <= 0)
			{
				printf("ERROR:  Login failed!\n");
				putchar('\n');
				pauseExecution();
			}

			else
			{
				putchar('\n');
				if (accountTicketingDataArray->accounts[isFound].accountType == 'A')
				{
					ap = &(accountTicketingDataArray->accounts[isFound]);
					menuAgent(accountTicketingDataArray, ap);  //login with Agent account
				}
				else if (accountTicketingDataArray->accounts[isFound].accountType == 'C')
				{
					ap = &(accountTicketingDataArray->accounts[isFound]);
					menuCustomer(accountTicketingDataArray, ap); //login with Customer account
				}
			}
		}
		else
		{
			printf("Are you sure you want to exit? ([Y]es|[N]o): "); 
			yesno = getCharOption("yYnN");       //exit program
			putchar('\n');
			if (yesno == 'y' || yesno == 'Y')
			{
				flag = 1;
				printf("==============================================\n");
				printf("Account Ticketing System - Terminated\n");
				printf("==============================================\n");
			}
		}
	} while (flag == 0);
	return isFound;
}

void menuAgent(struct AccountTicketingData accountTicketingDataArray[], const struct Account ap[])
{   //agent's menu after login
	int selectnum, i, flag, isFound;
	char yesno;

	struct Account* newap = NULL;
	do
	{
		newap = NULL;
		flag = 0;
		printf("AGENT: %s (%d)\n", ap->userLogin.nameOfuser, ap->accountNum);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n");
		putchar('\n');
		printf("Selection: ");

		selectnum = getIntFromRange(0, 12);
		putchar('\n');
		if (selectnum == 1) // add new account
		{
			int maxAccountnum = 0;
			for (i = 0; i < accountTicketingDataArray->ACCOUNT_MAX_SIZE; i++) //find empty account which has account number as 0
			{
				if (accountTicketingDataArray->accounts[i].accountNum == 0)
				{
					newap = &accountTicketingDataArray->accounts[i];
					break;
				}
			}
			if (newap == NULL)
			{
				printf("ERROR: Account listing is FULL, call ITS Support!\n");
				putchar('\n');
				pauseExecution();
			}
			else
			{
				for (i = 0; i < accountTicketingDataArray->ACCOUNT_MAX_SIZE; i++) // calculate max account number of current account array
				{
					if (accountTicketingDataArray->accounts[i].accountNum > maxAccountnum)
					{
						maxAccountnum = accountTicketingDataArray->accounts[i].accountNum;
					}
				}
				getAccountwithNum(newap, maxAccountnum + 1); // create account with account number which is maxaccount number + 1
				getUserLogin(&(newap->userLogin)); //get user login datas
				getDemographic(&(newap->demoGraphic)); //get demographic datas
				printf("*** New account added! ***\n");
				putchar('\n');
				pauseExecution();
			}
		}
		if (selectnum == 2)  // modify existing account
		{
			printf("Enter the account#: "); 
			isFound = findAccountIndexByAcctNum(0, (const struct Account*)accountTicketingDataArray->accounts, accountTicketingDataArray->ACCOUNT_MAX_SIZE, 1);
			putchar('\n');
			if (isFound == -1)
			{
				printf("ERROR: Access Denied.\n");
				pauseExecution();
			}
			else
				updateAccount(&(accountTicketingDataArray->accounts[isFound])); // call updateAccount menu
		}
		if (selectnum == 3) //remove account
		{
			printf("Enter the account#: ");
			isFound = findAccountIndexByAcctNum(0, (const struct Account*)accountTicketingDataArray->accounts, accountTicketingDataArray->ACCOUNT_MAX_SIZE, 1);
			if (isFound == -1)
			{
				printf("ERROR: Access Denied.\n");
				pauseExecution();
			}
			else if (accountTicketingDataArray->accounts[isFound].accountNum == ap->accountNum)
			{   // if agent enter his/her own account, print error message
				putchar('\n');
				printf("ERROR: You can't remove your own account!\n");
				putchar('\n');
				pauseExecution();
			}
			else
			{
				displayAccountDetailHeader();
				displayAccountDetailRecord(&(accountTicketingDataArray->accounts[isFound]));
				putchar('\n');
				printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
				yesno = getCharOption("YN");
				putchar('\n');
				if (yesno == 'Y')
				{
					for (i = 0; i < accountTicketingDataArray->TICKET_MAX_SIZE; i++)
					{
						// find all tickets that has given account number
						if (accountTicketingDataArray->tickets[i].numberOfticket!=0 && accountTicketingDataArray->tickets[i].customerAccountNumber == accountTicketingDataArray->accounts[isFound].accountNum)
						{     //if found ticket is ACTIVE status, just remove it from array
							if (accountTicketingDataArray->tickets[i].ticketStatusIndicator == 1)
								accountTicketingDataArray->tickets[i].numberOfticket = 0;
							else if (accountTicketingDataArray->tickets[i].ticketStatusIndicator == 0)
							{  //if found ticket is CLOSED status, archive this ticket and then remove it from array
								archiveTicket(accountTicketingDataArray->tickets[i]);
								accountTicketingDataArray->tickets[i].numberOfticket = 0;
							}
						}
					}
					archiveAccount(accountTicketingDataArray->accounts[isFound]); //archive the account
					accountTicketingDataArray->accounts[isFound].accountNum = 0;  //remove the account
					printf("*** Account Removed! ***\n");
					putchar('\n');
					pauseExecution();
				}
				if (yesno == 'N')
				{
					printf("*** No changes made! ***\n");
					putchar('\n');
					pauseExecution();
				}
			}
		}
		if (selectnum == 4) //display all accounts with summary view
		{
			displayAllAccountSummaryRecords((const struct Account*)accountTicketingDataArray->accounts, accountTicketingDataArray->ACCOUNT_MAX_SIZE);
			putchar('\n');
			pauseExecution();
		}
		if (selectnum == 5) //display all accounts with detailed view
		{
			displayAllAccountDetailRecords((const struct Account*)accountTicketingDataArray->accounts, accountTicketingDataArray->ACCOUNT_MAX_SIZE);
			putchar('\n');
			pauseExecution();
		}
		if (selectnum == 6) //List all new tickets (ACTIVE and having only singlge message)
		{
			int inputNum;
			do
			{
				inputNum = 0;
				displayTicketsHeader();
				displayNewTicketsRecord((const struct AccountTicketingData*)accountTicketingDataArray);
				putchar('\n');
				printf("Enter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				inputNum = getPositiveOrZeroInteger();   //prompt user the ticket number of which he/she want to see messages
				putchar('\n');
				if (inputNum != 0)
				{
					isFound = findTicketIndexByTicketNum(inputNum, accountTicketingDataArray->tickets, accountTicketingDataArray->TICKET_MAX_SIZE, 0);
					if (isFound == -1)
					{
						printf("ERROR: Invalid ticket number.\n");
						putchar('\n');
						pauseExecution();
					}
					else
					{
						openMessages((const struct Ticket*)&(accountTicketingDataArray->tickets[isFound])); //if user type ticket number to see all messages of the ticket, call openMessages function 
					}
				}
			} while (inputNum != 0);
		}
		if (selectnum == 7) // List all ACTIVE tickets (logic is same to menu 6)
		{
			int inputNum;
			do
			{
				inputNum = 0;
				displayTicketsHeader();
				displayActiveTicketsRecord((const struct AccountTicketingData*)accountTicketingDataArray);
				putchar('\n');
				printf("Enter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				inputNum = getPositiveOrZeroInteger();
				putchar('\n');
				if (inputNum != 0)
				{
					isFound = findTicketIndexByTicketNum(inputNum, accountTicketingDataArray->tickets, accountTicketingDataArray->TICKET_MAX_SIZE, 0);
					if (isFound == -1)
					{
						printf("ERROR: Invalid ticket number.\n");
						putchar('\n');
						pauseExecution();
					}
					else
					{
						openMessages((const struct Ticket*)&(accountTicketingDataArray->tickets[isFound]));
					}
				}
			} while (inputNum != 0);
		}
		if (selectnum == 8) //List all CLOSED tickets (logic is same to menu 6)
		{
			int inputNum;
			do
			{
				inputNum = 0;
				displayTicketsHeader();
				displayClosedTicketsRecord((const struct AccountTicketingData*)accountTicketingDataArray);
				putchar('\n');
				printf("Enter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				inputNum = getPositiveOrZeroInteger();
				putchar('\n');
				if (inputNum != 0)
				{
					isFound = findTicketIndexByTicketNum(inputNum, accountTicketingDataArray->tickets, accountTicketingDataArray->TICKET_MAX_SIZE, 0);
					if (isFound == -1)
					{
						printf("ERROR: Invalid ticket number.\n");
						putchar('\n');
						pauseExecution();
					}
					else
					{
						openMessages((const struct Ticket*)&(accountTicketingDataArray->tickets[isFound]));
					}
				}
			} while (inputNum != 0);
		}
		if (selectnum == 9) //manage ticket
		{
			printf("Enter ticket number: "); //prompt ticket number
			isFound = findTicketIndexByTicketNum(0, (const struct Ticket*)accountTicketingDataArray->tickets, accountTicketingDataArray->TICKET_MAX_SIZE, 1);
			putchar('\n');
			if (isFound == -1)
			{
				printf("ERROR: Access Denied.\n");
				pauseExecution();
			}
			else
				updateTicketForAgent(&(accountTicketingDataArray->tickets[isFound]), ap); // call updateTicketForAgent menu
		}
		if (selectnum == 10) //archive all closed tickets
		{
			printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			
			yesno = getCharOption("YN");
			putchar('\n');
			if (yesno == 'Y')
				printf("*** %d tickets archived ***\n", archiveClosedTickets(accountTicketingDataArray));
			else
				printf("*** No changes made! ***\n");
			putchar('\n');
			pauseExecution();
		}
		if (selectnum == 11) //count archived number of accounts
		{
			printf("There are %d account(s) currently archived.\n", countArchivedAccounts());
			putchar('\n');
			pauseExecution();
		}
		if (selectnum == 12) //count archived number of tickets and messages
		{
			int tc, mc;
			countArchivedTickets(&tc, &mc);
			printf("There are %d ticket(s) and a total of %d message(s) archived.\n", tc, mc);
			putchar('\n');
			pauseExecution();
		}
		if (selectnum == 0) // logout with updating current accounts and tickets
		{
			flag = 1;
			printf("Saving session modifications...\n");
			printf("   %d account saved.\n", SaveAllAccounts(accountTicketingDataArray));
			printf("   %d tickets saved.\n", SaveAllTickets(accountTicketingDataArray));
			printf("### LOGGED OUT ###\n");
			putchar('\n');
		}
	} while (flag == 0);
}

void menuCustomer(struct AccountTicketingData accountTicketingDataArray[], const struct Account ap[])
{ //customer's menu after login
	int i, selectnum, flag, isFound;
	struct Ticket* newtp = NULL;

	do
	{
		newtp = NULL;
		flag = 0;
		printf("CUSTOMER: %s (%d)\n", ap->userLogin.nameOfuser, ap->accountNum);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n");
		putchar('\n');
		printf("Selection: ");
		selectnum = getIntFromRange(0, 4);
		putchar('\n');
		if (selectnum == 1) //view detail of current login account
		{
			displayAccountDetailHeader();
			displayAccountDetailRecord(ap);
			putchar('\n');
			pauseExecution();
		}
		if (selectnum == 2) //create new ticket to current login account
		{
			int maxTicketnum = 0;
			for (i = 0; i < accountTicketingDataArray->TICKET_MAX_SIZE; i++)
			{ // search empty ticket
				if (accountTicketingDataArray->tickets[i].numberOfticket == 0)
				{
					newtp = &accountTicketingDataArray->tickets[i];
					break;
				}
			}
			if (newtp == NULL)
			{
				printf("ERROR: Ticket listing is FULL, call ITS Support!\n");
				putchar('\n');
				pauseExecution();
			}
			else
			{
				for (i = 0; i < accountTicketingDataArray->TICKET_MAX_SIZE; i++)
				{ //calculate max ticket number of current ticket array
					if (accountTicketingDataArray->tickets[i].numberOfticket > maxTicketnum)
					{
						maxTicketnum = accountTicketingDataArray->tickets->numberOfticket;
					}
				}
				getTicketwithNum(newtp, maxTicketnum + 1, ap); //create ticket with ticket number which is maxticket number + 1
				printf("*** New ticket created! ***\n");
				putchar('\n');
				pauseExecution();
			}
		}
		if (selectnum == 3) //modify current login account's ticket
		{
			printf("Enter ticket number: ");
			isFound = findTicketIndexByTicketNum(0, (const struct Ticket*)accountTicketingDataArray->tickets, accountTicketingDataArray->TICKET_MAX_SIZE, 1);
			putchar('\n');
			if (isFound == -1 || accountTicketingDataArray->tickets[isFound].customerAccountNumber != ap->accountNum) {
				printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n");
				putchar('\n');
				pauseExecution();
			}
			else if (accountTicketingDataArray->tickets[isFound].ticketStatusIndicator == 0)
			{
				printf("ERROR: Ticket is closed - changes are not permitted.\n");
				putchar('\n');
				pauseExecution();
			}
			else
				updateTicketForCustomer(&(accountTicketingDataArray->tickets[isFound])); // call updateTicketForCustomer

		}
		if (selectnum == 4) //List current login account's all tickets
		{
			int inputNum;
			do
			{
				inputNum = 0;
				displayCustomerTicketsHeader();
				displayCustomerTicketsRecord((const struct AccountTicketingData*)accountTicketingDataArray, ap);
				putchar('\n');
				printf("Enter the ticket number to view the messages or\n");
				printf("0 to return to previous menu: ");
				inputNum = getPositiveOrZeroInteger(); //prompt user the ticket number of which he/she want to see messages
				putchar('\n');
				if (inputNum != 0)
				{
					isFound = findTicketIndexByTicketNum(inputNum, accountTicketingDataArray->tickets, accountTicketingDataArray->TICKET_MAX_SIZE, 0);
					if (isFound == -1 || accountTicketingDataArray->tickets[isFound].customerAccountNumber != ap->accountNum) {
						printf("ERROR: Invalid ticket number - you may only access your own tickets.\n");
						putchar('\n'); //verify if user typed his/her own ticket number
						pauseExecution();
					}
					else
					{
						openMessages((const struct Ticket*)&(accountTicketingDataArray->tickets[isFound])); //if user type ticket number correctly to see all messages of the ticket, call openMessages function 
					}
				}
			} while (inputNum != 0);
		}
		if (selectnum == 0) //Logout with updating current tickets
		{
			flag = 1;
			printf("Saving session modifications...\n");
			printf("   %d tickets saved.\n", SaveAllTickets(accountTicketingDataArray));
			printf("### LOGGED OUT ###\n");
			putchar('\n');
		}
	} while (flag == 0);
}
int findAccountIndexByAcctNum(int accountNum, const struct Account* accountArray, int maxAccountNum, unsigned int flag) //find given account number and return the found account's number. If not found, return -1
{
	int an, i, foundIndex = -1;
	if (flag != 0)
	{

		an = getPositiveInteger();
	}
	else
		an = accountNum;
	for (i = 0; i < maxAccountNum; i++)
	{
		if (accountArray[i].accountNum == an)
		{
			foundIndex = i;
			break;
		}

	}
	return foundIndex;
}

int findTicketIndexByTicketNum(int ticketNum, const struct Ticket* ticketArray, int maxTicketNum, unsigned int flag) //find given ticket number and return the found ticket's number. If not found, return -1
{
	int tn, i, foundIndex = -1;
	if (flag != 0)
	{

		tn = getPositiveInteger();
	}
	else
		tn = ticketNum;
	for (i = 0; i < maxTicketNum; i++)
	{
		if (ticketArray[i].numberOfticket == tn)
		{
			foundIndex = i;
			break;
		}
	}
	return foundIndex;
}

void updateTicketForAgent(struct Ticket* tp, const struct Account* ap)
{ //update ticket menu for agent
	int selectnum, flag;
	char yesNo;
	do {
		flag = 0;
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", tp->numberOfticket);
		printf("----------------------------------------\n");
		printf("Status  : %6s\n", tp->ticketStatusIndicator ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", tp->subjectLine);
		printf("Acct#   : %5d\n", tp->customerAccountNumber);
		printf("Customer: %s\n", tp->messages[0].nameOfuser);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		selectnum = getIntFromRange(0, 3);
		putchar('\n');
		if (selectnum == 1) //add a message to this ticket
		{
			if (tp->ticketStatusIndicator == 0)
			{
				printf("ERROR: Ticket is closed - new messages are not permitted.\n");
				putchar('\n');
			}
			else
			{
				writeMessageByagent(tp, ap);
				putchar('\n');
			}
		}
		if (selectnum == 2) //close this ticket
		{
			if (tp->ticketStatusIndicator == 0)
			{
				printf("ERROR: Ticket is already closed!\n");
			}
			else
			{
				printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				yesNo = getCharOption("YN");
				if (yesNo == 'Y')
				{
					tp->ticketStatusIndicator = 0;
					if (tp->numOfmessageCounter < MESSAGE_SIZE)
					{
						putchar('\n');
						printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
						yesNo = getCharOption("YN");
						if (yesNo == 'Y')
						{
							putchar('\n');
							writeMessageByagent(tp, ap);
						}
					}
				}
				putchar('\n');
				printf("*** Ticket closed! ***\n");
			}
			putchar('\n');
		}
		if (selectnum == 3) //reopen this ticket
		{
			if (tp->ticketStatusIndicator == 1)
			{
				printf("ERROR: Ticket is already active!\n");
			}
			else
			{
				printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				yesNo = getCharOption("YN");
				if (yesNo == 'Y')
				{
					tp->ticketStatusIndicator = 1;
					putchar('\n');
					printf("*** Ticket re-opened! ***\n");
				}
			}
			putchar('\n');
		}
		if (selectnum == 0)//exit
		{
			flag = 1;
		}
	} while (flag == 0);
}

void updateTicketForCustomer(struct Ticket* tp)
{//update ticket menu for customer
	int selectnum, flag;
	char yesNo;
	do {
		flag = 0;
		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", tp->numberOfticket);
		printf("----------------------------------------\n");
		printf("Status  : %6s\n", tp->ticketStatusIndicator ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", tp->subjectLine);
		printf("----------------------------------------\n");
		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		selectnum = getIntFromRange(0, 3);
		putchar('\n');
		if (selectnum == 1) //modify the subject of this ticket
		{
			printf("Enter the revised ticket SUBJECT (30 chars. maximum): ");
			getCString(tp->subjectLine, 1, 30);
			putchar('\n');
		}
		if (selectnum == 2) // add a message to this ticket
		{
			writeMessageBycustomer(tp);
			putchar('\n');
		}
		if (selectnum == 3) //close this ticket
		{
			printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			yesNo = getCharOption("YN");
			if (yesNo == 'Y')
			{
				tp->ticketStatusIndicator = 0;
				flag = 1;
				if (tp->numOfmessageCounter < MESSAGE_SIZE)
				{
					putchar('\n');
					printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
					yesNo = getCharOption("YN");
					if (yesNo == 'Y')
					{
						putchar('\n');
						writeMessageBycustomer(tp);
					}
				}
			}
			putchar('\n');
			printf("*** Ticket closed! ***\n");
			putchar('\n');
			pauseExecution();
		}
		if (selectnum == 0) //exit
		{
			flag = 1;
			pauseExecution();
		}
	} while (flag == 0);
}

void updateAccount(struct Account* ap)
{ //update account menu for agent
	int selectnum, flag;
	do {
		flag = 0;
		printf("Account: %05d - Update Options\n", ap->accountNum);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", ap->accountType);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		selectnum = getIntFromRange(0, 3);
		putchar('\n');
		if (selectnum == 1) //update account type
		{
			printf("Enter the account type (A=Agent | C=Customer): ");
			ap->accountType = getCharOption("AC");
		}
		if (selectnum == 2) //update user login
		{
			updateUserLogin(&(ap->userLogin));
		}
		if (selectnum == 3) //update user demographic
		{
			updateDemographic(&(ap->demoGraphic));
		}
		if (selectnum == 0) //exit
		{
			flag = 1;
		}
	} while (flag == 0);

}
void updateUserLogin(struct UserLogin* ulp)
{ //update user login
	int selectnum, flag;
	do {
		flag = 0;
		printf("User Login: %s - Update Options\n", ulp->loginName);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", ulp->nameOfuser);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		selectnum = getIntFromRange(0, 2);
		putchar('\n');
		if (selectnum == 1)
		{ //update display name
			printf("Enter the display name (30 chars max): ");
			getCString(ulp->nameOfuser, 1, 30);
			putchar('\n');
		}
		if (selectnum == 2)
		{ //update password
			getUserPw(ulp->password, 8, 8);
			putchar('\n');
		}
		if (selectnum == 0) //exit
		{
			flag = 1;
		}
	} while (flag == 0);
}
void updateDemographic(struct Demographic* dp)
{ //update demographic
	int selectnum, flag;
	do {
		flag = 0;
		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", dp->houseHoldIncome);
		printf("2) Country (current value: %s)\n", dp->country);
		printf("0) Done\n");
		printf("Selection: ");
		selectnum = getIntFromRange(0, 2);
		putchar('\n');
		if (selectnum == 1) //update household income
		{
			printf("Enter the household Income: $");
			dp->houseHoldIncome = getPositiveDouble();
			putchar('\n');
		}
		if (selectnum == 2) //update country name
		{
			getCountry(dp->country, 1, 30);

			putchar('\n');
		}
		if (selectnum == 0) //exit
		{
			flag = 1;
		}
	} while (flag == 0);
}

void pauseExecution(void) //pause function
{
	printf("<< ENTER key to Continue... >>"); //print message
	clearStandardInputBuffer(); //call clearStandardInputBuffer function
	putchar('\n');
}

