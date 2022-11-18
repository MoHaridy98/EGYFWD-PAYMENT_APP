#include <stdio.h>
#include <string.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Enter Name: ");
	gets(cardData->cardHolderName);
	uint8_t nameSize = strlen(cardData->cardHolderName);
	if (nameSize < 20 || nameSize >24)
		return WRONG_NAME;
	else
		return CARD_OK;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Enter expiry date mm/yy: ");
	gets(cardData->cardExpirationDate);
	uint8_t dateSize = strlen(cardData->cardExpirationDate);
	if (dateSize != 5 || cardData->cardExpirationDate[2] != '/')
		return WRONG_EXP_DATE;
	else
		return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Enter card number: ");
	gets(cardData->primaryAccountNumber);
	uint8_t panSize = strlen(cardData->primaryAccountNumber);
	if (panSize < 16 || panSize > 19)
		return WRONG_PAN;
	else
		return CARD_OK;
}