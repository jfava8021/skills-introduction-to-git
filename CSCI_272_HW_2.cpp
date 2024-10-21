//classes go into header files for extra credit

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

class Name
{
    private:
        string first_name;
        string last_name;

    public:
        Name(const string& first, const string& last)
            : first_name(first), last_name(last) {}
        
        string get_first_name() const {return first_name;}//getter
        string get_last_name() const {return last_name;}//getter

        void set_first_name(const string& first) {first_name = first;};//setter
        void set_last_name(const string& last) {last_name = last;}//setter
};

class Depositor
{
    private:
        Name depositor_name;
        int social_security_number;
    
    public:
        Depositor(const Name& name, const int& ssn)
            : depositor_name(name), social_security_number(ssn) {}

        Name get_name() const {return depositor_name;}//getter
        int get_social_security_number() const {return social_security_number;}//getter

        void set_name(const Name& name) {depositor_name = name;}; //setter
        // dont have this void set_social_security_number(const int& ssn) {social_security_number = ssn;}//setter
};

class BankAccount
{
    private:
        Depositor depositor_account;
        int account_number;
        double balance;

    public:
        BankAccount(const Depositor& depositor, int acc_num, double bal)
            : depositor_account(depositor), account_number(acc_num), balance(bal) {}

        Depositor get_depositor() const {return depositor_account;}//getter
        int get_account_number() const {return account_number;}//getter
        double get_balance() const {return balance;}//getter

        void set_depositor(const Depositor& depositor) {depositor_account = depositor;}//setter
        // void set_account_number(int acc_num) {account_number = acc_num;}//setter
         void set_balance(double bal) {balance = bal;}//setter
};

void menu();
int read_accts(vector<BankAccount> &accounts);
int new_acct(vector<BankAccount> &accounts);
void print_accts(const vector<BankAccount> &accounts);
void withdrawl(vector<BankAccount> &accounts);
void deposit(vector<BankAccount> &accounts);
int delete_account(vector<BankAccount> &accounts);
void balance(vector<BankAccount> & accounts);
void account_info(vector<BankAccount> &accounts);
//Support Functions
bool account_exists(const vector<BankAccount> &accounts, int account_number);
bool has_balance(const vector<BankAccount> &accounts, int account_number);
bool social_security_number_exists(const vector<BankAccount> &accounts, int ssn);
int find_social_security_number_index(const vector<BankAccount> &accounts, int ssn);
int find_account_index(const vector<BankAccount> &accounts, int account_number);//findacct function

int main()
{
    cout << fixed << setprecision(2);
    vector<BankAccount> accounts;
    read_accts(accounts);
    print_accts(accounts);
    
    char teller_selection = 'Z';

    while(teller_selection != 'Q')
    {
        menu();

        cout << "Please enter your selection here: ";
        cin >> teller_selection;
        cout << "\n" << endl;

        switch(teller_selection) 
        {
            case 'W':
                cout << "You have selected Withdrawl." << endl;
                withdrawl(accounts);
                break;
            case 'D':
                cout << "You have selected Deposit." << endl;
                deposit(accounts);
                break;
            case 'N':
                cout << "You have selected New Account." << endl;
                new_acct(accounts);
                break;
            case 'B':
                cout << "You have selected Balance." << endl;
                balance(accounts);
                break;
            case 'I':
                cout << "You have selected Account Information." << endl;
                account_info(accounts);
                break;
            case 'Q':
                cout << "You have selected Quit." << endl;
                print_accts(accounts);
                return 0;
            case 'X':
                cout << "You have selected Delete Account." << endl;
                delete_account(accounts);
                break;
            default:
                cout << "Invalid selection. Please try again." << endl;
                menu();
                break;
        }
    }

    return 0;
}

void menu()
{
    cout << "\n" << endl;
    cout << "Hello, and welcome to the Fake Bank Inc teller system! Please make a selection from the following options." << endl;
    cout << "(W) Withdrawl" << endl;
    cout << "(D) Deposit" << endl;
    cout << "(N) New Account" << endl;
    cout << "(B) Balance" << endl;
    cout << "(I) Account Information" << endl;
    cout << "(Q) Quit" << endl;
    cout << "(X) Delete Account" << endl;
}

