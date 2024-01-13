#include <iostream>
#include <vector>
using namespace std;
class Employee {
private:
    int ssn;
    long phoneNumber;
    string firstName;
    string lastName;


public:
    Employee() {
        ssn = 0;
        phoneNumber = 0;
        firstName = "";
        lastName = "";

    }
    Employee(int ssn, long phone, string fn, string ln)
    {
        this->ssn = ssn;
        phoneNumber = phone;
        firstName = fn;
        lastName = ln;
    }
    int getSSN() { return ssn; }
    int getPhoneNumber() { return phoneNumber; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }


    void setSSN(int ssn) { this->ssn = ssn; }
    void setPhoneNumber(long phone) { phoneNumber = phone; }
    void setFirstName(string f) { firstName = f; }
    void setLastName(string l) { lastName = l; }

};
struct node {
    int ssn;
    long phoneNumber;
    string firstName;
    string lastName;
    node* next;
    node* prev;
    node(int s, long pn, string f, string l, node* n = nullptr, node* p = nullptr)
    {
        ssn = s;
        phoneNumber = pn;
        firstName = f;
        lastName = l;
        next = n;
        prev = p;
    }
};

struct node* createNode();
void insertAtEnd(node*& head, node*& temp1);
void PrintForward(node* head);
void deleteNode(node*& head, int ssnToDelete);
int linearSearch(node* head, int ssnToFind);
void swapNodes(node*& x, node*& y);
int getCountOfNodes(node* head);
void bubbleSort(node*& head);
void selectionSort(node*& head);
void insertionSort(node*& head);
void countingSort(node*& head);
void quickSort(node* low, node* high);
node* merge(node* first, node* second);
void mergeSort(node*&);
node* split(node*);
node* partition(node* low, node* high);
node* minNode(node* head);
node* lastNode(node* head);

