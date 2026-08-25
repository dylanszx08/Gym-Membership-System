#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

// Maximum limits
const int MAX_MEMBERS = 50;
const int time_booking = 6;
const int date_booking = 7;
const int MAX_PLACES = 10;

// Struct definitions
struct Member {
    int id;
    string name;
    string password;
    string paymentMethod; // ZIHIN (Teammate B)
    string trainer;       // HILSON (Teammate C)
};

struct Booking {
    int userId;
    char name[50];
    bool active;
};

// Global booking system storage
int available_places[date_booking][time_booking];
Booking slot_bookings[date_booking][time_booking][MAX_PLACES];
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

// --- Function Prototypes ---
void init_places();
void displayUserBookings(int userId);
void create_transaction(Member members[], int loggedInIndex);
void create_booking(int userId, string userName);
void modify_booking(int userId, string userName);
void search_booking();
bool display_timetable(int userId, string userName);

// Services / Subscription module prototypes
void Member_subscription(Member members[], int loggedInIndex);
void display_services(Member members[], int loggedInIndex);
void add_service(Member members[], int loggedInIndex);
void personal(Member members[], int loggedInIndex);
void coach(Member members[], int loggedInIndex);
void removeservice();

// Member record management prototypes (Dylan's Module)
void signUpMember(Member members[], int& count);
void updateMember(Member members[], int count);
void deleteMember(Member members[], int* count);
void searchMember(Member members[], int count);
void displayMembers(Member members[], int count);

// Trainer scheduling (Student C's Module)
void runTrainerScheduling(Member members[], int loggedInIndex);

// Initialize array values and date titles
void init_places() {
    time_t now = time(0);
    for (int d = 0; d < date_booking; d++) {
        time_t t = now + (d * 86400);
        tm day = *localtime(&t);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%d %b (%a)", &day);
        dateSlot[d] = buffer;

        for (int time_idx = 0; time_idx < time_booking; time_idx++) {
            available_places[d][time_idx] = MAX_PLACES;
            for (int s = 0; s < MAX_PLACES; s++) {
                slot_bookings[d][time_idx][s].active = false;
                slot_bookings[d][time_idx][s].userId = 0;
                slot_bookings[d][time_idx][s].name[0] = '\0';
            }
        }
    }
}

// Helper to print bookings directly on the main user dashboard
void displayUserBookings(int userId) {
    cout << "  ACTIVE BOOKINGS:\n";
    bool hasBooking = false;
    for (int d = 0; d < date_booking; d++) {
        for (int t = 0; t < time_booking; t++) {
            for (int s = 0; s < MAX_PLACES; s++) {
                if (slot_bookings[d][t][s].active && slot_bookings[d][t][s].userId == userId) {
                    cout << "   - " << dateSlot[d] << " @ " << timeSlot[t] << "\n";
                    hasBooking = true;
                }
            }
        }
    }
    if (!hasBooking) {
        cout << "   - No active slot bookings.\n";
    }
}

