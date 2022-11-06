#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

class PaymentNode
{
public:
    string payment_id;
    string user_name;
    string f_name;
    string l_name;
    string ic_no;
    string departure_stn_id;
    string departure_stn_name;
    string destination_stn_id;
    string destination_stn_name;
    int total_duration;
    double ticket_amount;
    string transct_date;
    string departure_time;

    PaymentNode *next;
    PaymentNode *prev;
};

class PaymentList
{
    PaymentNode *Head;
    PaymentNode *Tail;

public:
    // CRUD functions
    // inserting new payment record
    void newPayment(PaymentNode **head, string inp_user, string inp_first_nm, string inp_last_nm, string inp_icNo, string inp_dep_stnId, string inp_dep_stnName, string inp_dest_stnId, string inp_dest_stnName, double inp_amount, int inp_duration, string today, string inp_dep_time);
    // deleting payment record based on payment id
    void deletePayment(PaymentNode **hd, string id);
    // updating payment record
    void editPayment(PaymentNode **head, string targetID, string newStartID, string newStartName, string newEndID, string newEndName, int newDuration, string newDeparture, double newCost, string dt);
    // the form for payment editing
    void form_editPayment(PaymentNode *hd, PaymentNode *curr);

    // getters
    // get payment details based on payment id
    void getPaymentDetails(PaymentNode *head, string role, string id);
    // get payment details based on user name
    void getPaymentDetails(PaymentNode *head, string role, string id, string inp_user);
    // get member's payment details
    void getPaymentDetails_asMember(PaymentNode *pHead, string searchValue);
    void getAllPayments(PaymentNode *head, string role);
    void getAllPayments(PaymentNode *head, string role, string id, string inp_user);

    // search function
    void searchPayment(PaymentNode *pHead, string role, string searchBy, string searchValue);

    // menu functions
    void menu_admin(PaymentNode *hd);
    void menu_member(PaymentNode *hd, string inp_user);
    void menu_purchase(PaymentNode *hd, string inp_user);
    void menu_ticketSummary(PaymentNode *hd, string inp_user, string startStID, string endStID, string direction);

    // sort functions
    void insertionSort(PaymentNode **head_ref);
    void sortedInsert(PaymentNode **head_ref, PaymentNode *newNode);

    int getSize(PaymentNode *head);
};

