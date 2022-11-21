#include <stdio.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"

void appStart(void) {
    ST_cardData_t card;
    ST_terminalData_t terminal;
    ST_transaction_t transaction;

    //get card date
    if (getCardHolderName(&card) != CARD_OK) {
        printf("FAILED: WRONG HOLDER NAME\n\n");
        return 0;
    }
    if (getCardExpiryDate(&card) != CARD_OK) {
        printf("FAILED: WRONG EXPIRY DATE\n\n");
        return 0;
    }
    if (getCardPAN(&card) != CARD_OK) {
        printf("FAILED: WRONG CARD NUMBER\n\n");
        return 0;
    }
    //end get card data

    //get terminal data
    if (getTransactionDate(&terminal) != TERMINAL_OK) {
        printf("FAILED: WRONG TRANSACTION DATE\n\n");
        return 0;
    }
    if (isCardExpired(&card, &terminal) != TERMINAL_OK) {
        printf("FAILED: EXPIRED CARD\n\n");
        return 0;
    }
    if (getTransactionAmount(&terminal) != TERMINAL_OK) {
        printf("FAILED: INVALID AMOUNT\n\n");
        return 0;
    }
    if (setMaxAmount(&terminal) != TERMINAL_OK) {
        printf("FAILED: INVALID MAX AMOUNT\n\n");
        return 0;
    }
    if (isBelowMaxAmount(&terminal) != TERMINAL_OK) {
        printf("FAILED: EXCEED MAX AMOUNT\n\n");
        return 0;
    }
    //end get terminal data

    //get server data
    transaction.cardHolderData = card;
    transaction.terminalData = terminal;
    if (recieveTransactionData(&transaction) != APPROVED) {
        printf("FALIED: TRANSACTION FAILED\n\n");
        return 0;
    }
    else
        printf("TRANSACTION SUCCEDDED\n\n");
    //end get server data


}