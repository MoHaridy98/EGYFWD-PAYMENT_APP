#include <stdio.h>
#include <string.h>
//#include <time.h>
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	/*time_t t;
	t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("%d/%d/%d", tm.tm_mday + 1, tm.tm_mon + 1, tm.tm_year + 1900);*/
	printf("Enter transaction date dd/mm/yyyy: ");
	gets(termData->transactionDate);
	if (strlen(termData->transactionDate) != 10 || termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/')
		return WRONG_DATE;
	else
		return TERMINAL_OK;
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