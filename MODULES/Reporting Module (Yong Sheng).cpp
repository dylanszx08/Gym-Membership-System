#include <iostream>
#include <string>

using namespace std;


// =================================
// Structure
// =================================

struct Member
{
    string memberID;
    string name;
    int age;
    string membershipType;
    string status;
    double fee;
};



// =================================
// Global Variables
// =================================

Member members[100];

int memberCount = 0;



// =================================
// Function Declaration
// =================================

void mainMenu();

void reportingMenu();

void generateSummaryReport();

void generateDetailedReport();

void calculateStatistics();

void sortRecords();

void displayAnalysis();




// =================================
// Main Function
// =================================

int main()
{

    // Sample Member Data

    members[0] =
    {
        "M001",
        "Jason",
        20,
        "Monthly",
        "Active",
        100
    };


    members[1] =
    {
        "M002",
        "Alice",
        22,
        "Annual",
        "Active",
        900
    };


    members[2] =
    {
        "M003",
        "Kevin",
        25,
        "Monthly",
        "Expired",
        100
    };


    members[3] =
    {
        "M004",
        "Mary",
        21,
        "Annual",
        "Active",
        900
    };


    members[4] =
    {
        "M005",
        "David",
        28,
        "Monthly",
        "Expired",
        100
    };


    memberCount = 5;



    mainMenu();



    return 0;
}






// =================================
// Main Menu
// =================================

void mainMenu()
{

    int choice;


    do
    {

        cout << "\n====================================\n";
        cout << "       GYM MEMBERSHIP SYSTEM        \n";
        cout << "====================================\n";


        cout << "1. Reporting Module\n";

        cout << "2. Exit\n";


        cout << "\nEnter your choice: ";

        cin >> choice;



        switch(choice)
        {

            case 1:

                reportingMenu();

                break;


            case 2:

                cout << "\nSystem Exit...\n";

                break;


            default:

                cout << "\nInvalid Choice!\n";

        }


    }while(choice != 2);


}






// =================================
// Reporting Menu
// =================================

void reportingMenu()
{

    int choice;


    do
    {

        cout << "\n====================================\n";
        cout << "          REPORTING MODULE          \n";
        cout << "====================================\n";


        cout << "1. Generate Summary Report\n";

        cout << "2. Generate Detailed Report\n";

        cout << "3. Calculate Statistics\n";

        cout << "4. Sort Records\n";

        cout << "5. Display Analysis\n";

        cout << "6. Back\n";


        cout << "\nEnter your choice: ";

        cin >> choice;



        switch(choice)
        {

            case 1:

                generateSummaryReport();

                break;


            case 2:

                generateDetailedReport();

                break;


            case 3:

                calculateStatistics();

                break;


            case 4:

                sortRecords();

                break;


            case 5:

                displayAnalysis();

                break;


            case 6:

                cout << "\nBack to main menu...\n";

                break;


            default:

                cout << "\nInvalid Choice!\n";

        }



    }while(choice != 6);


}





// =================================
// Temporary Functions
// They will be completed in Part 2 & 3
// =================================


void generateSummaryReport()
{

    int activeMembers = 0;
    int expiredMembers = 0;

    int monthlyMembers = 0;
    int annualMembers = 0;

    double totalRevenue = 0;



    for(int i = 0; i < memberCount; i++)
    {

        // Count Active and Expired Members

        if(members[i].status == "Active")
        {
            activeMembers++;
        }
        else if(members[i].status == "Expired")
        {
            expiredMembers++;
        }



        // Count Membership Type

        if(members[i].membershipType == "Monthly")
        {
            monthlyMembers++;
        }
        else if(members[i].membershipType == "Annual")
        {
            annualMembers++;
        }



        // Calculate Revenue

        totalRevenue += members[i].fee;

    }



    cout << "\n====================================\n";
    cout << "          SUMMARY REPORT            \n";
    cout << "====================================\n";


    cout << "Total Members       : "
         << memberCount << endl;


    cout << "Active Members      : "
         << activeMembers << endl;


    cout << "Expired Members     : "
         << expiredMembers << endl;


    cout << "Monthly Members     : "
         << monthlyMembers << endl;


    cout << "Annual Members      : "
         << annualMembers << endl;


    cout << "Total Revenue       : RM"
         << totalRevenue << endl;


    cout << "====================================\n";

}



void generateDetailedReport()
{

    cout << "\n=================================================\n";
    cout << "              DETAILED REPORT                    \n";
    cout << "=================================================\n";


    cout << "ID\tName\tAge\tPlan\tStatus\tFee\n";


    cout << "-------------------------------------------------\n";



    for(int i = 0; i < memberCount; i++)
    {


        cout << members[i].memberID << "\t";

        cout << members[i].name << "\t";

        cout << members[i].age << "\t";

        cout << members[i].membershipType << "\t";

        cout << members[i].status << "\t";

        cout << "RM" << members[i].fee;


        cout << endl;

    }



    cout << "=================================================\n";

}



