// ============================================================
//  GYM MANAGEMENT SYSTEM - COMBINED BUILD
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
const int MAX_SERVICES = 2;

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
    int userId; // Ties transaction directly to a user
    char methodType[20];
    char cardHolderName[50];
    char cardNumber[20];
    char expiryDate[10];
};

// Global 1D Arrays (booking module)
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

// ============================================================
//  FUNCTION PROTOTYPES - Helper Header Display
// ============================================================
void displayUserHeader(const Member& m);

// ============================================================
//  FUNCTION PROTOTYPES - Member Module
// ============================================================
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

// ============================================================
//  FUNCTION PROTOTYPES - Booking / Transaction Module
// ============================================================
bool is_only_digits(const char str[]);
int get_available_places(int d, int t);
void add_to_history(int userId, const char name[], const char date[], const char slot[], const char status[]);
void save_all_data();
void load_all_data();
void create_transaction(int loggedInID);
void modify_transaction(int loggedInID);
void list_transaction();
bool display_timetable(const Member& currentMember);
void create_booking(const Member& currentMember);
void modify_booking(int loggedInID, const Member& currentMember);
void search_booking();
void display_booking_summary(int loggedInID);

// ============================================================
//  FUNCTION PROTOTYPES - Student D (Reporting Module)
// ============================================================
void reportingModule(const Member members[], int memberCount, const Member& currentMember);
void generateSummaryReport(const Member members[], int memberCount);
void generateDetailedReport(const Member members[], int memberCount);
void calculateStatistics(const Member members[], int memberCount);
void sortRecords(const Member members[], int memberCount);
void displayAnalysis(const Member members[], int memberCount);
double calculateMemberFee(const Member& m);
int getValidChoiceStudentD(int min, int max);

// ============================================================
//  FUNCTION PROTOTYPES - Menu glue
// ============================================================
void Menutransaction(const Member& currentMember);

// ============================================================
//  HEADER DISPLAY HELPER
// ============================================================
void displayUserHeader(const Member& m) {
    cout << "===========================================================\n";
    cout << " LOGGED IN MEMBER : " << m.name << " (ID: " << m.id << ")\n";
    cout << " Personal Sub     : " << (m.personalmembership.empty() ? "None" : m.personalmembership) << "\n";
    cout << " Coach Sub        : " << (m.coachmembership.empty() ? "None" : m.coachmembership) << "\n";
    cout << "===========================================================\n\n";
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    Member members[MAX_MEMBERS];
    int memberCount = 0;
    int portalChoice;
    fstream customer;
    ofstream openfile("customer.txt", ios::app);
    openfile.close();
    customer.open("customer.txt", fstream::in);
    if (customer.is_open()) {
        while (memberCount < MAX_MEMBERS && customer >> members[memberCount].id) {
            customer.ignore();
            getline(customer, members[memberCount].name);
            getline(customer, members[memberCount].password);
            getline(customer, members[memberCount].personalmembership);
            getline(customer, members[memberCount].coachmembership);
            memberCount++;
        }
        customer.close();
    }
    else {
        cout << "Failed to load file" << endl;
        cout << "Press Enter to continue...";
        cin.get();
    }

    load_all_data();
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
            cin.ignore(100, '\n');
            cout << "Invalid choice! Enter 1-3: ";
            cin >> portalChoice;
        }
        cin.ignore();

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
            cin.ignore();
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
                displayUserHeader(members[userIndex]);
                cout << "===================================\n";
                cout << "        GYM MEMBERSHIP SYSTEM       \n";
                cout << "===================================\n";
                cout << "1. Member Management \n";
                cout << "2. Member subscription \n";
                cout << "3. Transaction & Booking \n";
                cout << "4. Reporting Module \n";
                cout << "5. Log Out\n";
                cout << "Choice (1-5): ";
                cin >> systemChoice;
                while (cin.fail() || systemChoice < 1 || systemChoice > 5) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid choice! Enter 1-5: ";
                    cin >> systemChoice;
                }
                if (systemChoice == 1) {
                    int subChoice;
                    do {
                        system("cls");
                        displayUserHeader(members[userIndex]);
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
                            cin.ignore(100, '\n');
                            cout << "Invalid choice! Enter 1-5: ";
                            cin >> subChoice;
                        }
                        if (subChoice == 1) {
                            system("cls");
                            displayUserHeader(members[userIndex]);
                            updateMember(members, memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(); cin.get();
                        }
                        else if (subChoice == 2) {
                            system("cls");
                            displayUserHeader(members[userIndex]);
                            deleteMember(members, &memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(); cin.get();
                        }
                        else if (subChoice == 3) {
                            system("cls");
                            displayUserHeader(members[userIndex]);
                            searchMember(members, memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(); cin.get();
                        }
                        else if (subChoice == 4) {
                            system("cls");
                            displayUserHeader(members[userIndex]);
                            displayMembers(members, memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(); cin.get();
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
                        cin.ignore(); cin.get();
                        break;
                    }
                    userIndex = newIndex;
                }
                else if (systemChoice == 2) {
                    Member_subscription(members, userIndex, memberCount);
                }
                else if (systemChoice == 3) {
                    system("cls");
                    Menutransaction(members[userIndex]);
                }
                else if (systemChoice == 4) {
                    system("cls");
                    reportingModule(members, memberCount, members[userIndex]);
                }
            } while (systemChoice != 5);
        }
    } while (portalChoice != 3);
    system("cls");
    cout << "Program exited successfully.\n";
    return 0;
}

