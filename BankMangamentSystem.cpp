/* Bank Management System using C++ and compiled using GCC Compiler */
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string.h>
using namespace std;

/* Defining functions */
int login();     // function for loginscreen
void intro();    // function to display mainpage
void date1();    // to get current date
void delay();    // function for loading effect
void callExit(); // exit function

// CLASS USED IN PROJECT
class account
{
    int Account_No;
    char Account_Holder_Name[44];
    char type;
    int Deposit_Amount;

public:
    void Open_account();               // function to get data from user
    void Display_account() const;      // function to show data on screen
    void Update();                     // function to add new data
    void dep(int);                     // function to accept amount and add to balance amount
    void Withdraw(int);                // function to accept amount and subtract from balance amount
    void report() const;               // function to show data in tabular format
    int Return_Account_Number() const; // function to return account number
    int Return_Deposit_Amount() const; // function to return balance amount
    char Return_type() const;          // function to return type of account
};                                     // class ends here

void account::Display_account() const
{
    cout << "\nAccount No. : " << Account_No;
    cout << "\nAccount Holder Name : ";
    cout << Account_Holder_Name;
    cout << "\nType of Account : \t" << type;
    cout << "\n\tBalance amount : " << Deposit_Amount;
}
void account::Open_account()
{
    cout << "\nPlease! Enter The account No. :";
    cin >> Account_No;
    cout << "\nPlease! Enter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(Account_Holder_Name, 44);
    cout << "\nPlease! Enter Type of The account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\nPlease! Enter The Initial amount(>=440 for Saving and >=1000 for current ) : ";
    cin >> Deposit_Amount;
    cout << "\n\nAccount Created..";
}

void account::dep(int x)
{
    Deposit_Amount += x;
}

void account::Withdraw(int x)
{
    Deposit_Amount -= x;
}

void account::report() const
{
    cout << Account_No << setw(10) << " " << Account_Holder_Name << setw(10) << " " << type << setw(6) << Deposit_Amount << endl;
}

void account::Update()
{
    cout << "\nAccount No. : " << Account_No;
    cout << "\nUpdate Account Holder Name : ";
    cin.ignore();
    cin.getline(Account_Holder_Name, 44);
    cout << "\nUpdate Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nUpdate Balance amount : ";
    cin >> Deposit_Amount;
}

int account::Return_Account_Number() const
{
    return Account_No;
}

char account::Return_type() const
{
    return type;
}
int account::Return_Deposit_Amount() const
{
    return Deposit_Amount;
}

// function declaration

void delete_account(int);                   // function to delete record of file
void display_all();                         // function to display all account details
void write_account();                       // function to write record in binary file
void display_sp(int);                       // function to display account details given by user
void Deposit_Amount_withWithdraw(int, int); // function to desposit/withWithdraw amount for given account
void intro();                               // introductory screen function
void Update_account(int);                   // function to Update record of file
// THE MAIN FUNCTION OF PROGRAM

int main()
{
    char ch;
    int num;
    login();
    intro();
    do
    {
        system("cls");
        cout << "\n\n\t\tMAIN MENU";
        cout << "\n\t\t01. NEW ACCOUNT";
        cout << "\n\t\t02. Deposit_Amount AMOUNT";
        cout << "\n\t\t03. WITHWithdraw AMOUNT";
        cout << "\n\t\t04. BALANCE ENQUIRY";
        cout << "\n\t\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t\t06. CLOSE AN ACCOUNT";
        cout << "\n\t\t07. Update AN ACCOUNT";
        cout << "\n\t\t08. EXIT";
        cout << "\n\t\tSelect Your Option (1/2/3/4/5/6/7/8) :";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout << "\n\t\tPlease! Enter The account No. : ";
            cin >> num;
            Deposit_Amount_withWithdraw(num, 1);
            break;
        case '3':
            cout << "\n\t\tPlease! Enter The account No. : ";
            cin >> num;
            Deposit_Amount_withWithdraw(num, 2);
            break;
        case '4':
            cout << "\n\t\tPlease! Enter The account No. : ";
            cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout << "\n\t\tPlease! Enter The account No. : ";
            cin >> num;
            delete_account(num);
            break;
        case '7':
            cout << "\n\t\tPlease! Enter The account No. : ";
            cin >> num;
            Update_account(num);
            break;
        case '8':
            cout << "\n\t\tThanks for using bank managemnt system";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
}
// function to write in file

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.Open_account();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
    outFile.close();
}

// function to read specific record from file

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.Return_Account_Number() == n)
        {
            ac.Display_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\nAccount number does not exist";
}

// function to Update record of file

void Update_account(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.Return_Account_Number() == n)
        {
            ac.Display_account();
            cout << "\nPlease! Enter The New Details of account : " << endl;
            ac.Update();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\t\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n Record Not Found ";
}

