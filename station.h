#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

// DATA STRUCTURE - DOUBLY LINKED LIST
class StationNode
{
public:
    // current station details
    string station_id;
    string station_name;
    // next station details
    string next_station_id;
    string next_station_name;
    int dist_to_next_station;
    double cost_to_next_station;
    int time_to_next_station;
    // Previous station
    string prev_station_id;
    string prev_station_name;
    int dist_to_prev_station;
    double cost_to_prev_station;
    int time_to_prev_station;

    // Linked list pointer
    StationNode *next;
    StationNode *prev;
};

// Doubly Linked List
class StationDLL
{
    StationNode *head;
    StationNode *tail;

public:
    //  CRUD Functions
    //      Station details
    void newStation_FinalPos(StationNode **head, string newStationID, string newStationName, string previousID, string previousName, int dist_to_prevStation);
    void form_newStn_FinPos(StationNode *hd, string stID, string stName, int prevDist);

    void newStation_FirstPos(StationNode **head, string newStationID, string newStationName, string previousID, string previousName, int dist_to_nextStation);
    void form_newStn_FstPos(StationNode *hd, string stID, string stName, int nextDist);

    void editStation(StationNode **head, string existID, string edit_Name, double edit_price_to_prevStation, int edit_time_to_prevStation, double edit_price_to_nextStation, int edit_time_to_nextStation);
    void form_edtStn(StationNode *main, StationNode *curr);

    // viewing all stations (can be in directional)
    void viewStations(StationNode *head, string role);
    void viewStations(StationNode *head, string role, string direction); // overloading

    void viewStation_details(StationNode *head, string role);

    // calculations
    double calc_price(StationNode *head, string direction);
    int calc_time(StationNode *head, string direction);
    int calc_travel_duration(StationNode *hd, string station1, string station2, string direction);
    double calc_travel_cost(StationNode *hd, string station1, string station2, string direction);

    int get_size(StationNode *head);

    // menu snippets
    void menu_admin(StationNode *hd);

    bool checkExist_stationID(StationNode *main, string stID);
};

void StationDLL::newStation_FinalPos(StationNode **head, string newStationID, string newStationName, string previousID, string previousName, int dist_to_prevStation)
{
    StationNode *newNode = new StationNode;
    StationNode *last = *head;

    newNode->station_id = newStationID;
    newNode->station_name = newStationName;
    newNode->prev_station_id = previousID;
    newNode->prev_station_name = previousName;
    newNode->dist_to_prev_station = dist_to_prevStation;
    if (dist_to_prevStation != 0)
    {
        newNode->cost_to_prev_station = dist_to_prevStation * 0.1;
        newNode->time_to_prev_station = dist_to_prevStation - 1;
    }
    else
    {
        newNode->cost_to_prev_station = 0;
        newNode->time_to_prev_station = 0;
    }
    newNode->next_station_id = "N/A";
    newNode->next_station_name = "N/A";
    newNode->dist_to_next_station = 0;
    newNode->cost_to_next_station = 0;
    newNode->time_to_next_station = 0;
    newNode->next = nullptr;

    // If list is empty, make new head
    if (*head == NULL)
    {
        *head = newNode;
        newNode->prev = NULL;
        return;
    }

    // Traverse to end of list
    while (last->next != NULL)
        last = last->next;

    // changing last node
    last->next = newNode;

    last->next_station_id = newStationID;
    last->next_station_name = newStationName;
    last->dist_to_next_station = dist_to_prevStation;
    last->cost_to_next_station = dist_to_prevStation * 0.1;
    last->time_to_next_station = dist_to_prevStation - 1;

    // make last node as previous of new node
    newNode->prev = last;

    return;
}

