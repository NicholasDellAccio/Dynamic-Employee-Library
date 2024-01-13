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

class DynStack
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
    node* top;
public:
    DynStack() { top = nullptr; }
    ~DynStack();
    void push();
    void pop(int&);
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
    node* getTop();
    node* getEnd();
    int getCountOfNodes(node* head);
};
void DynStack::push()
{
    int ssn;
    long phone;
    string FirstName, LastName;
    node* temp;
    cout << "Enter employees ssn, phone number, first name, and last name: " << endl;
    cin >> ssn >> phone >> FirstName >> LastName;
    temp = new node(ssn, phone, FirstName, LastName);
    if (isEmpty()) {

        top = temp;
    }
    else {
        temp->next = top;
        top->prev = temp;
        top = temp;
    }

}
void DynStack::pop(int& ssn)
{
    if (!isEmpty()) {
        ssn = top->ssn;
        node* temp = top;
        top = top->next;
        if (top != nullptr) {

            top->prev = nullptr;
        }
        delete temp;
    }
    else {
        cout << "Stack is empty. Cannot pop." << endl;
    }
}

bool DynStack::isEmpty() const
{
    return top == nullptr;
}
DynStack::~DynStack()
{
    node* garbage = top;
    while (garbage != nullptr)
    {
        top = top->next;
        garbage->next = nullptr;
        delete garbage;
        garbage = top;
    }

}
void DynStack::PrintForward()
{
    node* temp = top;
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

int DynStack::linearSearch(int ssnToFind)
{
    node* temp = top;
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


void DynStack::bubbleSort()
{
    int size = getCountOfNodes(top);
    node* temp = top;
    bool swapped = true;
    for (int i = size - 1; i > 0 && swapped; i--)
    {
        temp = top;
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
void DynStack::selectionSort()
{

    node* temp = top;
    node* min_Node = nullptr;
    while (temp)
    {
        min_Node = minNode(temp);
        swapNodes(temp, min_Node);
        temp = temp->next;
    }

}
void DynStack::insertionSort()
{
    node* start = new node(0, 0, "", "");
    start->next = top;
    node* curr = top;
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

    top = start->next;
}
void DynStack::countingSort()
{
    node* temp = top;

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
    temp = top;
    for (int i = 0; i < output.size(); i++)
    {
        temp->ssn = output[i].getSSN();
        temp->phoneNumber = output[i].getPhoneNumber();
        temp->firstName = output[i].getFirstName();
        temp->lastName = output[i].getLastName();
        temp = temp->next;
    }

}
void DynStack::quickSort(node* low, node* high)
{
    if (high != nullptr && low != high && low != high->next)
    {
        node* pivot = partition(low, high);
        quickSort(low, pivot->prev);
        quickSort(pivot->next, high);
    }
}

DynStack::node* DynStack::partition(node* low, node* high) {
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
void DynStack::mergeSort_() {
    mergeSort(top);
}

void DynStack::mergeSort(node*& top)
{
    if (!top || !top->next)
        return;

    node* second = split(top);

    mergeSort(top);
    mergeSort(second);

    top = merge(top, second);
}
DynStack::node* DynStack::merge(node* first, node* second)
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
DynStack::node* DynStack::split(node* head)
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
DynStack::node* DynStack::minNode(node* head)
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


void DynStack::swapNodes(node*& x, node*& y)
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
int DynStack::getCountOfNodes(node* head)
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

DynStack::node* DynStack::getTop()
{
    return top;
}
DynStack::node* DynStack::getEnd()
{
    node* temp = top;
    while (temp && temp->next)
        temp = temp->next;
    return temp;
}


int main()
{
    DynStack stack;
    int size;
    int choice;
    bool exit = false;
    int pop;
    int nodeToSearch;
    cout << "MENU: " << endl;
    cout << "Enter 1 to make a stack of employees" << endl;
    cout << "Enter 2 display the stack from the beginning" << endl;
    cout << "Enter 3 to push a node at the end of the stack" << endl;
    cout << "Enter 4 to pop a node from the stack" << endl;
    cout << "Enter 5 to search for a node in the stack" << endl;
    cout << "Enter 6 to sort a stack of employees" << endl;
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
                stack.push();
            }
        }
        else if (choice == 2)
        {
            stack.PrintForward();
        }
        else if (choice == 3)
        {
            stack.push();
        }
        else if (choice == 4)
        {
            stack.pop(pop);
        }
        else if (choice == 5)
        {
            cout << "Enter a snn to find: " << endl;
            cin >> nodeToSearch;
            cout << "That snn is at node " << stack.linearSearch(nodeToSearch);
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
            cout << "Enter 6 for quick sort" << endl;
            cin >> sortChoice;
            if (sortChoice == 1)
            {
                stack.bubbleSort();
            }
            else if (sortChoice == 2)
            {
                stack.selectionSort();
            }
            else if (sortChoice == 3)
            {
                stack.insertionSort();
            }
            else if (sortChoice == 4)
            {
                stack.countingSort();
            }
            else if (sortChoice == 5)
            {
                stack.quickSort(stack.getTop(), stack.getEnd());
            }
            else if (sortChoice == 6)
            {
                stack.mergeSort_();
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

    stack.~DynStack();
}

