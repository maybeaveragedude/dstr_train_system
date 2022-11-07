#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>
#include "station.h"
#include "purchaseQueue.h"
#include "member.h"

#include "payment.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;

StationNode *head = NULL;
StationDLL station;
PaymentNode *payment_head = NULL;
PaymentList pList;
PurchaseQueue purchase_queue(10);
MemberDLL memberList;

void menu_adminHome(string role);
void menu_paymentSearch_option();
string estimated_time(int hour, int minute, int duration);

// for initialising the data in the program (station, payment, member)
void insertDummyData()
{
    // Add stations

    // header,
    // station id,
    // station name,
    // previous station id,
    // previous station name,
    // distance to previous station
    station.newStation_FinalPos(&head, "SS01", "Titiwangsa", "N/A", "N/A", 0);
    station.newStation_FinalPos(&head, "SS02", "PTWC", "SS01", "Titiwangsa", 4);
    station.newStation_FinalPos(&head, "SS03", "Sultan Ismail", "SS02", "PTWC", 8);
    station.newStation_FinalPos(&head, "SS04", "Majlis Jamek", "SS03", "Sultan Ismail", 8);
    station.newStation_FinalPos(&head, "SS05", "Plaza Rakyat", "SS04", "Majlis Jamek", 6);
    station.newStation_FinalPos(&head, "SS06", "Hang Tuah", "SS05", "Plaza Rakyat", 10);
    station.newStation_FinalPos(&head, "SS07", "Pudu", "SS06", "Hang Tuah", 5);
    station.newStation_FinalPos(&head, "SS08", "Chan Sow Lin", "SS07", "Pudu", 5);

    // Add default users

    // username,
    // password,
    // first name,
    // last name,
    // role

    memberList.newUser("admin", "123", "Shawn", "Lee", "admin");
    memberList.newUser("admin2", "123", "Vanessa", "Teng", "admin");
    memberList.newUser("admin3", "123", "Clement", "Ho", "admin");
    memberList.newUser("admin4", "123", "Qiu", "Teng", "admin");
    memberList.newUser("user1", "123", "User", "Test", "member");
    memberList.newUser("user2", "123", "Pill", "Cosby", "member");
    memberList.newUser("user3", "123", "Mike", "Hawk", "member");
    memberList.newUser("user4", "123", "Chris", "Peacock", "member");

    // Set variable for current date & time
    time_t now = time(0);
    char *today = ctime(&now);

    // Add payment

    // payment node head
    // username
    // first name
    // last name
    // ic no.
    // departure station id
    // departure station name
    // arrival station id
    // arrival station name
    // ticket amount
    // duration
    // transaction date
    // departure time

    pList.newPayment(&payment_head, "user1", "User", "Test", "0114721554", "SS02", "PWTC", "SS07", "Pudu", 3.7, 37, today, "4:20 PM");
    pList.newPayment(&payment_head, "user1", "User", "Test", "0112472554", "SS04", "Majlis Jamek", "SS08", "Chan Sow Lin", 2.6, 26, today, "3:30 PM");
    pList.newPayment(&payment_head, "user2", "Pill", "Cosby", "0194425582", "SS05", "Plaza Rakyat", "SS02", "PWTC", 2.2, 22, today, "8:10 AM");
    pList.newPayment(&payment_head, "user2", "Pill", "Cosby", "0194425582", "SS04", "Majlis Jamek", "SS06", "Hang Tuah", 1.6, 16, today, "10:30 PM");
    pList.newPayment(&payment_head, "user3", "Mike", "Hawk", "0163335481", "SS05", "Plaza Rakyat", "SS04", "Majlis Jamek", 0.6, 6, today, "5:20 PM");
    pList.newPayment(&payment_head, "user3", "Mike", "Hawk", "0163335481", "SS03", "Sultan Ismail", "SS05", "Plaza Rakyat", 1.4, 14, today, "9:20 AM");
    pList.newPayment(&payment_head, "user4", "Chris", "Peacock", "0112721554", "SS01", "Titiwangsa", "SS08", "Chan Sow Lin", 4.6, 46, today, "5:50 PM");
    pList.newPayment(&payment_head, "user4", "Chris", "Peacock", "0112721554", "SS01", "Titiwangsa", "SS02", "PWTC", 0.4, 4, today, "6:00 PM");

    purchase_queue.enqueue("queueUser1", 4);
    purchase_queue.enqueue("queueUser2", 3);
    purchase_queue.enqueue("queueUser3", 2);
}

