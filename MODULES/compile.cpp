#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

// function 1: add service
void Member_subscription(Member members[], int customermembership, int count);
void display_services(Member members[], int customermembership, int count);
void add_service(Member members[], int customermembership, int count);
void personal(Member members[], int customermembership, int count);
void coach(Member members[], int customermembership, int count);

// function 2: remove service
void removeservice();
void saveAllMembersToFile(const Member members[], int count) {
    ofstream customer("customer.txt", ios::trunc);
    if (customer.is_open()) {
        for (int i = 0; i < count; i++) {
            customer << members[i].id << endl;
            customer << members[i].name << endl;
            customer << members[i].password << endl;
            customer << members[i].membership << endl;
        }
        customer.close();
    }
}
// let user choose
void display_services(Member members[], int customermembership, int count) {
    int choice;

    cout << "Gym Membership Services" << endl;
    cout << "Please select a service" << endl;

    cout << "1. Add Service" << endl;
    cout << "2. Remove Service" << endl;
    cout << "3. Upgrade Service" << endl;
    cout << "4. Renew Service" << endl;
    cout << "5. Display all services you own" << endl;
    cout << "Your choice: ";

    
    do {
        cin >> choice;
        if (choice == 1) {
        cout << "\033[2J\033[1;1H";
        add_service(members, customermembership, count);
    }
        else if(choice == 2){ 
        cout << "\033[2J\033[1;1H";
        cout << "You have selected remove service." << endl;
            removeservice(members, customermembership, count);
        }
        else if (choice == 3) {
            cout << "\033[2J\033[1;1H";
            cout << "You have selected upgrade service." << endl;
        }
        else if (choice == 4) {
            cout << "\033[2J\033[1;1H";
            cout << "You have selected renew service." << endl;
        }
        else if  (choice == 5) {
            cout << "\033[2J\033[1;1H";
            cout << "You have selected display all service you own." << endl;
        }
        else {
            cout << "\033[2J\033[1;1H";
            cout << "Invalid choice. Please select a valid option." << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
     
    } while (choice <= 0 || choice >= 6);
}

// adding new serivce        
void add_service(Member members[], int customermembership, int count) {

    cout << "You have selected to add a new service." << endl;

    int addservicechoice;
    cout << "Please select the type of service you would like to add:" << endl;
    cout << "1. Personal Training" << endl;
    cout << "2. Coach Training" << endl;
    cout << "Your choice: ";
    cin >> addservicechoice;

    switch (addservicechoice) {
    case 1:
        cout << "\033[2J\033[1;1H";
        personal(members, customermembership, count);
        break;
    case 2:
        cout << "\033[2J\033[1;1H";
        coach(members, customermembership, count);
        break;
    default:
        cout << "\033[2J\033[1;1H";
        cout << "Invalid choice. Please select a valid option." << endl;
        break;
    }
}

void personal(Member members[], int customermembership, int count) {
    int afteraddservice;

    do {
        cout << "\033[2J\033[1;1H";
        cout << "You have selected to add Personal Training." << endl;
        cout << "Please choose your interested membership: " << endl;
        cout << "1. Monthly membership: RM50/month" << endl;
        cout << "2. Yearly membership: RM500/year" << endl;
        cout << "3. Life time membership: RM2000" << endl;
        cout << "Your choice: ";
        cin >> afteraddservice;
        // jmp to bill
        
        if (afteraddservice == 1) {
            cout << "Please proceed to pay" << endl;
            ofstream customer("customer", ios::app);
            if (customer.is_open())
                members[customermembership].membership = "Monthly coach membership";
            customer.close();
            if (!customer.is_open())
                cout << "cannot save membership";
        }
        else if (afteraddservice == 2) {
            cout << "Please proceed to pay" << endl;
            ofstream customer("customer", ios::app);
            if (customer.is_open())
                customer << yearly_membership << endl;
            customer.close();
            if (!customer.is_open())
                cout << "cannot save membership";
        }
        else if (afteraddservice == 3) {
            cout << "Please proceed to pay" << endl;
            ofstream customer("customer", ios::app);
            if (customer.is_open())
                customer << lifetime_membership << endl;
            customer.close();
            if (!customer.is_open())
                cout << "cannot save membership";
        }
        else if (afteraddservice <= 0 || afteraddservice >= 4) {
            cout << "\033[2J\033[1;1H";
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    } while (afteraddservice <= 0 || afteraddservice >= 4);
    
    

}

void coach(Member members[], int customermembership, int count) {
    int afteraddservice_coach;
 
    string monthly_coach_membership;
    string yearly_coach_membership;
    string lifetime_coach_membership;

    monthly_coach_membership = "Monthly coach membership";
    yearly_coach_membership = "Yearly coach membership";
    lifetime_coach_membership = "Life time coach membership";

    cout << "You have selected to add Coach Training." << endl;
    cout << "Please choose your interested membership: " << endl;
    cout << "1. Monthly membership: RM80/month" << endl;
    cout << "2. Yearly membership: RM800/year" << endl;
    cout << "3. Life time membership: RM3500" << endl;
    cout << "Your choice: ";
    // jmp to bill
    
    do {
        cin >> afteraddservice_coach;
        if (afteraddservice_coach == 1) {
            cout << "Please proceed to pay" << endl;
            ofstream customer("customer", ios::app);
            if (customer.is_open())
                customer << monthly_coach_membership << endl;
            customer.close();
            if (!customer.is_open())
                cout << "cannot save caoch membership";
        }
        else if (afteraddservice_coach == 2) {
            cout << "Please proceed to pay" << endl;
            ofstream customer("customer", ios::app);
            if (customer.is_open())
                customer << yearly_coach_membership << endl;
            customer.close();
            if (!customer.is_open())
                cout << "cannot save coach membership";
        }
        else if (afteraddservice_coach == 3) {
            cout << "Please proceed to pay" << endl;
            ofstream customer("customer", ios::app);
            if (customer.is_open())
                customer << lifetime_coach_membership << endl;
            customer.close();
            if (!customer.is_open())
                cout << "cannot save coach membership";
        }
        else if (afteraddservice_coach <= 0 || afteraddservice_coach >= 4) {
            cout << "\033[2J\033[1;1H";
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    } while (afteraddservice_coach <= 0 || afteraddservice_coach >= 4);
}

const int MAX_MEMBERS = 50;
const int MAX_SERVICES = 2;
struct membership {

    string monthly_coach_membership;
    string yearly_coach_membership;
    string lifetime_coach_membership;
    string monthly_membership;
    string yearly_membership;
    string lifetime_membership;


};
struct Member {
    int id;
    string name;
    string password;
    string paymentMethod; // ZIHIN
    string trainer;       // HILSON
    string membership;
};

// --- DYLAN RECORD MANAGEMENT MODULE
void signUpMember(Member members[], int& count);     // 1. Add Record (Pass by Reference) [5]
void updateMember(Member members[], int count);       // 2. Update Record (Pass by Value) [5]
void deleteMember(Member members[], int* count);      // 3. Delete Record (Pass by Pointer) [5]
void searchMember(Member members[], int count);       // 4. Search Record (Linear Search) [2]
void displayMembers(Member members[], int count);     // 5. Display All Records (with Bubble Sort) [2]

// --- Teammate Integration Placeholders ---
void Member_subscription();  // Student B's Module [6, 7]


int main() {
    Member members[MAX_MEMBERS];
    int memberCount = 0; // Tracks loaded and registered members
    int portalChoice;
    fstream customer;
    customer.open("customer.txt", fstream::in);

    if (customer.is_open()) {

        while (memberCount < MAX_MEMBERS &&
            customer >> members[memberCount].id) {
            customer.ignore();
            getline(customer, members[memberCount].name);
            getline(customer, members[memberCount].password);
            getline(customer, members[memberCount].membership);



            memberCount++;
        }
          customer.close();
}
    
    else {
       
        cout << "Failed to load file" << endl;
        cout << "Press Enter to continue...";
        cin.get();
    }

    srand(static_cast<unsigned int>(time(NULL)));

    // 2. Access Portal Loop
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

        // Input validation
        while (cin.fail() || portalChoice < 1 || portalChoice > 3) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid choice! Enter 1-3: ";
            cin >> portalChoice;
        }
        cin.ignore(); // Clear newline buffer

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

            // Linear search to verify user credentials
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

            // Dashboard Sub-menu
            int systemChoice;
            do {
                system("cls");
                cout << "===================================\n";
                cout << "        GYM MEMBERSHIP SYSTEM       \n";
                cout << "===================================\n";
                cout << "WELCOME " << members[userIndex].name << " (ID: " << members[userIndex].id << ")!!!\n\n";
                cout << "1. Member Management (Sub-Menu)\n";
                cout << "2. Member subscription (Teammate B Module)\n";
                cout << "3. Trainer Scheduling (Teammate C Module)\n";
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
                    Member_subscription();
                }
                //else if (systemChoice == 3) {
                //    runTrainerScheduling(members, userIndex);
                //}
            } while (systemChoice != 4);
        }
    } while (portalChoice != 3);

    system("cls");
    cout << "Program exited successfully.\n";
    return 0;
}

