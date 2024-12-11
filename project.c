#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    int acc_no;
    float balance;
} Account;

const char *ACCOUNT_FILE = "account.dat";

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();

int main() {
    while (1) {
        int choice;
        printf("\n\n*** Bank Management System ***");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Check Balance");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                deposit_money();
                break;
            case 3:
                withdraw_money();
                break;
            case 4:
                check_balance();
                break;
            case 5:
                printf("\nThank you for using the Bank Management System.\n");
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}

void create_account() {
    Account acc;
    FILE *file = fopen(ACCOUNT_FILE, "a");
    if (file == NULL) {
        printf("\nError opening file.\n");
        return;
    }

    printf("\nEnter your name: ");
    scanf("%s", acc.name);
    printf("Enter your account number: ");
    scanf("%d", &acc.acc_no);
    acc.balance = 0;

    fprintf(file, "%s %d %.2f\n", acc.name, acc.acc_no, acc.balance);
    fclose(file);
    printf("\nAccount created successfully!\n");
}

void deposit_money() {
    int acc_no;
    float money;
    Account acc;
    FILE *file = fopen(ACCOUNT_FILE, "r");
    FILE *temp_file = fopen("temp.dat", "w");
    if (file == NULL || temp_file == NULL) {
        printf("\nError opening file.\n");
        return;
    }

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to deposit: ");
    scanf("%f", &money);

    int found = 0;
    while (fscanf(file, "%s %d %f", acc.name, &acc.acc_no, &acc.balance) == 3) {
        if (acc.acc_no == acc_no) {
            acc.balance += money;
            found = 1;
        }
        fprintf(temp_file, "%s %d %.2f\n", acc.name, acc.acc_no, acc.balance);
    }

    fclose(file);
    fclose(temp_file);
    remove(ACCOUNT_FILE);
    rename("temp.dat", ACCOUNT_FILE);

    if (found)
        printf("\nDeposit successful.\n");
    else
        printf("\nAccount not found.\n");
}

void withdraw_money() {
    int acc_no;
    float money;
    Account acc;
    FILE *file = fopen(ACCOUNT_FILE, "r");
    FILE *temp_file = fopen("temp.dat", "w");
    if (file == NULL || temp_file == NULL) {
        printf("\nError opening file.\n");
        return;
    }

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter amount to withdraw: ");
    scanf("%f", &money);

    int found = 0;
    while (fscanf(file, "%s %d %f", acc.name, &acc.acc_no, &acc.balance) == 3) {
        if (acc.acc_no == acc_no) {
            if (acc.balance >= money) {
                acc.balance -= money;
                found = 1;
            } else {
                printf("\nInsufficient balance.\n");
            }
        }
        fprintf(temp_file, "%s %d %.2f\n", acc.name, acc.acc_no, acc.balance);
    }

    fclose(file);
    fclose(temp_file);
    remove(ACCOUNT_FILE);
    rename("temp.dat", ACCOUNT_FILE);

    if (found)
        printf("\nWithdrawal successful.\n");
    else
        printf("\nAccount not found.\n");
}

void check_balance() {
    int acc_no;
    Account acc;
    FILE *file = fopen(ACCOUNT_FILE, "r");
    if (file == NULL) {
        printf("\nError opening file.\n");
        return;
    }

    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);

    while (fscanf(file, "%s %d %f", acc.name, &acc.acc_no, &acc.balance) == 3) {
        if (acc.acc_no == acc_no) {
            printf("\nYour current balance: Rs.%.2f\n", acc.balance);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("\nAccount not found.\n");
}
