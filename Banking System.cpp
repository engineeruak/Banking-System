//Banking System
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Transaction class to store transaction history
class Transaction {
public:
    string type; // deposit, withdrawal, transfer
    double amount;
    string timestamp;

    Transaction(string type, double amount) {
        this->type = type;
        this->amount = amount;
        time_t now = time(0);
        char* dt = ctime(&now);
        this->timestamp = dt;
    }

    void displayTransaction() {
        cout << "Type: " << type << ", Amount: " << amount << ", Timestamp: " << timestamp;
    }
};

// Account class with account details and operations
class Account {
public:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

    Account(int accountNumber, double initialBalance = 0.0) {
        this->accountNumber = accountNumber;
        this->balance = initialBalance;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposited " << amount << ". New balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return;
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));
        cout << "Withdrew " << amount << ". New balance: " << balance << endl;
    }

    void transfer(Account &recipient, double amount) {
        if (this == &recipient) {
            cout << "Cannot transfer to the same account!" << endl;
            return;
        }
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return;
        }
        balance -= amount;
        recipient.balance += amount;
        transactions.push_back(Transaction("Transfer", amount));
        recipient.transactions.push_back(Transaction("Received Transfer", amount));
        cout << "Transferred " << amount << " to account " << recipient.accountNumber << endl;
    }

    void displayAccountInfo() {
        cout << "Account Number: " << accountNumber << ", Balance: " << balance << endl;
    }

    void displayTransactionHistory() {
        if (transactions.empty()) {
            cout << "No transactions." << endl;
            return;
        }
        cout << "Transaction History for Account " << accountNumber << ":" << endl;
        for (auto &t : transactions) {
            t.displayTransaction();
        }
    }
};

// Customer class to manage accounts
class Customer {
public:
    string name;
    vector<Account> accounts;

    Customer(string name) {
        this->name = name;
    }

    void addAccount(Account account) {
        accounts.push_back(account);
    }

    void displayCustomerInfo() {
        cout << "Customer: " << name << endl;
        for (auto &acc : accounts) {
            acc.displayAccountInfo();
        }
    }
};

int main() {
    // Example usage
    Customer cust("Ahmad Khan");
    Account acc1(12345, 1000.0);
    cust.addAccount(acc1);
    acc1.deposit(500.0);
    acc1.withdraw(200.0);
    Account acc2(67890, 0.0);
    cust.addAccount(acc2);
    acc1.transfer(acc2, 300.0);
    cust.displayCustomerInfo();
    acc1.displayTransactionHistory();
    acc2.displayTransactionHistory();
    system("pause");
    return 0;
}
