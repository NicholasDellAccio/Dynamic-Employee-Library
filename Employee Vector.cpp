#include <vector>
#include <iostream>
#include <random>
#include <string>


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
int linearSearch(vector<Employee> vect, int target);
int binarySearch(vector<Employee> vect, int target);
void printVector(vector<Employee>& vect);
void selectionSort(vector<Employee>& vect);
void bubbleSort(vector<Employee>& vect);
void insertionSort(vector<Employee>& vect);
void quickSort(vector<Employee>& vect, int start, int end);
int partition(vector <Employee>& vect, int start, int end);
void mergeSort(vector<Employee>& vect, int p, int r);
void merge(vector<Employee>& vect, int p, int q, int r);
void swap(Employee& x, Employee& y);
void countingSort(vector<Employee>& vect);
void deleteEmployee(vector<Employee>& vect, int target);
Employee createEmployee();
int main()
{
	vector<Employee> vect;
	int size;
	int choice;
	bool exit = false;
	int employeeToDelete;
	int target;
	cout << "MENU: " << endl;
	cout << "Enter 1 to make a list of employees" << endl;
	cout << "Enter 2 display the list from the beginning" << endl;
	cout << "Enter 3 to insert a empolyee at the end of the list" << endl;
	cout << "Enter 4 to delete a employee from the list" << endl;
	cout << "Enter 5 to search for a employee in the list" << endl;
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
				vect.push_back(createEmployee());
			}
		}
		else if (choice == 2)
		{
			printVector(vect);
		}
		else if (choice == 3)
		{
			vect.push_back(createEmployee());
		}
		else if (choice == 4)
		{
			if (vect.size() == 0)
			{
				cout << "List is empty" << endl;
			}
			else
			{
				cout << "Enter a snn to delete: " << endl;
				cin >> employeeToDelete;
				deleteEmployee(vect, employeeToDelete);
			}

		}
		else if (choice == 5)
		{
			cout << "Enter a snn to find: " << endl;
			cin >> target;
			cout << "That snn is at index " << linearSearch(vect, target) << endl;
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
				bubbleSort(vect);
			}
			else if (sortChoice == 2)
			{
				selectionSort(vect);
			}
			else if (sortChoice == 3)
			{
				insertionSort(vect);
			}
			else if (sortChoice == 4)
			{
				countingSort(vect);
			}
			else if (sortChoice == 5)
			{
				quickSort(vect, 0, vect.size() - 1);
			}
			else if (sortChoice == 6)
			{
				mergeSort(vect, 0, vect.size() - 1);
			}
			else
			{
				cout << "Invalid choice";
			}
		}
		else if (choice == 7)
		{
			exit = true;
		}
		else
		{
			cout << "Wrong Choice" << endl;
		}
	}

	countingSort(vect);
	printVector(vect);
}

Employee createEmployee()
{
	int ssn;
	long phone;
	string FirstName, LastName;
	Employee temp;
	cout << "Enter employees ssn, phone number, first name, and last name: " << endl;
	cin >> ssn >> phone >> FirstName >> LastName;
	temp = Employee(ssn, phone, FirstName, LastName);
	return temp;

}

void deleteEmployee(vector<Employee>& vect, int target)
{
	int index = linearSearch(vect, target);
	if (index >= 0)
	{
		cout << "Employee with SSN " << target << " has been deleted." << endl;
		vect.erase(vect.begin() + index);
	}
	else
	{
		cout << "Employee with SSN " << target << " was not found in the list." << endl;
	}

}

void bubbleSort(vector<Employee>& vect)
{
	bool swapped = true;
	for (int i = vect.size() - 1; i > 0 && swapped; i--)
	{
		swapped = false;
		for (int j = 0; j < i; j++)
		{
			if (vect[j].getSSN() > vect[j + 1].getSSN())
			{
				swap(vect[j], vect[j + 1]);
				swapped = true;
			}
		}
	}
}