// pragma for StationList class (extra functions)
//  function:
//  1. menu_admin
#pragma region StationList
void StationDLL::menu_admin(StationNode *hd)
{
    int userMenuIn;
    cout << "\nHello, Admin." << endl;
    cout << "================== MAIN MENU ==================" << endl;
    cout << "\nBrowse\n--------\n[1] Browse All Stations\n[2] Browse Station Details\n\nCRUD\n--------\n[3] Add a new station\n\n[4] Exit\n";
    cout << "===============================================" << endl;
    cout << "Menu Selection:  ";
    cin >> userMenuIn;
    // If menu doesnt exist

    switch (userMenuIn)
    {
    case 1:
        return viewStations(hd, "admin");
        break;
    case 2:
        return viewStation_details(hd, "admin");

        break;
    case 3:
        int directionMenuIn;
        cout << "*========= DIRECTION =========*\n";
        cout << "[1] Front\n[2] End\n";
        cout << "*=============================*\n";
        cout << "Menu Selection:  ";
        cin >> directionMenuIn;

        switch (directionMenuIn)
        {
        case 1:
            form_newStn_FstPos(hd, "", "", 0);

            break;
        case 2:
            form_newStn_FinPos(hd, "", "", 0);

            break;
        default:
            cout << "\nInvalid option, please select again.\n"
                 << endl;
            return menu_admin(hd);
            break;
        }

        break; // breaking case 3
    case 4:

        cout << "Thank you, have a good day.";
        EXIT_SUCCESS;
        break;
    default:
        cout << "\nInvalid option, please select again. \n";
        return menu_admin(hd);
        break;
    }

    return;
}
#pragma endregion

// pragma for MemberList class (extra functions)
//  function:
//  1. loginUser
#pragma region MemberList
void MemberDLL::loginUser(StationNode *hd, StationDLL st)

{
    string usr, pwd;
    cout << "\nPlease enter your Username : ";
    cin >> usr;
    cout << "Please enter your Password : ";
    cin >> pwd;

    // int res = ValidateLogin(usr, pwd);
    int res = checkLogin(usr, pwd);

    if (res == 1)
    {
        return menu_adminHome("admin");
    }
    else if (res == 2)
    {
        return menu_adminHome(usr);
    }
    cout << "Username or Password is incorrect!\n";
    return loginUser(hd, st);
}
#pragma endregion

// pragma for PaymentList class (extra functions)
//  functions:
//  1. menu_admin
//  2. menu_purchase
//  3. menu_ticketSummary
//  4. form_editPayment

#pragma region PaymentList
void PaymentList::menu_admin(PaymentNode *payment_head)
{
    int userMenuIn;
    cout << "\nWelcome back, Admin." << endl;
    cout << "================= PAYMENT MENU =================" << endl;
    cout << "\nBrowse\n--------\n[1] Browse Payments\n[2] Search Payments List\n\n[3] Exit\n";
    cout << "\n================================================" << endl;
    cout << "\nMenu Selection:  ";
    cin >> userMenuIn;
    // If userMenuIn is outside the range of optioons
    string searchSel = "";
    string searchVal = "";
    switch (userMenuIn)
    {
    case 1:
        return getAllPayments(payment_head, "admin");

        break;
    case 2:

        menu_paymentSearch_option();
        cin >> searchSel;
        // cout << "Search (Exp: PWTC) : ";
        if (searchSel == "6")
            return menu_admin(payment_head);
        if (searchSel == "1")
        {
            cout << "Search (Exp: user1) : ";
            cin >> searchVal;

            searchPayment(payment_head, "admin", "username", searchVal);
        }
        if (searchSel == "2")
        {
            cout << "Search (Exp: Shawn) : ";
            cin >> searchVal;

            searchPayment(payment_head, "admin", "firstName", searchVal);
        }
        if (searchSel == "3")
        {
            cout << "Search (Exp: Lee) : ";
            cin >> searchVal;

            searchPayment(payment_head, "admin", "lastName", searchVal);
        }
        if (searchSel == "4")
        {
            cout << "Search (Exp: PWTC) : ";
            cin >> searchVal;

            searchPayment(payment_head, "admin", "startStation", searchVal);
        }
        if (searchSel == "5")
        {
            cout << "Search (Exp: PWTC) : ";
            cin >> searchVal;

            searchPayment(payment_head, "admin", "endStation", searchVal);
        }
        break;
    case 3:

        cout << "Thank you, have a good day.";
        EXIT_SUCCESS;
        break;
    default:
        cout << "\nMenu doesn't exist, try again. \n";
        return menu_admin(payment_head);
        break;
    }
    return;
}

