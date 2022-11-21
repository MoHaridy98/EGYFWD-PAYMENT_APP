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
static ST_transaction_t transactions[255] = { { { "Mohammad Yasser Omar","1234 4567 8910 4321","05/25" }
    , { 5000, 10000, "21/11/2020" }
    , APPROVED , 0 } , { { "Mohammad Yasser Omar","1234 4567 8910 4325","05/23" }
    , { 50000, 100000, "21/11/2020" }
    , APPROVED , 1 } };
static ST_accountsDB_t* accountRefrence;
uint32_t TSN = 2;

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
    for (int i = 0; i < sizeof(accountsDB) / sizeof(accountsDB[0]); i++) {
        if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0) {
            *accountRefrence = accountsDB[i];
            return SERVER_OK;
        }
    }
    accountRefrence = NULL;
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
    if (accountRefrence->state == BLOCKED) {
        return BLOCKED_ACCOUNT;
    }
    else
        return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
    if (termData->transAmount > accountRefrence->balance) {
        return LOW_BALANCE;
    }
    else {
        accountRefrence->balance -= termData->transAmount;
        printf("new balance: %.2f\n", accountRefrence->balance);
        return SERVER_OK;
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

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
    if (isValidAccount(&transData->cardHolderData, &accountRefrence) != APPROVED)
        return FRAUD_CARD;
    if (isBlockedAccount(&accountRefrence) != APPROVED)
        return DECLINED_STOLEN_CARD;
    if (isAmountAvailable(&transData->terminalData, &accountRefrence) != APPROVED)
        return DECLINED_INSUFFECIENT_FUND;
    if (saveTransaction(&transData) != SERVER_OK)
        return SAVING_FAILED;
    return APPROVED;

}

