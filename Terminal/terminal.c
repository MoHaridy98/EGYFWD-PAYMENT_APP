#include <stdio.h>
#include <string.h>
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("Enter transaction date dd/mm/yyyy: ");
	uint8_t date[11];
	gets(date);
	if (strlen(date) != 10 || date[2] != '/' || date[5] != '/' || date[3] > '1' ||
		(date[0] >= '3' && date[1] > '0') ||
		(date[3] == '1' && date[4] > '2') ||
		(date[3] == '0' && date[4] <= '0'))
		return WRONG_DATE;
	else {
		strcpy(termData->transactionDate, date);
		return TERMINAL_OK;
	}
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	uint8_t CEMonth = ((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
	uint8_t CEYear = ((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');

	uint8_t TMonth = ((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
	uint8_t TYear = ((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');

	if (TYear < CEYear || (TYear == CEYear && TMonth - CEMonth <= 0))
		return TERMINAL_OK;
	else
		return EXPIRED_CARD;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Enter transaction amount: ");
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
		return INVALID_AMOUNT;
	else
		return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf("Enter max transaction amount: ");
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;
	else {
		return TERMINAL_OK;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	return TERMINAL_OK;
}

void getTransactionDateTest(void)
{
	struct ST_terminalData_t terminal;
	struct ST_terminalData_t* terminalptr = &terminal;
	printf("Tester Name: Mohammad Yasser omar\n");
	printf("Function Name: getTransactionDate\n");
	printf("Test Case 1:\n");
	uint8_t r = getTransactionDate(terminalptr);
	printf("Expected Result: TERMINAL_OK\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: WRONG_DATE\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
	printf("Test Case 2:\n");
	r = getTransactionDate(terminalptr);
	printf("Expected Result: WRONG_DATE\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: WRONG_DATE\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
	printf("Test Case 3:\n");
	r = getTransactionDate(terminalptr);
	printf("Expected Result: WRONG_DATE\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: WRONG_DATE\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
}

void isCardExpriedTest(void)
{
	uint8_t r;
	struct ST_cardData_t card;
	struct ST_cardData_t* cardptr = &card;

	struct ST_terminalData_t terminal;
	struct ST_terminalData_t* terminalptr = &terminal;
	printf("Tester Name: Mohammad Yasser omar\n");
	printf("Function Name: isCardExpired\n");
	printf("Test Case 1:\n");
	if (getCardExpiryDate(cardptr) == CARD_OK && getTransactionDate(terminalptr) == TERMINAL_OK) {
		r = isCardExpired(cardptr, terminalptr);
		printf("Expected Result: TERMINAL_OK\n");
		if (r != TERMINAL_OK)
			printf("Actual Result: EXPIRED_CARD\n\n");
		else
			printf("Actual Result: TERMINAL_OK\n\n");
		printf("\n");
	}
	printf("Test Case 2:\n");
	if (getCardExpiryDate(cardptr) == CARD_OK && getTransactionDate(terminalptr) == TERMINAL_OK) {
		r = isCardExpired(cardptr, terminalptr);
		printf("Expected Result: EXPIRED_CARD\n");
		if (r != TERMINAL_OK)
			printf("Actual Result: EXPIRED_CARD\n\n");
		else
			printf("Actual Result: TERMINAL_OK\n\n");
		printf("\n");
	}
}

void getTransactionAmountTest(void)
{
	struct ST_terminalData_t terminal;
	struct ST_terminalData_t* terminalptr = &terminal;
	printf("Tester Name: Mohammad Yasser omar\n");
	printf("Function Name: getTransactionAmount\n");
	printf("Test Case 1:\n");
	uint8_t r = getTransactionAmount(terminalptr);
	printf("Expected Result: TERMINAL_OK\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: INVALID_AMOUNT\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
	printf("Test Case 2:\n");
	r = getTransactionAmount(terminalptr);
	printf("Expected Result: INVALID_AMOUNT\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: INVALID_AMOUNT\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
	printf("Test Case 3:\n");
	r = getTransactionAmount(terminalptr);
	printf("Expected Result: INVALID_AMOUNT\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: INVALID_AMOUNT\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
}

void setMaxAmountTest(void)
{
	struct ST_terminalData_t terminal;
	struct ST_terminalData_t* terminalptr = &terminal;
	printf("Tester Name: Mohammad Yasser omar\n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 1:\n");
	uint8_t r = setMaxAmount(terminalptr);
	printf("Expected Result: TERMINAL_OK\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: INVALID_MAX_AMOUNT\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
	printf("Test Case 2:\n");
	r = setMaxAmount(terminalptr);
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: INVALID_MAX_AMOUNT\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
	printf("Test Case 3:\n");
	r = setMaxAmount(terminalptr);
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: INVALID_MAX_AMOUNT\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
}

void isBelowMaxAmountTest(void)
{
	struct ST_terminalData_t terminal = { 5000, 10000,"" };
	struct ST_terminalData_t* terminalptr = &terminal;
	printf("Tester Name: Mohammad Yasser omar\n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 1:\n");
	uint8_t r = isBelowMaxAmount(terminalptr);
	printf("Input Data: Transaction amount is 5000 and max amount is 10000\n");
	printf("Expected Result: TERMINAL_OK\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: EXCEED_MAX_AMOUNT\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
	struct ST_terminalData_t terminal2 = { 10000, 5000,"" };
	struct ST_terminalData_t* terminalptr2 = &terminal2;
	printf("Test Case 2:\n");
	printf("Input Data: Transaction amount is 10000 and max amount is 5000\n");
	r = isBelowMaxAmount(terminalptr2);
	printf("Expected Result: EXCEED_MAX_AMOUNT\n");
	if (r != TERMINAL_OK)
		printf("Actual Result: EXCEED_MAX_AMOUNT\n\n");
	else
		printf("Actual Result: TERMINAL_OK\n\n");
	printf("\n");
}


//int main() {
//	//getTransactionDateTest();
//	//isCardExpriedTest();
//	//getTransactionAmountTest();
//	//setMaxAmountTest();
//	//isBelowMaxAmountTest();
//	return 0;
//}