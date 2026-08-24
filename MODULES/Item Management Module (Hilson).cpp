#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_MEMBERS = 50;
const int MAX_SERVICES = 2;

struct Service {
    string serviceType;
    string planType;
    double price;
};

struct Member {
    int id;
    string name;
    string password;
    string paymentMethod;
    string trainer;
    Service ownedServices[MAX_SERVICES];
    int serviceCount;
};

// Function prototypes
void signUpMember(Member members[], int& count);
void updateMember(Member members[], int count);
void deleteMember(Member members[], int* count);
void searchMember(Member members[], int count);
void displayMembers(Member members[], int count);

void saveMembersToFile(const Member members[], int count);
void loadMembersFromFile(Member members[], int& count);

void display_services(Member& currentMember);
void add_service(Member& currentMember);
void personal(Member& currentMember);
void coach(Member& currentMember);
void remove_service(Member& currentMember);
void upgrade_or_renew_service(Member& currentMember);
void display_owned_services(const Member& currentMember);

void runTrainerScheduling(Member members[], int loggedInIndex);

// ================= MAIN FUNCTION =================
int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    Member members[MAX_MEMBERS];
    int memberCount = 0;

    loadMembersFromFile(members, memberCount);

    int portalChoice;

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
            saveMembersToFile(members, memberCount);
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

            int systemChoice;
            do {
                system("cls");
                cout << "===================================\n";
                cout << "        GYM MEMBERSHIP SYSTEM       \n";
                cout << "===================================\n";
                cout << "WELCOME " << members[userIndex].name << " (ID: " << members[userIndex].id << ")!!!\n\n";
                cout << "1. Member Management (Sub-Menu)\n";
                cout << "2. Member Subscription & Services\n";
                cout << "3. Trainer Scheduling\n";
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
                            saveMembersToFile(members, memberCount);
                            cout << "\nPress Enter to continue...";
                            cin.ignore(); cin.get();
                        }
                        else if (subChoice == 2) {
                            system("cls");
                            deleteMember(members, &memberCount);
                            saveMembersToFile(members, memberCount);
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
                    display_services(members[userIndex]);
                    saveMembersToFile(members, memberCount);
                }
                else if (systemChoice == 3) {
                    runTrainerScheduling(members, userIndex);
                    saveMembersToFile(members, memberCount);
                }
            } while (systemChoice != 4);
        }
    } while (portalChoice != 3);

    saveMembersToFile(members, memberCount);
    system("cls");
    cout << "Data saved. Program exited successfully.\n";
    return 0;
}

// ================= FILE I/O =================

void saveMembersToFile(const Member members[], int count) {
    ofstream outFile("members_data.txt");
    if (!outFile) {
        cout << "Error saving data to file!\n";
        return;
    }

    outFile << count << "\n";
    for (int i = 0; i < count; i++) {
        outFile << members[i].id << "\n";
        outFile << members[i].name << "\n";
        outFile << members[i].password << "\n";
        outFile << members[i].paymentMethod << "\n";
        outFile << members[i].trainer << "\n";

        outFile << members[i].serviceCount << "\n";
        for (int j = 0; j < members[i].serviceCount; j++) {
            outFile << members[i].ownedServices[j].serviceType << "\n";
            outFile << members[i].ownedServices[j].planType << "\n";
            outFile << members[i].ownedServices[j].price << "\n";
        }
    }
    outFile.close();
}

void loadMembersFromFile(Member members[], int& count) {
    ifstream inFile("members_data.txt");
    if (!inFile) {
        return;
    }

    inFile >> count;
    inFile.ignore();

    for (int i = 0; i < count; i++) {
        inFile >> members[i].id;
        inFile.ignore();
        getline(inFile, members[i].name);
        getline(inFile, members[i].password);
        getline(inFile, members[i].paymentMethod);
        getline(inFile, members[i].trainer);

        inFile >> members[i].serviceCount;
        inFile.ignore();

        for (int j = 0; j < members[i].serviceCount; j++) {
            getline(inFile, members[i].ownedServices[j].serviceType);
            getline(inFile, members[i].ownedServices[j].planType);
            inFile >> members[i].ownedServices[j].price;
            inFile.ignore();
        }
    }
    inFile.close();
}

// ================= MEMBER REGISTRATION & MANAGEMENT =================