// ============================================================
//  MENU GLUE - Trainer Scheduling
// ============================================================
void Menutransaction(const Member& currentMember) {
    int choose;
    do {
        system("cls");
        displayUserHeader(currentMember);
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
        switch (choose) {
        case 1: create_transaction(currentMember.id); break;
        case 2: modify_transaction(currentMember.id); break;
        case 3: list_transaction(); break;
        case 4: create_booking(currentMember); break;
        case 5: modify_booking(currentMember.id, currentMember); break;
        case 6: search_booking(); break;
        case 7: display_booking_summary(currentMember.id); break;
        case 0: save_all_data(); break;
        default: break;
        }
    } while (choose != 0);
}

// ============================================================
//  MEMBER MODULE - implementations
// ============================================================
void signUpMember(Member members[], int& count) {
    if (count >= MAX_MEMBERS) {
        cout << "Database is full! Cannot register more members.\n";
        return;
    }
    string username;
    string password;
    cout << "==== Sign Up ====\n";
    cout << "Enter username: ";
    getline(cin, username);
    int isDuplicate = 0;
    for (int i = 0; i < count; i++) {
        if (members[i].name == username) {
            isDuplicate = 1;
            break;
        }
    }
    if (isDuplicate == 1) {
        cout << "Username already taken! Try another one.\n";
        return;
    }
    cout << "Enter password: ";
    cin >> members[count].password;
    cin.ignore();
    password = members[count].password;
    int randomID;
    int idExists;
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
    else cout << "customer details could not be saved sucessfully";
    cout << "\n==================================================\n";
    cout << "            REGISTRATION SUCCESSFUL!              \n";
    cout << "==================================================\n";
    cout << "  Welcome to the gym, " << username << "!\n";
    cout << "  Your auto-generated 4-Digit Member ID is: " << randomID << "\n";
    cout << "  Write this ID down! You will need it to search  \n";
    cout << "  or update your profile details.                 \n";
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
        cin.ignore();
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
            cout << "\n--- Member Found ---\n";
            cout << "ID:      " << members[i].id << "\n";
            cout << "Name:    " << members[i].name << "\n";
            cout << "Payment: " << members[i].paymentMethod << "\n";
            cout << "Personal membership: " << members[i].personalmembership << "\n";
            cout << "Coach membership: " << members[i].coachmembership << "\n";
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
    cout << left << setw(10) << "ID"
        << setw(15) << "NAME"
        << setw(20) << "PAYMENT"
        << setw(15) << "TRAINER" << endl;
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << members[i].id
            << setw(15) << members[i].name
            << setw(20) << members[i].paymentMethod
            << setw(15) << members[i].trainer << endl;
    }
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
        displayUserHeader(members[customermembership]);
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
            add_service(members, customermembership, count);
        }
        else if (choice == 2) {
            system("cls");
            cout << "You have selected remove service." << endl;
            removeservice(members, customermembership, count);
        }
        else if (choice == 3) {
            system("cls");
            cout << "You have selected upgrade service." << endl;
            upgrade_service(members, customermembership, count);
        }
        else if (choice == 4) {
            system("cls");
            cout << "You have selected renew service." << endl;
            renew_service(members, customermembership, count);
        }
        else if (choice == 5) {
            system("cls");
            cout << "You have selected display all service you own." << endl;
            customer_membership(members, customermembership, count);
        }
        else if (choice == 6) {
            return;
        }
        else {
            system("cls");
            cout << "Invalid choice. Please select a valid option." << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    } while (choice != 6);
}

