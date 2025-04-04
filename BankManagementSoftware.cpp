#include <iostream>
#include <string>
using namespace std;


struct BankAccount{
    int AccountNumber;
    string HolderName;
    double Balance;
};


void addAccounts(BankAccount*** Account , int &n);
void deposit(BankAccount*** Account , int &n);
void withdraw(BankAccount*** Account , int &n);
void displayAccounts(const BankAccount*** Account, int n);
void deleteAccount(BankAccount*** Account , int &n);


int main(){
cout << "\nWelcome to bank management software!!\n";
int num = 0; // initially 0 accounts
BankAccount** Account = nullptr;

    int choice ;
    do{ 
        cout << "\nMain menu:";
        cout << "\n1.Add accounts";
        cout << "\n2.Deposit funds";
        cout << "\n3.Withdraw funds";
        cout << "\n4.Display accounts";
        cout << "\n5.Delete accounts";
        cout << "\n6.Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                addAccounts(&Account , num);
                break;
            case 2:
                deposit(&Account , num);
                break;
            case 3:
                withdraw(&Account , num);
                break;
            case 4:
                displayAccounts(const_cast<const BankAccount***>(&Account), num);
                break;
            case 5:
                deleteAccount(&Account , num);
                break;
            case 6:
                cout << "Exiting...";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }while(choice!=6);

    delete[] Account;
    return 0;

}


void displayAccounts(const BankAccount*** Account, int n) {
    if (n == 0) {
        cout << "\nNo accounts available to display. Go to Option 1 in the main menu and add accounts\n";
        return;
    }

    cout << "\nDisplaying All Accounts:\n";
    for (int i = 0; i < n; i++) {
        cout << "\nAccount Number: " << (*Account)[i]->AccountNumber
             << "\nHolder Name: " << (*Account)[i]->HolderName
             << "\nBalance: " << (*Account)[i]->Balance
             << "\n-------------------------";
    }
}


void addAccounts(BankAccount*** Account, int &n) {
    int newAccounts;
    cout << "\nEnter the number of accounts to add: ";
    cin >> newAccounts;

    BankAccount **temp = new BankAccount*[n + newAccounts];

    for (int i = 0; i < n; i++) {
        temp[i] = (*Account)[i];
    }

    for (int i = 0; i < newAccounts; i++) {
        temp[n + i] = new BankAccount;
        
    
        cout << "Enter the account number: ";
        cin >> temp[n + i]->AccountNumber;
        cin.ignore(); 

        
        bool exists = false;
        for (int j = 0; j < n + i; j++) {  
            if (temp[j]->AccountNumber == temp[n + i]->AccountNumber) {
                cout << "Account already exists! Enter a unique account number.\n";
                exists = true;
                break;
            }
        }

        if (exists) {
            delete temp[n + i];  
            i--;  
            continue;
        }

        cout << "Enter the account holder name: ";
        getline(cin, temp[n + i]->HolderName);

        cout << "Enter the initial amount to be added to the account: ";
        cin >> temp[n + i]->Balance;
    }

    delete[] *Account; 

    *Account = temp;
    n += newAccounts;  

    cout << "Accounts added successfully!\n";
}


void deleteAccount(BankAccount*** Account, int &n) {
    if (n == 0) {
        cout << "\nNo accounts available. Go to Option 1 in the main menu and add accounts\n";
        return;
    }

    int tempAccNum;
    cout << "Enter the account number to delete: ";
    cin >> tempAccNum;

    int index = -1;

    for (int i = 0; i < n; i++) {
        if ((*Account)[i]->AccountNumber == tempAccNum) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Account not found\n";
        return;
    }

    delete (*Account)[index];

    for (int i = index; i < n - 1; i++) {
        (*Account)[i] = (*Account)[i + 1];
    }

    (*Account)[n - 1] = nullptr;

    n--; 
    cout << "Account deleted successfully!\n";
}


void deposit(BankAccount*** Account, int &n) {

    if (n == 0) {
        cout << "\nNo accounts available. Go to Option 1 in the main menu and add accounts\n";
        return;
    }

    int tempAccNum;
    cout << "\nEnter the Account number: ";
    cin >> tempAccNum;

    int amount;
    cout << "\nEnter Deposit Amount: ";
    cin >> amount;

    bool found = false;

    for (int i = 0; i < n; i++) {
        if ((*Account)[i]->AccountNumber == tempAccNum) {
            (*Account)[i]->Balance += amount;
            cout << "Amount deposited successfully! New Balance: " << (*Account)[i]->Balance << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Account not found.\n";
    }
}


void withdraw(BankAccount*** Account, int &n) {
    
    if (n == 0) {
        cout << "\nNo accounts available. Go to Option 1 in the main menu and add accounts\n";
        return;
    }

    int tempAccNum;
    cout << "\nEnter the Account number: ";
    cin >> tempAccNum;

    int amount;
    cout << "\nEnter withdrawal Amount: ";
    cin >> amount;

    for (int i = 0; i < n; i++) {
        if ((*Account)[i]->AccountNumber == tempAccNum) {
            if ((*Account)[i]->Balance >= amount) {
                (*Account)[i]->Balance -= amount;
                cout << "Amount withdrawn successfully! New Balance: " << (*Account)[i]->Balance << "\n";
            } else {
                cout << "Insufficient balance! Your current balance is: " << (*Account)[i]->Balance << "\n";
            }
            return; 
        }
    }

    cout << "Account not found.\n";
}
