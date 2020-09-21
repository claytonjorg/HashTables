/*
	Name: Clayton Jorgensen
	Date: 04/15/2018
	Description: "hashproj.cpp" - Is the driver program to run this project.
*/

#include<iostream>
#include "passserver.h"
#include "hashtable.h"
#include<utility>

using namespace std;

/*
	Function: Menu() : Displays the user options
*/
void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

/*
	Function: skipSpace() : Skips whitespace
*/
void skipSpace()
{
	char wspace;
	while (isspace(cin.peek()) && !cin.eof()) 
	{
		cin.get(wspace);
	}
}

/*
	Function: Main() : Main driving force behind the usablity of the program.
*/
int main() 
{
	int capacity;
	char choice;

	/* ---- Prompt User ---- */
	cout << "Enter prefered hash table capacity: ";
	cin >> capacity;
	if (capacity <= 0) 
	{
		cout << "**Input too large for prime_below()\nSet to default capacity\n11\n";
		capacity = 11;
	}
	PassServer spass(capacity);

	/* ---- Start Options Loop ---- */
	do 
	{
		Menu();
		cin >> choice;

		/* ---- Option L = Load Password File ---- */
		if (choice == 'l') 
		{
			string filename;
			cout << "Enter password file name to load from: ";
			skipSpace();
			getline(cin, filename);
			if (!spass.load(filename.c_str()))
			{
				cout << "Cannot open file " << filename << '\n';
			}
		}
		/* ---- Option A = Add a User ---- */
		else if (choice == 'a') 
		{
			string usrName;
			string psd;
			cout << "Enter user name: ";
			skipSpace();
			getline(cin, usrName);
			cout << "Enter password: ";
			skipSpace();
			getline(cin, psd);
			pair<string, string> newPair(usrName, psd);
			if (spass.addUser(newPair))
			{
				cout << "User " << usrName << " added.\n";
			}
			else
			{
				cout << "*****Error: User already exists. Could not add user.\n";
			}
		}
		/* ---- Option R = Remove a User ---- */
		else if (choice == 'r') 
		{
			string usrName;
			cout << "Enter username: ";
			skipSpace();
			getline(cin, usrName);
			if (spass.removeUser(usrName))
			{
				cout << "User " << usrName << " deleted.\n";
			}
			else
			{
				cout << "*****Error: User not found. Could not delete user.\n";
			}
		}
		/* ---- Option C = Change a User's Password ---- */
		else if (choice == 'c') 
		{
			string usrName;
			string oldpsd;
			string newpsd;
			cout << "Enter username: ";
			skipSpace();
			getline(cin, usrName);
			cout << "Enter password: ";
			skipSpace();
			getline(cin, oldpsd);
			cout << "Enter new password: ";
			skipSpace();
			getline(cin, newpsd);
			pair<string, string> oldPair(usrName, oldpsd);
			if (spass.changePassword(oldPair, newpsd))
			{
				cout << "Password changed for user " << usrName << '\n';
			}
			else
			{
				cout << "*****Error: Could not change user password.\n";
			}
		}
		/* ---- Option F = Search for a Username ---- */
		else if (choice == 'f') 
		{
			string usrName;
			cout << "Enter username: ";
			skipSpace();
			getline(cin, usrName);
			if (spass.find(usrName))
			{
				cout << "User " << "'" << usrName << "'" << " found.\n";
			}
			else
			{
				cout << "User " << "'" << usrName << "'" << " not found.\n";
			}
		}
		/* ---- Option D = Display or Dump Hashtable to Screen ---- */
		else if (choice == 'd') 
		{
			spass.dump();
		}
		/* ---- Option S = Display the current Size of the Hashtable ---- */
		else if (choice == 's') 
		{
			cout << "Size of hashtable: " << spass.size() << '\n';
		}
		/* ---- Option W = Write Password File ---- */
		else if (choice == 'w') 
		{
			string psdFilename;
			cout << "Enter password file name to write to: ";
			skipSpace();
			getline(cin, psdFilename);
			spass.write_to_file(psdFilename.c_str());
		}
		/* ---- Option X = Quit Program ---- */
		else if (choice == 'x') 
		{

		}
		else
		{
			cout << "*****Error: Invalid entry.  Try again.";
		}

	} while (choice != 'x');

	return 0;
}