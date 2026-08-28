// ============================================================
//  GYM MANAGEMENT SYSTEM - FULL COMBINED BUILD (FIXED)
// ============================================================
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cctype>
using namespace std;

// ============================================================
//  MEMBER MODULE - constants & struct
// ============================================================
const int MAX_MEMBERS = 50;

struct Member {
    int id;
    string name;
    string password;
    string paymentMethod;
    string trainer;
    string personalmembership;
    string coachmembership;
};

// ============================================================
//  BOOKING / TRANSACTION MODULE - constants & structs
// ============================================================
const int TOTAL_DATES = 7;
const int TOTAL_TIMES = 6;
const int MAX_SEATS_PER_SLOT = 10;
const int MAX_BOOKINGS = 100;
const int MAX_HISTORY = 100;
const int MAX_TRANSACTIONS = 100;

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
    int userId;
    char methodType[20];
    char cardHolderName[50];
    char cardNumber[20];
    char expiryDate[10];
};

// Global Arrays
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

// Helper Function Prototypes
bool is_only_digits(const char str[]);
int get_available_places(int d, int t);
void add_to_history(int userId, const char name[], const char date[], const char slot[], const char status[]);
void save_all_data();
void load_all_data();
string getPaymentMethodForUser(int userId, const string& currentMethod);
bool hasPaymentMethod(int userId, const string& currentMethod);
void create_transaction_for_user(Member& member);
void displayUserBanner(const Member& member);

// Core Function Prototypes
void Member_subscription(Member members[], int customermembership, int count);
void display_services(Member members[], int customermembership, int count);
void customer_membership(Member members[], int customermembership, int count);
void add_service(Member members[], int customermembership, int count);
void upgrade_service(Member members[], int customermembership, int count);
void renew_service(Member members[], int customermembership, int count);
void personal(Member members[], int customermembership, int count);
void coach(Member members[], int customermembership, int count);
void saveAllMembersToFile(const Member members[], int count);
void removeservice(Member members[], int customermembership, int count);
void signUpMember(Member members[], int& count);
void updateMember(Member members[], int count);
void deleteMember(Member members[], int* count);
void searchMember(Member members[], int count);
void displayMembers(Member members[], int count);

void create_transaction(const Member& currentMember);
void modify_transaction(const Member& currentMember);
void list_transaction(const Member& currentMember);
bool display_timetable(const Member& currentMember);
void create_booking(const Member& currentMember);
void modify_booking(const Member& currentMember);
void search_booking(const Member& currentMember);
void display_booking_summary(const Member& currentMember);
void trainerSchedulingMenu(const Member& currentMember);

void reportingModule(const Member members[], int memberCount);
void generateSummaryReport(const Member members[], int memberCount);
void generateDetailedReport(const Member members[], int memberCount);
void calculateStatistics(const Member members[], int memberCount);
void sortRecords(const Member members[], int memberCount);
void displayAnalysis(const Member members[], int memberCount);
double calculateMemberFee(const Member& m);
double calculateTotalGymEarnings(const Member members[], int memberCount);
int getValidChoiceStudentD(int min, int max);