void StationDLL::newStation_FirstPos(StationNode **head, string newStationID, string newStationName, string previousID, string previousName, int dist_to_nextStation)
{
    StationNode *newNode = new StationNode;

    // Set new node data
    newNode->station_id = newStationID;
    newNode->station_name = newStationName;
    newNode->next_station_id = (*head)->station_id;
    newNode->next_station_name = (*head)->station_name;
    newNode->dist_to_next_station = dist_to_nextStation;
    newNode->cost_to_next_station = dist_to_nextStation * 0.1;
    newNode->time_to_next_station = dist_to_nextStation - 1;

    // Set previous data of following node
    (*head)->prev_station_id = newStationID;
    (*head)->prev_station_name = newStationName;
    (*head)->dist_to_prev_station = dist_to_nextStation;
    if (dist_to_nextStation != 0)
    {
        (*head)->cost_to_prev_station = dist_to_nextStation * 0.1;
        (*head)->time_to_prev_station = dist_to_nextStation - 1;
    }
    else
    {
        (*head)->cost_to_prev_station = 0;
        (*head)->time_to_prev_station = 0;
    }

    // Set next pointer of new node
    newNode->next = (*head);

    // Set head to new node
    (*head) = newNode;
}

double StationDLL::calc_price(StationNode *head, string direction)
{
    double price = 0.0;
    if (direction == "Forward")
    {
        price = head->dist_to_next_station * 0.1;
    }
    else if (direction == "Backward")
    {
        price = head->dist_to_prev_station * 0.1;
    }
    return price;
}

int StationDLL::calc_time(StationNode *head, string direction)
{
    int time = 0;
    if (direction == "Forward")
    {
        time = head->dist_to_next_station - 1;
    }
    else if (direction == "Backward")
    {
        time = head->dist_to_prev_station - 1;
    }
    return time;
}