void add_service(Member members[], int customermembership, int count) {
    displayUserHeader(members[customermembership]);
    cout << "You have selected to add a new service." << endl;
    int addservicechoice;
    cout << "Please select the type of service you would like to add:" << endl;
    cout << "1. Personal Training" << endl;
    cout << "2. Coach Training" << endl;
    cout << "Your choice: ";
    cin >> addservicechoice;
    while (cin.fail() || addservicechoice < 1 || addservicechoice > 2) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid choice! Enter 1-2: ";
        cin >> addservicechoice;
    }
    switch (addservicechoice) {
    case 1:
        system("cls");
        personal(members, customermembership, count);
        break;
    case 2:
        system("cls");
        coach(members, customermembership, count);
        break;
    }
}

void personal(Member members[], int customermembership, int count) {
    int afteraddservice;
    system("cls");
    displayUserHeader(members[customermembership]);

    cout << "You have selected to add Personal Training." << endl;
    cout << "Please choose your interested membership: " << endl;
    cout << "1. Monthly membership: RM50/month" << endl;
    cout << "2. Yearly membership: RM500/year" << endl;
    cout << "3. Life time membership: RM2000" << endl;
    cout << "Your choice: ";
    cin >> afteraddservice;

    while (cin.fail() || afteraddservice < 1 || afteraddservice > 3) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid choice! Enter 1-3: ";
        cin >> afteraddservice;
    }

    string planName = "";
    double price = 0.0;

    if (afteraddservice == 1) {
        planName = "Monthly membership";
        price = 50.0;
    }
    else if (afteraddservice == 2) {
        planName = "Yearly membership";
        price = 500.0;
    }
    else if (afteraddservice == 3) {
        planName = "Life time membership";
        price = 2000.0;
    }

    members[customermembership].personalmembership = planName;
    saveAllMembersToFile(members, count);

    cout << "\n===========================================================\n";
    cout << "              TRANSACTION & EARNINGS RECEIPT               \n";
    cout << "===========================================================\n";
    cout << "Member ID           : " << members[customermembership].id << endl;
    cout << "Member Name         : " << members[customermembership].name << endl;
    cout << "Added Plan          : Personal Training (" << planName << ")" << endl;
    cout << "Payment Method      : " << members[customermembership].paymentMethod << endl;
    cout << "Amount Paid         : RM " << fixed << setprecision(2) << price << endl;
    cout << "-----------------------------------------------------------\n";
    cout << "Member Total Revenue : RM " << fixed << setprecision(2) << calculateMemberFee(members[customermembership]) << endl;
    cout << "===========================================================\n";
    cout << "Service added successfully! Press Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

void coach(Member members[], int customermembership, int count) {
    int afteraddservice_coach;
    system("cls");
    displayUserHeader(members[customermembership]);

    cout << "You have selected to add Coach Training." << endl;
    cout << "Please choose your interested membership: " << endl;
    cout << "1. Monthly coach membership: RM80/month" << endl;
    cout << "2. Yearly coach membership: RM800/year" << endl;
    cout << "3. Life time coach membership: RM3500" << endl;
    cout << "Your choice: ";
    cin >> afteraddservice_coach;

    while (cin.fail() || afteraddservice_coach < 1 || afteraddservice_coach > 3) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid choice! Enter 1-3: ";
        cin >> afteraddservice_coach;
    }

    string planName = "";
    double price = 0.0;

    if (afteraddservice_coach == 1) {
        planName = "Monthly coach membership";
        price = 80.0;
    }
    else if (afteraddservice_coach == 2) {
        planName = "Yearly coach membership";
        price = 800.0;
    }
    else if (afteraddservice_coach == 3) {
        planName = "Life time coach membership";
        price = 3500.0;
    }

    members[customermembership].coachmembership = planName;
    saveAllMembersToFile(members, count);

    cout << "\n===========================================================\n";
    cout << "              TRANSACTION & EARNINGS RECEIPT               \n";
    cout << "===========================================================\n";
    cout << "Member ID           : " << members[customermembership].id << endl;
    cout << "Member Name         : " << members[customermembership].name << endl;
    cout << "Added Plan          : Coach Training (" << planName << ")" << endl;
    cout << "Payment Method      : " << members[customermembership].paymentMethod << endl;
    cout << "Amount Paid         : RM " << fixed << setprecision(2) << price << endl;
    cout << "-----------------------------------------------------------\n";
    cout << "Member Total Revenue : RM " << fixed << setprecision(2) << calculateMemberFee(members[customermembership]) << endl;
    cout << "===========================================================\n";
    cout << "Service added successfully! Press Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