void PaymentList::menu_purchase(PaymentNode *hd, string usr)
{
    int userMenuIn;
    string direction, start_stationID, endStID;
    bool valid;

    cout << "\nSelect a route" << endl;
    cout << "=========================== MAIN MENU ===========================" << endl;
    cout << "\n[1] Titiwangsa -> Chan Sow Lin\n[2] Chan Sow Lin -> Titiwangsa\n[3] Cancel\n";
    cout << "\n=================================================================" << endl;
    cout << "Menu Selection:  ";
    cin >> userMenuIn;

    switch (userMenuIn)
    {
    case 1:
        direction = "Forward";
        break;
    case 2:
        direction = "Backward";
        break;

    case 3: 
        return menu_member(hd, usr);

    default:
        cout << "\nInvalid option, please select again. \n";
        return menu_purchase(hd, usr);
        break;
    }

    station.viewStations(head, "member", direction);

    // enter start station ID
    cout << "Select your departure station (exp: SS02): ";
    cin >> start_stationID;
    valid = station.checkExist_stationID(head, start_stationID);
    if (!valid)
    {
        cout << "Invalid Station ID!";
        return menu_purchase(hd, usr);
    }
    // enter destination station ID
    cout << "Select your destination station (exp: SS04): ";
    cin >> endStID;
    valid = station.checkExist_stationID(head, endStID);
    if (!valid)
    {
        cout << "Invalid Station ID!";
        return menu_purchase(hd, usr);
    }
    menu_ticketSummary(hd, usr, start_stationID, endStID, direction);
    return menu_member(hd, usr);
}

void PaymentList::menu_ticketSummary(PaymentNode *payment_head, string usr, string start_stationID, string endStID, string direction)
{
    PaymentNode *curr = payment_head;
    StationNode *sCurr = head;
    string startName, endName;
    int dur = station.calc_travel_duration(head, start_stationID, endStID, direction);
    double cost = station.calc_travel_cost(head, start_stationID, endStID, direction);

    // Set variable for current date & time
    time_t now = time(0);
    char *today = ctime(&now);

    // traverse to end of
    while (curr->next != NULL)
        curr = curr->next;

    while (true)
    {
        if (sCurr == NULL)
            break;
        if (start_stationID == sCurr->station_id)
        {
            startName = sCurr->station_name;
        }
        if (endStID == sCurr->station_id)
        {
            endName = sCurr->station_name;
        }

        sCurr = sCurr->next;
    }

    int size = getSize(payment_head);
    int page = 1, input = 0, tId = 0;

    try
    {
        tId = stoi(curr->payment_id);
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Error converting string to int, please enter whole numbers\n";
        return menu_ticketSummary(payment_head, usr, start_stationID, endStID, direction);
    }
    cout << "\nReview Station Selection and Details Below";
    cout << "\n======================== Purchase Details ========================\n";
    cout << left << setw(30) << "Departure Station ID : " << start_stationID << endl;
    cout << left << setw(30) << "Departure Station Name : " << startName << endl;
    cout << left << setw(30) << "Destination Station ID : " << endStID << endl;
    cout << left << setw(30) << "Destination Station Name : " << endName << endl;
    cout << left << setw(30) << "Estimated Travel Duration : " << dur << " minutes" << endl;
    cout << left << setw(30) << "Ticket Cost : "
         << "RM " << cost << endl;
    cout << "=====================================================================\n"
         << endl;

    cout << "[1] to Proceed With Purchase" << endl;
    cout << "[R] to Return to Menus" << endl;
    cout << "\nMenu Selection:  ";
    int userMenuIn = 0;
    cin >> userMenuIn;
    cin.ignore();
    if (userMenuIn != 1)
    {
        return menu_purchase(payment_head, usr);
    }

    string dept, first, last, id;

    cout << "\nEnter Your Departure Time (06:00AM to 01:00AM format)\nInput >> ";
    getline(cin, dept);

    cout << "\nEnter your First Name\nInput >> ";
    getline(cin, first);

    cout << "\nEnter your Last Name\nInput >> ";
    getline(cin, last);

    cout << "\nEnter your Identification Number\nInput >> ";
    getline(cin, id);

    cout << "\n========================New Ticket========================\n";
    cout << left << setw(30) << "Ticket ID : " << tId + 1 << endl;
    cout << left << setw(30) << "Username : " << usr << endl;
    cout << left << setw(30) << "First Name : " << first << endl;
    cout << left << setw(30) << "Last Name : " << last << endl;
    cout << left << setw(30) << "Identification Number : " << id << endl;
    cout << left << setw(30) << "Departure Station ID : " << start_stationID << endl;
    cout << left << setw(30) << "Departure Station Name : " << startName << endl;
    cout << left << setw(30) << "Destination Station ID : " << endStID << endl;
    cout << left << setw(30) << "Destination Station Name : " << endName << endl;
    cout << left << setw(30) << "Estimated Travel Duration : " << dur << " minutes" << endl;
    cout << left << setw(30) << "Departure Time: " << dept << endl;
    cout << left << setw(30) << "Ticket Cost : "
         << "RM " << cost << endl;
    cout << left << setw(30) << "Time created : " << today << endl;
    cout << "============================================================\n"
         << endl;

    // TODO: add purchase queue buffer here

    cout << "[1] to Enter Purchase Queue" << endl;
    cout << "[C] to Cancel Purchase" << endl;
    cout << "\nMenu Selection:  ";
    cin >> input;

    if (input == 1)
    {

        // add user to purchase queue
        purchase_queue.enqueue(usr, tId);
        cout << "You have been added to the purchase queue. Please wait for your turn to purchase.\n";
        // purchase_queue.getPosition(usr);

        while (purchase_queue.getPositionValue(usr) > 1)
        {
            purchase_queue.dequeue();
            purchase_queue.getPosition(usr);
            sleep_for(1s);
        }

        pList.newPayment(&payment_head, usr, first, last, id, start_stationID, startName, endStID, endName, cost, dur, today, dept);
        cout << "\nSuccessfully Purchased A New Ticket!\n";
        return menu_member(payment_head, usr);
    }

    return menu_member(payment_head, usr);
}

