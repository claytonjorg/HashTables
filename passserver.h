/*  
	Name: Clayton Jorgensen
	Date: 04/15/2018
	Description: "passserver.h" - Stores the declarations for the passserver class
*/

#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include<iostream>
#include<string>
#include<cstring>
#include<crypt.h>
#include<utility>
#include<unistd.h>
#include<stdlib.h>

using namespace std;
using namespace data;

class PassServer																					// ---- Class PassServer Interface ----
{
	public:																							// ---- Public Interface ----

		PassServer(size_t size = 101);																// Constructor, create a hash table of the specified size 
		~PassServer();																				// Destructor
		bool load(const char* filename);															// Load a password file into the HashTable object
		bool addUser(std::pair<string, string> & kv);												// Add a new username and password
		bool addUser(std::pair<string, string> && kv);												// Move version of adduser
		bool removeUser(const string & k);															// Delete an existing user with username k
		bool changePassword(const pair<string, string> & p, const string & newpassword);			// Change an existing user's password
		bool find(const string & user) const;														// Check if a user exists (if user is in the hash table)
		void dump() const;																			// Show the structure and contents of the HashTable object to the screen
		size_t size() const;																		// Return the size of the HashTable (the number of username/password pairs in the table)
		bool write_to_file(const char* filename) const;												// Save the username and password combination into a file

	private:																						// ---- Private Interface ----

		HashTable<string, string> htable;															// Create a Hashtable
		string encrypt(const string & str);															// Encrypt the parameter str and return the encrypted string
};
#endif