void signUpMember(Member members[], int& count) {
    if (count >= MAX_MEMBERS) {
        cout << "Database is full! Cannot register more members.\n";
        return;
    }

    string username;
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
    members[count].serviceCount = 0;

    cout << "\n==================================================\n";
    cout << "           REGISTRATION SUCCESSFUL!               \n";
    cout << "==================================================\n";
    cout << "  Welcome to the gym, " << username << "!\n";
    cout << "  Your Member ID is: " << randomID << "\n";
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
            cout << "ID:       " << members[i].id << "\n";
            cout << "Name:     " << members[i].name << "\n";
            cout << "Payment:  " << members[i].paymentMethod << "\n";
            cout << "Trainer:  " << members[i].trainer << "\n";
            cout << "Services Owned: " << members[i].serviceCount << "\n";
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
        << setw(15) << "TRAINER"
        << setw(10) << "SERVICES" << endl;
    cout << "----------------------------------------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << members[i].id
            << setw(15) << members[i].name
            << setw(20) << members[i].paymentMethod
            << setw(15) << members[i].trainer
            << setw(10) << members[i].serviceCount << endl;
    }
}

// ================= SERVICE & SUBSCRIPTION MODULE =================

void display_services(Member& currentMember) {
    int choice;
    do {
        system("cls");
        cout << "--- Gym Membership Services ---\n";
        cout << "1. Add Service\n";
        cout << "2. Renew / Upgrade Service\n";
        cout << "3. Remove Service\n";
        cout << "4. Display All Services You Own\n";
        cout << "5. Back to Main Menu\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            add_service(currentMember);
            break;
        case 2:
            upgrade_or_renew_service(currentMember);
            break;
        case 3:
            remove_service(currentMember);
            break;
        case 4:
            display_owned_services(currentMember);
            cout << "\nPress Enter to return...";
            cin.ignore(); cin.get();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice! Press Enter to try again...";
            cin.ignore(); cin.get();
            break;
        }
    } while (choice != 5);
}

void add_service(Member& currentMember) {
    if (currentMember.serviceCount >= MAX_SERVICES) {
        cout << "You have reached the maximum service limit (" << MAX_SERVICES << ").\n";
        cout << "Press Enter to return...";
        cin.ignore(); cin.get();
        return;
    }

    system("cls");
    int addservicechoice;
    cout << "Select Service Type:\n";
    cout << "1. Personal Training\n";
    cout << "2. Coach Training\n";
    cout << "Your choice: ";
    cin >> addservicechoice;

    if (addservicechoice == 1) {
        personal(currentMember);
    }
    else if (addservicechoice == 2) {
        coach(currentMember);
    }
}

void personal(Member& currentMember) {
    int choice;
    cout << "\n--- Personal Training ---\n";
    cout << "1. Monthly Membership: RM50/month\n";
    cout << "2. Yearly Membership: RM500/year\n";
    cout << "3. Lifetime Membership: RM2000\n";
    cout << "Your choice: ";
    cin >> choice;

    Service s;
    s.serviceType = "Personal Training";

    if (choice == 1) { s.planType = "Monthly"; s.price = 50.0; }
    else if (choice == 2) { s.planType = "Yearly"; s.price = 500.0; }
    else if (choice == 3) { s.planType = "Lifetime"; s.price = 2000.0; }
    else { cout << "Invalid plan.\n"; return; }

    currentMember.ownedServices[currentMember.serviceCount] = s;
    currentMember.serviceCount++;

    cout << "Service added successfully! Total RM" << s.price << " paid.\n";
    cout << "Press Enter to continue...";
    cin.ignore(); cin.get();
}

void coach(Member& currentMember) {
    int choice;
    cout << "\n--- Coach Training ---\n";
    cout << "1. Monthly Membership: RM80/month\n";
    cout << "2. Yearly Membership: RM800/year\n";
    cout << "3. Lifetime Membership: RM3500\n";
    cout << "Your choice: ";
    cin >> choice;

    Service s;
    s.serviceType = "Coach Training";

    if (choice == 1) { s.planType = "Monthly"; s.price = 80.0; }
    else if (choice == 2) { s.planType = "Yearly"; s.price = 800.0; }
    else if (choice == 3) { s.planType = "Lifetime"; s.price = 3500.0; }
    else { cout << "Invalid plan.\n"; return; }

    currentMember.ownedServices[currentMember.serviceCount] = s;
    currentMember.serviceCount++;

    cout << "Service added successfully! Total RM" << s.price << " paid.\n";
    cout << "Press Enter to continue...";
    cin.ignore(); cin.get();
}