// ============================================================
//  BANNER HELPER
// ============================================================
void displayUserBanner(const Member& member) {
    cout << "==================================================================================\n";
    cout << " LOGGED IN MEMBER : " << member.name << " (ID: " << member.id << ")\n";
    cout << " Personal Sub     : " << (member.personalmembership.empty() ? "None" : member.personalmembership) << "\n";
    cout << " Coach Sub        : " << (member.coachmembership.empty() ? "None" : member.coachmembership) << "\n";
    cout << "==================================================================================\n\n";
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    Member members[MAX_MEMBERS];
    int memberCount = 0;
    int portalChoice;

    load_all_data();

    fstream customer;
    customer.open("customer.txt", fstream::in);
    if (customer.is_open()) {
        while (memberCount < MAX_MEMBERS && customer >> members[memberCount].id) {
            customer.ignore(1000, '\n');
            getline(customer, members[memberCount].name);
            getline(customer, members[memberCount].password);
            getline(customer, members[memberCount].personalmembership);
            getline(customer, members[memberCount].coachmembership);
            members[memberCount].trainer = "Not yet picked";
            members[memberCount].paymentMethod = getPaymentMethodForUser(members[memberCount].id, "Not yet picked");
            memberCount++;
        }
        customer.close();
    }

    srand(static_cast<unsigned int>(time(NULL)));

    do {
        system("cls");
        cout << "===================================\n";
        cout << "      GYM SYSTEM ACCESS PORTAL     \n";
        cout << "===================================\n";
        cout << "1. Sign Up (Register)\n";
        cout << "2. Log In\n";
        cout << "3. Exit Program\n";
        cout << "Choice (1-3): ";
        cin >> portalChoice;

        while (cin.fail() || portalChoice < 1 || portalChoice > 3) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice! Enter 1-3: ";
            cin >> portalChoice;
        }
        cin.ignore(1000, '\n');

        if (portalChoice == 1) {
            system("cls");
            signUpMember(members, memberCount);
            cout << "\nPress Enter to return to portal...";
            cin.get();
        }
        else if (portalChoice == 2) {
            system("cls");
            string usernameLI, passwordLI;
            cout << "==== Log In =====" << endl;
            cout << "Username: ";
            getline(cin, usernameLI);

            int userIndex = -1;
            for (int i = 0; i < memberCount; i++) {
                if (members[i].name == usernameLI) {
                    userIndex = i;
                    break;
                }
            }

            if (userIndex == -1) {
                cout << "Username not found! Log in failed.\n";
                cout << "\nPress Enter to return...";
                cin.get();
                continue;
            }

            cout << "Password: ";
            cin >> passwordLI;
            cin.ignore(1000, '\n');

            if (members[userIndex].password != passwordLI) {
                cout << "Incorrect password! Log in failed.\n";
                cout << "\nPress Enter to return...";
                cin.get();
                continue;
            }

            int loggedInID = members[userIndex].id;
            int systemChoice;

            do {
                system("cls");
                displayUserBanner(members[userIndex]);
                cout << "===================================\n";
                cout << "        GYM MEMBERSHIP SYSTEM       \n";
                cout << "===================================\n";
                cout << "1. Member Management (Sub-Menu)\n";
                cout << "2. Member Subscription\n";
                cout << "3. Trainer Scheduling & Payments\n";
                cout << "4. Reporting Module\n";
                cout << "5. Log Out\n";
                cout << "Choice (1-5): ";
                cin >> systemChoice;

                while (cin.fail() || systemChoice < 1 || systemChoice > 5) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid choice! Enter 1-5: ";
                    cin >> systemChoice;
                }

                if (systemChoice == 1) {
                    int subChoice;
                    do {
                        system("cls");
                        displayUserBanner(members[userIndex]);
                        cout << "--- Member Management Sub-Menu ---\n";
                        cout << "1. Update Member Details\n";
                        cout << "2. Delete Member Account\n";
                        cout << "3. Search Member Record\n";
                        cout << "4. Display All Registered Members\n";
                        cout << "5. Back\n";
                        cout << "Choice (1-5): ";
                        cin >> subChoice;

                        while (cin.fail() || subChoice < 1 || subChoice > 5) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid choice! Enter 1-5: ";
                            cin >> subChoice;
                        }

                        if (subChoice == 1) {
                            system("cls");
                            displayUserBanner(members[userIndex]);
                            updateMember(members, memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(1000, '\n'); cin.get();
                        }
                        else if (subChoice == 2) {
                            system("cls");
                            displayUserBanner(members[userIndex]);
                            deleteMember(members, &memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(1000, '\n'); cin.get();
                        }
                        else if (subChoice == 3) {
                            system("cls");
                            displayUserBanner(members[userIndex]);
                            searchMember(members, memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(1000, '\n'); cin.get();
                        }
                        else if (subChoice == 4) {
                            system("cls");
                            displayUserBanner(members[userIndex]);
                            displayMembers(members, memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(1000, '\n'); cin.get();
                        }
                    } while (subChoice != 5);

                    int newIndex = -1;
                    for (int i = 0; i < memberCount; i++) {
                        if (members[i].id == loggedInID) {
                            newIndex = i;
                            break;
                        }
                    }
                    if (newIndex == -1) {
                        cout << "Your account no longer exists. Logging out...\n";
                        cin.ignore(1000, '\n'); cin.get();
                        break;
                    }
                    userIndex = newIndex;
                }
                else if (systemChoice == 2) {
                    Member_subscription(members, userIndex, memberCount);
                }
                else if (systemChoice == 3) {
                    system("cls");
                    trainerSchedulingMenu(members[userIndex]);
                }
                else if (systemChoice == 4) {
                    system("cls");
                    reportingModule(members, memberCount);
                }
            } while (systemChoice != 5);
        }
    } while (portalChoice != 3);

    system("cls");
    cout << "Program exited successfully.\n";
    return 0;
}

// ============================================================
//  TRAINER SCHEDULING MENU
// ============================================================
void trainerSchedulingMenu(const Member& currentMember) {
    int choose;
    do {
        system("cls");
        displayUserBanner(currentMember);
        cout << "========================================" << endl;
        cout << "       TRAINER SCHEDULING & PAYMENTS     " << endl;
        cout << "========================================" << endl;
        cout << "          1.Create Transaction          " << endl;
        cout << "          2.Modify Transaction          " << endl;
        cout << "          3.List Transaction            " << endl;
        cout << "          4.Create Booking              " << endl;
        cout << "          5.Modify Booking              " << endl;
        cout << "          6.Search Booking              " << endl;
        cout << "          7.Display Booking Summary     " << endl;
        cout << "          0.Back to Main Menu           " << endl;
        cout << "========================================" << endl;
        cout << "Select a function: ";

        cin >> choose;

        while (cin.fail() || choose < 0 || choose > 7) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice! Enter 0-7: ";
            cin >> choose;
        }
        cin.ignore(1000, '\n');

        switch (choose) {
        case 1: create_transaction(currentMember); break;
        case 2: modify_transaction(currentMember); break;
        case 3: list_transaction(currentMember); break;
        case 4: create_booking(currentMember); break;
        case 5: modify_booking(currentMember); break;
        case 6: search_booking(currentMember); break;
        case 7: display_booking_summary(currentMember); break;
        case 0: save_all_data(); break;
        }
    } while (choose != 0);
}

