#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <fstream>

using namespace std;

// Global Constants
const int TOTAL_DATES = 7;
const int TOTAL_TIMES = 6;
const int MAX_SEATS_PER_SLOT = 10;
const int MAX_BOOKINGS = 100;
const int MAX_HISTORY = 100;
const int MAX_TRANSACTIONS = 100;

// Structures using C-strings
struct Booking {
    int userId;
    char name[50];
    int dateIdx;
    int timeIdx;
    bool active;
};

struct HistoryRecord {
    int userId;
    char name[50];
    char date[30];
    char timeSlot[30];
    char status[15];
};

struct TransactionRecord {
    int txId;
    int userId; // Ties transaction directly to a user
    char methodType[20];
    char cardHolderName[50];
    char cardNumber[20];
    char expiryDate[10];
};

// Global 1D Arrays
Booking bookings[MAX_BOOKINGS];
int booking_count = 0;

HistoryRecord history_log[MAX_HISTORY];
int history_count = 0;

TransactionRecord transaction_log[MAX_TRANSACTIONS];
int transaction_count = 0;

// Fixed Date and Time Arrays
char dateSlot[TOTAL_DATES][30] = {
    "Day 1 (Mon)", "Day 2 (Tue)", "Day 3 (Wed)",
    "Day 4 (Thu)", "Day 5 (Fri)", "Day 6 (Sat)", "Day 7 (Sun)"
};

char timeSlot[TOTAL_TIMES][30] = {
    "09:00 AM - 11:00 AM",
    "11:00 AM - 01:00 PM",
    "01:00 PM - 03:00 PM",
    "03:00 PM - 05:00 PM",
    "05:00 PM - 07:00 PM",
    "07:00 PM - 09:00 PM"
};

// Function Prototypes
bool is_only_digits(const char str[]);
int get_available_places(int d, int t);
void add_to_history(int userId, const char name[], const char date[], const char slot[], const char status[]);
void save_all_data();
void load_all_data();
void create_transaction();
void modify_transaction();
void list_transaction();
bool display_timetable();
void create_booking();
void modify_booking();
void search_booking();
void display_booking_summary();

// File I/O: Save Data
void save_all_data() {
    // Save Bookings
    ofstream fout_b("bookings.txt");
    if (fout_b) {
        fout_b << booking_count << endl;
        for (int i = 0; i < booking_count; i++) {
            fout_b << bookings[i].userId << endl;
            fout_b << bookings[i].name << endl;
            fout_b << bookings[i].dateIdx << endl;
            fout_b << bookings[i].timeIdx << endl;
            fout_b << bookings[i].active << endl;
        }
        fout_b.close();
    }

    // Save Transactions
    ofstream fout_t("transactions.txt");
    if (fout_t) {
        fout_t << transaction_count << endl;
        for (int i = 0; i < transaction_count; i++) {
            fout_t << transaction_log[i].txId << endl;
            fout_t << transaction_log[i].userId << endl;
            fout_t << transaction_log[i].methodType << endl;
            fout_t << transaction_log[i].cardHolderName << endl;
            fout_t << transaction_log[i].cardNumber << endl;
            fout_t << transaction_log[i].expiryDate << endl;
        }
        fout_t.close();
    }

    // Save History
    ofstream fout_h("history.txt");
    if (fout_h) {
        fout_h << history_count << endl;
        for (int i = 0; i < history_count; i++) {
            fout_h << history_log[i].userId << endl;
            fout_h << history_log[i].name << endl;
            fout_h << history_log[i].date << endl;
            fout_h << history_log[i].timeSlot << endl;
            fout_h << history_log[i].status << endl;
        }
        fout_h.close();
    }
}

