#include <stdio.h>
#include <string.h>
#include "server.h"

static ST_accountsDB_t accountsDB[255] = {
    {1593.5, RUNNING,"1234 4567 8910 4320"},
    {5449.5, RUNNING,"1234 4567 8910 4321"},
    {1986.5, RUNNING,"1234 4567 8910 4322"},
    {4843.0, BLOCKED,"1234 4567 8910 4323"},
    {9841.0, BLOCKED,"1234 4567 8910 4324"},
    {9567.0, BLOCKED,"1234 4567 8910 4325"}
};
static ST_transaction_t transactions[255] = { 0 };
static ST_accountsDB_t* accountRefrence;
uint32_t TSN = 0;

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
    for (int i = 0; i < 255; i++) {
        if (strcmp(cardData->primaryAccountNumber,accountsDB[i].primaryAccountNumber) == 0) {
            *accountRefrence = accountsDB[i];
            return APPROVED;
        }
    }
    accountRefrence = NULL;
    printf("\nACCOUNT NOT VALID\n");
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence){
    if (accountRefrence->state == BLOCKED) {
        printf("\nACCOUNT IS BLOCKED\n");
        return BLOCKED_ACCOUNT;
    }
    else
        return APPROVED;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
    if (termData->transAmount > accountRefrence->balance) {
        printf("\nACCOUNT LOW BALANCE\n");
        return LOW_BALANCE;
    }
    else {
        accountRefrence->balance -= termData->transAmount;
        return APPROVED;
    }
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
    if (TSN > 255) {
        printf("\nMAX TRANSACTION SEQUENCE NUMBER\n");
        return SAVING_FAILED;
    }
    else {
        transactions[TSN].cardHolderData = transData->cardHolderData;
        transactions[TSN].terminalData = transData->terminalData;
        transactions[TSN].transState = transData->transState;
        transactions[TSN].transactionSequenceNumber = TSN;
        TSN++;
        return SERVER_OK;
    }
}

void listSavedTransactions(void) {
    for (int i = 0; i < TSN; i++) {
        printf("\n#########################\n");
        printf("Transaction Sequence Number: %d\n",transactions[i].transactionSequenceNumber);
        printf("Transaction Date: %s\n",transactions[i].terminalData.transactionDate);
        printf("Transaction Amount: %f\n",transactions[i].terminalData.transAmount);

        printf("Transaction State: %d\n",transactions->transState);

        printf("Terminal Max Amount: %f\n",transactions[i].terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n",transactions[i].cardHolderData.cardHolderName);
        printf("PAN: %s\n",transactions[i].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n",transactions[i].cardHolderData.cardExpirationDate);
        printf("#########################\n");

    }
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
    if (isValidAccount(&transData->cardHolderData, &accountRefrence) != APPROVED)
        return FRAUD_CARD;
    if (isBlockedAccount(&accountRefrence) != APPROVED)
        return DECLINED_STOLEN_CARD;
    if (isAmountAvailable(&transData->terminalData, &accountRefrence) != APPROVED)
        return DECLINED_INSUFFECIENT_FUND;
    if (saveTransaction(&transData) != SERVER_OK)
        return SAVING_FAILED;
    //listSavedTransactions();

    return APPROVED;

}

