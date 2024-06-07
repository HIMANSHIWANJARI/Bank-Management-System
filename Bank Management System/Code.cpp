#include <bits/stdc++.h>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string date;

    Transaction(string t, double a, string d) : type(t), amount(a), date(d) {}
};

class BankAccount {
private:
    string name;
    int accountNum;
    double balance;
    vector<Transaction> transactions;

public:
    BankAccount(string n, int ac, double bal) {
        name = n;
        accountNum = ac;
        balance = bal;
    }

    string getName() {
        return name;
    }

    int getAccountNum() {
        return accountNum;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount, currentDateTime()));
    }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "\t\tWithdraw Successfully..." << endl;
            transactions.push_back(Transaction("Withdraw", amount, currentDateTime()));
        } else {
            cout << "\t\tInsufficient Balance...." << endl;
        }
    }

    void showTransactions() {
        cout << "\t\tTransaction History for " << name << " (Account Number: " << accountNum << ")" << endl;
        for (size_t i = 0; i < transactions.size(); ++i) {
            Transaction t = transactions[i];
            cout << t.date << " - " << t.type << ": " << t.amount << endl;
        }
    }

    string currentDateTime() {
        time_t now = time(0);
        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", localtime(&now));
        return string(buf);
    }
};

class BankManagement {
private:
    vector<BankAccount> accounts;

public:
    void AddAccount(string name, int accountNum, double balance) {
        accounts.push_back(BankAccount(name, accountNum, balance));
    }

    void showAllAccounts() {
        cout << "\t\tAll Account Holders " << endl;
        for (size_t i = 0; i < accounts.size(); ++i) {
            cout << "Name: " << accounts[i].getName() << " | Account Number: " << accounts[i].getAccountNum() << " | Balance: " << accounts[i].getBalance() << endl;
        }
    }

    void searchAccount(int account) {
        cout << "\t\tAccount Holder " << endl;
        for (size_t i = 0; i < accounts.size(); ++i) {
            if (accounts[i].getAccountNum() == account) {
                cout << "Name: " << accounts[i].getName() << " | Account Number: " << accounts[i].getAccountNum() << " | Balance: " << accounts[i].getBalance() << endl;
            }
        }
    }

    BankAccount* findAccount(int accountNum) {
        for (size_t i = 0; i < accounts.size(); ++i) {
            if (accounts[i].getAccountNum() == accountNum) {
                return &accounts[i];
            }
        }
        return NULL;
    }

    void showTransactionHistory(int accountNum) {
        BankAccount* account = findAccount(accountNum);
        if (account != NULL) {
            account->showTransactions();
        } else {
            cout << "\t\tAccount Not Found ..." << endl;
        }
    }
};

int main() {
    BankManagement bank;
    int choice;
    char op;
    do {
        system("cls");
        cout << "\t\t Bank Management System" << endl;
        cout << "\t\t\tMain Menu" << endl;
        cout << "\t\t1. Create New Account" << endl;
        cout << "\t\t2. Show All Accounts" << endl;
        cout << "\t\t3. Search Account" << endl;
        cout << "\t\t4. Deposit Money" << endl;
        cout << "\t\t5. Withdraw Money" << endl;
        cout << "\t\t6. Show Transaction History" << endl;
        cout << "\t\t7. Exit" << endl;
        cout << "\t\t-------------------------------" << endl;
        cout << "\t\tEnter Your Choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                string name;
                int accountNum;
                double balance;
                cout << "\t\tEnter Name: ";
                cin >> name;
                cout << "\t\tEnter Account Number: ";
                cin >> accountNum;
                cout << "\t\tEnter Initial Balance: ";
                cin >> balance;
                bank.AddAccount(name, accountNum, balance);
                cout << "\t\tAccount Created Successfully...." << endl;
                break;
            }
            case 2: {
                bank.showAllAccounts();
                break;
            }
            case 3: {
                int accountNum;
                cout << "Enter Account Number: ";
                cin >> accountNum;
                bank.searchAccount(accountNum);
                break;
            }
            case 4: {
                int accountNum;
                double amount;
                cout << "\t\tEnter Account Number to Deposit Money: ";
                cin >> accountNum;
                BankAccount* account = bank.findAccount(accountNum);
                if (account != NULL) {
                    cout << "\t\tEnter Amount to Deposit: ";
                    cin >> amount;
                    account->deposit(amount);
                    cout << "\t\t" << amount << " Deposited Successfully ...." << endl;
                } else {
                    cout << "\t\tAccount Not Found ..." << endl;
                }
                break;
            }
            case 5: {
                int accountNum;
                double amount;
                cout << "\t\tEnter Account Number to Withdraw Money: ";
                cin >> accountNum;
                BankAccount* account = bank.findAccount(accountNum);
                if (account != NULL) {
                    cout << "\t\tEnter Amount to Withdraw: ";
                    cin >> amount;
                    account->withdraw(amount);
                } else {
                    cout << "\t\tAccount Not Found ..." << endl;
                }
                break;
            }
            case 6: {
                int accountNum;
                cout << "\t\tEnter Account Number to View Transaction History: ";
                cin >> accountNum;
                bank.showTransactionHistory(accountNum);
                break;
            }
            case 7: {
                exit(0);
                break;
            }
            default: {
                cout << "\t\tInvalid Choice! Please try again." << endl;
                break;
            }
        }
        cout << "\t\tDo You Want to Continue or Exit [Y/N]? ";
        cin >> op;
    } while (op == 'y' || op == 'Y');

    return 0;
}
