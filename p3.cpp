//Jeremiah Hobbs & Scott McMaster
//P3.cpp
//June 7, 2021
//Driver file that uses the PatientPriorityQueue to facilitate commands input
//by the user.

#include "PatientPriorityQueue.h"

#include <fstream>
#include <iostream>
#include <string>
#include <regex>

using namespace std;


void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.

void execCommandsFromFileCmd(string, PatientPriorityQueue &); 
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.


int main() {
	// declare variables
	string line;

	// welcome message
	welcome();

	// process commands
	PatientPriorityQueue priQueue;
	do {
		cout << "\ntriage> ";
		getline(cin, line);
	} while (processLine(line, priQueue));

	// goodbye message
	goodbye();
}
/**
 * Processes the line passed in by the user.
 * @param line string passed by the user
 * @param priQueue queue to place the line in
 * @return true if line is processed
 */
bool processLine(string line, PatientPriorityQueue &priQueue) {
	// get command
	string cmd = delimitBySpace(line);
	if (cmd.length() == 0) {
		cout << "Error: no command given.";
		return false;
	}
	
	// process user input
	if (cmd == "help")
		help();
	else if (cmd == "add")
		addPatientCmd(line, priQueue);
	else if (cmd == "peek")
		peekNextCmd(priQueue);
	else if (cmd == "next")
		removePatientCmd(priQueue);
	else if (cmd == "list")
		showPatientListCmd(priQueue);
	else if (cmd == "load")
		execCommandsFromFileCmd(line, priQueue);
	else if (cmd == "quit")
		return false;
	else
		cout << "Error: unrecognized command: " << cmd << endl;

	return true;
}
/**
 * Adds a patient to the priority queue
 * @param line patients information
 * @param priQueue queue to add patient into.
 */
void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
    string priority, name;
    // get priority and name
    priority = delimitBySpace(line);
    if(priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }
    name = line;
    //Deletes leading and trailing space of names
    name = std::regex_replace(name, std::regex("^ +| +$|( ) +"),
                              "$1");
    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }
    if (priority == "emergency" || priority == "urgent" ||
    priority == "immediate" || priority == "minimal") {
        priQueue.add(name, priority);
    }
    else{
        cout<<"Error: invalid priority code given. \n";
    }
}
/**
 * Peek the next patient to receive help at the top of the queue
 * @param priQueue the Priority Queue
 */
void peekNextCmd(PatientPriorityQueue &priQueue) {
    if (priQueue.size() > 0) {
	cout<<"The patient in line is: " + priQueue.peek().getName()+ "\n";
}
    else{
        cout<< "Nobody is in the waiting room.\n";
    }
}
/**
 * Removes the next person from the queue.
 * @param priQueue PatientPriorityQueue
 */
void removePatientCmd(PatientPriorityQueue &priQueue) {
    if (priQueue.size() > 0) {
        cout<<"This patient will now be seen: "+ priQueue.remove().getName() +
        "\n";
    }
    else{
        cout<< "Nobody is in the waiting room.\n";
    }
}
/**
 * Shows the current patients in the list
 * @param priQueue PatientPruorityQueue to be seen
 */
void showPatientListCmd(PatientPriorityQueue &priQueue) {
    if (priQueue.size() > 0) {
        cout << "# patients waiting: " << priQueue.size() << endl;
        cout << "  Arrival #   Priority Code   Patient Name\n"
             << "+-----------+---------------+--------------+\n";
        cout << priQueue.to_string();
    }
    else{
        cout<< "Nobody is in the waiting room.\n";
    }
}
/**
 * Opens the file and reads the commands in the list
 * @param filename File to be read
 * @param priQueue PatientPriorityQueue to be filled
 */
void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
	ifstream infile;
	string line;

	// open and read from file
	infile.open(filename);
	if (infile) {
		while (getline(infile, line)) {
			cout << "\ntriage> " << line;
			// process file input 
			processLine(line, priQueue);
		} 
	} else {
		cout << "Error: could not open file.\n";
	}
	// close file
	infile.close();
}
/**
 * Eliminates space inside of lines passed to the program
 * @param s string being passed
 * @return string without space
 */
string delimitBySpace(string &s) {
	unsigned pos = 0;
	char delimiter = ' ';
	string result = ""; 

	pos = s.find(delimiter);
	if (pos != string::npos) {
		result = s.substr(0, pos);
		s.erase(0, pos + 1);
	}
	return result;
}
/**
 * Prints welcome message to the user
 */
void welcome() {
	cout<<"Hello and Welcome! \n\nThe triage nurse will determine "
       "the patient's priority based on\n"
       "their injury or illness and enter the patient's full name along with\n"
       "the urgency level based on the table above to "
       "indicate the priority.\n\n"
       "Please type in 'help' to find the list of available interactions.\n";
}
/**
 * Prints goodbye message to the user
 */
void goodbye() {
	cout<<"\nThanks for using the program. I hope everyone was able to receive"
       " help. Take care.";
}	
/**
 * Prints the available commands that the user can use.
 */
void help() {
	cout << "add <priority-code> <patient-name>\n"
<< "            Adds the patient to the triage system.\n"
<< "            <priority-code> must be one of the 4 accepted priority codes:\n"
<< "                1. immediate 2. emergency 3. urgent 4. minimal\n"
<< "            <patient-name>: patient's full legal name (may contain spaces)\n"
<< "next        Announces the patient to be seen next. Takes into account the\n"
<< "            type of emergency and the patient's arrival order.\n"
<< "peek        Displays the patient that is next in line, but keeps in queue\n"
<< "list        Displays the list of all patients that are still waiting\n"
<< "            in the order that they have arrived.\n"
<< "load <file> Reads the file and executes the command on each line\n"
<< "help        Displays this menu\n"
<< "quit        Exits the program\n";
}
