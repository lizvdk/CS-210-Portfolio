#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("myfirstprogram");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functinon you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"myfirstprogram");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functinon you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"myfirstprogram");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	// printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void displayMenu() {
	cout << endl
		 << "******************* MENU ********************" << endl
		 << "1: Display frequency of all items" << endl
		 << "2: Display frequency of a specific item" << endl
		 << "3: View Histogram" << endl
		 << "4: Exit" << endl
		 << "*********************************************" << endl;
}

/*
Description:
	Prompts user for int until valid input is received.
	https://www.youtube.com/watch?v=m2P5A4nR51g
Example:
	int input = getValidIntInput()
Return:
	Returns integer from cin.
*/
int getValidIntInput() {
	int input;

	while (!(cin >> input)) {
		// Explain error
		cout << "ERROR: an integer must be entered: ";
		// Clear input stream
		cin.clear();
		// Discard previous input
		cin.ignore(132, '\n');
	}

	return input;
}

int getMenuSelection() {
	int selection;
	cout << "Enter your selection as a number 1, 2, 3, or 4: ";
	selection = getValidIntInput();

	return selection;
}

/*
Description:
	Prints histogram bar with label.
Example:
	printBarWithLabel("Apples", 3);
Return:
	prints "Apples ***"
	return void
*/
void printBarWithLabel(string label, int length) {
	// Print label
	cout << setw(12) << label << " ";

	// Print `length` number of asterisks.
	for (int i = 0; i < length; i++) {
		cout << "*";
	}
	
	cout << endl;
}

void printFrequencyOfAllItems() {
	// Call Python function
	CallProcedure("PrintFrequencyOfAllItems");
}

void printFrequenyOfItem() {
	string itemName;
	
	// Prompt a user to input the item, or word, they wish to look for.
	cout << "Enter item name: ";
	cin >> itemName;
	
	// Write a C++ function to take the user’s inputand pass it to Python.
	int frequencyOfItem;
	frequencyOfItem = callIntFunc("FrequencyOfItem", itemName);
	
	// Display the value returned from Python.
	cout << itemName << " purchase count: " << frequencyOfItem << endl;
}

void writeFrequencyToFile() {
	// C++ prompts Python to execute its relevant function to create the dat file.
	CallProcedure("OutputFrequencyToFile");
}

void printHistogram() {
	ifstream inFS; // Input file stream
	string currLine;
	
	writeFrequencyToFile();

	// Open input file.
	inFS.open("frequency.dat");

	// Return error if there is a problem opening the input file.
	if (!inFS.is_open()) {
		cout << "Could not open file frequency.dat." << endl;
	}

	// Loop through the newly created file and read the name and frequency on each row.
	while (!inFS.eof()) {  	// Get lines from input file until the end of file is reached.
		getline(inFS, currLine);

		if (!inFS.fail()) {
			// Split the line contents into item and frequency.
			int spaceIndex = currLine.find(' ');
			string item = currLine.substr(0, spaceIndex);
			string frequency = currLine.substr(spaceIndex, currLine.size() - 1);

			printBarWithLabel(item, stoi(frequency));
		}
	}

	// Close file
	inFS.close();
}

void handleMenuSelection(int selection) {
	switch (selection) {
	case 1:
		printFrequencyOfAllItems();
		break;
	case 2:
		printFrequenyOfItem();
		break;
	case 3:
		printHistogram();
		break;
	case 4:
		cout << "Goodbye!" << endl;
		break;
	default:
		cout << "Invalid menu selection" << endl;
		break;
	}
}

void main() {
	int menuSelection = 1;
	int const QUIT_PROGRAM = 4;

	// Loop menu until user selects option '4' to quit.
	do {
		displayMenu();
		menuSelection = getMenuSelection();
		handleMenuSelection(menuSelection);
	} while (menuSelection != QUIT_PROGRAM);
}