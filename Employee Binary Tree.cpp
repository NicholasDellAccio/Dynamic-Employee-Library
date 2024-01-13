

#include <iostream>
using namespace std;

struct TreeNode {
    int ssn;
    long phoneNumber;
    string firstName;
    string lastName;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int ssn, long phone, string fn, string ln, TreeNode* L = nullptr, TreeNode* R = nullptr)
    {
        this->ssn = ssn;
        phoneNumber = phone;
        firstName = fn;
        lastName = ln;
        left = L;
        right = R;
    }
};

TreeNode* createNode();
void insert(TreeNode*&, TreeNode*);
bool search(TreeNode*, int);
void makeDeletion(TreeNode*&);
void remove(TreeNode*&, int);
void printInOrder(TreeNode*);
void printPreOrder(TreeNode*);
void printPostOrder(TreeNode*);


int main()
{
    TreeNode* root = nullptr;
    int size;
    int choice;
    bool exit = false;
    int nodeToDelete;
    int nodeToSearch;
    cout << "MENU: " << endl;
    cout << "Enter 1 to mulitple Employees to a binary tree" << endl;
    cout << "Enter 2 to add one Employee to the tree" << endl;
    cout << "Enter 3 to print the tree in order" << endl;
    cout << "Enter 4 to print the tree in preorder" << endl;
    cout << "Enter 5 to print the tree in postorder" << endl;
    cout << "Enter 6 to search if a Employee exists" << endl;
    cout << "Enter 7 to delete a Employee in the tree" << endl;
    cout << "Enter 8 to exit" << endl;
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
                insert(root, createNode());
            }
        }
        else if (choice == 2)
        {
            insert(root, createNode());
        }
        else if (choice == 3)
        {
            printInOrder(root);
        }
        else if (choice == 4)
        {
            printPreOrder(root);
        }
        else if (choice == 5)
        {
            printPostOrder(root);
        }
        else if (choice == 6)
        {
            cout << "Enter a snn to find: " << endl;
            cin >> nodeToSearch;
            if (search(root, nodeToSearch))
            {
                cout << "That Employee exists" << endl;
            }
            else
            {
                cout << "That Employee does not exists" << endl;
            }
        }
        else if (choice == 7)
        {
            cout << "Enter a snn to delete: " << endl;
            cin >> nodeToDelete;
            remove(root, nodeToDelete);
        }
        else if (choice == 8)
        {
            exit = true;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }


}
TreeNode* createNode()
{
    int ssn;
    long phone;
    string FirstName, LastName;
    TreeNode* temp;
    cout << "Enter employees ssn, phone number, first name, and last name: " << endl;
    cin >> ssn >> phone >> FirstName >> LastName;
    temp = new TreeNode(ssn, phone, FirstName, LastName);
    return temp;
}
void insert(TreeNode*& root, TreeNode* newNode)
{

    if (root == nullptr)
        root = newNode;
    if (root->ssn == newNode->ssn)
        return;
    if (newNode->ssn < root->ssn)
        insert(root->left, newNode);
    if (newNode->ssn > root->ssn)
        insert(root->right, newNode);
}

bool search(TreeNode* root, int val)
{
    if (root == nullptr)
    {
        return false;
    }
    else if (root->ssn == val)
    {
        return true;
    }
    else if (root->ssn < val)
    {
        search(root->right, val);
    }
    else if (root->ssn > val)
    {
        search(root->left, val);
    }
}

void remove(TreeNode*& tree, int num)
{
    if (tree == nullptr) return;
    if (num < tree->ssn)
        remove(tree->left, num);
    else if (num > tree->ssn)
        remove(tree->right, num);
    else
        makeDeletion(tree);
}
void makeDeletion(TreeNode*& tree)
{
    TreeNode* nodeToDelete = tree;
    TreeNode* attachPoint;

    if (tree->right == nullptr)
    {
        tree = tree->left;
    }
    else if (tree->left == nullptr)
    {
        tree = tree->right;
    }
    else
    {
        attachPoint = tree->right;
        while (attachPoint->left != nullptr) {
            attachPoint = attachPoint->left;
        }
        attachPoint->left = tree->left;
        tree = tree->right;
    }
    delete nodeToDelete;
}

void printInOrder(TreeNode* q)
{
    if (q != nullptr)
    {
        printInOrder(q->left);
        cout << q->ssn << " " << q->phoneNumber << " " << q->firstName << " " << q->lastName << endl;
        printInOrder(q->right);
    }
}
void printPreOrder(TreeNode* q)
{
    if (q != nullptr)
    {
        cout << q->ssn << " " << q->phoneNumber << " " << q->firstName << " " << q->lastName << endl;
        printPreOrder(q->left);
        printPreOrder(q->right);

    }
}

void printPostOrder(TreeNode* q)
{
    if (q != nullptr)
    {

        printPostOrder(q->left);
        printPostOrder(q->right);
        cout << q->ssn << " " << q->phoneNumber << " " << q->firstName << " " << q->lastName << endl;
    }

}