void removeservice(Member members[], int customermembership, int count) {
    displayUserHeader(members[customermembership]);
    cout << "Please select the Membership you want to remove;" << endl;
    cout << "WARNING:Removing membership will not refund your money!!!" << endl;
    cout << "-------- Membership Owned By " << members[customermembership].name << "--------" << endl;
    cout << "1.Personal  Membership: " << members[customermembership].personalmembership << endl;
    cout << "2.Coach  Membership: " << members[customermembership].coachmembership << endl;
    cout << "3.Return" << endl;
    cout << "Your choice: ";
    int removemembership;
    cin >> removemembership;
    while (cin.fail() || removemembership < 1 || removemembership > 3) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid choice! Enter 1-3: ";
        cin >> removemembership;
    }
    if (removemembership == 1) {
        if (members[customermembership].personalmembership == "None") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "You don't have a Personal Training membership to remove.\n";
            cout << "Press Enter to return" << endl;
            cin.get(); cin.ignore();
            return;
        }
        else {
            members[customermembership].personalmembership = "None";
            saveAllMembersToFile(members, count);
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "You have removed your personal membership" << endl;
            cout << "Press Enter to return" << endl;
            cin.get(); cin.ignore();
            return;
        }
    }
    else if (removemembership == 2) {
        if (members[customermembership].coachmembership == "None") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "You don't have a Coach Training membership to remove." << endl;
            cout << "Press Enter to return" << endl;
            cin.get(); cin.ignore();
            return;
        }
        else {
            members[customermembership].coachmembership = "None";
            saveAllMembersToFile(members, count);
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "You have removed your coach membership" << endl;
            cout << "Press Enter to return" << endl;
            cin.get(); cin.ignore();
            return;
        }
    }
    else if (removemembership == 3) {
        return;
    }
}

