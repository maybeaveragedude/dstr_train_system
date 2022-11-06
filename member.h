#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

class MemberNode // doubly linked list
{
public:
    string username;
    string password;
    string firstName;
    string lastName;
    string role;

    MemberNode *prev;
    MemberNode *next;
};
class MemberDLL
{

public:
    MemberNode *head;
    MemberNode *tail;
    int size;
    void newUser(string username, string password, string firstName, string lastName, string role);
    // void Enqueue(string username, string password, string firstName, string lastName, string role);
    bool deleteUser(string username);

    void viewMemberList();
    void sortListByName();
    void menu_admin();

    void loginUser(StationNode *hd, StationDLL st);
    void registerUser(StationNode *hd, StationDLL st);
    
    int checkLogin(string name, string password);
    bool checkUsernameExists(string usr);
};

void MemberDLL::newUser(string user_name, string pass_word, string first_name, string last_name, string role_)
{
    MemberNode *newNode = new MemberNode;
    newNode->username = user_name;
    newNode->password = pass_word;
    newNode->firstName = first_name;
    newNode->lastName = last_name;
    newNode->role = role_;

    newNode->next = nullptr;
    newNode->prev = tail;
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        tail->next = newNode;
    }
    tail = newNode;

    size++;
}

bool MemberDLL::deleteUser(string usr)
{

    MemberNode *temp = head;
    MemberNode *prev = nullptr;
    MemberNode *next = nullptr;

    while (temp != nullptr)
    {
        if (temp->username == usr)
        {
            if (temp == head)
            {
                head = temp->next;
                head->prev = nullptr;
            }
            else if (temp == tail)
            {
                tail = temp->prev;
                tail->next = nullptr;
            }
            else
            {
                prev = temp->prev;
                next = temp->next;
                prev->next = next;
                next->prev = prev;
            }
            delete temp;
            size--;
            return true;
            break;
        }
        temp = temp->next;
    }
    return false;
}

void MemberDLL::viewMemberList()
{
    MemberNode *temp = head;
    cout << "\nUsername\tFirst Name\tLast Name\tRole" << endl;
    cout << "----------------------------------------------------------------" << endl;
    while (temp != nullptr)
    {
        cout << temp->username << "\t\t" << temp->firstName << "\t\t" << temp->lastName << "\t\t" << temp->role << endl;
        temp = temp->next;
    }
}

void MemberDLL::sortListByName()
{

    MemberNode *temp = head;
    // sort a doubly linked list
    while (temp != nullptr)
    {
        MemberNode *tempRef = temp->next;
        while (tempRef != nullptr)
        {
            if (temp->firstName > tempRef->firstName)
            {
                string tempUsername = temp->username;
                string tempPassword = temp->password;
                string tempFirstName = temp->firstName;
                string tempLastName = temp->lastName;
                string tempRole = temp->role;

                temp->username = tempRef->username;
                temp->password = tempRef->password;
                temp->firstName = tempRef->firstName;
                temp->lastName = tempRef->lastName;
                temp->role = tempRef->role;

                tempRef->username = tempUsername;
                tempRef->password = tempPassword;
                tempRef->firstName = tempFirstName;
                tempRef->lastName = tempLastName;
                tempRef->role = tempRole;
            }
            tempRef = tempRef->next;
        }
        temp = temp->next;
    }
}

void MemberDLL::menu_admin()
{
    cout << "========================== MEMBERS ==========================" << endl;
    viewMemberList();
    cout << "\n=============================================================" << endl;
    cout << "\n[1] Delete Member" << endl;
    cout << "[2] Sort Member List by First Name" << endl;
    cout << "[3] Exit" << endl;

    int choice;
    cout << "\nMenu Selection: " << endl;
    cin >> choice;
    string usr;

    switch (choice)
    {
    case 1:
        cout << "Enter username to delete: ";
        cin >> usr;

        if (deleteUser(usr) == true)
        {
            cout << "User deleted successfully!" << endl;
        }
        else
        {
            cout << "User not found!" << endl;
        }
        menu_admin();
        break;
    case 2:
        sortListByName();
        cout << "Member list sorted!" << endl;
        menu_admin();
        break;
    case 3:
        cout << "Thank you, have a good day.";
        EXIT_SUCCESS;
        break;
    default:
        cout << "Invalid input. Please try again." << endl;
        menu_admin();
        break;
    }
}

int MemberDLL::checkLogin(string usr, string pwd)
{
    MemberNode *tempNode = new MemberNode;
    tempNode = head;

    if (tempNode != nullptr)
    {
        for (int i = 0; i < size; i++)
        {
            if (usr == tempNode->username && pwd == tempNode->password)
            {
                if (tempNode->role == "admin")
                {
                    return 1;
                }
                if (tempNode->role == "member")
                {
                    return 2;
                }
            }
            tempNode = tempNode->next;
        }
        return 0;
    }
    return 0;
}

void MemberDLL::registerUser(StationNode *hd, StationDLL st)
{
    string username, password, firstName, lastName;

    cout << "\nWelcome!\nPlease enter your desired Username : ";
    cin >> username;
    if (checkUsernameExists(username) == true)
    {
        cout << "\n****Username already taken!****\n";
        return registerUser(hd, st);
    }
    cout << "Please enter your desired Password : ";
    cin >> password;

    cout << "Please enter your first name : ";
    cin >> firstName;

    cout << "Please enter your last name : ";
    cin >> lastName;

    newUser(username, password, firstName, lastName, "member");
    cout << "New member created!\n";
    return loginUser(hd, st);
}

bool MemberDLL::checkUsernameExists(string usr)
{
    MemberNode *tempNode = new MemberNode;
    tempNode = head;
    int found = 0;

    if (tempNode != nullptr)
    {
        for (int i = 0; i < size; i++)
        {
            if (usr == tempNode->username)
            {
                return true;
            }
        }
    }
    return false;
}