// Function 1: Sign Up (Add Record - Pass by Reference)
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
   
 



    // Inline duplicate username check [2]
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
    cin.ignore(); // Clear buffer [10]
    password = members[count].password;
    // Scale random 4-digit ID: rand() % ((max + 1) - min) + min [13]
    // max = 9999, min = 1000 -> rand() % 9000 + 1000
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

    // Save details to array [14]
    members[count].id = randomID;
    members[count].name = username;
    members[count].paymentMethod = "Not yet picked";
    members[count].trainer = "Not yet picked";
    
    ofstream customer("customer.txt", ios::app);
    if (customer.is_open()) {

        customer << randomID << endl;
        customer << username << endl;
        customer << password << endl;
        customer.close();
    }
    else cout << "customer details could not be saved sucessfully";
    // User-friendly display box for the randomized ID
    cout << "\n==================================================\n";
    cout << "            REGISTRATION SUCCESSFUL!              \n";
    cout << "==================================================\n";
    cout << "  Welcome to the gym, " << username << "!\n";
    cout << "  Your auto-generated 4-Digit Member ID is: " << randomID << "\n";
    cout << "  Write this ID down! You will need it to search  \n";
    cout << "  or update your profile details.                 \n";
    cout << "==================================================\n";

    count++; // Increment count
}