void listSavedTransactions(void) {
    for (int i = 0; i < TSN; i++) {
        printf("\n#########################\n");
        printf("Transaction Sequence Number: %d\n", transactions[i].transactionSequenceNumber);
        printf("Transaction Date: %s\n", transactions[i].terminalData.transactionDate);
        printf("Transaction Amount: %.2f\n", transactions[i].terminalData.transAmount);

        printf("Transaction State: %d\n", transactions->transState);

        printf("Terminal Max Amount: %.2f\n", transactions[i].terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n", transactions[i].cardHolderData.cardHolderName);
        printf("PAN: %s\n", transactions[i].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", transactions[i].cardHolderData.cardExpirationDate);
        printf("#########################\n");

    }
}

void isValidAccountTest(void)
{
    struct ST_cardData_t card = { "", "1234 4567 8910 4321", "" };
    struct ST_cardData_t* cardptr = &card;
    struct ST_accountsDB_t x = { 0,RUNNING,"" };
    struct ST_accountsDB_t* xptr = &x;
    printf("Tester Name: Mohammad Yasser Omar\n");
    printf("Function Name: isValidAccount\n");
    printf("Test Case 1:\n");
    printf("Input Data: PAN: 1234 4567 8910 4321\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: ");
    if (isValidAccount(cardptr, xptr) == SERVER_OK) {
        printf("SERVER_OK");
    }
    else {
        printf("ACCOUNT_NOT_FOUND");
    }
    printf("\n");
    struct ST_cardData_t card1 = { "", "1234 1234 5678 9101", "" };
    struct ST_cardData_t* cardptr1 = &card1;
    struct ST_accountsDB_t y = { 0,RUNNING,"" };
    struct ST_accountsDB_t* yptr = &y;
    printf("Test Case 2:\n");
    printf("Input Data: PAN:1234 1234 5678 9101\n");
    printf("Expected Result: ACCOUNT_NOT_FOUND\n");
    printf("Actual Result: ");
    if (isValidAccount(cardptr1, yptr) == SERVER_OK) {
        printf("SERVER_OK");
    }
    else {
        printf("ACCOUNT_NOT_FOUND");
    }
    printf("\n");
}

void isBlockedAccountTest(void)
{
    struct ST_accountsDB_t x = { 0,RUNNING,"" };
    struct ST_accountsDB_t* xptr = &x;
    printf("Tester Name: Mohammad Yasser Omar\n");
    printf("Function Name: isBlockedAccount\n");
    printf("Test Case 1:\n");
    printf("Input Data: Running account\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: ");
    if (isBlockedAccount(xptr) == SERVER_OK) {
        printf("SERVER_OK");
    }
    else {
        printf("BLOCKED_ACCOUNT");
    }
    printf("\n");
    struct ST_accountsDB_t y = { 0,BLOCKED,"" };
    struct ST_accountsDB_t* yptr = &y;
    printf("Test Case 2:\n");
    printf("Input Data: Blocked account\n");
    printf("Expected Result: BLOCKED_ACCOUNT\n");
    printf("Actual Result: ");
    if (isBlockedAccount(yptr) == SERVER_OK) {
        printf("SERVER_OK");
    }
    else {
        printf("BLOCKED_ACCOUNT");
    }
    printf("\n");
}

void isAmountAvailableTest(void)
{
    struct ST_accountsDB_t x = { 10000,RUNNING,"" };
    struct ST_accountsDB_t* xptr = &x;
    struct ST_terminalData_t a = { 10000,5000,"" };
    struct ST_terminalData_t* aptr = &a;
    printf("Tester Name: Mohammad Yasser Omar\n");
    printf("Function Name: isAmountAvailable\n");
    printf("Test Case 1:\n");
    printf("Input Data: available amount\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: ");
    if (isAmountAvailable(aptr, xptr) == SERVER_OK) {
        printf("SERVER_OK");
    }
    else {
        printf("LOW_BALANCE");
    }
    printf("\n");
    struct ST_accountsDB_t y = { 1000,RUNNING,"" };
    struct ST_accountsDB_t* yptr = &y;
    struct ST_terminalData_t b = { 5000,10000,"" };
    struct ST_terminalData_t* bptr = &b;
    printf("Test Case 2:\n");
    printf("Input Data: low amount\n");
    printf("Expected Result: LOW_BALANCE\n");
    printf("Actual Result: ");
    if (isAmountAvailable(bptr, yptr) == SERVER_OK) {
        printf("SERVER_OK");
    }
    else {
        printf("LOW_BALANCE");
    }
    printf("\n");
}

void recieveTransactionDataTest(void)
{
    ST_transaction_t x = { {"","1234 4567 8910 4321","" }, {0, 0, ""},APPROVED,0 };
    ST_transaction_t* xptr = &x;
    printf("Tester Name: Mohammad Yasser Omar\n");
    printf("Function Name: recieveTransactionData\n");
    printf("Test Case 1:\n");
    printf("Input Data: Avaliable account\n");
    printf("Expected Result: APPROVED\n");
    printf("Actual Result: ");
    if (recieveTransactionData(xptr) == APPROVED) {
        printf("APPROVED");
    }
    else {
        printf("DECLINED");
    }
    printf("\n");
    ST_transaction_t y = { {"","1234 4567 8910 4325","" }, {0, 0, ""},APPROVED,0 };
    ST_transaction_t* yptr = &y;
    printf("Test Case 2:\n");
    printf("Input Data: Stolen account\n");
    printf("Expected Result: DECLINED_STOLEN_CARD\n");
    printf("Actual Result: ");
    if (recieveTransactionData(yptr) == APPROVED) {
        printf("APPROVED");
    }
    else {
        printf("DECLINED_STOLEN_CARD");
    }
    printf("\n");
}

void saveTransactionTest(void)
{
    ST_transaction_t t = { { "Mohammad Yasser Omar","1234 4567 8910 4321","05/25" }
    , { 5000, 10000, "21/11/2020" }
    , APPROVED , 0 };
    ST_transaction_t* tptr = &t;
    printf("Tester Name: Mohammad Yasser Omar\n");
    printf("Function Name: saveTransaction\n");
    printf("Test Case 1:\n");
    printf("Input Data: Valid card data & valid transaction data\n");
    printf("Expected Result: SERVER_OK\n");
    printf("Actual Result: ");
    if (saveTransaction(tptr) == SERVER_OK)
        printf("SERVER_OK");
    else
        printf("ERROR");
    printf("\n");
}

void listSavedTransactionsTest(void)
{
    printf("Tester Name: Mohammad Yasser Omar\n");
    printf("Function Name: listSavedTransactionsn");
    printf("Test Case 1:\n");
    printf("Input Data: 2 saved transactions in DB");
    printf("Expected Result: printed succesfully\n");
    printf("Actual Result: ");
    listSavedTransactions();
}

//int main() {
//    //isValidAccountTest();
//    //isBlockedAccountTest();
//    //isAmountAvailableTest();
//    //recieveTransactionDataTest();
//    //saveTransactionTest();
//    //listSavedTransactions();
//}