void upgrade_service(Member members[], int customermembership, int count) {
back:
    int option;
    int membership_upgrade;
    int coach_membership_upgrade;
    char year_to_life;
    char coach_year_to_life;
    displayUserHeader(members[customermembership]);
    cout << "----- Upgrade Membership Services -----" << endl;
    cout << "Please select the service you want to upgrade" << endl;
    cout << "1.Personal Membership:" << members[customermembership].personalmembership << endl;
    cout << "2.Coach Membership:" << members[customermembership].coachmembership << endl;
    cout << "3.Return" << endl;
    cout << "Your choice: ";
    cin >> option;
    while (cin.fail() || option < 1 || option > 3) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid choice! Enter 1-3: ";
        cin >> option;
    }
    if (option == 1) {
        if (members[customermembership].personalmembership == "None") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "You don't own any personal membership" << endl;
            cout << "Please press enter to choose again" << endl;
            cin.get();
            cin.ignore();
            goto back;
        }
        else if (members[customermembership].personalmembership == "Monthly membership") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "Your membership is monthly right now" << endl;
            cout << "Please select the membership plan you want to upgrade to" << endl;
            cout << "1.Yearly membership (RM500/year)" << endl;
            cout << "2.Life time mebership (Rm2000)" << endl;
            cout << "Your choice: ";
            cin >> membership_upgrade;
            while (cin.fail() || membership_upgrade < 1 || membership_upgrade > 2) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid choice! Enter 1-2: ";
                cin >> membership_upgrade;
            }
            do {
            redo:
                if (membership_upgrade == 1) {
                    members[customermembership].personalmembership = "Yearly membership";
                    saveAllMembersToFile(members, count);
                    system("cls");
                    displayUserHeader(members[customermembership]);
                    cout << "Thank you for supporting our services" << endl;
                    cout << "Your membership has been updated to yearly plan" << endl;
                    cout << "Press Enter to return to main menu" << endl;
                    cin.get();
                    cin.ignore();
                    return;
                }
                else if (membership_upgrade == 2) {
                    members[customermembership].personalmembership = "Life time membership";
                    saveAllMembersToFile(members, count);
                    system("cls");
                    displayUserHeader(members[customermembership]);
                    cout << "Thank you for supporting our services" << endl;
                    cout << "Your membership has been updated to Life time plan" << endl;
                    cout << "Press Enter to return to main menu" << endl;
                    cin.get();
                    cin.ignore();
                    return;
                }
                else {
                    cout << "Invalid option,please try again" << endl;
                    goto redo;
                }
            } while (membership_upgrade <= 0 || membership_upgrade >= 3);
        }
        else if (members[customermembership].personalmembership == "Yearly membership") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "Your membership is yearly right now" << endl;
            cout << "Would you like to upgrade to Life time membership?" << endl;
            cout << "press y for yes and n for no" << endl;
            cin >> year_to_life;
            while (cin.fail() || (year_to_life != 'y' && year_to_life != 'Y' && year_to_life != 'n' && year_to_life != 'N')) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid choice! Enter y or n: ";
                cin >> year_to_life;
            }
            do {
                if (year_to_life == 'y' || year_to_life == 'Y') {
                    members[customermembership].personalmembership = "Life time membership";
                    saveAllMembersToFile(members, count);
                    system("cls");
                    displayUserHeader(members[customermembership]);
                    cout << "Your membership has been upgraded to Life time" << endl;
                    cout << "THank you for supporting our services" << endl;
                    cout << "Press Enter to return" << endl;
                    cin.get();
                    cin.ignore();
                    return;
                }
                else if (year_to_life == 'n' || year_to_life == 'N') {
                    members[customermembership].personalmembership = "Yearly membership";
                    saveAllMembersToFile(members, count);
                    system("cls");
                    displayUserHeader(members[customermembership]);
                    cout << "Your membership stayed the same" << endl;
                    cout << "Press Enter to return" << endl;
                    cin.get();
                    cin.ignore();
                    return;
                }
                else {
                    cout << "invalid choice,Please try again" << endl;
                    cout << "Press Enter to continue " << endl;
                    cin >> year_to_life;
                }
            } while (year_to_life != 'y' && year_to_life != 'Y' && year_to_life != 'n' && year_to_life != 'N');
        }
        else if (members[customermembership].personalmembership == "Life time membership") {
            cout << "Your membership is already Life time plan" << endl;
            cout << "Thank you for your support" << endl;
            cout << "Press Enter to return" << endl;
            cin.get();
            cin.ignore();
            return;
        }
    }
    else if (option == 2) {
        if (members[customermembership].coachmembership == "None") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "You don't own any coach membership" << endl;
            cout << "Please press enter to choose again" << endl;
            cin.get();
            cin.ignore();
            goto back;
        }
        else if (members[customermembership].coachmembership == "Monthly coach membership") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "Your coach membership is monthly right now" << endl;
            cout << "Please select the membership plan you want to upgrade to" << endl;
            cout << "1.Yearly coach membership (RM800/year)" << endl;
            cout << "2.Life time coach mebership (Rm3500)" << endl;
            cout << "Your choice: ";
            cin >> coach_membership_upgrade;
            while (cin.fail() || coach_membership_upgrade < 1 || coach_membership_upgrade > 2) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid choice! Enter 1-2: ";
                cin >> coach_membership_upgrade;
            }
            do {
            redo2:
                if (coach_membership_upgrade == 1) {
                    members[customermembership].coachmembership = "Yearly coach membership";
                    saveAllMembersToFile(members, count);
                    system("cls");
                    displayUserHeader(members[customermembership]);
                    cout << "Thank you for supporting our services" << endl;
                    cout << "Your coach membership has been updated to yearly plan" << endl;
                    cout << "Press Enter to return to main menu" << endl;
                    cin.get();
                    cin.ignore();
                    return;
                }
                else if (coach_membership_upgrade == 2) {
                    system("cls");
                    members[customermembership].coachmembership = "Life time coach membership";
                    saveAllMembersToFile(members, count);
                    displayUserHeader(members[customermembership]);
                    cout << "Thank you for supporting our services" << endl;
                    cout << "Your coach membership has been updated to Lifetime plan" << endl;
                    cout << "Press Enter to return to main menu" << endl;
                    cin.get();
                    cin.ignore();
                    return;
                }
                else {
                    cout << "Invalid option,please try again" << endl;
                    goto redo2;
                }
            } while (coach_membership_upgrade <= 0 || coach_membership_upgrade >= 3);
        }
        else if (members[customermembership].coachmembership == "Yearly coach membership") {
            saveAllMembersToFile(members, count);
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "Your membership is yearly right now" << endl;
            cout << "Would you like to upgrade to Life time coach membership?" << endl;
            cout << "press y for yes and n for no" << endl;
            cin >> coach_year_to_life;
            do {
                if (coach_year_to_life == 'y' || coach_year_to_life == 'Y') {
                    members[customermembership].coachmembership = "Life time coach membership";
                    saveAllMembersToFile(members, count);
                    system("cls");
                    displayUserHeader(members[customermembership]);
                    cout << "Your coach membership has been upgraded to Life time" << endl;
                    cout << "THank you for supporting our services" << endl;
                    cout << "Press Enter to return" << endl;
                    cin.get();
                    cin.ignore();
                    return;
                }
                else if (coach_year_to_life == 'n' || coach_year_to_life == 'N') {
                    members[customermembership].coachmembership = "Yearly coach membership";
                    saveAllMembersToFile(members, count);
                    system("cls");
                    displayUserHeader(members[customermembership]);
                    cout << "Your coach membership stayed the same" << endl;
                    cout << "Press Enter to return" << endl;
                    cin.get();
                    cin.ignore();
                    return;
                }
                else {
                    cout << "invalid choice,Please try again" << endl;
                    cout << "Press Enter to continue " << endl;
                    cin >> coach_year_to_life;
                }
            } while (coach_year_to_life != 'y' && coach_year_to_life != 'Y' && coach_year_to_life != 'n' && coach_year_to_life != 'N');
        }
        else if (members[customermembership].coachmembership == "Life time coach membership") {
            cout << "Your coach membership is already Life time plan" << endl;
            cout << "Thank you for your support" << endl;
            cout << "Press Enter to return" << endl;
            cin.get();
            cin.ignore();
            return;
        }
    }
    else if (option == 3) {
        return;
    }
}