// ============================================================
//  PAYMENT TRANSACTION FUNCTIONS (NO USER ID PROMPT REQUIRED)
// ============================================================
void create_transaction(const Member& currentMember) {
    system("cls");
    displayUserBanner(currentMember);
    cout << "===== CREATE PAYMENT TRANSACTION =====" << endl;

    int method;
    cout << "---------------------------------------" << endl;
    cout << "|     1. Credit Cards                   |" << endl;
    cout << "|     2. Debit Cards                    |" << endl;
    cout << "|     0. Exit Menu                      |" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Choose payment method: ";
    cin >> method;

    while (cin.fail() || (method != 0 && method != 1 && method != 2)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice! Enter 0, 1, or 2: ";
        cin >> method;
    }

    if (method == 0) return;

    TransactionRecord tx;
    tx.txId = transaction_count + 1001;
    tx.userId = currentMember.id; // Automatically linked to logged-in user!
    strcpy(tx.methodType, (method == 1) ? "Credit Card" : "Debit Card");

    cin.ignore(1000, '\n');
    cout << "Enter Cardholder Name: ";
    cin.getline(tx.cardHolderName, 50);

    bool validCard = false;
    do {
        cout << "Enter Card Number (12 to 16 digits only): ";
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
        cout << "\n[+] Transaction recorded successfully for " << currentMember.name << " (ID: " << currentMember.id << ")!" << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.get();
}

void modify_transaction(const Member& currentMember) {
    system("cls");
    displayUserBanner(currentMember);
    cout << "===== Modify Transaction =====" << endl;

    int user_matches[MAX_TRANSACTIONS];
    int match_count = 0;
    for (int i = 0; i < transaction_count; i++) {
        if (transaction_log[i].userId == currentMember.id) {
            user_matches[match_count] = i;
            match_count++;
        }
    }

    if (match_count == 0) {
        cout << "\n[!] No transactions found for your account (ID " << currentMember.id << ")!\n";
        cout << "\nPress Enter to return to main menu...";
        cin.get();
        return;
    }

    cout << "\n---------------- YOUR TRANSACTIONS (ID: " << currentMember.id << ") ----------------\n";
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
        cout << "Enter new Card Number (12 to 16 digits only): ";
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
        cout << "Enter new Expiry Date MM/YY (e.g., 12/26): ";
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

void list_transaction(const Member& currentMember) {
    system("cls");
    displayUserBanner(currentMember);
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

bool display_timetable(const Member& currentMember) {
    cout << "\n------- SELECT DATE -------" << endl;
    for (int i = 0; i < TOTAL_DATES; i++) {
        cout << (i + 1) << ". " << dateSlot[i] << endl;
    }
    int dateChoice;
    cout << "\nChoose date (1-7, or 0 to exit): ";
    cin >> dateChoice;

    if (cin.fail() || dateChoice <= 0 || dateChoice > TOTAL_DATES) {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
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

    if (cin.fail() || timeChoice <= 0 || timeChoice > TOTAL_TIMES) {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    int t = timeChoice - 1;

    if (get_available_places(d, t) > 0) {
        if (booking_count < MAX_BOOKINGS) {
            bookings[booking_count].userId = currentMember.id;
            strcpy(bookings[booking_count].name, currentMember.name.c_str());
            bookings[booking_count].dateIdx = d;
            bookings[booking_count].timeIdx = t;
            bookings[booking_count].active = true;
            booking_count++;

            add_to_history(currentMember.id, currentMember.name.c_str(), dateSlot[d], timeSlot[t], "ACTIVE");
            save_all_data();
            cout << "\n[+] Booking confirmed for " << currentMember.name << " (ID: " << currentMember.id << ") on "
                << dateSlot[d] << " at " << timeSlot[t] << endl;
        }
    }
    else {
        cout << "\n[!] Fully Booked! No places available for this slot." << endl;
    }
    cin.ignore(1000, '\n');
    return true;
}

void create_booking(const Member& currentMember) {
    system("cls");
    displayUserBanner(currentMember);
    cout << "===== Create Booking =====" << endl;
    bool completed = display_timetable(currentMember);
    if (completed) {
        cout << "\nPress Enter to return to main menu...";
        cin.get();
    }
}

void modify_booking(const Member& currentMember) {
    system("cls");
    displayUserBanner(currentMember);
    cout << "===== Modify Booking =====" << endl;

    int user_matches[MAX_BOOKINGS];
    int match_count = 0;
    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].active && bookings[i].userId == currentMember.id) {
            user_matches[match_count] = i;
            match_count++;
        }
    }

    if (match_count == 0) {
        cout << "\n[!] No active bookings found for your account (ID " << currentMember.id << ")!\n";
        cout << "\nPress Enter to return to main menu...";
        cin.ignore(1000, '\n');
        cin.get();
        return;
    }

    cout << "\n---------------- YOUR ACTIVE BOOKINGS ----------------\n";
    for (int i = 0; i < match_count; i++) {
        int idx = user_matches[i];
        cout << " " << (i + 1) << ". Date: " << left << setw(15) << dateSlot[bookings[idx].dateIdx]
            << " | Time: " << setw(22) << timeSlot[bookings[idx].timeIdx]
            << " | Name: " << bookings[idx].name << endl;
    }
    cout << "------------------------------------------------------\n";

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
    bool completed = display_timetable(currentMember);
    if (completed) {
        cout << "\nPress Enter to return to main menu...";
        cin.get();
    }
}

void search_booking(const Member& currentMember) {
    system("cls");
    displayUserBanner(currentMember);
    cout << "========================================\n";
    cout << "             SEARCH BOOKINGS            \n";
    cout << "========================================\n";
    cout << "1. Search by Date & Time Slot\n";
    cout << "2. View My Active Bookings\n";
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
        bool found = false;
        int count = 1;
        cout << "\nActive bookings for " << currentMember.name << " (ID: " << currentMember.id << "):\n";
        for (int i = 0; i < booking_count; i++) {
            if (bookings[i].active && bookings[i].userId == currentMember.id) {
                cout << " " << count++ << ". Date: " << dateSlot[bookings[i].dateIdx]
                    << " | Slot: " << timeSlot[bookings[i].timeIdx] << endl;
                found = true;
            }
        }
        if (!found) cout << " No active bookings found.\n";
    }
    cin.ignore(1000, '\n');
    cout << "\nPress Enter to return to menu...";
    cin.get();
}

void display_booking_summary(const Member& currentMember) {
    system("cls");
    displayUserBanner(currentMember);
    int target_id = currentMember.id;

    int active_count = 0;
    int cancelled_count = 0;

    for (int i = 0; i < history_count; i++) {
        if (history_log[i].userId == target_id) {
            if (strcmp(history_log[i].status, "ACTIVE") == 0) active_count++;
            else if (strcmp(history_log[i].status, "CANCELLED") == 0) cancelled_count++;
        }
    }

    cout << "=========================================================\n";
    cout << " BOOKING SUMMARY FOR: " << currentMember.name << " (ID: " << target_id << ")\n";
    cout << "=========================================================\n";
    cout << " Total Active Bookings   : " << active_count << "\n";
    cout << " Total Cancelled Bookings: " << cancelled_count << "\n";
    cout << " Total Booking Activity  : " << (active_count + cancelled_count) << "\n";
    cout << "=========================================================\n";

    cout << left << setw(16) << "DATE" << setw(24) << "TIME SLOT" << setw(12) << "STATUS" << endl;
    cout << "---------------------------------------------------------\n";
    for (int i = 0; i < history_count; i++) {
        if (history_log[i].userId == target_id) {
            cout << left << setw(16) << history_log[i].date
                << setw(24) << history_log[i].timeSlot
                << setw(12) << history_log[i].status << endl;
        }
    }
    cin.ignore(1000, '\n');
    cout << "\nPress Enter to return to menu...";
    cin.get();
}

// ============================================================
//  PAYMENT UTILITY HELPERS
// ============================================================
string getPaymentMethodForUser(int userId, const string& currentMethod) {
    if (currentMethod != "Not yet picked" && !currentMethod.empty()) {
        return currentMethod;
    }
    for (int i = 0; i < transaction_count; i++) {
        if (transaction_log[i].userId == userId) {
            return string(transaction_log[i].methodType);
        }
    }
    return "Not yet picked";
}

bool hasPaymentMethod(int userId, const string& currentMethod) {
    string method = getPaymentMethodForUser(userId, currentMethod);
    return (method != "Not yet picked" && !method.empty());
}

void create_transaction_for_user(Member& member) {
    cout << "\n==================================================" << endl;
    cout << "       NO PAYMENT METHOD FOUND FOR MEMBER         " << endl;
    cout << "    Please enter payment details to continue      " << endl;
    cout << "==================================================" << endl;
    cout << "1. Credit Card" << endl;
    cout << "2. Debit Card" << endl;
    cout << "Select method (1-2): ";

    int method;
    cin >> method;
    while (cin.fail() || (method != 1 && method != 2)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice! Enter 1 or 2: ";
        cin >> method;
    }
    cin.ignore(1000, '\n');

    TransactionRecord tx;
    tx.txId = transaction_count + 1001;
    tx.userId = member.id;
    strcpy(tx.methodType, (method == 1) ? "Credit Card" : "Debit Card");

    cout << "Enter Cardholder Name: ";
    cin.getline(tx.cardHolderName, 50);

    bool validCard = false;
    do {
        cout << "Enter Card Number (12 to 16 digits only): ";
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
        cout << "Enter Expiry Date MM/YY (e.g., 12/26): ";
        cin.getline(tx.expiryDate, 10);
        int expLen = (int)strlen(tx.expiryDate);
        if (expLen != 5 || tx.expiryDate[2] != '/') {
            cout << "[!] Invalid format! Must be MM/YY (e.g., 12/26).\n\n";
        }
    } while ((int)strlen(tx.expiryDate) != 5 || tx.expiryDate[2] != '/');

    if (transaction_count < MAX_TRANSACTIONS) {
        transaction_log[transaction_count] = tx;
        transaction_count++;
        member.paymentMethod = tx.methodType;
        save_all_data();
        cout << "\n[+] Payment transaction created successfully!" << endl;
    }
}

// ============================================================
//  MEMBER MODULE IMPLEMENTATION
// ============================================================
void signUpMember(Member members[], int& count) {
    if (count >= MAX_MEMBERS) {
        cout << "Database is full! Cannot register more members.\n";
        return;
    }

    string username, password;
    cout << "==== Sign Up ====\n";
    cout << "Enter username: ";
    getline(cin, username);

    for (int i = 0; i < count; i++) {
        if (members[i].name == username) {
            cout << "Username already taken! Try another one.\n";
            return;
        }
    }

    cout << "Enter password: ";
    cin >> members[count].password;
    cin.ignore(1000, '\n');

    password = members[count].password;

    int randomID, idExists;
    do {
        randomID = rand() % 9000 + 1000;
        idExists = 0;
        for (int i = 0; i < count; i++) {
            if (members[i].id == randomID) {
                idExists = 1;
                break;
            }
        }
    } while (idExists == 1);

    members[count].id = randomID;
    members[count].name = username;
    members[count].paymentMethod = "Not yet picked";
    members[count].trainer = "Not yet picked";
    members[count].personalmembership = "None";
    members[count].coachmembership = "None";

    ofstream customer("customer.txt", ios::app);
    if (customer.is_open()) {
        customer << randomID << endl;
        customer << username << endl;
        customer << password << endl;
        customer << members[count].personalmembership << endl;
        customer << members[count].coachmembership << endl;
        customer.close();
    }

    cout << "\n==================================================\n";
    cout << "            REGISTRATION SUCCESSFUL!              \n";
    cout << "==================================================\n";
    cout << "  Welcome to the gym, " << username << "!\n";
    cout << "  Your auto-generated 4-Digit Member ID is: " << randomID << "\n";
    cout << "==================================================\n";

    count++;
}

void updateMember(Member members[], int count) {
    int searchID, foundIndex = -1;
    cout << "Enter Member ID to update: ";
    cin >> searchID;

    for (int i = 0; i < count; i++) {
        if (members[i].id == searchID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        cin.ignore(1000, '\n');
        cout << "Enter New Username: ";
        getline(cin, members[foundIndex].name);
        cout << "Enter New Password: ";
        cin >> members[foundIndex].password;
        cout << "Member details updated successfully!\n";
        saveAllMembersToFile(members, count);
    }
    else {
        cout << "Member ID not found.\n";
    }
}

void deleteMember(Member members[], int* count) {
    int searchID, foundIndex = -1;
    cout << "Enter Member ID to delete: ";
    cin >> searchID;

    for (int i = 0; i < *count; i++) {
        if (members[i].id == searchID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < (*count) - 1; i++) {
            members[i] = members[i + 1];
        }
        (*count)--;
        cout << "Member record deleted successfully.\n";
        saveAllMembersToFile(members, *count);
    }
    else {
        cout << "Member ID not found.\n";
    }
}

void searchMember(Member members[], int count) {
    int searchID;
    cout << "Enter Member ID to search: ";
    cin >> searchID;

    for (int i = 0; i < count; i++) {
        if (members[i].id == searchID) {
            string pm = getPaymentMethodForUser(members[i].id, members[i].paymentMethod);
            members[i].paymentMethod = pm;
            cout << "\n--- Member Found ---\n";
            cout << "ID:                  " << members[i].id << "\n";
            cout << "Name:                " << members[i].name << "\n";
            cout << "Payment Method:      " << members[i].paymentMethod << "\n";
            cout << "Personal membership: " << members[i].personalmembership << "\n";
            cout << "Coach membership:    " << members[i].coachmembership << "\n";
            return;
        }
    }
    cout << "Member ID not found.\n";
}

void displayMembers(Member members[], int count) {
    if (count == 0) {
        cout << "No registered members yet.\n";
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (members[j].id > members[j + 1].id) {
                Member temp = members[j];
                members[j] = members[j + 1];
                members[j + 1] = temp;
            }
        }
    }

    cout << "====================================================================================================\n";
    cout << "                                  REGISTERED GYM MEMBERS LIST                                       \n";
    cout << "====================================================================================================\n";
    cout << left << setw(8) << "ID"
        << setw(16) << "NAME"
        << setw(20) << "PAYMENT METHOD"
        << setw(25) << "PERSONAL SUBSCRIPTION"
        << setw(25) << "COACH SUBSCRIPTION" << endl;
    cout << "----------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        string pm = getPaymentMethodForUser(members[i].id, members[i].paymentMethod);
        members[i].paymentMethod = pm;

        cout << left << setw(8) << members[i].id
            << setw(16) << members[i].name
            << setw(20) << members[i].paymentMethod
            << setw(25) << (members[i].personalmembership.empty() ? "None" : members[i].personalmembership)
            << setw(25) << (members[i].coachmembership.empty() ? "None" : members[i].coachmembership) << endl;
    }
    cout << "====================================================================================================\n";
}

