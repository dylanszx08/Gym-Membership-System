#include <iostream>
#include <string>

using namespace std;

int payment_method;
string card_name, card_number, card_expiry_date;
string card_credit_name, card_credit_number, card_credit_expiry_date;
string card_debit_name, card_debit_number, card_debit_expiry_date;

void create_transaction() {
    bool in_transaction = true;

    while (in_transaction) {
        cout << " \n---------------------------------------" << endl;
        cout << "|     1. Credit Cards                   |" << endl;
        cout << "|     2. Debit Cards                    |" << endl;
        cout << "|     3. Exit Menu                      |" << endl;
        cout << " ---------------------------------------" << endl;
        cout << "Choose payment method (or 3 to Exit): ";
        cin >> payment_method;
        cin.ignore();

        if (payment_method == 3) {
            cout << "Exiting payment menu." << endl;
            break;
        }

        if (payment_method == 1) {
            cout << "\n----- Enter Credit Card Details -----" << endl;
            cout << "Cardholder Name: ";
            getline(cin, card_credit_name);
            if (card_credit_name == "0") {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }

            bool canceled = false;
            do {
                cout << "Masked Card Number: ";
                getline(cin, card_credit_number);
                if (card_credit_number == "0") {
                    canceled = true;
                    break;
                }
                if (card_credit_number.length() > 16 || card_credit_number.length() < 15) {
                    cout << "\n[!] Invalid ! Please double check your masked number.\n" << endl;
                }
                
            } while (card_credit_number.length() > 16 || card_credit_number.length() < 15);
            if (canceled) {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue; 
            }

            cout << "Expiry Date (MM/YY): ";
            getline(cin, card_credit_expiry_date);
            if (card_credit_expiry_date == "0") {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }

            cout << "\n[+] Transaction details recorded successfully!" << endl;
            in_transaction = false;

        }
        else if (payment_method == 2) {
            cout << "\n----- Enter Debit Card Details -----" << endl;
            cout << "Cardholder Name: ";
            getline(cin, card_debit_name);
            if (card_debit_name == "0") {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }

            bool canceled = false;
            do {
                cout << "Masked Card Number: ";
                getline(cin, card_debit_number);
                if (card_debit_number == "0") {
                    canceled = true;
                    break;
                }
                if (card_debit_number.length() > 16 || card_debit_number.length() < 15) {
                    cout << "\n[!] Invalid ! Please double check your masked number.\n" << endl;
                }
            } while (card_debit_number.length() > 16 || card_debit_number.length() < 15);
            if (canceled) {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }

            cout << "Expiry Date (MM/YY): ";
            getline(cin, card_debit_expiry_date);
            if (card_debit_expiry_date == "0") {
                cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
                continue;
            }

            cout << "\n[+] Transaction details recorded successfully!" << endl;
            in_transaction = false;
        }
        else {
            cout << "\nInvalid choice! You must enter 1, 2, or 3.." << endl;
        }
    }
}

int main() {
    create_transaction();
    return 0;
}
