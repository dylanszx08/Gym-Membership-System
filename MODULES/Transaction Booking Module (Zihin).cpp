#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <ctime>

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
            if (strcmp(p.card_credit_name, "0") == 0) {
                cout << "\n[!] Transaction canceled." << endl;
                continue;
            }

            bool canceled = false;
            do {
                cout << "Masked Card Number: ";
                cin.getline(p.card_credit_number, 20);
                if (strcmp(p.card_credit_number, "0") == 0) {
                    canceled = true;
                    break;
                }
                if (strlen(p.card_credit_number) > 16 || strlen(p.card_credit_number) < 12) {
                    cout << "\n[!] Invalid! Please double check your masked number.\n" << endl;
                }
            } while (strlen(p.card_credit_number) > 16 || strlen(p.card_credit_number) < 12);

            if (canceled) {
                cout << "\n[!] Transaction canceled." << endl;
                continue;
            }

            cout << "Expiry Date (MM/YY): ";
            cin.getline(p.card_credit_expiry_date, 10);
            if (strcmp(p.card_credit_expiry_date, "0") == 0) {
                cout << "\n[!] Transaction canceled." << endl;
                continue;
            }
            cout << "\n[+] Transaction details recorded successfully!" << endl;
            in_transaction = false;
        }
        else if (p.payment_method == 2) {
            cout << "\n----- Enter Debit Card Details -----" << endl;
            cout << "Cardholder Name (or 0 to cancel): ";
            cin.getline(p.card_debit_name, 50);
            if (strcmp(p.card_debit_name, "0") == 0) {
                cout << "\n[!] Transaction canceled." << endl;
                continue;
            }

            bool canceled = false;
            do {
                cout << "Masked Card Number: ";
                cin.getline(p.card_debit_number, 20);
                if (strcmp(p.card_debit_number, "0") == 0) {
                    canceled = true;
                    break;
                }
                if (strlen(p.card_debit_number) > 16 || strlen(p.card_debit_number) < 12) {
                    cout << "\n[!] Invalid! Please double check your masked number.\n" << endl;
                }
            } while (strlen(p.card_debit_number) > 16 || strlen(p.card_debit_number) < 12);

            if (canceled) {
                cout << "\n[!] Transaction canceled." << endl;
                continue;
            }

            cout << "Expiry Date (MM/YY): ";
            cin.getline(p.card_debit_expiry_date, 10);
            if (strcmp(p.card_debit_expiry_date, "0") == 0) {
                cout << "\n[!] Transaction canceled." << endl;
                continue;
            }

            cout << "\n[+] Transaction details recorded successfully!" << endl;
            in_transaction = false;
        }
        else {
            cout << "\nInvalid choice! You must enter 1, 2, or 3." << endl;
        }
    }
}

void list_transaction() {
    system("CLS");
    cout << "\n[Feature under construction: List Transaction]\n";
    cout << "\nPress Enter to return to the menu...";
    cin.get();
}

const int time_booking = 6;
const int date_booking = 7;
const int MAX_PLACES = 10; 
int available_places[date_booking][time_booking];
void init_places() {
    for (int d = 0; d < date_booking; d++) {
        for (int t = 0; t < time_booking; t++) {
            available_places[d][t] = MAX_PLACES;
        }
    }
}

int booking;
time_t now = time(0);
tm today = *localtime(&now);
string dateSlot[date_booking];

string timeSlot[time_booking] = {
    "09:00 AM - 11:00 AM",
    "11:00 AM - 01:00 PM",
    "01:00 PM - 03:00 PM",
    "03:00 PM - 05:00 PM",
    "05:00 PM - 07:00 PM",
    "07:00 PM - 09:00 PM"
};

int slotStartHours[time_booking] = { 9, 11, 13, 15, 17, 19 };

void display_timetable() {
    time_t now = time(0);
    int currentHour = today.tm_hour;

    cout << "------- DATE -------" << endl;
    for (int i = 0; i < date_booking; i++) {
        time_t t = now + (i * 86400);
        tm day = *localtime(&t);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%d %b (%a)", &day);
        dateSlot[i] = buffer;
        cout << (i + 1) << ". " << dateSlot[i] << endl;
    }

    cout << "\nChoose your date (1-7): ";
    cin >> booking;

    int d = booking - 1;
    if (d >= 0 && d < date_booking) {
        system("CLS");
        cout << "\n----- Selected Date: " << dateSlot[d] << " -----" << endl;
        cout << "Slot           Time          Places Available" << endl;
        for (int i = 0; i < time_booking; i++) {
            bool isPast = (d == 0 && currentHour >= slotStartHours[i]);
            if (isPast) {
                cout << " " << i + 1 << ".     " << timeSlot[i] << "     [UNAVAILABLE - Passed]" << endl;
            }
            else {
                cout << " " << i + 1 << ".     " << timeSlot[i] << "     "<< available_places[d][i] << " / " << MAX_PLACES << endl;
            }
        }

        int slot_choice;
        cout << "\nChoose your time slot (1-6): ";
        cin >> slot_choice;

        int t = slot_choice - 1;
        if (t >= 0 && t < time_booking) {
            if (available_places[d][t] > 0) {
                available_places[d][t]--;
                cout << "\n[+] Booking confirmed for " << dateSlot[d]
                    << " at " << timeSlot[t] << endl;
                cout << "    Remaining places in this slot: " << available_places[d][t] << endl;
            }
            else {
                cout << "\n[!] Fully Booked! No places available for this slot." << endl;
            }
        }
        else {
            cout << "\n[!] Invalid time slot choice." << endl;
        }
    }
    else {
        cout << "\n[!] Invalid date choice." << endl;
    }
}

void create_booking() {
    system("CLS");
    cout << "\n===== Create Booking =====" << endl;
    display_timetable();
    cout << "\nPress Enter to return to main menu...";
    cin.ignore(1000, '\n');
    cin.get();
}

void modify_booking() {
    system("CLS");
    cout << "\n[Feature under construction: Modify Booking]\n";
}

void search_booking() {
    system("CLS");
    cout << "\n[Feature under construction: Search Booking]\n";
}

void display_booking_summary() {
    system("CLS");
    cout << "\n[Feature under construction: Display Booking Summary]\n";
}

int main() {
    system("CLS");
    init_places();
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
        cin.ignore(1000, '\n');

        switch (choose) {
        case 1: create_transaction(); break;
        case 2: list_transaction(); break;
        case 3: create_booking(); break;
        case 4: modify_booking(); break;
        case 5: search_booking(); break;
        case 6: display_booking_summary(); break;
        case 0: cout << "\nExiting main menu." << endl; break;
        default: cout << "Invalid selection. Please choose between 0 to 6 only." << endl; break;
        }
    }
}