void renew_service(Member members[], int customermembership, int count) {
    int pick;
    displayUserHeader(members[customermembership]);
    cout << "Please choose the membership you want to renew " << endl;
    cout << "----- Membership owned -----" << endl;
    cout << "1.Personal: " << members[customermembership].personalmembership << endl;
    cout << "2.Coach: " << members[customermembership].coachmembership << endl;
    cout << "3.Back to menu" << endl;
    cout << "Your Choice:";
    cin >> pick;
    if (pick == 1) {
        if (members[customermembership].personalmembership == "Monthly membership" || members[customermembership].personalmembership == "Yearly membership") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "Your Personal " << members[customermembership].personalmembership << " will be renew after paying the bills" << endl;
            cout << "Press Enter to proceed to pay" << endl;
            cin.get();
            cin.ignore();
        }
        else if (members[customermembership].personalmembership == "Life time membership") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "Your Personal Membership is already a Life time membership" << endl;
            cout << "No Renew is needed" << endl;
            cout << "Press Enter to return to menu" << endl;
            cin.get();
            cin.ignore();
            return;
        }
    }
    else if (pick == 2) {
        if (members[customermembership].coachmembership == "Montly coach membership" || members[customermembership].coachmembership == "Yearly coach membership") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "Your " << members[customermembership].coachmembership << " will be renew after paying the bills" << endl;
            cout << "Press Enter to proceed to pay" << endl;
            cin.get();
            cin.ignore();
        }
        else if (members[customermembership].coachmembership == "Life time coach membership") {
            system("cls");
            displayUserHeader(members[customermembership]);
            cout << "Your Personal Membership is already a Life time coach membership" << endl;
            cout << "No Renew is needed" << endl;
            cout << "Press Enter to return to menu" << endl;
            cin.get();
            cin.ignore();
            return;
        }
    }
    else if (pick == 3) {
        return;
    }
}

void customer_membership(Member members[], int customermembership, int count) {
    system("cls");
    displayUserHeader(members[customermembership]);
    cout << "----- Membership owned by " << members[customermembership].name << "-----" << endl;
    cout << "Personal Membership: " << members[customermembership].personalmembership << endl;
    cout << "Coach Membership: " << members[customermembership].coachmembership << endl;
    cout << "Press Enter to return to menu" << endl;
    cin.get();
    cin.ignore();
    return;
}

// ============================================================
//  BOOKING / TRANSACTION MODULE - implementations
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
        if (!isdigit(str[i])) {
            return false;
        }
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

void create_transaction(int loggedInID) {
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
        tx.userId = loggedInID; // Automatically assigned from logged-in session
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
            cout << "\n[+] Transaction recorded successfully for User ID " << loggedInID << "!" << endl;
        }
    }
    else {
        cout << "\n[!] Invalid selection." << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.get();
}

