#include <stdio.h>
#include <string.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Enter Name: ");
	uint8_t name[25];
	gets(name);
	uint8_t nameSize = strlen(name);
	if (nameSize < 20 || nameSize >24)
		return WRONG_NAME;
	else {
		for (int i = 0; i < nameSize; i++)
			if (name[i] > '0' && name[i] < '9') {
				return WRONG_NAME;
			}
		strcpy(cardData->cardHolderName, name);
		return CARD_OK;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Enter expiry date mm/yy: ");
	uint8_t date[6];
	gets(date);
	uint8_t dateSize = strlen(date);
	if (dateSize != 5 || date[2] != '/' || date[0] > '1' || (date[0] == '1' && date[1] > '2') || (date[0] == '0' && date[1] <= '0'))
		return WRONG_EXP_DATE;
	else {
		strcpy(cardData->cardExpirationDate, date);
		return CARD_OK;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Enter card number: ");
	uint8_t number[20];
	gets(number);
	uint8_t panSize = strlen(number);
	if (panSize < 16 || panSize > 19)
		return WRONG_PAN;
	else {
		for (int i = 0; i < panSize; i++)
			if ((number[i] >= 'a' && number[i] <= 'z') || (number[i] >= 'A' && number[i] <= 'Z')) {
				return WRONG_PAN;
			}
		strcpy(cardData->primaryAccountNumber, number);
		return CARD_OK;
	}
}

void getCardHolderNameTest(void)
{
	struct ST_cardData_t card;
	struct ST_cardData_t* cardptr = &card;
	printf("Tester Name: Mohammad Yasser omar\n");
	printf("Function Name: getCardHolderName\n");
	printf("Test Case 1:\n");
	uint8_t r = getCardHolderName(cardptr);
	printf("Expected Result: CARD_OK\n");
	if (r != CARD_OK)
		printf("Actual Result: WRONG_NAME\n\n");
	else
		printf("Actual Result: CARD_OK\n\n");
	printf("\n");
	printf("Test Case 2:\n");
	r = getCardHolderName(cardptr);
	printf("Expected Result: WRONG_NAME\n");
	if (r != CARD_OK)
		printf("Actual Result: WRONG_NAME\n\n");
	else
		printf("Actual Result: CARD_OK\n\n");
	printf("\n");
	printf("Test Case 3:\n");
	r = getCardHolderName(cardptr);
	printf("Expected Result: WRONG_NAME\n");
	if (r != CARD_OK)
		printf("Actual Result: WRONG_NAME\n\n");
	else
		printf("Actual Result: CARD_OK\n\n");
	printf("\n");
}

void getCardExpiryDateTest(void)
{
	struct ST_cardData_t card;
	struct ST_cardData_t* cardptr = &card;
	printf("Tester Name: Mohammad Yasser omar\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("Test Case 1:\n");
	uint8_t r = getCardExpiryDate(cardptr);
	printf("Expected Result: CARD_OK\n");
	if (r != CARD_OK)
		printf("Actual Result: WRONG_EXP_DATE\n\n");
	else
		printf("Actual Result: CARD_OK\n\n");
	printf("\n");
	printf("Test Case 2:\n");
	r = getCardExpiryDate(cardptr);
	printf("Expected Result: WRONG_EXP_DATE\n");
	if (r != CARD_OK)
		printf("Actual Result: WRONG_EXP_DATE\n\n");
	else
		printf("Actual Result: CARD_OK\n\n");
	printf("\n");
	printf("Test Case 3:\n");
	r = getCardExpiryDate(cardptr);
	printf("Expected Result: WRONG_EXP_DATE\n");
	if (r != CARD_OK)
		printf("Actual Result: WRONG_EXP_DATE\n\n");
	else
		printf("Actual Result: CARD_OK\n\n");
	printf("\n");
}

void getCardPANTest(void)
{
	struct ST_cardData_t card;
	struct ST_cardData_t* cardptr = &card;
	printf("Tester Name: Mohammad Yasser omar\n");
	printf("Function Name: getCardPAN\n");
	printf("Test Case 1:\n");
	uint8_t r = getCardPAN(cardptr);
	printf("Expected Result: CARD_OK\n");
	if (r != CARD_OK)
		printf("Actual Result: WRONG WRONG_PAN NAME\n\n");
	else
		printf("Actual Result: CARD_OK\n\n");
	printf("\n");
	printf("Test Case 2:\n");
	r = getCardPAN(cardptr);
	printf("Expected Result: WRONG_PAN\n");
	if (r != CARD_OK)
		printf("Actual Result: WRONG_PAN\n\n");
	else
		printf("Actual Result: CARD_OK\n\n");
	printf("\n");
	printf("Test Case 3:\n");
	r = getCardPAN(cardptr);
	printf("Expected Result: WRONG_PAN\n");
	if (r != CARD_OK)
		printf("Actual Result: WRONG_PAN\n\n");
	else
		printf("Actual Result: CARD_OK\n\n");
	printf("\n");
}



//int main() {
//	//getCardHolderNameTest();
//	//getCardExpiryDateTest();
//	//getCardPANTest();
//	//return 0;
//}