int read_accts(vector<BankAccount> &accounts) 
{
    accounts.push_back(BankAccount(Depositor(Name("Jordan", "Fava"), 112994372), 458761032, 1000.00));
    accounts.push_back(BankAccount(Depositor(Name("Raymond", "Romano"), 111782452), 934820735, 55500.55));
    accounts.push_back(BankAccount(Depositor(Name("Doctor", "Evil"), 684014279), 599573615, 10000.01));
    accounts.push_back(BankAccount(Depositor(Name("John", "Cena"), 406226836), 102468957, 1745.28));
    accounts.push_back(BankAccount(Depositor(Name("Master", "Splinter"), 110300123), 753590138, 10.10));
    return accounts.size();
}

void print_accts(const vector<BankAccount> &accounts)
{
    cout << setw(15) << "Account Number" << setw(15) << "First Name" << setw(15) << "Last Name" << setw(15) << "SSN" << setw(15) << "Balance" << "\n" << endl;
    for (int i = 0; i < accounts.size(); i++)
    {
        string ssn_string = to_string(accounts[i].get_depositor().get_social_security_number());
        string ssn_last_four = ssn_string.substr(ssn_string.length() - 4);
        int ssn_index = find_social_security_number_index(accounts, i);
        string censor = "***-**-";
        string censored_ssn = censor + ssn_last_four;
        cout << setw(15) << accounts[i].get_account_number() << setw(15) << accounts[i].get_depositor().get_name().get_first_name() << setw(15) << accounts[i].get_depositor().get_name().get_last_name() << setw(15) << censored_ssn << setw(15) << accounts[i].get_balance() << endl;
    }
}

int new_acct(vector<BankAccount> &accounts)
{

    string create_first_name, create_last_name;
    int create_account_number, create_ssn;
    double create_balance;
    char verification;

    cout << "Please enter the account number for the new account: ";
    cin >> create_account_number;
    if (account_exists(accounts, create_account_number))
    {
        cout << "Account Number already exists. Please select a new Account Number and try again." << "\n" << endl;
        return -1;
    }
    //continue with account creation
    cout << "Please enter the first name: ";
    cin >> create_first_name;
    cout << "Please enter the last name: ";
    cin >> create_last_name;
    cout << "Please enter the social security number: ";
    cin >> create_ssn;
    cout << "Please enter the starting balance: ";
    cin >> create_balance;
    cout << "Please verify the information below: " << endl;
    cout << "Account Number: " << create_account_number << endl;
    cout << "First Name: " << create_first_name << endl;
    cout << "Last Name: " << create_last_name << endl;
    cout << "Social Security Number: " << create_ssn << endl;
    cout << "Starting Balance: " << create_balance << endl;
    cout << "Is this information correct? (Y/N): ";
    cin >> verification;

    if (verification == 'Y')
    {
        accounts.push_back(BankAccount(Depositor(Name(create_first_name, create_last_name), create_ssn), create_account_number, create_balance));
        cout << "Account created successfully." << endl;
        return accounts.size(); // account creation successful print words
        
    }
    else
    {
        cout << "Account creation cancelled." << endl;
        return -1; // account creation failed
    }
}

void balance(vector<BankAccount> &accounts)
{
    int account_number;
    cout << "Please enter the account number: ";
    cin >> account_number;
    if (!account_exists(accounts, account_number))
    {
        cout << "This account does not exist. Please try again." << endl;
        return;
    }
    else
    {
        int account_number_index = find_account_index(accounts, account_number);
        cout << "Account number: " << account_number << " has a balance of: $" << accounts[account_number_index].get_balance() << endl;
    }
}

void withdrawl(vector<BankAccount> &accounts)

{
    int account_number;
    cout << "Please enter the account number: ";
    cin >> account_number;
    if (!account_exists(accounts, account_number))
    {
    cout << "Account number does not exist. Please verify account number and try again." << endl;
    return;
    }
    else
    {
        cout << "Please enter the amount to withdraw: $";
        double withdrawl_amount;
        cin >> withdrawl_amount;

        int account_number_index = find_account_index(accounts, account_number);
       
        if (withdrawl_amount < 0)
        {
            cout << "Invalid withdrawl amount. Please try again." << endl;
            return;
        }
        else if (withdrawl_amount > accounts[account_number_index].get_balance())
        {
            cout << "Insufficient funds. Please check balance and try again." << endl;
            return;
        }
        else
        {
            accounts[account_number_index].set_balance(accounts[account_number_index].get_balance() - withdrawl_amount);
            cout << "Withdrawl successful. New balance: $" << accounts[account_number_index].get_balance() << endl;
            return;
        }
    }
}