// File I/O: Load Data
void load_all_data() {
    // Load Bookings
    ifstream fin_b("bookings.txt");
    if (fin_b) {
        fin_b >> booking_count;
        for (int i = 0; i < booking_count; i++) {
            fin_b >> bookings[i].userId;
            fin_b.ignore(1000, '\n');
            fin_b.getline(bookings[i].name, 50);
            fin_b >> bookings[i].dateIdx;
            fin_b >> bookings[i].timeIdx;
            fin_b >> bookings[i].active;
        }
        fin_b.close();
    }

    // Load Transactions
    ifstream fin_t("transactions.txt");
    if (fin_t) {
        fin_t >> transaction_count;
        for (int i = 0; i < transaction_count; i++) {
            fin_t >> transaction_log[i].txId;
            fin_t >> transaction_log[i].userId;
            fin_t.ignore(1000, '\n');
            fin_t.getline(transaction_log[i].methodType, 20);
            fin_t.getline(transaction_log[i].cardHolderName, 50);
            fin_t.getline(transaction_log[i].cardNumber, 20);
            fin_t.getline(transaction_log[i].expiryDate, 10);
        }
        fin_t.close();
    }

    // Load History
    ifstream fin_h("history.txt");
    if (fin_h) {
        fin_h >> history_count;
        for (int i = 0; i < history_count; i++) {
            fin_h >> history_log[i].userId;
            fin_h.ignore(1000, '\n');
            fin_h.getline(history_log[i].name, 50);
            fin_h.getline(history_log[i].date, 30);
            fin_h.getline(history_log[i].timeSlot, 30);
            fin_h.getline(history_log[i].status, 15);
        }
        fin_h.close();
    }
}

// Helper function to check digits
bool is_only_digits(const char str[]) {
    int len = (int)strlen(str);
    if (len == 0) return false;
    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

// Calculate open places in a slot
int get_available_places(int d, int t) {
    int occupied = 0;
    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].active && bookings[i].dateIdx == d && bookings[i].timeIdx == t) {
            occupied++;
        }
    }
    return MAX_SEATS_PER_SLOT - occupied;
}

// History Logger
void add_to_history(int userId, const char name[], const char date[], const char slot[], const char status[]) {
    if (history_count < MAX_HISTORY) {
        history_log[history_count].userId = userId;
        strcpy(history_log[history_count].name, name);
        strcpy(history_log[history_count].date, date);
        strcpy(history_log[history_count].timeSlot, slot);
        strcpy(history_log[history_count].status, status);
        history_count++;
    }
}

