#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

void create_transaction();
void list_transaction();
void create_booking();
void modify_booking();
void search_booking();
void display_booking_summary();

struct Person {
    char name[50];
    int age, id;
    int payment_method;

    char card_credit_name[50];
    char card_credit_number[20];
    char card_credit_expiry_date[10];

    char card_debit_name[50];
    char card_debit_number[20];
    char card_debit_expiry_date[10];
};

void saveTransaction(const Person& p) {
    ofstream outFile("transactions.dat", ios::binary | ios::app);
    if (!outFile) {
        cout << "\n[!] Error: could not open file for saving.\n";
        return;
    }
    outFile.write(reinterpret_cast<const char*>(&p), sizeof(Person));
    outFile.close();
}

void create_transaction() {
    system("CLS");
    Person p;
    bool in_transaction = true;

    while (in_transaction) {
        cout << " \n ---------------------------------------" << endl;
        cout << "|     1. Credit Cards                   |" << endl;
        cout << "|     2. Debit Cards                    |" << endl;
        cout << "|     3. Exit Menu                      |" << endl;
        cout << " ---------------------------------------" << endl;
        cout << "Choose payment method (or 3 to Exit): ";
        cin >> p.payment_method;
        cin.ignore(1000, '\n');

        if (p.payment_method == 3) {
            cout << "Exiting payment menu." << endl;
            break;
        }

        if (p.payment_method == 1) {
            cout << "\n----- Enter Credit Card Details -----" << endl;
            cout << "Cardholder Name (or 0 to cancel): ";
            cin.getline(p.card_credit_name, 50);
            if (strcmp(p.card_credit_name,"0") == 0 ) {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }

            bool canceled = false;
            do {
                cout << "Masked Card Number: ";
                cin.getline(p.card_credit_number,20);
                if (strcmp(p.card_credit_number,"0") == 0) {
                    canceled = true;
                    break;
                }
                if (strlen(p.card_credit_number) > 16 || strlen(p.card_credit_number) < 12) {
                    cout << "\n[!] Invalid! Please double check your masked number.\n" << endl;
                }

            } while (strlen(p.card_credit_number) > 16 || strlen(p.card_credit_number) < 12);

            if (canceled) {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }

            cout << "Expiry Date (MM/YY): ";
            cin.getline(p.card_credit_expiry_date,10);
            if (strcmp(p.card_credit_expiry_date,"0") == 0) {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }
            cout << "\n[+] Transaction details recorded successfully!" << endl;
            saveTransaction(p);
            in_transaction = false;
        }
        else if (p.payment_method == 2) {
            cout << "\n----- Enter Debit Card Details -----" << endl;
            cout << "Cardholder Name (or 0 to cancel): ";
            cin.getline(p.card_debit_name,50);
            if (strcmp(p.card_debit_name,"0") == 0) {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }

            bool canceled = false;
            do {
                cout << "Masked Card Number: ";
                cin.getline(p.card_debit_number,20);
                if (strcmp(p.card_debit_number,"0") == 0) {
                    canceled = true;
                    break;
                }
                if (strlen(p.card_debit_number) > 16 || strlen(p.card_debit_number) < 12) {
                    cout << "\n[!] Invalid! Please double check your masked number.\n" << endl;
                }
            } while (strlen(p.card_debit_number) > 16 || strlen(p.card_debit_number) < 12);

            if (canceled) {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }

            cout << "Expiry Date (MM/YY): ";
            cin.getline(p.card_debit_expiry_date,10);
            if (strcmp(p.card_debit_expiry_date,"0") == 0) {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }

            cout << "\n[+] Transaction details recorded successfully!" << endl;
            saveTransaction(p);
            in_transaction = false;
        }
        else {
            cout << "\nInvalid choice! You must enter 1, 2, or 3." << endl;
        }
    }
}

void list_transaction() {
    ifstream inFile("transactions.dat", ios::binary);
    if (!inFile) {
        cout << "\n[!] No transactions found.\n";
        return;
    }

    Person p;
    while (inFile.read(reinterpret_cast<char*>(&p), sizeof(Person))) {
        cout << "Payment Method: " << (p.payment_method == 1 ? "Credit" : "Debit") << "\n";
        if (p.payment_method == 1) {
            cout << p.card_credit_name << "," << p.card_credit_number << "," << p.card_credit_expiry_date << "\n";
        }
        else {
            cout << p.card_debit_name << "," << p.card_debit_number << "," << p.card_debit_expiry_date << "\n";
        }
        cout << "----------------------------\n";
    }
    inFile.close();
}

void create_booking() {
    cout << "\n[Feature under construction: Create Booking]\n";
}

void modify_booking() {
    cout << "\n[Feature under construction: Modify Booking]\n";
}

void search_booking() {
    cout << "\n[Feature under construction: Search Booking]\n";
}

void display_booking_summary() {
    cout << "\n[Feature under construction: Display Booking Summary]\n";
}

int main() {
    system("CLS");
    int choose = -1;

    while (choose != 0) {
        cout << "========================================" << endl;
        cout << "       TRANSACTION & BOOKING MENU       " << endl;
        cout << "========================================" << endl;
        cout << "         1.Create Transaction           " << endl;
        cout << "         2.List Transaction             " << endl;
        cout << "         3.Create Booking               " << endl;
        cout << "         4.Modify Booking               " << endl;
        cout << "         5.Search Booking               " << endl;
        cout << "         6.Display Booking Summary      " << endl;
        cout << "         0.Exit                         " << endl;
        cout << "========================================" << endl;
        cout << "Select a function: ";
        cin >> choose;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choose) {
        case 1:
            create_transaction();
            break;
        case 2:
            list_transaction();
            break;
        case 3:
            create_booking();
            break;
        case 4:
            modify_booking();
            break;
        case 5:
            search_booking();
            break;
        case 6:
            display_booking_summary();
            break;
        case 0:
            cout << "\nExiting main menu." << endl;
            break;
        default:
            cout << "Invalid selection. Please choose between 0 to 6 only." << endl;
            break;
        }
    }
}
