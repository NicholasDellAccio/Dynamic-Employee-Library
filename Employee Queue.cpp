#include<iostream>
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

class DynQueue
{
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
    node* front;
    node* rear;
public:

    DynQueue() {
        front = nullptr;
        rear = nullptr;
    }
    ~DynQueue();
    void enqueue();
    void dequeue(int&);
    bool isEmpty() const;
    void PrintForward();
    int linearSearch(int ssnToFind);
    void bubbleSort();
    void selectionSort();
    void insertionSort();
    void countingSort();
    void quickSort(node* low, node* high);
    void mergeSort_();
    void mergeSort(node*&);
    node* merge(node*, node*);
    node* split(node*);
    void swapNodes(node*& x, node*& y);
    node* minNode(node* head);
    node* partition(node* low, node* high);
    int getCountOfNodes(node* head);
    node* getFront() { return front; }
    node* getRear() { return rear; }
};
void DynQueue::enqueue()
{
    int ssn;
    long phone;
    string FirstName, LastName;
    node* temp;
    cout << "Enter employees ssn, phone number, first name, and last name: " << endl;
    cin >> ssn >> phone >> FirstName >> LastName;
    temp = new node(ssn, phone, FirstName, LastName);
    if (isEmpty()) {

        front = temp;
        rear = temp;
    }
    else {
        rear->next = temp;
        temp->prev = rear;
        rear = temp;
    }

}
void DynQueue::dequeue(int& ssn)
{
    if (!isEmpty()) {

        ssn = front->ssn;
        node* temp = front;
        front = front->next;
        delete temp;
    }
    else {
        cout << "Stack is empty. Cannot pop." << endl;
    }
}

bool DynQueue::isEmpty() const
{
    return front == nullptr;
}
DynQueue::~DynQueue()
{
    node* garbage = front;
    while (garbage != nullptr)
    {
        front = front->next;
        garbage->next = nullptr;
        delete garbage;
        garbage = front;
    }

}
void DynQueue::PrintForward()
{
    node* temp = front;
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

int DynQueue::linearSearch(int ssnToFind)
{
    node* temp = front;
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


void DynQueue::bubbleSort()
{
    int size = getCountOfNodes(front);
    node* temp = front;
    bool swapped = true;
    for (int i = size - 1; i > 0 && swapped; i--)
    {
        temp = front;
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
void DynQueue::selectionSort()
{

    node* temp = front;
    node* min_Node = nullptr;
    while (temp)
    {
        min_Node = minNode(temp);
        swapNodes(temp, min_Node);
        temp = temp->next;
    }

}
void DynQueue::insertionSort()
{
    node* start = new node(0, 0, "", "");
    start->next = front;
    node* curr = front;
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

    front = start->next;
}
void DynQueue::countingSort()
{
    node* temp = front;

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
    temp = front;
    for (int i = 0; i < output.size(); i++)
    {
        temp->ssn = output[i].getSSN();
        temp->phoneNumber = output[i].getPhoneNumber();
        temp->firstName = output[i].getFirstName();
        temp->lastName = output[i].getLastName();
        temp = temp->next;
    }

}

void DynQueue::quickSort(node* low, node* high)
{
    if (high != nullptr && low != high && low != high->next)
    {
        node* pivot = partition(low, high);
        quickSort(low, pivot->prev);
        quickSort(pivot->next, high);
    }
}


DynQueue::node* DynQueue::partition(node* low, node* high) {
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
void DynQueue::mergeSort_() {
    mergeSort(front);
}

void DynQueue::mergeSort(node*& front)
{
    if (!front || !front->next)
        return;

    node* second = split(front);

    mergeSort(front);
    mergeSort(second);

    front = merge(front, second);
}
DynQueue::node* DynQueue::merge(node* first, node* second)
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
DynQueue::node* DynQueue::split(node* head)
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

DynQueue::node* DynQueue::minNode(node* head)
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


void DynQueue::swapNodes(node*& x, node*& y)
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
int DynQueue::getCountOfNodes(node* head)
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



int main()
{
    DynQueue queue;
    int size;
    int choice;
    bool exit = false;
    int pop;
    int nodeToSearch;
    cout << "MENU: " << endl;
    cout << "Enter 1 to make a queue of employees" << endl;
    cout << "Enter 2 display the queue from the beginning" << endl;
    cout << "Enter 3 to enqueue a node at the end of the queue" << endl;
    cout << "Enter 4 to dequeue a node from the queue" << endl;
    cout << "Enter 5 to search for a node in the queue" << endl;
    cout << "Enter 6 to sort a queue of employees" << endl;
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
                queue.enqueue();
            }
        }
        else if (choice == 2)
        {
            queue.PrintForward();
        }
        else if (choice == 3)
        {
            queue.enqueue();
        }
        else if (choice == 4)
        {
            queue.dequeue(pop);
        }
        else if (choice == 5)
        {
            cout << "Enter a snn to find: " << endl;
            cin >> nodeToSearch;
            cout << "That snn is at node " << queue.linearSearch(nodeToSearch);
        }
        else if (choice == 6)
        {
            int sortChoice;
            cout << "Please enter your sort choice" << endl;
            cout << "Enter 1 for bubble sort" << endl;
            cout << "Enter 2 for selection sort" << endl;
            cout << "Enter 3 for insertion sort" << endl;
            cout << "Enter 4 for countingSort" << endl;
            cout << "Enter 5 for quick sort" << endl;
            cout << "Enter 6 for merge sort" << endl;
            cin >> sortChoice;
            if (sortChoice == 1)
            {
                queue.bubbleSort();
            }
            else if (sortChoice == 2)
            {
                queue.selectionSort();
            }
            else if (sortChoice == 3)
            {
                queue.insertionSort();
            }
            else if (sortChoice == 4)
            {
                queue.countingSort();
            }
            else if (sortChoice == 5)
            {
                queue.quickSort(queue.getFront(), queue.getRear());
            }
            else if (sortChoice == 6)
            {

                queue.mergeSort_();
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

    queue.~DynQueue();
}