void Member_subscription(Member members[], int customermembership, int count) {
    system("cls");
    display_services(members, customermembership, count);
}

void saveAllMembersToFile(const Member members[], int count) {
    ofstream customer("customer.txt", ios::trunc);
    if (customer.is_open()) {
        for (int i = 0; i < count; i++) {
            customer << members[i].id << endl;
            customer << members[i].name << endl;
            customer << members[i].password << endl;
            customer << members[i].personalmembership << endl;
            customer << members[i].coachmembership << endl;
        }
        customer.close();
    }
}

void display_services(Member members[], int customermembership, int count) {
    int choice;
    do {
        system("cls");
        displayUserBanner(members[customermembership]);
        cout << "Gym Membership Services" << endl;
        cout << "Please select a service" << endl;
        cout << "1. Add Service" << endl;
        cout << "2. Remove Service" << endl;
        cout << "3. Upgrade Service" << endl;
        cout << "4. Renew Service" << endl;
        cout << "5. Display all services you own" << endl;
        cout << "6. Back" << endl;
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            displayUserBanner(members[customermembership]);
            add_service(members, customermembership, count);
        }
        else if (choice == 2) {
            system("cls");
            displayUserBanner(members[customermembership]);
            removeservice(members, customermembership, count);
        }
        else if (choice == 3) {
            system("cls");
            displayUserBanner(members[customermembership]);
            upgrade_service(members, customermembership, count);
        }
        else if (choice == 4) {
            system("cls");
            displayUserBanner(members[customermembership]);
            renew_service(members, customermembership, count);
        }
        else if (choice == 5) {
            system("cls");
            displayUserBanner(members[customermembership]);
            customer_membership(members, customermembership, count);
        }
        else if (choice == 6) {
            return;
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while (choice != 6);
}

void add_service(Member members[], int customermembership, int count) {
    cout << "You have selected to add a new service." << endl;
    int addservicechoice;
    cout << "Please select the type of service you would like to add:" << endl;
    cout << "1. Personal Training" << endl;
    cout << "2. Coach Training" << endl;
    cout << "Your choice: ";
    cin >> addservicechoice;

    while (cin.fail() || addservicechoice < 1 || addservicechoice > 2) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice! Enter 1-2: ";
        cin >> addservicechoice;
    }

    switch (addservicechoice) {
    case 1:
        system("cls");
        displayUserBanner(members[customermembership]);
        personal(members, customermembership, count);
        break;
    case 2:
        system("cls");
        displayUserBanner(members[customermembership]);
        coach(members, customermembership, count);
        break;
    }
}

