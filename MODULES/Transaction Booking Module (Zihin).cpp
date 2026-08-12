#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct User {
    int id;
    int payment_method;
    string card_name;
    string card_number_masked;
    string card_expiry_date;
};

const int maxUsers = 100;
User users[maxUsers];
int userCount = 0;
int nextId = 1;

void createTransaction() {
    if (userCount >= maxUsers) {
        cout << "\nCannot create transaction: Storage is full!" << endl;
        return;
    }

    User u;
    u.id = nextId++;
    bool in_transaction = true;

    while (in_transaction) {
        cout << "\n---------------------------------------" << endl;
        cout << "|     1. Credit Cards                   |" << endl;
        cout << "|     2. Debit Cards                    |" << endl;
        cout << "|     0. Exit Menu                      |" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Choose payment method (or 0 to Exit): ";
        cin >> u.payment_method;
        cin.ignore();

        if (u.payment_method == 0) {
            cout << "Exiting payment menu." << endl;
            return;
        }

        if (u.payment_method != 1 && u.payment_method != 2) {
            cout << "\nInvalid choice! You must enter 1, 2, or 3." << endl;
            continue;
        }

        string label = (u.payment_method == 1) ? "Credit" : "Debit";
        cout << "\n----- Enter " << label << " Card Details -----" << endl;

        cout << "Cardholder Name (or 0 to cancel): ";
        getline(cin, u.card_name);
        if (u.card_name == "0") {
            cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
            continue;
        }

        bool canceled = false;
        string number;
        do {
            cout << "Card Number (last 4 digits only): ";
            getline(cin, number);
            if (number == "0") {
                canceled = true;
                break;
            }
            if (number.length() != 4 || number.find_first_not_of("0123456789") != string::npos) {
                cout << "\n[!] Invalid! Please enter exactly 4 digits.\n" << endl;
            }
        } while (number.length() != 4 || number.find_first_not_of("0123456789") != string::npos);

        if (canceled) {
            cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
            continue;
        }
        u.card_number_masked = "**** **** **** " + number;

        cout << "Expiry Date (MM/YY): ";
        getline(cin, u.card_expiry_date);
        if (u.card_expiry_date == "0") {
            cout << "\n[!] Transaction canceled. Returning to payment menu..." << endl;
            continue;
        }

        cout << "\n[+] Transaction details recorded successfully!" << endl;
        //push_back
        users[userCount] = u;
        userCount++;

        in_transaction = false;
    }
}

void listTransactions() {
    if (userCount == 0) {
        cout << "\nNo transactions recorded yet.\n";
        return;
    }

    for (const auto& u : users) {
        cout << u.id << " | " << (u.payment_method == 1 ? "Credit" : "Debit")
            << " | " << u.card_name
            << " | " << u.card_number_masked
            << " | " << u.card_expiry_date << "\n";
    }
}

void editTransaction(int id) {
    for (auto& u : users) {
        if (u.id == id) {
            cout << "Enter new cardholder name (" << u.card_name << "): ";
            getline(cin, u.card_name);

            cout << "Enter new expiry date (" << u.card_expiry_date << "): ";
            getline(cin, u.card_expiry_date);

            cout << "Transaction updated.\n";
            return;
        }
    }
    cout << "Transaction not found.\n";
}

void saveToFile(const string& filename) {
    ofstream out(filename);
    for (const auto& u : users) {
        out << u.id << "," << u.payment_method << "," << u.card_name << ","
            << u.card_number_masked << "," << u.card_expiry_date << "\n";
    }
}

void loadFromFile(const string& filename) {
    userCount = 0;
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string idStr, pmStr, name, number, expiry;
        getline(ss, idStr, ',');
        getline(ss, pmStr, ',');
        getline(ss, name, ',');
        getline(ss, number, ',');
        getline(ss, expiry, ',');

        if (idStr.empty() || idStr == "0") continue;

        User u;
        u.id = stoi(idStr);
        u.payment_method = stoi(pmStr);
        u.card_name = name;
        u.card_number_masked = number;
        u.card_expiry_date = expiry;

        if (userCount < maxUsers) {
            users[userCount] = u;
            userCount++;
        }

        if (u.id >= nextId) nextId = u.id + 1;
    }
}

void create_booking();
void modify_booking();
void search_booking();
void display_booking_summary();

void create_booking() {
    //for (auto& u : users) {
    //    cout << "Enter your member ID : "
    //    if (u.id == id) {
    //        
    //    }
    //}
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
    loadFromFile("transactions.txt"); // load saved data on startup
    int choose = -1;

    while (choose != 0) {
        cout << "========================================" << endl;
        cout << "               MAIN MENU                " << endl;
        cout << "========================================" << endl;
        cout << "          1.Create Transaction          " << endl;
        cout << "          2.Create Booking              " << endl;
        cout << "          3.Modify Booking              " << endl;
        cout << "          4.Search Booking              " << endl;
        cout << "          5.Display Booking Summary     " << endl;
        cout << "          6.List Transactions           " << endl;
        cout << "          7.Edit Transaction            " << endl;
        cout << "          0.Exit                        " << endl;
        cout << "========================================" << endl;
        cout << "Select a function: ";
        cin >> choose;
        cin.ignore(100, '\n');

        switch (choose) {
        case 1:
            createTransaction();
            break;
        case 2:
            create_booking();
            break;
        case 3:
            modify_booking();
            break;
        case 4:
            search_booking();
            break;
        case 5:
            display_booking_summary();
            break;
        case 6:
            listTransactions();
            break;
        case 7: {
            int id;
            cout << "Enter ID to edit: ";
            cin >> id;
            cin.ignore(100, '\n');
            editTransaction(id);
            break;
        }
        case 0:
            cout << "\nExiting main menu." << endl;
            saveToFile("transactions.txt");
            break;
        default:
            cout << "Invalid selection. Please choose between 0 to 7 only." << endl;
            break;
        }
    }
    return 0;
}