void create_transaction() {
    int method;
    cout << "\n---------------------------------------" << endl;
    cout << "|     1. Credit Cards                   |" << endl;
    cout << "|     2. Debit Cards                    |" << endl;
    cout << "|     0. Exit Menu                      |" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Choose payment method: ";
    cin >> method;

    if (method == 0) return;

    if (method == 1 || method == 2) {
        TransactionRecord tx;
        tx.txId = transaction_count + 1001;
        strcpy(tx.methodType, (method == 1) ? "Credit Card" : "Debit Card");

        cout << "Enter User ID: ";
        cin >> tx.userId;
        cin.ignore(1000, '\n');

        cout << "Enter Cardholder Name: ";
        cin.getline(tx.cardHolderName, 50);

        bool validCard = false;
        do {
            cout << "Enter Masked Card Number (12 to 16 digits only): ";
            cin.getline(tx.cardNumber, 20);

            int len = (int)strlen(tx.cardNumber);
            if (len < 12 || len > 16) {
                cout << "[!] Invalid length! Must be between 12 and 16 digits.\n\n";
            }
            else if (!is_only_digits(tx.cardNumber)) {
                cout << "[!] Invalid format! Card number must contain numbers only.\n\n";
            }
            else {
                validCard = true;
            }
        } while (!validCard);

        do {
            cout << "Enter Expiry Date MM/YY (exactly 5 characters, e.g., 12/26): ";
            cin.getline(tx.expiryDate, 10);
            int expLen = (int)strlen(tx.expiryDate);
            if (expLen != 5 || tx.expiryDate[2] != '/') {
                cout << "[!] Invalid format! Must be MM/YY (e.g., 12/26).\n\n";
            }
        } while ((int)strlen(tx.expiryDate) != 5 || tx.expiryDate[2] != '/');

        if (transaction_count < MAX_TRANSACTIONS) {
            transaction_log[transaction_count] = tx;
            transaction_count++;
            save_all_data();
            cout << "\n[+] Transaction recorded successfully!" << endl;
        }
    }
    else {
        cout << "\n[!] Invalid selection." << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.get();
}

void modify_transaction() {
    cout << "\n===== Modify Transaction =====" << endl;
    int target_id;
    cout << "Enter your User ID: ";
    if (!(cin >> target_id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    // Filter transaction log for target User ID only
    int user_matches[MAX_TRANSACTIONS];
    int match_count = 0;

    for (int i = 0; i < transaction_count; i++) {
        if (transaction_log[i].userId == target_id) {
            user_matches[match_count] = i;
            match_count++;
        }
    }

    if (match_count == 0) {
        cout << "\n[!] No transactions found for User ID " << target_id << "!\n";
        cout << "\nPress Enter to return to main menu...";
        cin.ignore(1000, '\n');
        cin.get();
        return;
    }

    cout << "\n---------------- TRANSACTIONS FOR USER " << target_id << " ----------------\n";
    for (int i = 0; i < match_count; i++) {
        int idx = user_matches[i];
        cout << " " << (i + 1) << ". TX ID: " << transaction_log[idx].txId
            << " | Type: " << left << setw(12) << transaction_log[idx].methodType
            << " | Name: " << setw(20) << transaction_log[idx].cardHolderName
            << " | Card: " << transaction_log[idx].cardNumber << endl;
    }
    cout << "------------------------------------------------------------------------\n";

    int choice;
    cout << "\nSelect transaction to modify (1-" << match_count << ", or 0 to exit): ";
    cin >> choice;

    if (choice <= 0 || choice > match_count) {
        cout << "\nModification canceled." << endl;
        cin.ignore(1000, '\n');
        cin.get();
        return;
    }

    int edit_idx = user_matches[choice - 1];

    int method;
    cout << "\nSelect new payment method (1. Credit Card, 2. Debit Card): ";
    cin >> method;
    cin.ignore(1000, '\n');

    if (method == 1 || method == 2) {
        strcpy(transaction_log[edit_idx].methodType, (method == 1) ? "Credit Card" : "Debit Card");
    }

    cout << "Enter new Cardholder Name: ";
    cin.getline(transaction_log[edit_idx].cardHolderName, 50);

    bool validCard = false;
    do {
        cout << "Enter new Masked Card Number (12 to 16 digits only): ";
        cin.getline(transaction_log[edit_idx].cardNumber, 20);

        int len = (int)strlen(transaction_log[edit_idx].cardNumber);
        if (len < 12 || len > 16) {
            cout << "[!] Invalid length! Must be between 12 and 16 digits.\n\n";
        }
        else if (!is_only_digits(transaction_log[edit_idx].cardNumber)) {
            cout << "[!] Invalid format! Card number must contain numbers only.\n\n";
        }
        else {
            validCard = true;
        }
    } while (!validCard);

    do {
        cout << "Enter new Expiry Date MM/YY (exactly 5 characters, e.g., 12/26): ";
        cin.getline(transaction_log[edit_idx].expiryDate, 10);
        int expLen = (int)strlen(transaction_log[edit_idx].expiryDate);
        if (expLen != 5 || transaction_log[edit_idx].expiryDate[2] != '/') {
            cout << "[!] Invalid format! Must be MM/YY (e.g., 12/26).\n\n";
        }
    } while ((int)strlen(transaction_log[edit_idx].expiryDate) != 5 || transaction_log[edit_idx].expiryDate[2] != '/');

    save_all_data();
    cout << "\n[+] Transaction updated successfully!" << endl;
    cout << "\nPress Enter to continue...";
    cin.get();
}

void list_transaction() {
    cout << "==================================================================================\n";
    cout << "                            LIST OF PAYMENT TRANSACTIONS                          \n";
    cout << "==================================================================================\n";

    if (transaction_count == 0) {
        cout << " No payment transactions recorded yet.\n";
    }
    else {
        cout << left << setw(8) << "TX ID"
            << setw(10) << "USER ID"
            << setw(16) << "TYPE"
            << setw(22) << "CARDHOLDER NAME"
            << setw(18) << "CARD NUMBER"
            << setw(10) << "EXPIRY" << endl;
        cout << "----------------------------------------------------------------------------------\n";

        for (int i = 0; i < transaction_count; i++) {
            cout << left << setw(8) << transaction_log[i].txId
                << setw(10) << transaction_log[i].userId
                << setw(16) << transaction_log[i].methodType
                << setw(22) << transaction_log[i].cardHolderName
                << setw(18) << transaction_log[i].cardNumber
                << setw(10) << transaction_log[i].expiryDate << endl;
        }
    }
    cout << "==================================================================================\n";
    cout << "\nPress Enter to continue...";
    cin.get();
}

bool display_timetable() {
    cout << "\n------- SELECT DATE -------" << endl;
    for (int i = 0; i < TOTAL_DATES; i++) {
        cout << (i + 1) << ". " << dateSlot[i] << endl;
    }

    int dateChoice;
    cout << "\nChoose date (1-7, or 0 to exit): ";
    cin >> dateChoice;

    if (dateChoice <= 0 || dateChoice > TOTAL_DATES) return false;
    int d = dateChoice - 1;

    cout << "\n----- Selected Date: " << dateSlot[d] << " -----" << endl;
    cout << "Slot           Time           Places Available" << endl;
    for (int i = 0; i < TOTAL_TIMES; i++) {
        int avail = get_available_places(d, i);
        cout << " " << (i + 1) << ".     " << timeSlot[i] << "     " << avail << " / " << MAX_SEATS_PER_SLOT << endl;
    }

    int timeChoice;
    cout << "\nChoose time slot (1-6, or 0 to exit): ";
    cin >> timeChoice;

    if (timeChoice <= 0 || timeChoice > TOTAL_TIMES) return false;
    int t = timeChoice - 1;

    if (get_available_places(d, t) > 0) {
        char bookerName[50];
        int bookerId;

        cin.ignore(1000, '\n');
        cout << "\nEnter Booker Name: ";
        cin.getline(bookerName, 50);
        cout << "Enter Booker User ID: ";
        cin >> bookerId;

        if (booking_count < MAX_BOOKINGS) {
            bookings[booking_count].userId = bookerId;
            strcpy(bookings[booking_count].name, bookerName);
            bookings[booking_count].dateIdx = d;
            bookings[booking_count].timeIdx = t;
            bookings[booking_count].active = true;
            booking_count++;

            add_to_history(bookerId, bookerName, dateSlot[d], timeSlot[t], "ACTIVE");
            save_all_data();

            cout << "\n[+] Booking confirmed for " << bookerName << " (ID: " << bookerId << ") on "
                << dateSlot[d] << " at " << timeSlot[t] << endl;
        }
    }
    else {
        cout << "\n[!] Fully Booked! No places available for this slot." << endl;
    }
    return true;
}

void create_booking() {
    cout << "\n===== Create Booking =====" << endl;
    bool completed = display_timetable();
    if (completed) {
        cout << "\nPress Enter to return to main menu...";
        cin.ignore(1000, '\n');
        cin.get();
    }
}

void modify_booking() {
    cout << "\n===== Modify Booking =====" << endl;
    int target_id;
    cout << "Enter your User ID: ";
    if (!(cin >> target_id)) {
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    int user_matches[MAX_BOOKINGS];
    int match_count = 0;

    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].active && bookings[i].userId == target_id) {
            user_matches[match_count] = i;
            match_count++;
        }
    }

    if (match_count == 0) {
        cout << "\n[!] No active bookings found for User ID " << target_id << "!\n";
        cout << "\nPress Enter to return to main menu...";
        cin.ignore(1000, '\n');
        cin.get();
        return;
    }

    cout << "\n---------------- ACTIVE BOOKINGS FOR USER " << target_id << " ----------------\n";
    for (int i = 0; i < match_count; i++) {
        int idx = user_matches[i];
        cout << " " << (i + 1) << ". Date: " << left << setw(15) << dateSlot[bookings[idx].dateIdx]
            << " | Time: " << setw(22) << timeSlot[bookings[idx].timeIdx]
            << " | Name: " << bookings[idx].name << endl;
    }
    cout << "----------------------------------------------------------------\n";

    int choice;
    cout << "\nSelect booking to cancel (1-" << match_count << ", or 0 to exit): ";
    cin >> choice;

    if (choice <= 0 || choice > match_count) {
        cout << "\nModification canceled." << endl;
        cin.ignore(1000, '\n');
        cin.get();
        return;
    }

    int cancel_idx = user_matches[choice - 1];
    bookings[cancel_idx].active = false;

    add_to_history(bookings[cancel_idx].userId, bookings[cancel_idx].name,
        dateSlot[bookings[cancel_idx].dateIdx], timeSlot[bookings[cancel_idx].timeIdx], "CANCELLED");
    save_all_data();

    cout << "\n[+] Previous booking canceled successfully!" << endl;

    cout << "\n--- Select Your New Booking Slot ---" << endl;
    bool completed = display_timetable();

    if (completed) {
        cout << "\nPress Enter to return to main menu...";
        cin.ignore(1000, '\n');
        cin.get();
    }
}

void search_booking() {
    cout << "\n========================================\n";
    cout << "             SEARCH BOOKINGS            \n";
    cout << "========================================\n";
    cout << "1. Search by Date & Time Slot\n";
    cout << "2. Search by User ID\n";
    cout << "0. Back to Main Menu\n";
    cout << "Choice: ";

    int mode;
    cin >> mode;

    if (mode == 1) {
        int d, t;
        cout << "\nEnter Date number (1-7): ";
        cin >> d;
        cout << "Enter Time Slot (1-6): ";
        cin >> t;
        d--; t--;

        if (d >= 0 && d < TOTAL_DATES && t >= 0 && t < TOTAL_TIMES) {
            cout << "\nBookings for: " << dateSlot[d] << " [" << timeSlot[t] << "]\n";
            int found = 0;
            for (int i = 0; i < booking_count; i++) {
                if (bookings[i].active && bookings[i].dateIdx == d && bookings[i].timeIdx == t) {
                    found++;
                    cout << " " << found << ". Name: " << bookings[i].name << " | User ID: " << bookings[i].userId << endl;
                }
            }
            if (found == 0) cout << " (No bookings found)\n";
        }
    }
    else if (mode == 2) {
        int target_id;
        cout << "\nEnter User ID to search: ";
        cin >> target_id;

        bool found = false;
        int count = 1;
        for (int i = 0; i < booking_count; i++) {
            if (bookings[i].active && bookings[i].userId == target_id) {
                cout << " " << count++ << ". Date: " << dateSlot[bookings[i].dateIdx]
                    << " | Slot: " << timeSlot[bookings[i].timeIdx]
                    << " | Name: " << bookings[i].name << endl;
                found = true;
            }
        }
        if (!found) cout << " No active bookings found for User ID " << target_id << endl;
    }

    cin.ignore(1000, '\n');
    cout << "\nPress Enter to return to menu...";
    cin.get();
}

void display_booking_summary() {
    int target_id;
    cout << "\nEnter User ID to view summary: ";
    cin >> target_id;

    int active_count = 0;
    int cancelled_count = 0;
    char userName[50] = "Unknown User";
    bool foundUser = false;

    for (int i = 0; i < history_count; i++) {
        if (history_log[i].userId == target_id) {
            if (!foundUser) {
                strcpy(userName, history_log[i].name);
                foundUser = true;
            }
            if (strcmp(history_log[i].status, "ACTIVE") == 0) active_count++;
            else if (strcmp(history_log[i].status, "CANCELLED") == 0) cancelled_count++;
        }
    }

    cout << "\n=========================================================\n";
    cout << " BOOKING SUMMARY FOR USER ID: " << target_id << "\n";
    if (foundUser) cout << " User Name: " << userName << "\n";
    cout << "=========================================================\n";
    cout << " Total Active Bookings   : " << active_count << "\n";
    cout << " Total Cancelled Bookings: " << cancelled_count << "\n";
    cout << " Total Booking Activity  : " << (active_count + cancelled_count) << "\n";
    cout << "=========================================================\n";

    if (foundUser) {
        cout << left << setw(16) << "DATE" << setw(24) << "TIME SLOT" << setw(12) << "STATUS" << endl;
        cout << "---------------------------------------------------------\n";
        for (int i = 0; i < history_count; i++) {
            if (history_log[i].userId == target_id) {
                cout << left << setw(16) << history_log[i].date
                    << setw(24) << history_log[i].timeSlot
                    << setw(12) << history_log[i].status << endl;
            }
        }
    }

    cin.ignore(1000, '\n');
    cout << "\nPress Enter to return to menu...";
    cin.get();
}

int main() {
    load_all_data();

    int choose = -1;

    while (choose != 0) {
        cout << "\n========================================" << endl;
        cout << "       TRANSACTION & BOOKING MENU       " << endl;
        cout << "========================================" << endl;
        cout << "          1.Create Transaction          " << endl;
        cout << "          2.Modify Transaction          " << endl;
        cout << "          3.List Transaction            " << endl;
        cout << "          4.Create Booking              " << endl;
        cout << "          5.Modify Booking              " << endl;
        cout << "          6.Search Booking              " << endl;
        cout << "          7.Display Booking Summary     " << endl;
        cout << "          0.Exit                        " << endl;
        cout << "========================================" << endl;
        cout << "Select a function: ";

        if (!(cin >> choose)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choose) {
        case 1: create_transaction(); break;
        case 2: modify_transaction(); break;
        case 3: list_transaction(); break;
        case 4: create_booking(); break;
        case 5: modify_booking(); break;
        case 6: search_booking(); break;
        case 7: display_booking_summary(); break;
        case 0: save_all_data(); break;
        default: cout << "Invalid choice." << endl; break;
        }
    }
    return 0;
}