void personal(Member members[], int customermembership, int count) {
    int afteraddservice;
    cout << "You have selected to add Personal Training." << endl;
    cout << "Please choose your interested membership: " << endl;
    cout << "1. Monthly membership: RM50/month" << endl;
    cout << "2. Yearly membership: RM500/year" << endl;
    cout << "3. Life time membership: RM2000" << endl;
    cout << "Your choice: ";
    cin >> afteraddservice;

    while (cin.fail() || afteraddservice < 1 || afteraddservice > 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice! Enter 1-3: ";
        cin >> afteraddservice;
    }

    double price = 0.0;
    string selectedPlan = "";

    if (afteraddservice == 1) { selectedPlan = "Monthly membership"; price = 50.0; }
    else if (afteraddservice == 2) { selectedPlan = "Yearly membership"; price = 500.0; }
    else if (afteraddservice == 3) { selectedPlan = "Life time membership"; price = 2000.0; }

    if (!hasPaymentMethod(members[customermembership].id, members[customermembership].paymentMethod)) {
        cout << "\n[!] Member has no registered payment method." << endl;
        cout << "Redirecting to create payment transaction now...\n";
        create_transaction_for_user(members[customermembership]);
    }
    else {
        members[customermembership].paymentMethod = getPaymentMethodForUser(members[customermembership].id, members[customermembership].paymentMethod);
    }

    members[customermembership].personalmembership = selectedPlan;
    saveAllMembersToFile(members, count);

    double memberRevenue = calculateMemberFee(members[customermembership]);
    double overallGymEarnings = calculateTotalGymEarnings(members, count);

    cout << "\n==================================================" << endl;
    cout << "          TRANSACTION & EARNINGS RECEIPT          " << endl;
    cout << "==================================================" << endl;
    cout << " Member ID            : " << members[customermembership].id << endl;
    cout << " Member Name          : " << members[customermembership].name << endl;
    cout << " Added Plan           : Personal Training (" << selectedPlan << ")" << endl;
    cout << " Payment Method       : " << members[customermembership].paymentMethod << endl;
    cout << " Amount Paid          : RM " << fixed << setprecision(2) << price << endl;
    cout << "--------------------------------------------------" << endl;
    cout << " Member Total Revenue : RM " << memberRevenue << endl;
    cout << " Total Gym Earnings   : RM " << overallGymEarnings << endl;
    cout << "==================================================" << endl;
    cout << "Service added successfully! Press Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

void coach(Member members[], int customermembership, int count) {
    int afteraddservice_coach;
    cout << "You have selected to add Coach Training." << endl;
    cout << "Please choose your interested membership: " << endl;
    cout << "1. Monthly coach membership: RM80/month" << endl;
    cout << "2. Yearly coach membership: RM800/year" << endl;
    cout << "3. Life time coach membership: RM3500" << endl;
    cout << "Your choice: ";
    cin >> afteraddservice_coach;

    while (cin.fail() || afteraddservice_coach < 1 || afteraddservice_coach > 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice! Enter 1-3: ";
        cin >> afteraddservice_coach;
    }

    double price = 0.0;
    string selectedPlan = "";

    if (afteraddservice_coach == 1) { selectedPlan = "Monthly coach membership"; price = 80.0; }
    else if (afteraddservice_coach == 2) { selectedPlan = "Yearly coach membership"; price = 800.0; }
    else if (afteraddservice_coach == 3) { selectedPlan = "Life time coach membership"; price = 3500.0; }

    if (!hasPaymentMethod(members[customermembership].id, members[customermembership].paymentMethod)) {
        cout << "\n[!] Member has no registered payment method." << endl;
        cout << "Redirecting to create payment transaction now...\n";
        create_transaction_for_user(members[customermembership]);
    }
    else {
        members[customermembership].paymentMethod = getPaymentMethodForUser(members[customermembership].id, members[customermembership].paymentMethod);
    }

    members[customermembership].coachmembership = selectedPlan;
    saveAllMembersToFile(members, count);

    double memberRevenue = calculateMemberFee(members[customermembership]);
    double overallGymEarnings = calculateTotalGymEarnings(members, count);

    cout << "\n==================================================" << endl;
    cout << "          TRANSACTION & EARNINGS RECEIPT          " << endl;
    cout << "==================================================" << endl;
    cout << " Member ID            : " << members[customermembership].id << endl;
    cout << " Member Name          : " << members[customermembership].name << endl;
    cout << " Added Plan           : Coach Training (" << selectedPlan << ")" << endl;
    cout << " Payment Method       : " << members[customermembership].paymentMethod << endl;
    cout << " Amount Paid          : RM " << fixed << setprecision(2) << price << endl;
    cout << "--------------------------------------------------" << endl;
    cout << " Member Total Revenue : RM " << memberRevenue << endl;
    cout << " Total Gym Earnings   : RM " << overallGymEarnings << endl;
    cout << "==================================================" << endl;
    cout << "Service added successfully! Press Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

void removeservice(Member members[], int customermembership, int count) {
    cout << "Please select the Membership you want to remove;" << endl;
    cout << "1.Personal  Membership: " << members[customermembership].personalmembership << endl;
    cout << "2.Coach     Membership: " << members[customermembership].coachmembership << endl;
    cout << "3.Return" << endl;
    cout << "Your choice: ";

    int removemembership;
    cin >> removemembership;

    while (cin.fail() || removemembership < 1 || removemembership > 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice! Enter 1-3: ";
        cin >> removemembership;
    }

    if (removemembership == 1) {
        members[customermembership].personalmembership = "None";
    }
    else if (removemembership == 2) {
        members[customermembership].coachmembership = "None";
    }
    else return;

    saveAllMembersToFile(members, count);
    cout << "Membership updated. Press Enter to return.";
    cin.ignore(1000, '\n'); cin.get();
}

void upgrade_service(Member members[], int customermembership, int count) {
    cout << "Feature available in main options.\n";
    cout << "Press Enter to return.";
    cin.ignore(1000, '\n'); cin.get();
}

void renew_service(Member members[], int customermembership, int count) {
    cout << "Service renewed successfully.\n";
    cout << "Press Enter to return.";
    cin.ignore(1000, '\n'); cin.get();
}

void customer_membership(Member members[], int customermembership, int count) {
    cout << "----- Membership owned by " << members[customermembership].name << "-----" << endl;
    cout << "Personal Membership: " << members[customermembership].personalmembership << endl;
    cout << "Coach Membership:    " << members[customermembership].coachmembership << endl;
    cout << "Press Enter to return to menu" << endl;
    cin.ignore(1000, '\n'); cin.get();
}

// ============================================================
//  FILE I/O HELPERS
// ============================================================
void save_all_data() {
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

void load_all_data() {
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

bool is_only_digits(const char str[]) {
    int len = (int)strlen(str);
    if (len == 0) return false;
    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

int get_available_places(int d, int t) {
    int occupied = 0;
    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].active && bookings[i].dateIdx == d && bookings[i].timeIdx == t) {
            occupied++;
        }
    }
    return MAX_SEATS_PER_SLOT - occupied;
}

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

// ============================================================
//  REPORTING MODULE
// ============================================================
double calculateMemberFee(const Member& m) {
    double total = 0.0;
    if (m.personalmembership == "Monthly membership") total += 50.0;
    else if (m.personalmembership == "Yearly membership") total += 500.0;
    else if (m.personalmembership == "Life time membership") total += 2000.0;

    if (m.coachmembership == "Monthly coach membership") total += 80.0;
    else if (m.coachmembership == "Yearly coach membership") total += 800.0;
    else if (m.coachmembership == "Life time coach membership") total += 3500.0;

    return total;
}

double calculateTotalGymEarnings(const Member members[], int memberCount) {
    double totalSystemRevenue = 0.0;
    for (int i = 0; i < memberCount; i++) {
        totalSystemRevenue += calculateMemberFee(members[i]);
    }
    return totalSystemRevenue;
}

int getValidChoiceStudentD(int min, int max) {
    int input;
    cin >> input;
    while (cin.fail() || input < min || input > max) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter a number between " << min << " and " << max << ": ";
        cin >> input;
    }
    return input;
}

void reportingModule(const Member members[], int memberCount) {
    int choice;
    do {
        system("cls");
        cout << "=========================================\n";
        cout << "      SYSTEM REPORTING & ANALYTICS       \n";
        cout << "=========================================\n";
        cout << "1. Generate Summary Report\n";
        cout << "2. Generate Detailed Report\n";
        cout << "3. Calculate Financial Statistics\n";
        cout << "4. Sort and View Records\n";
        cout << "5. Display Gym Business Analysis\n";
        cout << "6. Back to Main Menu\n";
        cout << "=========================================\n";
        cout << "Enter selection (1-6): ";
        choice = getValidChoiceStudentD(1, 6);

        switch (choice) {
        case 1: generateSummaryReport(members, memberCount); break;
        case 2: generateDetailedReport(members, memberCount); break;
        case 3: calculateStatistics(members, memberCount); break;
        case 4: sortRecords(members, memberCount); break;
        case 5: displayAnalysis(members, memberCount); break;
        case 6: cout << "\nReturning to main menu...\n"; break;
        }
    } while (choice != 6);
}

void generateSummaryReport(const Member members[], int memberCount) {
    system("cls");
    int activePersonal = 0, activeCoach = 0, totalActiveBookings = 0;

    for (int i = 0; i < memberCount; i++) {
        if (members[i].personalmembership != "None" && !members[i].personalmembership.empty()) activePersonal++;
        if (members[i].coachmembership != "None" && !members[i].coachmembership.empty()) activeCoach++;
    }

    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].active) totalActiveBookings++;
    }

    cout << "=========================================\n";
    cout << "            GYM EXECUTIVE SUMMARY        \n";
    cout << "=========================================\n";
    cout << " Registered Members         : " << memberCount << endl;
    cout << " Active Personal Training   : " << activePersonal << endl;
    cout << " Active Coach Training      : " << activeCoach << endl;
    cout << " Total Confirmed Bookings   : " << totalActiveBookings << endl;
    cout << " Total Overall Gym Earnings : RM " << fixed << setprecision(2) << calculateTotalGymEarnings(members, memberCount) << endl;
    cout << "=========================================\n";
    cout << "\nPress Enter to return to reporting menu...";
    cin.ignore(1000, '\n'); cin.get();
}