void PaymentList::form_editPayment(PaymentNode *hd, PaymentNode *curr)
{
    // Set variable for current date & time
    time_t now = time(0);
    char *today = ctime(&now);

    string newStartID, newEndID, direction, newDeparture;
    int newDuration = 0, userMenuIn = 0;
    double newCost = 0, prevCost = 0;

    StationNode *currNew = head;

    // Select new line direction
    cout << "\nSelect the new direction for the ticket" << endl;
    cout << "================ PAYMENT EDITING FORM MENU ================" << endl;
    cout << "\n[1] Titiwangsa -> Chan Sow Lin\n[2] Chan Sow Lin -> Titiwangsa\n[3] Cancel\n";
    cout << "===========================================================" << endl;
    cout << "\nMenu Selection:  ";
    cin >> userMenuIn;
    if (userMenuIn == 1)
    {
        direction = "Forward";
    }
    if (userMenuIn == 2)
    {
        direction = "Backward";
    }

    cout << "Update starting station ID, use UNDERSCORE as space [Original:  " << curr->departure_stn_id << "] : ";
    cin >> newStartID;
    replace(newStartID.begin(), newStartID.end(), '_', ' ');

    // Traverse list to get station Name
    while (currNew != NULL && currNew->station_id != newStartID)
    {
        if (currNew == NULL)
        {
            cout << "No such station!";
            return form_editPayment(hd, curr);
        }
        currNew = currNew->next;
    }

    // declare new vars for new starting name
    string newStartName = currNew->station_name;
    cout << "\nNew start station is " << newStartID << ", " << newStartName << endl;

    // reset currNew list
    currNew = head;

    cout << "Update ending station ID, use UNDERSCORE as space [Original:  " << curr->destination_stn_id << "] : ";
    cin >> newEndID;
    replace(newEndID.begin(), newEndID.end(), '_', ' ');

    // Traverse list to get station name
    while (currNew != NULL && currNew->station_id != newEndID)
    {
        if (currNew == NULL)
        {
            cout << "Station not found!";
            return form_editPayment(hd, curr);
        }
        currNew = currNew->next;
    }

    // declare new vars for new starting name
    string newEndName = currNew->station_name;
    cout << "\nNew destination station is " << newEndID << ", " << newEndName << endl;

    cout << "Update departure time [Original:  " << curr->departure_time << "] : ";
    cin >> newDeparture;

    newCost = station.calc_travel_cost(head, newStartID, newEndID, direction);
    if (newCost == 0)
    {
        cout << "Error calculating cost! Please try again." << endl;
        return form_editPayment(hd, curr);
    }

    newDuration = station.calc_travel_duration(head, newStartID, newEndID, direction);
    if (newDuration == 0)
    {
        cout << "Error calculating duration! Please try again." << endl;
        return form_editPayment(hd, curr);
    }

    cout << "\n======================== TICKET SUMMARY ========================\n";
    cout << left << setw(30) << "Ticket ID : " << curr->payment_id << endl;
    cout << left << setw(30) << "Username : " << curr->user_name << endl;
    cout << left << setw(30) << "First Name : " << curr->f_name << endl;
    cout << left << setw(30) << "Last Name : " << curr->l_name << endl;
    cout << left << setw(30) << "ID No. : " << curr->ic_no << endl;
    cout << left << setw(30) << "Departure Station ID : " << newStartID << endl;
    cout << left << setw(30) << "Departure Station Name : " << newStartName << endl;
    cout << left << setw(30) << "Destination Station ID : " << newEndID << endl;
    cout << left << setw(30) << "Destination Station Name : " << newEndName << endl;
    cout << left << setw(30) << "Estimated Travel Duration : " << newDuration << " minutes" << endl;
    cout << left << setw(30) << "Departure Time: " << newDeparture << endl;
    cout << left << setw(30) << "Ticket Cost : "
         << "RM " << newCost << endl;
    cout << left << setw(30) << "Time created : " << today << endl;
    cout << "==================================================================\n"
         << endl;
    cout << "[1] to Confirm" << endl;
    cout << "[C] to Cancel Purchase\n"
         << endl;

    cout << "Menu Selection:  ";
    cin >> userMenuIn;

    if (userMenuIn == 1)
    {
        editPayment(&payment_head, curr->payment_id, newStartID, newStartName, newEndID, newEndName, newDuration, newDeparture, newCost, today);
        return menu_admin(payment_head);
    }
    return menu_admin(payment_head);
}
#pragma endregion