void modify_transaction(int loggedInID) {
    cout << "\n===== Modify Transaction =====" << endl;
    int target_id = loggedInID; // Automatically use logged in user's ID
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
    cout << "\n==================================================================================\n";
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
    cin.ignore(1000, '\n');
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
        if (booking_count < MAX_BOOKINGS) {
            bookings[booking_count].userId = currentMember.id;
            strncpy(bookings[booking_count].name, currentMember.name.c_str(), 49);
            bookings[booking_count].name[49] = '\0';
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
    return true;
}

void create_booking(const Member& currentMember) {
    cout << "\n===== Create Booking =====" << endl;
    bool completed = display_timetable(currentMember);
    if (completed) {
        cout << "\nPress Enter to return to main menu...";
        cin.ignore(1000, '\n');
        cin.get();
    }
}

void modify_booking(int loggedInID, const Member& currentMember) {
    cout << "\n===== Modify Booking =====" << endl;
    int target_id = loggedInID; // Automatically use logged in ID
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
    bool completed = display_timetable(currentMember);
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

void display_booking_summary(int loggedInID) {
    int target_id = loggedInID; // Automatically use logged in user's ID
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

// =========================================================================
// STUDENT D MODULE: REPORTING & ANALYTICS MODULE
// =========================================================================
double calculateMemberFee(const Member& m) {
    double total = 0.0;
    if (m.personalmembership == "Monthly membership") total += 50.0;
    else if (m.personalmembership == "Yearly membership") total += 500.0;
    else if (m.personalmembership == "Life time membership") total += 2000.0;

    if (m.coachmembership == "Monthly coach membership" || m.coachmembership == "Montly coach membership") total += 80.0;
    else if (m.coachmembership == "Yearly coach membership") total += 800.0;
    else if (m.coachmembership == "Life time coach membership") total += 3500.0;
    return total;
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

void reportingModule(const Member members[], int memberCount, const Member& currentMember) {
    int choice;
    do {
        system("cls");
        displayUserHeader(currentMember);
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
        case 1:
            generateSummaryReport(members, memberCount);
            break;
        case 2:
            generateDetailedReport(members, memberCount);
            break;
        case 3:
            calculateStatistics(members, memberCount);
            break;
        case 4:
            sortRecords(members, memberCount);
            break;
        case 5:
            displayAnalysis(members, memberCount);
            break;
        case 6:
            cout << "\nReturning to main menu...\n";
            break;
        }
    } while (choice != 6);
}

void generateSummaryReport(const Member members[], int memberCount) {
    system("cls");
    int activePersonal = 0;
    int activeCoach = 0;
    int totalActiveBookings = 0;

    for (int i = 0; i < memberCount; i++) {
        if (members[i].personalmembership != "None" && !members[i].personalmembership.empty()) {
            activePersonal++;
        }
        if (members[i].coachmembership != "None" && !members[i].coachmembership.empty()) {
            activeCoach++;
        }
    }

    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].active) {
            totalActiveBookings++;
        }
    }
    cout << "=========================================\n";
    cout << "            GYM EXECUTIVE SUMMARY        \n";
    cout << "=========================================\n";
    cout << " Registered Members         : " << memberCount << endl;
    cout << " Active Personal Training   : " << activePersonal << endl;
    cout << " Active Coach Training      : " << activeCoach << endl;
    cout << " Total Confirmed Bookings   : " << totalActiveBookings << endl;
    cout << "=========================================\n";
    cout << "\nPress Enter to return to reporting menu...";
    cin.ignore();
    cin.get();
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
    if (memberCount == 0) {
        cout << "No member records found in the database.\n";
    }
    else {
        for (int i = 0; i < memberCount; i++) {
            double totalFee = calculateMemberFee(members[i]);
            cout << left << setw(8) << members[i].id
                << setw(15) << members[i].name
                << setw(25) << (members[i].personalmembership.empty() ? "None" : members[i].personalmembership)
                << setw(28) << (members[i].coachmembership.empty() ? "None" : members[i].coachmembership)
                << "RM " << fixed << setprecision(2) << totalFee << endl;
        }
    }
    cout << "--------------------------------------------------------------------------------------------\n";
    cout << "\nPress Enter to return to reporting menu...";
    cin.ignore();
    cin.get();
}

