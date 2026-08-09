#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits> // Required for buffer clearing

using namespace std;

int payment_method;

// Credit Card Variables
string card_credit_name, card_credit_number, card_credit_expiry_date;

// Debit Card Variables
string card_dedit_name, card_dedit_number, card_dedit_expiry_date;

void create_transaction() {
    cout << "----------------------------------------" << endl;
    cout << "|     1. Credit Cards                   |" << endl;
    cout << "|     2. Debit Cards                    |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Choose one payment method from above : ";
    cin >> payment_method;
    cin.ignore();

    if (payment_method == 1) {
        cout << "\n----- Enter Credit Card Details -----" << endl;
        cout << "Cardholder Name: ";
        getline(cin, card_credit_name);

        do {
            cout << "Masked Card Number: ";
            getline(cin, card_credit_number);
            if (card_credit_number.length() > 16) {
                cout << "Number too long! Please enter up to 16 digits.\n";
            }
        } while (card_credit_number.length() > 16);

        cout << "Expiry Date (MM/YY): ";
        getline(cin, card_credit_expiry_date);

    }
    else if (payment_method == 2) {
        cout << "\n----- Enter Debit Card Details -----" << endl;
        cout << "Cardholder Name: ";
        getline(cin, card_dedit_name);

        do {
            cout << "Masked Card Number: ";
            getline(cin, card_dedit_number);
            if (card_dedit_number.length() > 16) {
                cout << "Number too long! Please enter up to 16 digits.\n";
            }
        } while (card_dedit_number.length() > 16);

        cout << "Expiry Date (MM/YY): ";
        getline(cin, card_dedit_expiry_date);

    }
    else {
        cout << "Invalid choice! You must enter 1 or 2 only." << endl;
    }
}

int main() {
    create_transaction();
    return 0;
}