// pragma for non-member functions
//  functions:
//  1. loginHome
//  2. menu_adminHome
//  3. menu_paymentSearch_option
#pragma region non - member methods
void loginHome(MemberDLL memberList, StationNode *hd, StationDLL st)
{
    string userMenuIn, userMainMenuIn, adminMenuIn, memberMenuIn;

    cout << "\n------------------------------------------------------" << endl;
    cout << "   __         ______     ______  " << endl;
    cout << "  /\\ \\       /\\  == \\   /\\__  _\\ " << endl;
    cout << "  \\ \\ \\____  \\ \\  __<   \\/_/\\ \\/ " << endl;
    cout << "   \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\ " << endl;
    cout << "    \\/_____/   \\/_/ /_/     \\/_/    KUALA LUMPUR " << endl;
    cout << "\n\n               Ticket Purchasing System" << endl;
    cout << "\n------------------------------------------------------" << endl;

    cout << "\n=====================  MAIN MENU  ====================" << endl;
    cout << "\n[1] Admin \n[2] Member\n\n[3] Exit" << endl;
    cout << "\n======================================================" << endl;
    cout << "\nMenu Selection:  ";
    cin >> userMainMenuIn;

    int mainMenuInt = 0;
    int adminMenuInt = 0;
    int memberMenuInt = 0;

    try
    {
        mainMenuInt = stoi(userMainMenuIn);
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Error converting string to int, please enter whole numbers\n";
        // return loginHome(q, hd, st);
        return loginHome(memberList, hd, st);
    }
    switch (mainMenuInt)
    {
    case 1: // admin selected
        cout << "\n------------------------------------------------------" << endl;
        cout << "   __         ______     ______  " << endl;
        cout << "  /\\ \\       /\\  == \\   /\\__  _\\ " << endl;
        cout << "  \\ \\ \\____  \\ \\  __<   \\/_/\\ \\/ " << endl;
        cout << "   \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\ " << endl;
        cout << "    \\/_____/   \\/_/ /_/     \\/_/    KUALA LUMPUR " << endl;
        cout << "\n\n               Ticket Purchasing System" << endl;
        cout << "\n------------------------------------------------------" << endl;

        cout << "\n=====================  MAIN MENU  ====================" << endl;
        cout << "\n[1] Login \n[2] Register New User\n\n[3] Return" << endl;
        cout << "\n======================================================" << endl;
        cout << "\nMenu Selection:  ";
        cin >> adminMenuIn;

        try
        {
            adminMenuInt = stoi(adminMenuIn);
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
            cout << "Error converting string to int, please enter whole numbers\n";
            // return loginHome(q, hd, st);
            return loginHome(memberList, hd, st);
        }
        switch (adminMenuInt)
        {
        case 1: // login selected
            return memberList.loginUser(hd, st);

            break;
        case 2: // register selected
            memberList.registerUser(hd, st);

            break;
        case 3:
            return loginHome(memberList, hd, st);

            break;
        default:
            cout << "\nMenu not found, try again.\n";
            return loginHome(memberList, hd, st);
            break;
        }

        break;
    case 2: // member selected
        cout << "\n------------------------------------------------------" << endl;
        cout << "   __         ______     ______  " << endl;
        cout << "  /\\ \\       /\\  == \\   /\\__  _\\ " << endl;
        cout << "  \\ \\ \\____  \\ \\  __<   \\/_/\\ \\/ " << endl;
        cout << "   \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\ " << endl;
        cout << "    \\/_____/   \\/_/ /_/     \\/_/    KUALA LUMPUR " << endl;
        cout << "\n\n               Ticket Purchasing System" << endl;
        cout << "\n------------------------------------------------------" << endl;

        cout << "\n=====================  MAIN MENU  ====================" << endl;
        cout << "\n[1] Login \n\n[2] Return" << endl;
        cout << "\n======================================================" << endl;
        cout << "\nMenu Selection:  ";
        cin >> memberMenuIn;

        try
        {
            memberMenuInt = stoi(memberMenuIn);
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
            cout << "Error converting string to int, please enter whole numbers\n";
            // return loginHome(q, hd, st);
            return loginHome(memberList, hd, st);
        }
        switch (memberMenuInt)
        {
        case 1: // login selected
            return memberList.loginUser(hd, st);

            break;
        case 2:
            return loginHome(memberList, hd, st);

            break;
        default:
            cout << "\nMenu not found, try again.\n";
            return loginHome(memberList, hd, st);
            break;
        }

        break;
    case 3:
        cout << "Thank you, have a good day.";
        EXIT_SUCCESS;
        break;
    default:
        cout << "\nMenu not found, try again.\n";
        return loginHome(memberList, hd, st);
        break;
    }
}