void calculateStatistics()
{

    double totalFee = 0;


    double highestFee = members[0].fee;

    double lowestFee = members[0].fee;


    int activeCount = 0;



    for(int i = 0; i < memberCount; i++)
    {


        // Calculate total fee

        totalFee += members[i].fee;



        // Find highest fee

        if(members[i].fee > highestFee)
        {
            highestFee = members[i].fee;
        }



        // Find lowest fee

        if(members[i].fee < lowestFee)
        {
            lowestFee = members[i].fee;
        }



        // Count active member

        if(members[i].status == "Active")
        {
            activeCount++;
        }


    }



    double averageFee = totalFee / memberCount;



    double activePercentage =
        (double)activeCount / memberCount * 100;



    cout << "\n====================================\n";
    cout << "        STATISTICS REPORT            \n";
    cout << "====================================\n";


    cout << "Average Membership Fee : RM"
         << averageFee << endl;



    cout << "Highest Membership Fee : RM"
         << highestFee << endl;



    cout << "Lowest Membership Fee  : RM"
         << lowestFee << endl;



    cout << "Active Member Rate     : "
         << activePercentage
         << "%" << endl;



    cout << "====================================\n";


}



void sortRecords()
{

    int choice;


    cout << "\n====================================\n";
    cout << "          SORT RECORDS               \n";
    cout << "====================================\n";


    cout << "1. Sort by Name\n";

    cout << "2. Sort by Membership Fee\n";


    cout << "\nEnter your choice: ";

    cin >> choice;



    // Bubble Sort

    for(int i = 0; i < memberCount - 1; i++)
    {

        for(int j = 0; j < memberCount - i - 1; j++)
        {


            bool swapNeeded = false;



            // Sort Name A-Z

            if(choice == 1)
            {

                if(members[j].name > members[j+1].name)
                {
                    swapNeeded = true;
                }

            }



            // Sort Fee Low-High

            else if(choice == 2)
            {

                if(members[j].fee > members[j+1].fee)
                {
                    swapNeeded = true;
                }

            }




            if(swapNeeded)
            {

                Member temp = members[j];


                members[j] = members[j+1];


                members[j+1] = temp;

            }


        }

    }



    cout << "\nRecords sorted successfully!\n";



    // Display sorted result

    cout << "\n====================================\n";
    cout << "          SORTED RECORDS             \n";
    cout << "====================================\n";


    cout << "ID\tName\tPlan\tFee\n";


    for(int i = 0; i < memberCount; i++)
    {

        cout << members[i].memberID << "\t";

        cout << members[i].name << "\t";

        cout << members[i].membershipType << "\t";

        cout << "RM" << members[i].fee << endl;

    }


    cout << "====================================\n";


}


void displayAnalysis()
{

    int monthlyCount = 0;
    int annualCount = 0;


    double monthlyRevenue = 0;
    double annualRevenue = 0;


    int activeCount = 0;
    int expiredCount = 0;



    for(int i = 0; i < memberCount; i++)
    {


        // Count Membership Type

        if(members[i].membershipType == "Monthly")
        {
            monthlyCount++;

            monthlyRevenue += members[i].fee;
        }



        else if(members[i].membershipType == "Annual")
        {
            annualCount++;

            annualRevenue += members[i].fee;
        }




        // Count Status

        if(members[i].status == "Active")
        {
            activeCount++;
        }


        else if(members[i].status == "Expired")
        {
            expiredCount++;
        }


    }




    cout << "\n====================================\n";
    cout << "          MEMBER ANALYSIS            \n";
    cout << "====================================\n";



    // Most Popular Plan

    cout << "\nMost Popular Membership Plan: ";


    if(monthlyCount > annualCount)
    {
        cout << "Monthly";
    }


    else if(annualCount > monthlyCount)
    {
        cout << "Annual";
    }


    else
    {
        cout << "Both are Equal";
    }





    // Revenue Analysis

    cout << "\n\nMembership Revenue Analysis\n";

    cout << "Monthly Revenue : RM"
         << monthlyRevenue << endl;


    cout << "Annual Revenue  : RM"
         << annualRevenue << endl;



    cout << "\nHighest Revenue Plan: ";



    if(monthlyRevenue > annualRevenue)
    {
        cout << "Monthly";
    }


    else if(annualRevenue > monthlyRevenue)
    {
        cout << "Annual";
    }


    else
    {
        cout << "Same Revenue";
    }





    // Status Analysis

    cout << "\n\nMember Status Analysis\n";


    cout << "Active Members  : "
         << activeCount << endl;


    cout << "Expired Members : "
         << expiredCount << endl;



    cout << "\n====================================\n";


}