int main() {
    srand(time(NULL));
    init_places();

    Member members[MAX_MEMBERS];
    int memberCount = 0;
    int portalChoice;

    do {
        system("cls");
        cout << "===================================\n";
        cout << "     GYM SYSTEM ACCESS PORTAL      \n";
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

            // MAIN DASHBOARD (DASHBOARD UPDATED TO SHOW BOOKINGS IMMEDIATELY)
            int systemChoice;
            do {
                system("cls");
                cout << "===================================================\n";
                cout << "               GYM MEMBER DASHBOARD                \n";
                cout << "===================================================\n";
                cout << " WELCOME: " << members[userIndex].name << " (ID: " << members[userIndex].id << ")\n";
                cout << " PAYMENT METHOD : " << members[userIndex].paymentMethod << "\n";
                cout << " ASSIGNED TRAINER: " << members[userIndex].trainer << "\n";
                cout << "---------------------------------------------------\n";

                // Print user's live bookings directly on the main screen
                displayUserBookings(members[userIndex].id);

                cout << "===================================================\n";
                cout << "1. Member Management (Sub-Menu)\n";
                cout << "2. Member Subscription & Booking (Module B)\n";
                cout << "3. Trainer Scheduling (Module C)\n";
                cout << "4. Log Out\n";
                cout << "Choice (1-4): ";
                cin >> systemChoice;

                while (cin.fail() || systemChoice < 1 || systemChoice > 4) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid choice! Enter 1-4: ";
                    cin >> systemChoice;
                }

                if (systemChoice == 1) {
                    int subChoice;
                    do {
                        system("cls");
                        cout << "--- Member Management Sub-Menu ---\n";
                        cout << "1. Update Member Details\n";
                        cout << "2. Delete Member Account\n";
                        cout << "3. Search Member Record\n";
                        cout << "4. Display All Registered Members\n";
                        cout << "5. Back\n";
                        cout << "Choice (1-5): ";
                        cin >> subChoice;

                        if (subChoice == 1) {
                            system("cls");
                            updateMember(members, memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(); cin.get();
                        }
                        else if (subChoice == 2) {
                            system("cls");
                            deleteMember(members, &memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(); cin.get();
                        }
                        else if (subChoice == 3) {
                            system("cls");
                            searchMember(members, memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(); cin.get();
                        }
                        else if (subChoice == 4) {
                            system("cls");
                            displayMembers(members, memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(); cin.get();
                        }
                    } while (subChoice != 5);
                }
                else if (systemChoice == 2) {
                    Member_subscription(members, userIndex);
                }
                else if (systemChoice == 3) {
                    runTrainerScheduling(members, userIndex);
                }
            } while (systemChoice != 4);
        }
    } while (portalChoice != 3);

    system("cls");
    cout << "Program exited successfully.\n";
    return 0;
}

// =================================================================
// --- MEMBER MANAGEMENT MODULE ---
// =================================================================

void signUpMember(Member members[], int& count) {
    if (count >= MAX_MEMBERS) {
        cout << "Database is full! Cannot register more members.\n";
        return;
    }

    string username;
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

    ofstream customer("customer.txt", ios::app);
    if (customer.is_open()) {
        customer << randomID << " " << username << endl;
        customer.close();
    }

    cout << "\n==================================================\n";
    cout << "             REGISTRATION SUCCESSFUL!             \n";
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
        cin.ignore();
        cout << "Enter New Username: ";
        getline(cin, members[foundIndex].name);
        cout << "Enter New Password: ";
        cin >> members[foundIndex].password;
        cout << "Member details updated successfully!\n";
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
            cout << "Trainer: " << members[i].trainer << "\n";
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

// =================================================================
// --- SUBSCRIPTION & BOOKING MODULE ---
// =================================================================

void Member_subscription(Member members[], int loggedInIndex) {
    int subMenuChoice;
    do {
        system("cls");
        cout << "======================================================\n";
        cout << "            SUBSCRIPTION & BOOKING SYSTEM             \n";
        cout << "======================================================\n";
        cout << " User: " << members[loggedInIndex].name
            << " | ID: " << members[loggedInIndex].id << endl;
        cout << " Active Payment Info: " << members[loggedInIndex].paymentMethod << endl;
        cout << "------------------------------------------------------\n";
        displayUserBookings(members[loggedInIndex].id);
        cout << "------------------------------------------------------\n";
        cout << "1. Select Gym Plan (Triggers Payment)\n";
        cout << "2. Create Slot Booking\n";
        cout << "3. Modify Slot Booking\n";
        cout << "4. Search Bookings\n";
        cout << "5. Update Saved Payment Method\n";
        cout << "6. Back to Dashboard\n";
        cout << "Choice (1-6): ";
        cin >> subMenuChoice;

        switch (subMenuChoice) {
        case 1: add_service(members, loggedInIndex); break;
        case 2: create_booking(members[loggedInIndex].id, members[loggedInIndex].name); break;
        case 3: modify_booking(members[loggedInIndex].id, members[loggedInIndex].name); break;
        case 4: search_booking(); break;
        case 5: create_transaction(members, loggedInIndex); break;
        case 6: break;
        default: cout << "Invalid choice!\n"; break;
        }
    } while (subMenuChoice != 6);
}

void display_services(Member members[], int loggedInIndex) {
    int choice;
    system("cls");
    cout << "========================================\n";
    cout << "         Gym Services Menu              \n";
    cout << "========================================\n";
    cout << "1. Add Service\n";
    cout << "2. Remove Service\n";
    cout << "3. Back\n";
    cout << "Your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: add_service(members, loggedInIndex); break;
    case 2: removeservice(); break;
    case 3: break;
    default: cout << "Invalid option." << endl; break;
    }
}

void add_service(Member members[], int loggedInIndex) {
    system("cls");
    cout << "Select service type to add:\n";
    cout << "1. Personal Training\n";
    cout << "2. Coach Training\n";
    cout << "Your choice: ";
    int addservicechoice;
    cin >> addservicechoice;

    switch (addservicechoice) {
    case 1: personal(members, loggedInIndex); break;
    case 2: coach(members, loggedInIndex); break;
    default: cout << "Invalid choice." << endl; break;
    }
}

void personal(Member members[], int loggedInIndex) {
    int choice;
    system("cls");
    cout << "--- Personal Training Memberships ---\n";
    cout << "1. Monthly: RM50/month\n";
    cout << "2. Yearly: RM500/year\n";
    cout << "3. Lifetime: RM2000\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice >= 1 && choice <= 3) {
        cout << "\n[+] Plan selected! Moving directly to payment...\n";
        cout << "Press Enter to enter payment details...";
        cin.ignore(); cin.get();
        create_transaction(members, loggedInIndex);
    }
}

void coach(Member members[], int loggedInIndex) {
    int choice;
    system("cls");
    cout << "--- Coach Training Memberships ---\n";
    cout << "1. Monthly: RM80/month\n";
    cout << "2. Yearly: RM800/year\n";
    cout << "3. Lifetime: RM3500\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice >= 1 && choice <= 3) {
        cout << "\n[+] Plan selected! Moving directly to payment...\n";
        cout << "Press Enter to enter payment details...";
        cin.ignore(); cin.get();
        create_transaction(members, loggedInIndex);
    }
}