void menu_adminHome(string role)
{
    if (role == "admin")
    {
        int userMenuIn;
        cout << "\n------------------------------------------------------" << endl;
        cout << "   __         ______     ______  " << endl;
        cout << "  /\\ \\       /\\  == \\   /\\__  _\\ " << endl;
        cout << "  \\ \\ \\____  \\ \\  __<   \\/_/\\ \\/ " << endl;
        cout << "   \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\ " << endl;
        cout << "    \\/_____/   \\/_/ /_/     \\/_/    KUALA LUMPUR " << endl;
        cout << "\n\n               Ticket Purchasing System" << endl;
        cout << "\n------------------------------------------------------" << endl;

        cout << "\n=====================  MAIN MENU  ====================" << endl;
        cout << "\n[1] Payments \n[2] Stations \n[3] Members" << endl;
        cout << "\n======================================================" << endl;
        cout << "\nMenu Selection:  ";
        cin >> userMenuIn;
        switch (userMenuIn)
        {
        case 1:
            return pList.menu_admin(payment_head);

            break;
        case 2:
            return station.menu_admin(head);
            break;
        case 3:
            return memberList.menu_admin();
            break;
        }
    }

    return pList.menu_member(payment_head, role);

    cout << "\nInvalid option, please select again.\n";
    return menu_adminHome(role);
}

void menu_paymentSearch_option()
{
    cout << "================= Search Option ==================" << endl;
    cout << "[1] Username\n[2] First Name\n[3] Last Name\n[4] Departure Station \n[5] Destination Station\n\n[6] Return" << endl;
    cout << "==================================================" << endl;
    cout << "Menu Selection:  ";
}
#pragma endregion

int main()
{
    insertDummyData();
    // loginHome(q, head, station);
    loginHome(memberList, head, station);

    return 0;
}