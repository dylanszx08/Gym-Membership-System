#include <iostream>
#include <iomanip>
#include <fstream>  // Required for file operations
#include <string>

using namespace std;
int payment_menthod;
string card_credit_name;
string card_credit_number;
string card_credit_expiry_date;
string card_dedit_name;
string card_dedit_number;
string card_dedit_expiry_date;

void create_transaction() {
	cout << "----------------------------------------" << endl;
	cout << "|     1. Credit Cards                   |" << endl;
	cout << "|     2. Debit Cards                    |" << endl;
	cout << "----------------------------------------" << endl;
	cout << "Choose one payment menthod from atas : ";
	cin >> payment_menthod;
	
	switch (payment_menthod) {
	case 1:
		cout << "Cardholder Name: ";
		getline(cin, card_credit_name);
		cout << "Masked Card Number: ";
		getline(cin, card_credit_number);
		cout << "Expiry Date (MM/YY): ";
		getline(cin, card_credit_expiry_date);
	case 2:
		cout << "Cardholder Name: ";
		getline(cin, card_dedit_name);
		cout << "Masked Card Number: ";
		getline(cin, card_dedit_number);
		cout << "Expiry Date (MM/YY): ";
		getline(cin, card_dedit_expiry_date);
	default:
		cout << "Invalid ! You should just choose 1 or 2 only.";
	}
	
	
}

int main() {
	create_transaction();
	return 0;
}