// Function 2: Update Record (Pass by Value)
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

// Function 3: Delete Record (Pass by Pointer)
void deleteMember(Member members[], int* count) {
    int searchID, foundIndex = -1;
    cout << "Enter Member ID to delete: ";
    cin >> searchID;

    // Use *count to get the value the pointer is pointing to [5]
    for (int i = 0; i < *count; i++) {
        if (members[i].id == searchID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Shift remaining array items left to delete the index [15]
        for (int i = foundIndex; i < (*count) - 1; i++) {
            members[i] = members[i + 1];
        }
        (*count)--; // Lower the actual count via pointer
        cout << "Member record deleted successfully.\n";
    }
    else {
        cout << "Member ID not found.\n";
    }
}

// Function 4: Search Record (Linear Search)
void searchMember(Member members[], int count) {
    int searchID;
    cout << "Enter Member ID to search: ";
    cin >> searchID;

    // Linear Search [2]
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

// Function 5: Display All Records (with Bubble Sort)
void displayMembers(Member members[], int count) {
    if (count == 0) {
        cout << "No registered members yet.\n";
        return;
    }

    // Sort by ID using a clean Bubble Sort before displaying [2, 16]
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (members[j].id > members[j + 1].id) {
                Member temp = members[j]; // [17]
                members[j] = members[j + 1];
                members[j + 1] = temp;
            }
        }
    }

    // Display tabular layout using iomanip [18]
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
// --- Teammate Integration Placeholders ---
// =================================================================

void Member_subscription(Member members[], int customermembership, int count) {
    system("cls");
    display_services(members,customermembership,count);
}

//void runTrainerScheduling(Member members[], int loggedInIndex) {
//    system("cls");
//    cout << "--- Trainer Scheduling (Student C Module) ---\n";
//    cout << "Logged in user: " << members[loggedInIndex].name << endl;
//    cout << "Current Assigned Trainer: " << members[loggedInIndex].trainer << endl << endl;
//
//    int choice;
//    cout << "1. Coach Alex (Fitness)\n2. Coach Sarah (Strength)\nChoice: ";
//    cin >> choice;
//    if (choice == 1) members[loggedInIndex].trainer = "Coach Alex";
//    else if (choice == 2) members[loggedInIndex].trainer = "Coach Sarah";
//
//    cout << "\nTrainer assigned by Teammate C's Logic!\n";
//    cout << "Press Enter to continue...";
//    cin.ignore(); cin.get();
//}

void removeservice(Member members[], int customermembership, int count) {
    cout << "Please select the services you want to remove;" << endl;
}