void PaymentList::newPayment(PaymentNode **pHead, string inp_user, string inp_first_nm, string inp_last_nm, string inp_icNo, string inp_dep_stnId, string inp_dep_stnName, string inp_dest_stnId, string inp_dest_stnName, double inp_amount, int inp_duration, string today, string inp_dep_time)
{
    PaymentNode *newNode = new PaymentNode;
    PaymentNode *last = *pHead;
    PaymentNode *last1 = last;
    int id = 0;

    if (last1 != NULL)
    {
        while (last1->next != NULL)
            last1 = last1->next;

        try
        {
            id = stoi(last1->payment_id);
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
            cout << "Error converting string to int, please enter whole numbers\n";
            return;
        }
    }

    id++;
    stringstream ss;
    string idString;
    ss << id;
    ss >> idString;

    newNode->payment_id = idString;
    newNode->user_name = inp_user;
    newNode->f_name = inp_first_nm;
    newNode->l_name = inp_last_nm;
    newNode->ic_no = inp_icNo;
    newNode->departure_stn_id = inp_dep_stnId;
    newNode->departure_stn_name = inp_dep_stnName;
    newNode->destination_stn_id = inp_dest_stnId;
    newNode->destination_stn_name = inp_dest_stnName;
    newNode->total_duration = inp_duration;
    newNode->ticket_amount = inp_amount;
    newNode->transct_date = today;
    newNode->departure_time = inp_dep_time;
    newNode->next = nullptr;

    if (*pHead == NULL)
    {
        *pHead = newNode;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = newNode;
    newNode->prev = last;
    return;
}

void PaymentList::getPaymentDetails(PaymentNode *pHead, string role, string id)
{
    // admin view
    PaymentNode *curr = pHead;
    int size = getSize(pHead);
    int page = 1, tId = 0;
    string input;

    while (curr->payment_id != id)
        curr = curr->next;

    while (page)
    {
        cout << "\n======================== TICKET [" << id << "] ========================\n";
        cout << left << setw(30) << "Ticket ID : " << curr->payment_id << endl;
        cout << left << setw(30) << "Username : " << curr->user_name << endl;
        cout << left << setw(30) << "First Name : " << curr->f_name << endl;
        cout << left << setw(30) << "Last Name : " << curr->l_name << endl;
        cout << left << setw(30) << "Identification Number : " << curr->ic_no << endl;
        cout << left << setw(30) << "Last Name : " << curr->l_name << endl;
        cout << left << setw(30) << "Start Station ID : " << curr->departure_stn_id << endl;
        cout << left << setw(30) << "Start Station Name : " << curr->departure_stn_name << endl;
        cout << left << setw(30) << "End Station ID : " << curr->destination_stn_id << endl;
        cout << left << setw(30) << "End Station Name : " << curr->destination_stn_name << endl;
        cout << left << setw(30) << "Estimated Travel Duration : " << curr->total_duration << " minutes" << endl;
        cout << left << setw(30) << "Departure Time: " << curr->departure_time << endl;
        cout << left << setw(30) << "Ticket Cost : "
             << "RM " << curr->ticket_amount << endl;
        cout << left << setw(30) << "Time created : " << curr->transct_date << endl;
        cout << "==============================================================\n"
             << endl;
        cout << "[1] Return To List\n[EDIT] to edit this purchase entry\n[DELETE] to delete this purchase history\n";
        cout << "\nMenu Selection : ";
        cin >> input;
        if (input == "1")
        {
            break;
        }
        if (input == "DELETE")
        {
            cout << "Are you sure? This action cannot be undone [Y/n]\nInput >> ";
            cin >> input;
            if (input == "Y" || input == "y")
                deletePayment(&pHead, curr->payment_id);
            break;
        }
        if (input == "EDIT")
        {
            return form_editPayment(pHead, curr);
        }
    }

    if (role == "admin")
    {
        return getAllPayments(pHead, role);
    }

    //'role' here is username
    return getPaymentDetails_asMember(pHead, role);
}

// admin view all
void PaymentList::getAllPayments(PaymentNode *pHead, string role)
{
    PaymentNode *curr = pHead;
    int count = 0, page = 1;
    int size = getSize(pHead);
    string userMenuIn;

    cout << "\n======================================== TICKETS ========================================\n\n";
    cout << left << setw(5) << "ID" << left << setw(10) << "User" << left << setw(15) << "First Name" << left << setw(15) << "Start Station" << left
         << setw(15) << "End Station" << endl;
    cout << "--------------------------------------------------\n";

    while (curr != NULL)
    {
        cout << left << setw(5) << curr->payment_id << left << setw(10) << curr->user_name << left << setw(15) << curr->f_name << left << setw(15) << curr->departure_stn_name << left
             << setw(15) << curr->destination_stn_name << endl;

        count++;
        curr = curr->next;
    }

    cout << "\nEnter the Payment ID of the ticket to view more details" << endl;
    cout << "Enter 'ASC' to sort by first name ascendingly." << endl;
    cout << "Enter 'R' go back previous menu." << endl;

    cout << "=========================================================================================\n";
    // cout << "Enter the Payment ID of the ticket to view the details. Enter 'BACK' to return to menu.\nEnter 'SORT' to sort list by first name.\n";
    cout << "Menu Selection : ";
    cin >> userMenuIn;
    if (userMenuIn == "R")
    {
        return menu_admin(pHead);
    }
    if (userMenuIn == "ASC")
    {
        insertionSort(&pHead);
        return getAllPayments(pHead, role);
    }

    try
    {
        int id = stoi(userMenuIn);
        if (id >= 1 && id <= count)
        {
            return getPaymentDetails(pHead, role, userMenuIn);
        }
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Error converting string to int, please enter whole numbers\n";
        return getAllPayments(pHead, role);
    }

    cout << "***ID Out of Bounds or invalid input!***" << endl;
    return getAllPayments(pHead, role);
}

void PaymentList::searchPayment(PaymentNode *pHead, string role, string searchBy, string searchValue)
{
    PaymentNode *curr = pHead;
    int count = 0, page = 1;
    int size = getSize(pHead);
    string userMenuIn;

    cout << "\n================================= TICKETS [" << searchBy << ": " << searchValue << "] =================================\n\n";
    cout << left << setw(5) << "ID" << left << setw(10) << "User" << left << setw(15) << "First Name" << left << setw(15) << "Start Station" << left
         << setw(15) << "End Station" << endl;
    cout << "--------------------------------------------------\n";
    while (curr != NULL)
    {
        if ((searchBy == "username" && curr->user_name == searchValue) || (searchBy == "first name" && curr->f_name == searchValue) || (searchBy == "last name" && curr->l_name == searchValue) || (searchBy == "startStation" && curr->departure_stn_name == searchValue) || (searchBy == "endStation" && curr->destination_stn_name == searchValue))
        {
            cout << left << setw(5) << curr->payment_id << left << setw(10) << curr->user_name << left << setw(15) << curr->f_name << left << setw(15) << curr->departure_stn_name << left
                 << setw(15) << curr->destination_stn_name << endl;
            count++;
        }

        count++;
        curr = curr->next;
    }
    cout << "\nEnter the Payment ID of the ticket to view more details" << endl;
    cout << "Enter 'ASC' to sort by first name ascendingly." << endl;
    cout << "Enter 'R' go back previous menu." << endl;

    cout << "===========================================================================================\n";

    cout << "Menu Selection : ";
    cin >> userMenuIn;
    if (userMenuIn == "R")
    {
        return menu_admin(pHead);
    }
    if (userMenuIn == "ASC")
    {
        insertionSort(&pHead);
        return menu_admin(pHead);
    }
    try
    {
        int id = stoi(userMenuIn);
        if (id >= 1 && id <= count)
        {
            return getPaymentDetails(pHead, role, userMenuIn);
        }
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Error converting string to int, please enter whole numbers\n";
        return getAllPayments(pHead, role);
    }
    cout << "***ID Out of Bounds or invalid input!***" << endl;
    return getAllPayments(pHead, role);
}

void PaymentList::getPaymentDetails_asMember(PaymentNode *pHead, string searchValue)
{
    PaymentNode *curr = pHead;
    int count = 0, page = 1;
    int size = getSize(pHead);
    string userMenuIn;

    cout << "\n================================= TICKETS [User :" << searchValue << "] =================================\n\n";
    cout << left << setw(5) << "ID" << left << setw(10) << "User" << left << setw(15) << "Start Station" << left
         << setw(15) << "End Station" << endl;
    cout << "--------------------------------------------------\n";

    while (curr != NULL)
    {
        if (curr->user_name == searchValue)
        {
            cout << left << setw(5) << curr->payment_id << left << setw(10) << curr->user_name << left << setw(15) << curr->departure_stn_name << left
                 << setw(15) << curr->destination_stn_name << endl;
        }

        count++;
        curr = curr->next;
    }
    cout << "\nEnter the Payment ID of the ticket to view more details" << endl;
    cout << "Enter 'R' go back previous menu." << endl;

    cout << "===========================================================================================\n\n";

    cout << "Menu Selection : ";
    cin >> userMenuIn;
    if (userMenuIn == "R")
    {
        return menu_member(pHead, searchValue);
    }

    try
    {
        int id = stoi(userMenuIn);
        if (id >= 1 && id <= count)
        {
            return getPaymentDetails(pHead, searchValue, userMenuIn);
        }
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Error converting string to int, please enter whole numbers\n";
        return getPaymentDetails_asMember(pHead, searchValue);
    }
    cout << "***Out of Bounds or invalid input!***" << endl;
    return getPaymentDetails_asMember(pHead, searchValue);
}

void PaymentList::menu_member(PaymentNode *pHead, string inp_user)
{
    int userMenuIn;
    cout << "\nWelcome back, " << inp_user << "." << endl;
    cout << "================== USER MAIN MENU ==================" << endl;
    cout << "\n[1] Start New Purchase\n[2] View Transaction History\n[3] Exit system\n";
    cout << "\n====================================================" << endl;
    cout << "\nMenu Selection :  ";
    cin >> userMenuIn;
    // If userMenuIn is outside the range of optioons
    switch (userMenuIn)
    {
    case 1:
        return menu_purchase(pHead, inp_user);
        break;
    case 2:
        return getPaymentDetails_asMember(pHead, inp_user);
        break;
    case 3:
        cout << "Thank you for using our system. Have a nice day!" << endl;
        EXIT_SUCCESS;

        break;
    default:
        cout << "Invalid selection. Please try again." << endl;
        return menu_member(pHead, inp_user);
        break;
    }
}

int PaymentList::getSize(PaymentNode *pHead)
{
    int count = 0;
    PaymentNode *curr = pHead;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

void PaymentList::deletePayment(PaymentNode **pHead, string id)
{
    // Store head node
    PaymentNode *temp = *pHead;
    PaymentNode *prev = NULL;

    // If head node itself holds
    // the id to be deleted
    if (temp != NULL && temp->payment_id == id)
    {
        *pHead = temp->next; // Changed head
        delete temp;         // free old head
        return;
    }

    // Else Search for the id to be deleted,
    // keep track of the previous node as we
    // need to change 'prev->next' */
    else
    {
        while (temp != NULL && temp->payment_id != id)
        {
            prev = temp;
            temp = temp->next;
        }

        // If id was not present in linked list
        if (temp == NULL)
            return;

        // Unlink the node from linked list
        prev->next = temp->next;

        // Free memory
        delete temp;
    }
}

void PaymentList::editPayment(PaymentNode **head, string targetID, string newStartID, string newStartName, string newEndID, string newEndName, int newDuration, string newDeparture, double newCost, string dt)
{
    // StationNode* curr = new StationNode;
    PaymentNode *last = *head;

    while (last->payment_id != targetID)
        last = last->next;

    last->departure_stn_id = newStartID;
    last->departure_stn_name = newStartName;
    last->destination_stn_id = newEndID;
    last->destination_stn_name = newEndName;
    last->total_duration = newDuration;
    last->departure_time = newDeparture;
    last->ticket_amount = newCost;
    last->transct_date = dt;
}

void PaymentList::sortedInsert(struct PaymentNode **head_ref, struct PaymentNode *newNode)
{
    PaymentNode *current;

    // if list is empty
    if (*head_ref == NULL)
        *head_ref = newNode;

    // if the node is to be inserted at the beginning
    // of the doubly linked list
    else if ((*head_ref)->f_name >= newNode->f_name)
    {
        newNode->next = *head_ref;
        newNode->next->prev = newNode;
        *head_ref = newNode;
    }

    else
    {
        current = *head_ref;

        // locate the node after which the new node
        // is to be inserted
        while (current->next != NULL &&
               current->next->f_name < newNode->f_name)
            current = current->next;

        /*Make the appropriate links */

        newNode->next = current->next;

        // if the new node is not inserted
        // at the end of the list
        if (current->next != NULL)
            newNode->next->prev = newNode;

        current->next = newNode;
        newNode->prev = current;
    }
}

// function to sort a doubly linked list using insertion sort
void PaymentList::insertionSort(struct PaymentNode **head_ref)
{
    // Initialize 'sorted' - a sorted doubly linked list
    PaymentNode *sorted = NULL;

    // Traverse the given doubly linked list and
    // insert every node to 'sorted'
    PaymentNode *current = *head_ref;
    while (current != NULL)
    {

        // Store next for next iteration
        PaymentNode *next = current->next;

        // removing all the links so as to create 'current'
        // as a new node for insertion
        current->prev = current->next = NULL;

        // insert current in 'sorted' doubly linked list
        sortedInsert(&sorted, current);

        // Update current
        current = next;
    }

    // Update head_ref to point to sorted doubly linked list
    *head_ref = sorted;
}