void deposit(vector<BankAccount> &accounts)
{
    int account_number;
    cout << "Please enter the account number: ";
    cin >> account_number;
    if (!account_exists(accounts, account_number))
    {
        cout << "Account number does not exist. Please verify Account Number and try again." << endl;
        return;
    }
    double deposit_amount;
    cout << "Please enter the amount to deposit: $";
    cin >> deposit_amount;
    if (deposit_amount < 0)
    {
        cout << "Invalid deposit amount. Please try again." << endl;
        return;
    }
    else
    {
        int account_index_number = find_account_index(accounts, account_number);
        accounts[account_index_number].set_balance(accounts[account_index_number].get_balance() + deposit_amount);
        cout << "Deposit successful. New balance: $" << accounts[account_index_number].get_balance() << endl;
        return;
    }
}

int delete_account(vector<BankAccount> &accounts)
{   
    char delete_verification;
    int account_number;
    cout << "Please enter the account number you would like to delete: ";
    cin >> account_number;
    if (!account_exists(accounts, account_number))
    {
        cout << "Account Number does not exist. Please verify the Account Number and try again." << endl;
        return -1;
    }
    else
    {
        if (has_balance(accounts, account_number))//account still has balance
        {
            cout << "Account number " << account_number << " has a remaining balance. Please withdraw all funds before deleting the account." << endl;
            return -1;
        }
        else
        {
            int account_number_index = find_account_index(accounts, account_number);
            cout << "Account Number " << account_number << " is associated with the following account: " << endl;
            cout << "First Name: " << accounts[account_number_index].get_depositor().get_name().get_first_name() << endl;
            cout << "Last Name: " << accounts[account_number_index].get_depositor().get_name().get_last_name() << endl;
            cout << "Remaining Balance: " << accounts[account_number_index].get_balance() << endl;
            cout << "Are you sure you would like to delete this account? (Y/N): ";
            cin >> delete_verification;
            if (delete_verification == 'Y')
            {
                accounts.erase(accounts.begin() + account_number_index);
                cout << "Account number " << account_number << " has been successfully deleted." << endl;
                return accounts.size(); 
            }    
            else
            {
                cout << "Account deletion cancelled." << endl;
                return -1;
            }
        }
    } 
}

void account_info(vector<BankAccount> &accounts)
{
    int ssn;
    cout << "Please enter the social security number: ";
    cin >> ssn;
    if (social_security_number_exists(accounts, ssn))
    {
        string ssn_string = to_string(ssn);
        string ssn_last_four = ssn_string.substr(ssn_string.length() - 4);
        int ssn_index = find_social_security_number_index(accounts, ssn);
        string censor = "***-**-";
        string censored_ssn = censor + ssn_last_four;


        cout << "First Name: " << accounts[ssn_index].get_depositor().get_name().get_first_name() << endl;
        cout << "Last Name: " << accounts[ssn_index].get_depositor().get_name().get_last_name() << endl;
        cout << "Account Number: " << censored_ssn << endl;
        cout << "Balance: " << accounts[ssn_index].get_balance() << endl;
    }
    else
    {
        cout << "Account not found. Please check SSN and try again." << endl;
        return;
    }
}

//Support Functions
bool account_exists(const vector<BankAccount> &accounts, int account_number)//support function
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].get_account_number() == account_number)
        {
            return true; //account number already exists
        }
    }
    return false; //continue with account creation
}

bool has_balance(const vector<BankAccount> &accounts, int account_number)//support function
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].get_account_number() == account_number)
        {
            if (accounts[i].get_balance() > 0)
            {
                return true; //account has balance
            }
        }
    }
    return false; //account has no balance
}

int find_account_index(const vector<BankAccount> &accounts, int account_number)//support function
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].get_account_number() == account_number)
        {
            return i;
        }
    }
    return -1;
}

bool social_security_number_exists(const vector<BankAccount> &accounts, int ssn)// support function
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].get_depositor().get_social_security_number() == ssn)
        {
            return true;
        }
    }
    return false;
}

int find_social_security_number_index(const vector<BankAccount> &accounts, int ssn)//support function
{
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].get_depositor().get_social_security_number() == ssn)
        {
            return i;
        }
    }
    return -1;
}