// function to delete record of file

void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.Return_Account_Number() != n)
        {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\t\tRecord Deleted ..";
}

// function to display all accounts Deposit_Amount list

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\t\t\t\tACCOUNT HOLDER LIST\n";
    cout << "**********************************************************************\n";
    cout << "|  A/c no.      |        NAME            |  Type  |         Balance  | \n";
    cout << "**********************************************************************\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

//  	function to Deposit_Amount and withWithdraw amounts

void Deposit_Amount_withWithdraw(int n, int option)
{
    int Amount;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.Return_Account_Number() == n)
        {
            ac.Display_account();
            if (option == 1)
            {
                cout << "\n\t\tTO Deposit_AmountE AMOUNT ";
                cout << "\nPlease! Enter The amount to be Deposit_Amounted : ";
                cin >> Amount;
                ac.dep(Amount);
            }
            if (option == 2)
            {
                cout << "\n\t\tTO WITHWithdraw AMOUNT ";
                cout << "\nPlease! Enter The amount to be withWithdraw : ";
                cin >> Amount;
                int bal = ac.Return_Deposit_Amount() - Amount;
                if ((bal < 440 && ac.Return_type() == 'S') || (bal < 1000 && ac.Return_type() == 'C'))
                    cout << "Insufficience balance";
                else
                    ac.Withdraw(Amount);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\t\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n Record Not Found ";
}

int login()
{
    char username[30];
    char password[30];
    int true1 = 1;
    int try1 = 0;
    int i = 0;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n";
        cout << "\t\t\t\t    ************************\n";
        cout << "\t\t\t\t    |BANK MANAGEMENT SYSTEM|\n";
        cout << "\t\t\t\t    ************************\n";
        cout << "\n\n";
        cout << "\t\t\t\t\t";
        cout << "Username : ";
        cin >> username;
        cout << "\t\t\t\t\t";
        cout << "\n";
        cout << "\t\t\t\t\t";
        cout << "Password : ";
        cin >> password;
        if (strcmp(username, "aniket123") == 0 && strcmp(password, "Aniket2626") == 0)
        {
            cout << "\n\n";
            cout << "\t\t\t\t";
            cout << "You are accessed to the system!\n\n";
            cout << "\t\t\t\t";
            system("pause");
            system("cls");
            true1 = 0;
            return 1;
        }
        else
        {
            system("cls");
            try1 = try1 + 1;
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout << "\t\t\t\t\t";
            cout << "No. of attempts remain: " << 5 - try1;
            cout << "\n\n";
            cout << "\t\t\t\t";
            system("pause");
            if (try1 >= 5)
            {

                cout << "\t\t\t\t\t\t";
                cout << "\n";
                cout << "\t\t\t\t";
                cout << "No permission to enter the system!\n\n";
                cout << "\t\t\t\t";
                system("pause");
                callExit();
            }
        } // END OF ELSE
    } while (try1 < 5);
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}

// INTRODUCTION FUNCTION
void intro()
{
    int process = 0;
    system("cls");
    date1();
    cout << "\n";
    cout << "\t\t\t\t    ------------------------\n";
    cout << "\t\t\t\t    |BANK MANAGEMENT SYSTEM|\n";
    cout << "\t\t\t\t    ------------------------\n";
    cout << "\n";
    cout << "\t\t\t\t";
    cout << "Prepared By    ";
    cout << ":";
    cout << "   Aniket Laxman Patil";
    cout << "\n\n";
    cout << "\t\t\t\t";
    cout << "Mini Project   ";
    cout << ":";
    cout << "   Bank Management System";
    cout << "\n";
    cout << "\t\t\t\t";
    cout << "\n";
    cout << "\n";
    cout << "\t\t\t\t";
    system("pause");
    cout << "\n\t\t\t\tLoading";

    for (process = 0; process < 25; process++)
    {
        delay(150);
        cout << ".";
    }
}
void callExit()
{
    int process = 0;
    system("cls");
    cout << "\n\n\n\n\n";
    cout << "\n\tTaking You Out of The System";
    for (process = 0; process < 25; process++)
    {
        delay(150);
        cout << ".";
    }
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t";
    cout << "You are out of the System.\n";
    cout << "\t\t\t\t\t\t";
    cout << "Thank You !";
    cout << "\n\n";
    cout << "\t\t\t\t\t";
    system("pause");
    exit(0);
}

void date1()
{
    time_t T = time(NULL);
    struct tm tm = *localtime(&T);
    cout << "\n\n\n";
    cout << "\t\t\t\t\t Date:" << tm.tm_mday << "/" << tm.tm_mon + 1 << "/" << tm.tm_year + 1900 << "\n";
}