int main()
{
    node* head = nullptr;
    node* temp1 = nullptr;
    int size;
    int choice;
    bool exit = false;
    int nodeToDelete;
    int nodeToSearch;
    cout << "MENU: " << endl;
    cout << "Enter 1 to make a list of employees" << endl;
    cout << "Enter 2 display the list from the beginning" << endl;
    cout << "Enter 3 to insert a node at the end of the list" << endl;
    cout << "Enter 4 to delete a node from the list" << endl;
    cout << "Enter 5 to search for a node in the list" << endl;
    cout << "Enter 6 to sort a list of employees" << endl;
    cout << "Enter 7 to exit" << endl;
    cout << endl;



    while (!exit)
    {

        cout << "Enter a choice" << endl;
        cin >> choice;
        if (choice == 1)
        {
            cout << "Please enter size of list: " << endl;
            cin >> size;
            for (int i = 0; i < size; i++)
            {
                insertAtEnd(head, temp1);
            }
        }
        else if (choice == 2)
        {
            PrintForward(head);
        }
        else if (choice == 3)
        {
            insertAtEnd(head, temp1);
        }
        else if (choice == 4)
        {
            cout << "Enter a snn to delete: " << endl;
            cin >> nodeToDelete;
            deleteNode(head, nodeToDelete);
        }
        else if (choice == 5)
        {
            cout << "Enter a snn to find: " << endl;
            cin >> nodeToSearch;
            cout << "That snn is at node " << linearSearch(head, nodeToSearch);
        }
        else if (choice == 6)
        {
            int sortChoice;
            cout << "Please enter your sort choice" << endl;
            cout << "Enter 1 for bubble sort" << endl;
            cout << "Enter 2 for selection sort" << endl;
            cout << "Enter 3 for insertion sort" << endl;
            cout << "Enter 4 for counting sort" << endl;
            cout << "Enter 5 for quick sort" << endl;
            cout << "Enter 6 for merge sort" << endl;
            cin >> sortChoice;
            if (sortChoice == 1)
            {
                bubbleSort(head);
            }
            else if (sortChoice == 2)
            {
                selectionSort(head);
            }
            else if (sortChoice == 3)
            {
                insertionSort(head);
            }
            else if (sortChoice == 4)
            {
                countingSort(head);
            }
            else if (sortChoice == 5)
            {
                node* tail = lastNode(head);
                quickSort(head, tail);
            }
            else if (sortChoice == 6)
            {
                mergeSort(head);
            }
            else
            {
                cout << "Invalid choice" << endl;
            }
        }
        else if (choice == 7)
        {
            exit = true;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }


}

void PrintForward(node* head)
{
    node* temp = head;
    while (temp != nullptr)
    {
        cout << temp->ssn << endl;
        cout << temp->phoneNumber << endl;
        cout << temp->firstName << endl;
        cout << temp->lastName << endl;
        temp = temp->next;
        cout << endl;
    }

}

node* createNode()
{
    int ssn;
    long phone;
    string FirstName, LastName;
    node* temp;
    cout << "Enter employees ssn, phone number, first name, and last name: " << endl;
    cin >> ssn >> phone >> FirstName >> LastName;
    temp = new node(ssn, phone, FirstName, LastName);
    return temp;
}

void insertAtEnd(node*& head, node*& temp1)
{
    node* temp = createNode();

    if (head == nullptr) {
        head = temp;
        temp1 = head;
    }
    else {
        temp1->next = temp;
        temp->prev = temp1;
        temp1 = temp;
    }
}

void deleteNode(node*& head, int ssnToDelete) {
    if (head == nullptr) {
        cout << "List is empty. " << endl;
        return;
    }

    node* temp = head;
    node* previous = nullptr;

    while (temp != nullptr && temp->ssn != ssnToDelete) {
        previous = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Node with SSN " << ssnToDelete << " was not found in the list." << endl;
        return;
    }

    if (temp == head) {
        head = temp->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
    }
    else {
        previous->next = temp->next;
        if (temp->next != nullptr) {
            temp->next->prev = previous;
        }
        delete temp;
    }
    cout << "Node with SSN " << ssnToDelete << " has been deleted." << endl;
}

int linearSearch(node* head, int ssnToFind)
{
    node* temp = head;
    bool found = false;
    int position = -1;
    int node = 1;
    while (temp != nullptr && !found)
    {
        if (temp->ssn == ssnToFind)
        {
            position = node;
            found = true;
        }
        temp = temp->next;
        node++;
    }
    return position;
}

void bubbleSort(node*& head)
{
    int size = getCountOfNodes(head);
    node* temp = head;
    bool swapped = true;
    for (int i = size - 1; i > 0 && swapped; i--)
    {
        temp = head;
        swapped = false;
        for (int j = 0; j < i; j++)
        {
            if (temp->ssn > temp->next->ssn)
            {
                swapNodes(temp, temp->next);
                swapped = true;
            }
            temp = temp->next;
        }

    }
}

void selectionSort(node*& head)
{

    node* temp = head;
    node* min_Node = nullptr;
    while (temp)
    {
        min_Node = minNode(temp);
        swapNodes(temp, min_Node);
        temp = temp->next;
    }

}
node* minNode(node* head)
{
    if (head == nullptr) {
        return nullptr;
    }

    node* temp = head;
    node* minNode = temp;

    while (temp != nullptr)
    {
        if (temp->ssn < minNode->ssn)
        {
            minNode = temp;
        }
        temp = temp->next;
    }

    return minNode;
}

void insertionSort(node*& head)
{
    node* start = new node(0, 0, "", "");
    start->next = head;
    node* curr = head;
    node* prev = start;

    while (curr)
    {
        if (curr->next && (curr->next->ssn < curr->ssn))
        {
            while (prev->next && (prev->next->ssn < curr->next->ssn))
                prev = prev->next;


            node* temp = prev->next;
            prev->next = curr->next;
            curr->next = curr->next->next;
            prev->next->next = temp;

            prev = start;
        }
        else
        {
            curr = curr->next;
        }
    }

    head = start->next;
}

void quickSort(node* low, node* high)
{
    if (high != nullptr && low != high && low != high->next)
    {
        node* pivot = partition(low, high);
        quickSort(low, pivot->prev);
        quickSort(pivot->next, high);
    }
}


node* partition(node* low, node* high) {
    int pivot = low->ssn;
    node* pivotNode = low;
    node* i = low->next;

    while (i != nullptr && i != high->next) {
        if (i->ssn < pivot) {
            swapNodes(pivotNode->next, i);
            swapNodes(pivotNode, pivotNode->next);
            pivotNode = pivotNode->next;
        }
        i = i->next;
    }

    return pivotNode;
}


void countingSort(node*& head)
{

    node* temp = head;

    vector<Employee> vect;
    while (temp != nullptr)
    {
        vect.push_back(Employee(temp->ssn, temp->phoneNumber, temp->firstName, temp->lastName));
        temp = temp->next;
    }

    int maxSSN = vect[0].getSSN();

    for (int i = 1; i < vect.size(); i++) {
        int ssn = vect[i].getSSN();
        if (ssn > maxSSN) {
            maxSSN = ssn;
        }
    }

    vector<int> count(maxSSN + 1, 0);

    for (int i = 0; i < vect.size(); i++) {
        count[vect[i].getSSN()]++;
    }


    for (int i = 1; i <= maxSSN; i++) {
        count[i] += count[i - 1];
    }


    vector<Employee> output(vect.size());


    for (int i = vect.size() - 1; i >= 0; i--) {
        int index = count[vect[i].getSSN()] - 1;
        output[index] = vect[i];
        count[vect[i].getSSN()]--;
    }
    temp = head;
    for (int i = 0; i < output.size(); i++)
    {
        temp->ssn = output[i].getSSN();
        temp->phoneNumber = output[i].getPhoneNumber();
        temp->firstName = output[i].getFirstName();
        temp->lastName = output[i].getLastName();
        temp = temp->next;
    }


}
void mergeSort(node*& head)
{
    if (!head || !head->next)
        return;

    node* second = split(head);

    mergeSort(head);
    mergeSort(second);

    head = merge(head, second);
}

node* merge(node* first, node* second)
{

    if (!first)
        return second;


    if (!second)
        return first;


    if (first->ssn < second->ssn)
    {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = nullptr;
        return first;
    }
    else
    {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}
node* split(node* head)
{
    node* end = head;
    node* middle = head;
    while (end->next && end->next->next)
    {
        end = end->next->next;
        middle = middle->next;
    }
    node* temp = middle->next;
    middle->next = nullptr;
    return temp;

}


void swapNodes(node*& x, node*& y)
{
    int temp1 = x->ssn;
    long temp2 = x->phoneNumber;
    string temp3 = x->firstName;
    string temp4 = x->lastName;


    x->ssn = y->ssn;
    x->phoneNumber = y->phoneNumber;
    x->firstName = y->firstName;
    x->lastName = y->lastName;

    y->ssn = temp1;
    y->phoneNumber = temp2;
    y->firstName = temp3;
    y->lastName = temp4;
}

int getCountOfNodes(node* head)
{
    int count = 0;
    node* temp = head;
    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

node* lastNode(node* head)
{
    while (head && head->next)
        head = head->next;
    return head;
}
