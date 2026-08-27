#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

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


int main() {
    Member members[MAX_MEMBERS];
    int memberCount = 0;
    int portalChoice;
    fstream customer;
    customer.open("customer.txt", fstream::in);

    if (customer.is_open()) {

        while (memberCount < MAX_MEMBERS &&
            customer >> members[memberCount].id) {
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

                        while (cin.fail() || subChoice < 1 || subChoice > 5) {
                            cin.clear();
                            cin.ignore(100, '\n');
                            cout << "Invalid choice! Enter 1-5: ";
                            cin >> subChoice;
                        }

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
            } while (systemChoice != 4);
        }
    } while (portalChoice != 3);

    system("cls");
    cout << "Program exited successfully.\n";
    return 0;
}

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
        cout << "\033[2J\033[1;1H";
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
            cout << "\033[2J\033[1;1H";
            add_service(members, customermembership, count);
        }
        else if (choice == 2) {
            cout << "\033[2J\033[1;1H";
            cout << "You have selected remove service." << endl;
            removeservice(members, customermembership, count);
        }
        else if (choice == 3) {
            cout << "\033[2J\033[1;1H";
            cout << "You have selected upgrade service." << endl;
            upgrade_service(members, customermembership, count);

        }
        else if (choice == 4) {
            cout << "\033[2J\033[1;1H";
            cout << "You have selected renew service." << endl;
            renew_service(members, customermembership, count);
        }
        else if (choice == 5) {
            cout << "\033[2J\033[1;1H";
            cout << "You have selected display all service you own." << endl;
            customer_membership(members, customermembership, count);
        }
        else if (choice == 6) {
            return;
        }
        else {
            cout << "\033[2J\033[1;1H";
            cout << "Invalid choice. Please select a valid option." << endl;
            cin.clear();
            cin.ignore(100, '\n');
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
        cin.ignore(100, '\n');
        cout << "Invalid choice! Enter 1-2: ";
        cin >> addservicechoice;
    }

    switch (addservicechoice) {
    case 1:
        cout << "\033[2J\033[1;1H";
        personal(members, customermembership, count);
        break;
    case 2:
        cout << "\033[2J\033[1;1H";
        coach(members, customermembership, count);
        break;
   
    }
}

void personal(Member members[], int customermembership, int count) {
    int afteraddservice;

    cout << "\033[2J\033[1;1H";
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
    if (afteraddservice == 1) {
        cout << "Please proceed to pay" << endl;
        members[customermembership].personalmembership = "Monthly membership";
        saveAllMembersToFile(members, count);
        cin.get();
        return;
    }
    else if (afteraddservice == 2) {
        cout << "Please proceed to pay" << endl;
        members[customermembership].personalmembership = "Yearly membership";
        saveAllMembersToFile(members, count);
        return;
    }
    else if (afteraddservice == 3) {
        cout << "Please proceed to pay" << endl;
        members[customermembership].personalmembership = "Life time membership";
        saveAllMembersToFile(members, count);
        return;
    }
    else {
        cout << "\033[2J\033[1;1H";
        cout << "Invalid choice. Please select a valid option." << endl;
    }
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
        cin.ignore(100, '\n');
        cout << "Invalid choice! Enter 1-3: ";
        cin >> afteraddservice_coach;
    }
        if (afteraddservice_coach == 1) {
            cout << "Please proceed to pay" << endl;
            members[customermembership].coachmembership = "Monthly coach membership";
            saveAllMembersToFile(members, count);
            cin.get();
            return;


        }
        else if (afteraddservice_coach == 2) {
            cout << "Please proceed to pay" << endl;
            members[customermembership].coachmembership = "Yearly coach membership";
            saveAllMembersToFile(members, count);
            return;
        }
        else if (afteraddservice_coach == 3) {
            cout << "Please proceed to pay" << endl;
            members[customermembership].coachmembership = "Life time coach membership";
            saveAllMembersToFile(members, count);
            return;
        }
        else if (afteraddservice_coach <= 0 || afteraddservice_coach >= 4) {
            cout << "\033[2J\033[1;1H";
            cout << "Invalid choice. Please select a valid option." << endl;

        }

    }

void removeservice(Member members[], int customermembership, int count) {

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
                cout << "You don't have a Personal Training membership to remove.\n";
                cout << "Press Enter to return" << endl;
                cin.get();cin.ignore();
                

                return;
            }

            else {
                members[customermembership].personalmembership = "None";
                saveAllMembersToFile(members, count);
                system("cls");
                cout << "You have removed your personal membership" << endl;
                cout << "Press Enter to return" << endl;
                cin.get();cin.ignore();

                return;
            }
        }

        else if (removemembership == 2) {
            if (members[customermembership].coachmembership == "None") {
                system("cls");
                cout << "You don't have a Coach Training membership to remove." << endl;
                cout << "Press Enter to return" << endl;
                cin.get();cin.ignore();

                return;
            }
            else {
                members[customermembership].coachmembership = "None";
                saveAllMembersToFile(members, count);
                system("cls");
                cout << "You have removed your coach membership" << endl;
                cout << "Press Enter to return" << endl;
                cin.get();cin.ignore();

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
            cout << "You don't own any personal membership" << endl;
            cout << "Please press enter to choose again" << endl;
            cin.get();
            cin.ignore();
            goto back;

        }
        else if (members[customermembership].personalmembership == "Monthly membership") {
            system("cls");
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
            cout << "You don't own any coach membership" << endl;
            cout << "Please press enter to choose again" << endl;
            cin.get();
            cin.ignore();
            goto back;

        }
        else if (members[customermembership].coachmembership == "Monthly coach membership") {
            system("cls");
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
            cout << "Your membership is yearly right now" << endl;
            cout << "Would you like to upgrade to Life time coach membership?" << endl;
            cout << "press y for yes and n for no" << endl;
            cin >> coach_year_to_life;

            do {
                if (coach_year_to_life == 'y' || coach_year_to_life == 'Y') {
                    members[customermembership].coachmembership = "Life time coach membership";
                    saveAllMembersToFile(members, count);
                    system("cls");
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
    cout << "Please choose the membership you want to renew " << endl;
    cout << "----- Membership owned -----" << endl;
    cout << "1.Personal " << members[customermembership].personalmembership << endl;
    cout << "2.Coach " << members[customermembership].coachmembership << endl;
    cout << "3.Back to menu" << endl;
    cout << "Your Choice:";

    cin >> pick;
    if (pick == 1) {
        if (members[customermembership].personalmembership == "Monthly membership" || members[customermembership].personalmembership == "Yearly membership") {
            system("cls");
            cout << "Your Personal" << members[customermembership].personalmembership << " will be renew after paying the bills" << endl;
            cout << "Press Enter to proceed to pay" << endl;
            cin.get();
            cin.ignore();
        }

        else if (members[customermembership].personalmembership == "Life time membership") {
            system("cls");
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
            cout << "Your " << members[customermembership].coachmembership << " will be renew after paying the bills" << endl;
            cout << "Press Enter to proceed to pay" << endl;
            cin.get();
            cin.ignore();
        }

        else if (members[customermembership].coachmembership == "Life time coach membership") {
            system("cls");
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
    cout << "----- Membership owned by " << members[customermembership].name << "-----" << endl;
    cout << "Personal Membership: " << members[customermembership].personalmembership << endl;
    cout << "Coach Membership: " << members[customermembership].coachmembership << endl;
    cout << "Press Enter to return to menu" << endl;
    cin.get();
    cin.ignore();
    return;
}