void calculateStatistics(const Member members[], int memberCount) {
    system("cls");
    if (memberCount == 0) {
        cout << "No data available to perform statistical calculations.\n";
        cout << "\nPress Enter to return...";
        cin.ignore(); cin.get();
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
    double averageRevenue = totalRevenue / memberCount;
    cout << "=========================================\n";
    cout << "          FINANCIAL STATISTICS           \n";
    cout << "=========================================\n";
    cout << fixed << setprecision(2);
    cout << " Total Revenue              : RM " << totalRevenue << endl;
    cout << " Average Revenue Per Member : RM " << averageRevenue << endl;
    cout << " Highest Single Expenditure : RM " << highestRevenue << endl;
    cout << " Lowest Single Expenditure  : RM " << lowestRevenue << endl;
    cout << "=========================================\n";
    cout << "\nPress Enter to return to reporting menu...";
    cin.ignore(); cin.get();
}

void sortRecords(const Member members[], int memberCount) {
    system("cls");
    if (memberCount == 0) {
        cout << "No data available to perform sorting.\n";
        cout << "\nPress Enter to return...";
        cin.ignore(); cin.get();
        return;
    }
    cout << "--- Sort Settings ---\n";
    cout << "1. Sort by Member ID (Ascending)\n";
    cout << "2. Sort by Name (A to Z)\n";
    cout << "3. Sort by Spending Amount (Descending)\n";
    cout << "Choose option: ";
    int sortChoice = getValidChoiceStudentD(1, 3);

    Member tempMembers[MAX_MEMBERS];
    for (int i = 0; i < memberCount; i++) {
        tempMembers[i] = members[i];
    }

    for (int i = 0; i < memberCount - 1; i++) {
        for (int j = 0; j < memberCount - i - 1; j++) {
            bool swapNeeded = false;
            if (sortChoice == 1) {
                if (tempMembers[j].id > tempMembers[j + 1].id) swapNeeded = true;
            }
            else if (sortChoice == 2) {
                if (tempMembers[j].name > tempMembers[j + 1].name) swapNeeded = true;
            }
            else if (sortChoice == 3) {
                if (calculateMemberFee(tempMembers[j]) < calculateMemberFee(tempMembers[j + 1])) swapNeeded = true;
            }
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
    cout << left << setw(10) << "ID"
        << setw(18) << "NAME"
        << setw(25) << "PERSONAL PLAN"
        << "EST. SPENT" << endl;
    cout << "-----------------------------------------------------------------------\n";
    for (int i = 0; i < memberCount; i++) {
        cout << left << setw(10) << tempMembers[i].id
            << setw(18) << tempMembers[i].name
            << setw(25) << (tempMembers[i].personalmembership.empty() ? "None" : tempMembers[i].personalmembership)
            << "RM " << fixed << setprecision(2) << calculateMemberFee(tempMembers[i]) << endl;
    }
    cout << "-----------------------------------------------------------------------\n";
    cout << "\nPress Enter to return to reporting menu...";
    cin.ignore(); cin.get();
}

void displayAnalysis(const Member members[], int memberCount) {
    system("cls");
    int personalCount = 0;
    int coachCount = 0;
    for (int i = 0; i < memberCount; i++) {
        if (members[i].personalmembership != "None" && !members[i].personalmembership.empty()) personalCount++;
        if (members[i].coachmembership != "None" && !members[i].coachmembership.empty()) coachCount++;
    }

    string popularService = "No current subscription trend";
    if (personalCount > coachCount) {
        popularService = "Personal Training subscription plans";
    }
    else if (coachCount > personalCount) {
        popularService = "Coach Training subscription plans";
    }
    else if (personalCount > 0 && personalCount == coachCount) {
        popularService = "Both services share equal popularity";
    }

    int dayCounts[TOTAL_DATES] = { 0 };
    for (int i = 0; i < booking_count; i++) {
        if (bookings[i].active && bookings[i].dateIdx >= 0 && bookings[i].dateIdx < TOTAL_DATES) {
            dayCounts[bookings[i].dateIdx]++;
        }
    }
    cout << "==================================================\n";
    cout << "              BUSINESS INTELLIGENCE               \n";
    cout << "==================================================\n";
    cout << " Most Popular Service: \n   >> " << popularService << endl;
    cout << "--------------------------------------------------\n";
    cout << " [Subscription Summary Distribution]\n";
    cout << "  - Active Personal Members : " << personalCount << " active pax\n";
    cout << "  - Active Coach Members    : " << coachCount << " active pax\n";
    cout << "--------------------------------------------------\n";
    cout << " [Booking Distribution Frequency Tracker]\n";
    for (int i = 0; i < TOTAL_DATES; i++) {
        cout << "  - " << dateSlot[i] << ": " << dayCounts[i] << " scheduled booking(s)\n";
    }
    cout << "==================================================\n";
    cout << "\nPress Enter to return to reporting menu...";
    cin.ignore(); cin.get();
}