int StationDLL::get_size(StationNode *head)
{
    int count = 0;
    StationNode *curr = head;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

// Displays summary of all stations
void StationDLL::viewStations(StationNode *head, string role)
{
    StationNode *curr = head;


    cout << "\n------------------------------------------------------" << endl;
    cout << "   __         ______     ______  " << endl;
    cout << "  /\\ \\       /\\  == \\   /\\__  _\\ " << endl;
    cout << "  \\ \\ \\____  \\ \\  __<   \\/_/\\ \\/ " << endl;
    cout << "   \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\ " << endl;
    cout << "    \\/_____/   \\/_/ /_/     \\/_/    KUALA LUMPUR " << endl;
    cout << "\n\n              TITIWANGSA -> CHAN SOW LIN" << endl;
    cout << "\n------------------------------------------------------" << endl;

    // Forward linked list traversal
    while (curr != NULL)
    {
        // Initialize price
        double price = 0.0;
        // Function called to calculate price
        price = calc_price(curr, "Forward");
        // Print out stationID and stationName
        cout << "\n==============================\n\n";
        cout << " Station ID : " << curr->station_id << endl;
        cout << " Station Name : " << curr->station_name << endl;
        cout << "\n==============================" << endl;
        // IF statement to check if there is next station; If next distance is 0, there is no next station, therefore will not run the commands below
        if (curr->dist_to_next_station != 0)
        {
            cout << "        |" << endl;
            cout << "        |"
                 << " RM " << calc_price(curr, "Forward") << endl;
            cout << "        | " << curr->dist_to_next_station << "km (" << calc_time(curr, "Forward") << " mins)" << endl;
            cout << "        V";
        }
        // Set current node to next node and repeat loop
        curr = curr->next;
    }
    string inp = "";
    while (inp != "R")
    {
        cout << "\n[R] to return:  ";
        cin >> inp;
    }
    if (role == "admin")
    {
        return menu_admin(head);
    }
}

void StationDLL::viewStations(StationNode *head, string role, string direction)
{
    StationNode *curr = head;

    if (direction == "Backward")
    {
        cout << "\n------------------------------------------------------" << endl;
        cout << "   __         ______     ______  " << endl;
        cout << "  /\\ \\       /\\  == \\   /\\__  _\\ " << endl;
        cout << "  \\ \\ \\____  \\ \\  __<   \\/_/\\ \\/ " << endl;
        cout << "   \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\ " << endl;
        cout << "    \\/_____/   \\/_/ /_/     \\/_/    KUALA LUMPUR " << endl;
        cout << "\n\n              CHAN SOW LIN -> TITIWANGSA" << endl;
        cout << "\n------------------------------------------------------" << endl;

        // if 'direction' is Backwards, traverse to end of list for reverse traversal
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        while (curr != NULL)
        {
            // Initialize price
            double price = 0.0;
            // Function called to calculate price
            price = calc_price(curr, direction);
            // Print out stationID and stationName
            cout << "\n==============================\n";
            cout << " Station ID : " << curr->station_id << endl;
            cout << " Station Name : " << curr->station_name << endl;
            cout << "==============================" << endl;
            // IF statement to check if there is next station; If next distance is 0, there is no next station, therefore will not run the commands below
            if (curr->dist_to_prev_station != 0)
            {
                cout << "        |"
                     << " RM " << calc_price(curr, direction) << endl;
                cout << "        | " << curr->dist_to_prev_station << "km (" << calc_time(curr, direction) << " mins)" << endl;
                cout << "        V";
            }
            // Set current node to previous node and repeat loop
            curr = curr->prev;
        }
    }

    if (direction == "Forward")
    {
        cout << "\n------------------------------------------------------" << endl;
        cout << "   __         ______     ______  " << endl;
        cout << "  /\\ \\       /\\  == \\   /\\__  _\\ " << endl;
        cout << "  \\ \\ \\____  \\ \\  __<   \\/_/\\ \\/ " << endl;
        cout << "   \\ \\_____\\  \\ \\_\\ \\_\\    \\ \\_\\ " << endl;
        cout << "    \\/_____/   \\/_/ /_/     \\/_/    KUALA LUMPUR " << endl;
        cout << "\n\n              TITIWANGSA -> CHAN SOW LIN" << endl;
        cout << "\n------------------------------------------------------" << endl;

        while (curr != NULL)
        {
            // Initialize price
            double price = 0.0;
            // Function called to calculate price
            price = calc_price(curr, "Forward");
            // Print out stationID and stationName
            cout << "\n==============================\n";
            cout << " Station ID : " << curr->station_id << endl;
            cout << " Station Name : " << curr->station_name << endl;
            cout << "==============================" << endl;
            // IF statement to check if there is next station; If next distance is 0, there is no next station, therefore will not run the commands below
            if (curr->dist_to_next_station != 0)
            {
                // cout << "        | " << curr->dist_to_next_station << " KM" << endl;
                cout << "        |"
                     << " RM " << calc_price(curr, "Forward") << endl;
                cout << "        | " << curr->dist_to_next_station << "km (" << calc_time(curr, "Forward") << " mins)" << endl;
                cout << "        V";
            }
            // Set current node to next node and repeat loop
            curr = curr->next;
        }
    }
    return;
}

void StationDLL::viewStation_details(StationNode *head, string role)
{
    StationNode *curr = head;

    // Initialize price
    double price = 0.0;
    int size = get_size(head);
    int page = 1;
    int input = 0;
    while (page)
    {
        // Print out stationID and stationName
        cout << "\n======================== Station [" << page << "/" << size << "] ========================\n";
        cout << "\nStation ID : " << curr->station_id << endl;
        cout << "Station Name : " << curr->station_name << endl;
        cout << "Previous Station ID : " << curr->prev_station_id << endl;
        cout << "Previous Station Name : " << curr->prev_station_name << endl;
        cout << "Distance to previous station : " << curr->dist_to_prev_station << endl;
        cout << "Time to previous station : " << curr->time_to_prev_station << endl;
        cout << "Cost to previous station : RM" << curr->cost_to_prev_station << endl;
        cout << "Next Station ID : " << curr->next_station_id << endl;
        cout << "Next Station Name : " << curr->next_station_name << endl;
        cout << "Distance to next station : " << curr->dist_to_next_station << endl;
        cout << "Time to next station : " << curr->time_to_next_station << " minutes" << endl;
        cout << "Cost to next station : RM" << curr->cost_to_next_station << endl;
        cout << "\n===============================================================\n"
             << endl;
        cout << "[1] Next Station\n[2] Previous Station\n[3] Edit Station\n\n[4] Return\n";
        cout << "Menu Selection : ";
        cin >> input;
        if (input == 1)
        {
            if (page == size)
            {
                cout << "\n*Out of Bounds!\n";
                continue;
            }
            else
            {
                page++;
                curr = curr->next;
                continue;
            }
        }
        if (input == 2)
        {
            if (page == 1)
            {
                cout << "\n*Out of Bounds!\n";
                continue;
            }
            else
            {
                page--;
                curr = curr->prev;
                continue;
            }
        }
        if (input == 3)
        {
            // Show editable details
            return form_edtStn(head, curr);
        }
        // Break if selected return
        if (input == 4)
        {
            break;
        }
    }
    if (role == "admin")
    {
        return menu_admin(head);
    }
}


void StationDLL::form_newStn_FinPos(StationNode *hd, string stID, string stName, int prevDist)
{
    StationNode *curr = hd;
    // Traverse to end
    while (curr->next != NULL)
        curr = curr->next;

    // Form
    cout << "\n============== INSERT AT END ==============\n";
    cout << "[1] Station ID : " << stID << endl;
    cout << "[2] Station Name : " << stName << endl;
    cout << "[3] Previous Station ID : " << curr->station_id << endl;
    cout << "[4] Previous Station Name : " << curr->station_name << endl;
    cout << "[5] Distance to previous station : " << prevDist;
    cout << "\n===========================================\n";
    cout << "[CANCEL] to cancel and return.\n\n";
    if (stID == "")
    {
        cout << "Enter Station ID : ";
        cin >> stID;
        return form_newStn_FinPos(hd, stID, stName, prevDist);
    }
    else if (stID == "CANCEL")
    {
        return menu_admin(hd);
    }
    if (stName == "")
    {
        cout << "Enter Station Name : ";
        getline(cin, stName);
        return form_newStn_FinPos(hd, stID, stName, prevDist);
    }
    else if (stName == "CANCEL")
    {
        return menu_admin(hd);
    }
    if (prevDist == 0)
    {
        string dist;
        cout << "Enter Distance to Previous Station : ";
        cin >> dist;
        if (dist == "CANCEL")
        {
            return menu_admin(hd);
        }
        try
        {
            prevDist = stoi(dist);
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
            cout << "Error converting string to int, please enter whole numbers\n";
            return form_newStn_FinPos(hd, stID, stName, prevDist);
        }
        return form_newStn_FinPos(hd, stID, stName, prevDist);
    }
    // Confirmation Check
    string res1;
    cout << "\nAre you sure? [Y/n]\n";
    cin >> res1;
    if (res1 == "Y" || res1 == "y")
    {
        newStation_FinalPos(&hd, stID, stName, curr->station_id, curr->station_name, prevDist);
        return menu_admin(hd);
    }
    else if (res1 == "N" || res1 == "n")
    {
        // Cancel operation check
        string res2;
        cout << "\nCancel Operation? [Y/n]\n";
        cin >> res2;
        if (res2 == "Y" || res2 == "y")
        {
            return menu_admin(hd);
        }
        else
        {
            return form_newStn_FinPos(hd, "", "", 0);
        }
    }
    cout << "An error has occurred :(";
    return;
}

void StationDLL::form_newStn_FstPos(StationNode *hd, string stID, string stName, int nextDist)
{
    StationNode *curr = hd;

    // Form
    cout << "\n============= INSERT AT FRONT =============\n";
    cout << "[1] Station ID : " << stID << endl;
    cout << "[2] Station Name : " << stName << endl;
    cout << "[3] Next Station ID : " << curr->station_id << endl;
    cout << "[4] Next Station Name : " << curr->station_name << endl;
    cout << "[5] Distance to next station : " << nextDist;
    cout << "\n===========================================\n";
    cout << "[CANCEL] to cancel and return.\n\n";
    if (stID == "")
    {
        cout << "Enter Station ID : ";
        cin >> stID;
        return form_newStn_FstPos(hd, stID, stName, nextDist);
    }
    else if (stID == "CANCEL")
    {
        return menu_admin(hd);
    }
    if (stName == "")
    {
        cout << "Enter Station Name : ";
        getline(cin, stName);
        return form_newStn_FstPos(hd, stID, stName, nextDist);
    }
    else if (stName == "CANCEL")
    {
        return menu_admin(hd);
    }
    if (nextDist == 0)
    {
        string dist;
        cout << "Enter Distance to Next Station : ";
        cin >> dist;
        if (dist == "CANCEL")
        {
            return menu_admin(hd);
        }
        try
        {
            nextDist = stoi(dist);
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
            cout << "Error converting string to int, please enter whole numbers\n";
            return form_newStn_FstPos(hd, stID, stName, nextDist);
        }
        return form_newStn_FstPos(hd, stID, stName, nextDist);
    }
    // Confirmation Check
    string res1;
    cout << "\nAre you sure? [Y/n]\n";
    cin >> res1;

    if (res1 == "Y" || res1 == "y")
    {
        newStation_FirstPos(&hd, stID, stName, curr->station_id, curr->station_name, nextDist);
        return menu_admin(hd);
    }
    else if (res1 == "N" || res1 == "n")
    {
        // Cancel operation check
        string res2;
        cout << "\nCancel Operation? [Y/n]\n";
        cin >> res2;
        if (res2 == "Y" || res2 == "y")
        {
            return menu_admin(hd);
        }
        else
        {
            return form_newStn_FstPos(hd, "", "", 0);
        }
    }
    cout << "An error has occurred :(";
    return;
}

void StationDLL::form_edtStn(StationNode *main, StationNode *curr)
{
    string newStationName;
    int nextTime = 0, prevTime = 0;
    double nextCost = 0, prevCost = 0;

    cout << "Update station name, use UNDERSCORE as space [Original:  " << curr->station_name << "] : ";
    cin >> newStationName;
    replace(newStationName.begin(), newStationName.end(), '_', ' ');
    if (curr->time_to_prev_station != 0)
    {
        cout << "Update duration to previous station [Original:  " << curr->time_to_prev_station << " minutes] : ";
        cin >> prevTime;
    }
    if (curr->cost_to_prev_station != 0)
    {
        cout << "Update cost to previous station [Original:  RM " << curr->cost_to_prev_station << "] : ";
        cin >> prevCost;
    }
    if (curr->time_to_next_station != 0)
    {
        cout << "Update duration to next station [Original:  " << curr->time_to_next_station << " minutes] : ";
        cin >> nextTime;
    }
    if (curr->cost_to_next_station != 0)
    {
        cout << "Update cost to next station [Original:  RM " << curr->cost_to_next_station << "] : ";
        cin >> nextCost;
    }

    if (newStationName == "")
    {
        cout << "*Station name cannot be empty!\n";
        return form_edtStn(main, curr);
    }
    if (prevTime == 0 || prevCost == 0)
    {
        cout << "*Previous Station details cannot be empty!\n";
        return form_edtStn(main, curr);
    }
    if (nextTime == 0 || nextCost == 0)
    {
        cout << "*Next Station details cannot be empty!\n";
        return form_edtStn(main, curr);
    }

    string input;
    // Form
    cout << "\n=============Edit Output=============\n";
    cout << "Station ID : " << curr->station_id << endl;
    cout << "Station Name : " << newStationName << endl;
    cout << "Previous Station ID : " << curr->prev_station_id << endl;
    cout << "Previous Station Name : " << curr->prev_station_name << endl;
    cout << "Distance to previous station : " << curr->dist_to_prev_station << endl;
    cout << "Time to previous station : " << prevTime << " minutes" << endl;
    cout << "Cost to previous station : RM" << prevCost << endl;
    cout << "Next Station ID : " << curr->next_station_id << endl;
    cout << "Next Station Name : " << curr->next_station_name << endl;
    cout << "Distance to next station : " << curr->dist_to_next_station << endl;
    cout << "Time to next station : " << nextTime << " minutes" << endl;
    cout << "Cost to next station : RM" << nextCost << endl;
    cout << "\n=========================================\n";
    cout << "[CANCEL] to cancel and return.\n";
    cout << "[CONFIRM] to confirm.\n";
    cout << "Input : ";
    cin >> input;

    if (input == "CANCEL")
    {
        return menu_admin(main);
    }
    if (input == "CONFIRM")
    {
        editStation(&main, curr->station_id, newStationName, prevCost, prevTime, nextCost, nextTime);
        return menu_admin(main);
    }
}

void StationDLL::editStation(StationNode **head, string existID, string edit_Name, double edit_price_to_prevStation, int edit_time_to_prevStation, double edit_price_to_nextStation, int edit_time_to_nextStation)
{
    // StationNode* curr = new StationNode;
    StationNode *last = *head;

    while (last->station_id != existID)
        last = last->next;

    last->station_name = edit_Name;
    last->cost_to_prev_station = edit_price_to_prevStation;
    last->time_to_prev_station = edit_time_to_prevStation;
    last->cost_to_next_station = edit_price_to_nextStation;
    last->cost_to_next_station = edit_time_to_nextStation;
}

bool StationDLL::checkExist_stationID(StationNode *main, string stID)
{
    StationNode *curr = main;
    int loop = 1;

    while (true)
    {
        if (curr->station_id == stID)
        {
            return true;
        }
        if (curr == NULL)
            break;
        curr = curr->next;
    }

    return false;
}

int StationDLL::calc_travel_duration(StationNode *hd, string station1, string station2, string direction)
{
    StationNode *curr = new StationNode;
    curr = hd;
    int res = 0;

    if (direction == "Forward")
    {
        // loop until first station matches
        while (curr->next != NULL && curr->station_id != station1)
            curr = curr->next;
        // from first station add next station time until end station is reached
        while (curr->station_id != station2)
        {
            if (curr == NULL)
                break;
            res += curr->time_to_next_station;
            curr = curr->next;
        }
        return res;
    }

    if (direction == "Backward")
    {
        // loop list until the end first
        while (curr->next != NULL)
            curr = curr->next;

        // traverse backward until first station matches
        while (curr->prev != NULL && curr->station_id != station1)
            curr = curr->prev;
        // from first station add next station time until end station is reached
        while (curr->station_id != station2)
        {
            if (curr == NULL)
                break;
            res += curr->time_to_prev_station;
            curr = curr->prev;
        }
        return res;
    }
    return 0;
}

double StationDLL::calc_travel_cost(StationNode *hd, string station1, string station2, string direction)
{
    StationNode *curr = new StationNode;
    curr = hd;
    double res = 0;

    if (direction == "Forward")
    {
        // loop until first station matches
        while (curr->next != NULL && curr->station_id != station1)
            curr = curr->next;
        // from first station add next station time until end station is reached
        while (curr->station_id != station2)
        {
            if (curr == NULL)
                break;
            res += curr->cost_to_next_station;
            curr = curr->next;
        }
        return res;
    }

    if (direction == "Backward")
    {
        // loop list until the end first
        while (curr->next != NULL)
            curr = curr->next;

        // traverse backward until first station matches
        while (curr->prev != NULL && curr->station_id != station1)
            curr = curr->prev;
        // from first station add next station time until end station is reached
        while (curr->station_id != station2)
        {
            if (curr == NULL)
                break;
            res += curr->cost_to_prev_station;
            curr = curr->prev;
        }
        return res;
    }
    return 0;
}