void removeservice() {
    system("cls");
    cout << "Please select the service you want to remove:\n";
    cout << "[Feature under construction]\n";
    cout << "\nPress Enter to return...";
    cin.ignore(); cin.get();
}

void create_transaction(Member members[], int loggedInIndex) {
    system("cls");
    int paymentChoice;
    char card_name[50], card_num[20], card_exp[10];

    cout << " ---------------------------------------" << endl;
    cout << "|     1. Credit Cards                   |" << endl;
    cout << "|     2. Debit Cards                    |" << endl;
    cout << "|     0. Exit Menu                      |" << endl;
    cout << " ---------------------------------------" << endl;
    cout << "Choose payment method: ";
    cin >> paymentChoice;
    cin.ignore();

    if (paymentChoice == 0) return;

    if (paymentChoice == 1 || paymentChoice == 2) {
        string cardType = (paymentChoice == 1) ? "Credit Card (" : "Debit Card (";

        cout << "Cardholder Name: ";
        cin.getline(card_name, 50);

        do {
            cout << "Masked Card Number (12-16 digits): ";
            cin.getline(card_num, 20);
            if (strlen(card_num) > 16 || strlen(card_num) < 12) {
                cout << "[!] Invalid number length.\n";
            }
        } while (strlen(card_num) > 16 || strlen(card_num) < 12);

        cout << "Expiry Date MM/YY: ";
        cin.getline(card_exp, 10);

        members[loggedInIndex].paymentMethod = cardType + string(card_num) + ")";

        cout << "\n[+] Payment method recorded successfully for User ID "
            << members[loggedInIndex].id << "!" << endl;
        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

// --- Booking System Functions ---

bool display_timetable(int userId, string userName) {
    time_t now = time(0);
    tm today = *localtime(&now);
    int currentHour = today.tm_hour;

    cout << "------- DATE -------" << endl;
    for (int i = 0; i < date_booking; i++) {
        cout << (i + 1) << ". " << dateSlot[i] << endl;
    }

    int booking_choice;
    cout << "\nChoose your date (1-7, or 0 to exit): ";
    cin >> booking_choice;

    if (booking_choice == 0) return false;

    int d = booking_choice - 1;
    if (d >= 0 && d < date_booking) {
        system("cls");
        cout << "\n----- Selected Date: " << dateSlot[d] << " -----" << endl;
        cout << "Slot           Time           Places Available" << endl;
        for (int i = 0; i < time_booking; i++) {
            bool isPast = (d == 0 && currentHour >= slotStartHours[i]);
            if (isPast) {
                cout << " " << i + 1 << ".     " << timeSlot[i] << "     [UNAVAILABLE - Passed]" << endl;
            }
            else {
                cout << " " << i + 1 << ".     " << timeSlot[i] << "     " << available_places[d][i] << " / " << MAX_PLACES << endl;
            }
        }

        int slot_choice;
        cout << "\nChoose your time slot (1-6, or 0 to exit): ";
        cin >> slot_choice;

        if (slot_choice == 0) return false;

        int t = slot_choice - 1;
        if (t >= 0 && t < time_booking) {
            bool isPast = (d == 0 && currentHour >= slotStartHours[t]);

            if (isPast) {
                cout << "\n[!] That time slot has already passed for today!" << endl;
            }
            else if (available_places[d][t] > 0) {
                int seat_index = MAX_PLACES - available_places[d][t];

                slot_bookings[d][t][seat_index].userId = userId;
                strncpy(slot_bookings[d][t][seat_index].name, userName.c_str(), 49);
                slot_bookings[d][t][seat_index].active = true;

                available_places[d][t]--;

                cout << "\n[+] Booking confirmed for " << userName
                    << " (ID: " << userId << ") on "
                    << dateSlot[d] << " at " << timeSlot[t] << endl;
            }
            else {
                cout << "\n[!] Fully Booked! No places available for this slot." << endl;
            }
        }
        else {
            cout << "\n[!] Invalid time slot choice." << endl;
        }
    }
    return true;
}

void create_booking(int userId, string userName) {
    system("cls");
    cout << "\n===== Create Booking =====\n";
    bool completed = display_timetable(userId, userName);

    if (completed) {
        cout << "\nPress Enter to return...";
        cin.ignore(1000, '\n');
        cin.get();
    }
}

void modify_booking(int userId, string userName) {
    system("cls");
    cout << "\n===== Modify Booking =====\n";
    int old_d, old_t;

    cout << "Enter current Date number (1-7, or 0 to cancel): ";
    cin >> old_d;
    if (old_d == 0) return;
    cout << "Enter current Time Slot number (1-6, or 0 to cancel): ";
    cin >> old_t;
    if (old_t == 0) return;

    old_d--; old_t--;

    if (old_d < 0 || old_d >= date_booking || old_t < 0 || old_t >= time_booking) {
        cout << "\n[!] Invalid date or slot choice!" << endl;
        return;
    }

    if (available_places[old_d][old_t] >= MAX_PLACES) {
        cout << "\n[!] No active bookings in that slot!" << endl;
        return;
    }

    available_places[old_d][old_t]++;
    cout << "\n[+] Slot canceled! Choose your new date & time slot below:\n" << endl;
    display_timetable(userId, userName);
}

void search_booking() {
    system("cls");
    cout << "\n========================================\n";
    cout << "             SEARCH BOOKINGS            \n";
    cout << "========================================\n";
    cout << "1. Search by Date & Time Slot\n";
    cout << "2. Search by User ID\n";
    cout << "Choice: ";

    int mode;
    cin >> mode;

    if (mode == 1) {
        int search_d, search_t;
        cout << "Enter Date number (1-7): "; cin >> search_d;
        cout << "Enter Time Slot (1-6): "; cin >> search_t;
        search_d--; search_t--;

        if (search_d >= 0 && search_d < date_booking && search_t >= 0 && search_t < time_booking) {
            cout << "\nBookings for " << dateSlot[search_d] << " [" << timeSlot[search_t] << "]:\n";
            int count = 1;
            for (int i = 0; i < MAX_PLACES; i++) {
                if (slot_bookings[search_d][search_t][i].active) {
                    cout << " " << count++ << ". Name: " << slot_bookings[search_d][search_t][i].name
                        << " | ID: " << slot_bookings[search_d][search_t][i].userId << endl;
                }
            }
            if (count == 1) cout << " (No bookings recorded)\n";
        }
    }
    else if (mode == 2) {
        int target_id;
        cout << "Enter User ID: "; cin >> target_id;
        bool found = false;

        for (int d = 0; d < date_booking; d++) {
            for (int t = 0; t < time_booking; t++) {
                for (int s = 0; s < MAX_PLACES; s++) {
                    if (slot_bookings[d][t][s].active && slot_bookings[d][t][s].userId == target_id) {
                        cout << "- Date: " << dateSlot[d] << " | Time: " << timeSlot[t]
                            << " | Name: " << slot_bookings[d][t][s].name << endl;
                        found = true;
                    }
                }
            }
        }
        if (!found) cout << "No active bookings found for ID " << target_id << endl;
    }

    cout << "\nPress Enter to continue...";
    cin.ignore(); cin.get();
}

// =================================================================
// --- TRAINER SCHEDULING MODULE (Module C) ---
// =================================================================

void runTrainerScheduling(Member members[], int loggedInIndex) {
    system("cls");
    cout << "--- Trainer Scheduling (Student C Module) ---\n";
    cout << "Logged in user: " << members[loggedInIndex].name << endl;
    cout << "Current Assigned Trainer: " << members[loggedInIndex].trainer << endl << endl;

    int choice;
    cout << "1. Coach Alex (Fitness)\n2. Coach Sarah (Strength)\nChoice: ";
    cin >> choice;
    if (choice == 1) members[loggedInIndex].trainer = "Coach Alex";
    else if (choice == 2) members[loggedInIndex].trainer = "Coach Sarah";

    cout << "\nTrainer assigned!\n";
    cout << "Press Enter to continue...";
    cin.ignore(); cin.get();
}