void selectionSort(vector<Employee>& vect)
{
	int min;
	int minIndex;
	for (int i = 0; i < vect.size() - 1; i++)
	{
		min = vect[i].getSSN();
		minIndex = i;
		for (int j = i + 1; j < vect.size(); j++)
		{
			if (min > vect[j].getSSN())
			{
				min = vect[j].getSSN();
				minIndex = j;
			}
		}
		swap(vect[i], vect[minIndex]);
	}
}
void insertionSort(vector<Employee>& vect)
{
	Employee key;
	int i;
	for (int j = 1; j < vect.size(); j++)
	{
		key = vect[j];
		i = j - 1;
		while (i >= 0 && vect[i].getSSN() > key.getSSN())
		{
			vect[i + 1] = vect[i];
			i--;
		}
		vect[i + 1] = key;
	}
}

int partition(vector<Employee>& vect, int start, int end)
{
	int pivotValue = vect[start].getSSN();
	int pivotPosition = start;

	for (int pos = start + 1; pos <= end; pos++)
	{
		if (vect[pos].getSSN() < pivotValue)
		{
			swap(vect[pivotPosition + 1], vect[pos]);
			swap(vect[pivotPosition], vect[pivotPosition + 1]);
			pivotPosition++;
		}
	}
	return pivotPosition;
}

void quickSort(vector<Employee>& vect, int start, int end)
{
	if (start < end)
	{
		int p = partition(vect, start, end);

		quickSort(vect, start, p - 1);

		quickSort(vect, p + 1, end);
	}
}
int linearSearch(vector<Employee> vect, int target)
{
	int index = 0;
	int pos = -1;
	bool found = false;
	while (!found && index < vect.size())
	{
		if (target == vect[index].getSSN())
		{
			pos = index;
			found = true;
		}
		++index;
	}
	return pos;
}


void countingSort(vector<Employee>& vect) {
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

	for (int i = 0; i < vect.size(); i++) {
		vect[i] = output[i];
	}
}


void mergeSort(vector<Employee>& vect, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		mergeSort(vect, p, q);
		mergeSort(vect, q + 1, r);
		merge(vect, p, q, r);
	}

}
void merge(vector<Employee>& vect, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	vector<Employee>L;
	vector<Employee>R;
	for (int i = 0; i < n1; i++)
		L.push_back(vect[p + i]);
	L.push_back(Employee(INT_MAX, 0, "", ""));
	for (int i = 0; i < n2; i++)
		R.push_back(vect[q + i + 1]);
	R.push_back(Employee(INT_MAX, 0, "", ""));
	int i = 0;
	int j = 0;

	for (int k = p; k <= r; k++)
	{
		if (L[i].getSSN() <= R[j].getSSN())
		{
			vect[k] = L[i];
			i = i + 1;
		}
		else
		{
			vect[k] = R[j];
			j = j + 1;
		}
	}

}





int binarySearch(vector<Employee> vect, int target)
{
	int first = 0;
	int last = vect.size() - 1;
	int middle;
	int position = -1;
	bool found = false;

	while (!found && first <= last)
	{
		middle = (first + last) / 2;

		if (vect[middle].getSSN() == target)
		{
			found = true;
			position = middle;
		}
		else if (target < vect[middle].getSSN())
			last = middle - 1;

		else
			first = middle + 1;
	}
	return position;
}


void swap(Employee& x, Employee& y)
{
	int temp1;
	long temp2;
	string temp3;

	temp1 = x.getSSN();
	x.setSSN(y.getSSN());
	y.setSSN(temp1);

	temp2 = x.getPhoneNumber();
	x.setPhoneNumber(y.getPhoneNumber());
	y.setPhoneNumber(temp2);

	temp3 = x.getFirstName();
	x.setFirstName(y.getFirstName());
	y.setFirstName(temp3);

	temp3 = x.getLastName();
	x.setLastName(y.getLastName());
	y.setLastName(temp3);

}
void printVector(vector<Employee>& vect)
{
	for (int i = 0; i < vect.size(); i++)
	{
		cout << vect[i].getSSN() << "   ";
		cout << vect[i].getPhoneNumber() << "   ";
		cout << vect[i].getFirstName() << "   ";
		cout << vect[i].getLastName() << "    ";

		cout << endl;
	}

}