void upgrade_or_renew_service(Member& currentMember) {
    system("cls");
    if (currentMember.serviceCount == 0) {
        cout << "You have no active services to renew or upgrade.\n";
        cout << "Press Enter to return...";
        cin.ignore(); cin.get();
        return;
    }

    display_owned_services(currentMember);
    int selectedIndex;
    cout << "\nSelect the service number to Renew/Upgrade (1-" << currentMember.serviceCount << "): ";
    cin >> selectedIndex;

    if (selectedIndex < 1 || selectedIndex > currentMember.serviceCount) {
        cout << "Invalid service selection.\n";
        cout << "Press Enter to continue...";
        cin.ignore(); cin.get();
        return;
    }

    int targetIdx = selectedIndex - 1;
    Service& currentService = currentMember.ownedServices[targetIdx];

    cout << "\nSelected: " << currentService.serviceType << " (" << currentService.planType << ")\n";
    cout << "1. Renew current plan (" << currentService.planType << ")\n";
    cout << "2. Upgrade to a different plan\n";
    cout << "Your choice: ";
    int action;
    cin >> action;

    if (action == 1) {
        cout << "\nSuccessfully renewed " << currentService.serviceType << " (" << currentService.planType << ") for RM" << currentService.price << "!\n";
    }
    else if (action == 2) {
        cout << "\nSelect new plan level:\n";
        cout << "1. Monthly\n";
        cout << "2. Yearly\n";
        cout << "3. Lifetime\n";
        cout << "Choice: ";
        int planChoice;
        cin >> planChoice;

        if (currentService.serviceType == "Personal Training") {
            if (planChoice == 1) { currentService.planType = "Monthly"; currentService.price = 50.0; }
            else if (planChoice == 2) { currentService.planType = "Yearly"; currentService.price = 500.0; }
            else if (planChoice == 3) { currentService.planType = "Lifetime"; currentService.price = 2000.0; }
        }
        else if (currentService.serviceType == "Coach Training") {
            if (planChoice == 1) { currentService.planType = "Monthly"; currentService.price = 80.0; }
            else if (planChoice == 2) { currentService.planType = "Yearly"; currentService.price = 800.0; }
            else if (planChoice == 3) { currentService.planType = "Lifetime"; currentService.price = 3500.0; }
        }
        cout << "\nSuccessfully upgraded to " << currentService.planType << " plan (RM" << currentService.price << ")!\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore(); cin.get();
}

void remove_service(Member& currentMember) {
    system("cls");
    if (currentMember.serviceCount == 0) {
        cout << "You currently have no active services to remove.\n";
        cout << "Press Enter to return...";
        cin.ignore(); cin.get();
        return;
    }

    display_owned_services(currentMember);
    int removeIdx;
    cout << "\nEnter the number of the service to remove (1-" << currentMember.serviceCount << "): ";
    cin >> removeIdx;

    if (removeIdx >= 1 && removeIdx <= currentMember.serviceCount) {
        for (int i = removeIdx - 1; i < currentMember.serviceCount - 1; i++) {
            currentMember.ownedServices[i] = currentMember.ownedServices[i + 1];
        }
        currentMember.serviceCount--;
        cout << "Service removed successfully!\n";
    }
    else {
        cout << "Invalid service selection.\n";
    }
    cout << "Press Enter to continue...";
    cin.ignore(); cin.get();
}

void display_owned_services(const Member& currentMember) {
    cout << "\n--- Services Owned by " << currentMember.name << " ---\n";
    if (currentMember.serviceCount == 0) {
        cout << "No services registered.\n";
        return;
    }
    for (int i = 0; i < currentMember.serviceCount; i++) {
        cout << i + 1 << ". " << currentMember.ownedServices[i].serviceType
            << " (" << currentMember.ownedServices[i].planType << ") - RM"
            << currentMember.ownedServices[i].price << "\n";
    }
}

// ================= TRAINER SCHEDULING =================

void runTrainerScheduling(Member members[], int loggedInIndex) {
    system("cls");
    cout << "--- Trainer Scheduling ---\n";
    cout << "Logged in user: " << members[loggedInIndex].name << endl;
    cout << "Current Assigned Trainer: " << members[loggedInIndex].trainer << endl << endl;

    int choice;
    cout << "1. Coach Alex (Fitness)\n2. Coach Sarah (Strength)\nChoice: ";
    cin >> choice;
    if (choice == 1) members[loggedInIndex].trainer = "Coach Alex";
    else if (choice == 2) members[loggedInIndex].trainer = "Coach Sarah";

    cout << "\nTrainer assigned successfully!\n";
    cout << "Press Enter to continue...";
    cin.ignore(); cin.get();
}
