/* 
	Name: Clayton Jorgensen
	Date: 04/15/2018
	Description: "passserver.cpp" - Stores the function defintions for the passserver class
*/

#include "passserver.h"
#include "hashtable.h"

using namespace std;
using namespace data;

/*
	Function: PassServer(size_t size) : Constructor, create a hash table of the specified size 
*/
PassServer::PassServer(size_t size) 
{
	htable.resizeTable(size); 
}

/*
	Function: ~PassServer() : Destructor
*/
PassServer::~PassServer() 
{
	htable.clear();
}

/*
	Function: load(const char* filename) : Load a password file into the HashTable object
*/
bool PassServer::load(const char* filename) 
{
	return htable.load(filename);
}

/*
	Function: addUser(std::pair<string, string> & kv) : Add a new username and password
*/
bool PassServer::addUser(std::pair<string, string> & kv) 
{
	if (!htable.contains(kv.first))
	{
		string encryptedstr = encrypt(kv.second);
		pair<string, string> encryptedPair(kv.first, encryptedstr);
		htable.insert(encryptedPair);
		return true;
	}
	return false;
}

/*
	Function: addUser(std::pair<string, string> && kv) : Move version of adduser
*/
bool PassServer::addUser(std::pair<string, string> && kv) 
{
	pair<string, string> uncryptedPair(std::move(kv));
	return addUser(uncryptedPair);
}

/*
	Function: removeUser(const string & k) : Delete an existing user with username k
*/
bool PassServer::removeUser(const string & k) 
{
	htable.remove(k);
}

/*
	Function: changePassword(const pair<string, string> & p, const string & newpassword) : Change an existing user's password
*/
bool PassServer::changePassword(const pair<string, string> & p, const string & newpassword) 
{
	if (htable.contains(p.first))
	{
		if (p.second != newpassword)
		{
			string oldPassword = encrypt(p.second);
			string newPassword = encrypt(newpassword);
			pair<string, string> oldPair(p.first, oldPassword);

			if (htable.match(oldPair))
			{
				pair<string, string> newPair(p.first, newPassword);
				htable.insert(newPair);

				return true;
			}
		}
	}
	return false;
}

/*
	Function: find(const string & user) const : Check if a user exists (if user is in the hash table)
*/
bool PassServer::find(const string & user) const 
{
	return htable.contains(user);
}

/*
	Function: dump() const : Show the structure and contents of the HashTable object to the screen
*/
void PassServer::dump() const 
{
	htable.dump();
}

/*
	Function: size() const : Return the size of the HashTable (the number of username/password pairs in the table)
*/
size_t PassServer::size() const 
{
	htable.getSize();
}

/*
	Function: write_to_file(const char* filename) const : Save the username and password combination into a file
*/
bool PassServer::write_to_file(const char* filename) const 
{
	htable.write_to_file(filename);
}

/*
	Function: encrypt(const string & str) : Encrypt the parameter str and return the encrypted string
*/
string PassServer::encrypt(const string & str) 
{
	char salt[] = "$1$########";
	string cryptedstr = crypt(str.c_str(), salt);
	cryptedstr.replace(0, 12, "");
	return cryptedstr;
}