void generateDetailedReport(const Member members[], int memberCount) {
    system("cls");
    cout << "============================================================================================\n";
    cout << "                                   GYM SYSTEM DETAILED REPORT                               \n";
    cout << "============================================================================================\n";
    cout << left << setw(8) << "ID"
        << setw(15) << "NAME"
        << setw(25) << "PERSONAL SUBSCRIPTION"
        << setw(28) << "COACH SUBSCRIPTION"
        << "EST. REVENUE" << endl;
    cout << "--------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < memberCount; i++) {
        double totalFee = calculateMemberFee(members[i]);
        cout << left << setw(8) << members[i].id
            << setw(15) << members[i].name
            << setw(25) << (members[i].personalmembership.empty() ? "None" : members[i].personalmembership)
            << setw(28) << (members[i].coachmembership.empty() ? "None" : members[i].coachmembership)
            << "RM " << fixed << setprecision(2) << totalFee << endl;
    }
    cout << "--------------------------------------------------------------------------------------------\n";
    cout << "\nPress Enter to return to reporting menu...";
    cin.ignore(1000, '\n'); cin.get();
}

void calculateStatistics(const Member members[], int memberCount) {
    system("cls");
    if (memberCount == 0) {
        cout << "No data available.\n";
        cout << "\nPress Enter to return...";
        cin.ignore(1000, '\n'); cin.get();
        return;
    }

    double totalRevenue = 0.0;
    double highestRevenue = calculateMemberFee(members[0]);
    double lowestRevenue = calculateMemberFee(members[0]);

    for (int i = 0; i < memberCount; i++) {
        double currentFee = calculateMemberFee(members[i]);
        totalRevenue += currentFee;
        if (currentFee > highestRevenue) highestRevenue = currentFee;
        if (currentFee < lowestRevenue)  lowestRevenue = currentFee;
    }

    cout << "=========================================\n";
    cout << "          FINANCIAL STATISTICS           \n";
    cout << "=========================================\n";
    cout << fixed << setprecision(2);
    cout << " Total Revenue              : RM " << totalRevenue << endl;
    cout << " Average Revenue Per Member : RM " << (totalRevenue / memberCount) << endl;
    cout << " Highest Single Expenditure : RM " << highestRevenue << endl;
    cout << " Lowest Single Expenditure  : RM " << lowestRevenue << endl;
    cout << "=========================================\n";
    cout << "\nPress Enter to return to reporting menu...";
    cin.ignore(1000, '\n'); cin.get();
}

void sortRecords(const Member members[], int memberCount) {
    system("cls");
    cout << "--- Sort Settings ---\n";
    cout << "1. Sort by Member ID\n2. Sort by Name\n3. Sort by Spending\nChoice: ";
    int sortChoice = getValidChoiceStudentD(1, 3);

    Member tempMembers[MAX_MEMBERS];
    for (int i = 0; i < memberCount; i++) tempMembers[i] = members[i];

    for (int i = 0; i < memberCount - 1; i++) {
        for (int j = 0; j < memberCount - i - 1; j++) {
            bool swapNeeded = false;
            if (sortChoice == 1 && tempMembers[j].id > tempMembers[j + 1].id) swapNeeded = true;
            if (sortChoice == 2 && tempMembers[j].name > tempMembers[j + 1].name) swapNeeded = true;
            if (sortChoice == 3 && calculateMemberFee(tempMembers[j]) < calculateMemberFee(tempMembers[j + 1])) swapNeeded = true;

            if (swapNeeded) {
                Member temp = tempMembers[j];
                tempMembers[j] = tempMembers[j + 1];
                tempMembers[j + 1] = temp;
            }
        }
    }

    system("cls");
    cout << "=======================================================================\n";
    cout << "                          SORTED MEMBER RECORDS                        \n";
    cout << "=======================================================================\n";
    for (int i = 0; i < memberCount; i++) {
        cout << left << setw(10) << tempMembers[i].id
            << setw(18) << tempMembers[i].name
            << setw(25) << (tempMembers[i].personalmembership.empty() ? "None" : tempMembers[i].personalmembership)
            << "RM " << fixed << setprecision(2) << calculateMemberFee(tempMembers[i]) << endl;
    }
    cout << "-----------------------------------------------------------------------\n";
    cout << "\nPress Enter to return to reporting menu...";
    cin.ignore(1000, '\n'); cin.get();
}

void displayAnalysis(const Member members[], int memberCount) {
    system("cls");
    int personalCount = 0, coachCount = 0;
    for (int i = 0; i < memberCount; i++) {
        if (members[i].personalmembership != "None" && !members[i].personalmembership.empty()) personalCount++;
        if (members[i].coachmembership != "None" && !members[i].coachmembership.empty()) coachCount++;
    }

    cout << "==================================================\n";
    cout << "              BUSINESS INTELLIGENCE               \n";
    cout << "==================================================\n";
    cout << " Active Personal Members : " << personalCount << "\n";
    cout << " Active Coach Members    : " << coachCount << "\n";
    cout << "==================================================\n";
    cout << "\nPress Enter to return to reporting menu...";
    cin.ignore(1000, '\n'); cin.get();
}
