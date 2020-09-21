/*
	Name: Clayton Jorgensen
	Date: 04/15/2018
	Description: "hashtable.h" - Stores the class declarations for the class htable.
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H
 
#include<vector>
#include<list>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<functional>
#include<cctype>

namespace data															// ---- Namespace Interface ----
{
	template<typename K, typename V>
	class HashTable															// ---- Class HashTable Interface ----
	{
		public:																// ---- Public Interface ----

			explicit HashTable(size_t size = 101);							// Constructor, creates a hash table, where the size of the vector is set to prime_below(size) (where size is default to 101)
			~HashTable();													// Destructor, deletes all elements in hash table

			void resizeTable(size_t size);									// Resizes the table, helper function

			bool contains(const K & k) const;								// Checks if key k is in the hash table
			bool match(const std::pair<K, V> & kv) const;					// Checks if key-value pair is in the hash table
			bool insert(const std::pair<K, V> & kv);						// Adds the key-value pair kv into the hash table
			bool insert(std::pair<K, V> && kv);								// Move version of insert
			bool remove(const K & k);										// Deletes the key k and the corresponding value if it is in the hash table
			void clear();													// Deletes all elements in the hash table
			bool load(const char* filename);								// Loads the content of the file with name filename into the hash table
			void dump() const;												// Display all entries in the hash table
			int getSize() const;											// Returns the number of elements in the hash table
			bool write_to_file(const char* filename) const;					// Writes all elements in the hash table into a file with name filename

		private:															// ---- Private Interface ---- \\
		
			std::vector< std::list< std::pair<K, V> > > ArrayList;			// Array of linked-list, each link is a pair
			int currentSize;												// Stores the current size

			void makeEmpty();												// Deletes all elements in the hash table
			void rehash();													// Rehash function, called when the number of elements in the hash table is greater than the size of the vector
			size_t myhash(const K & k) const;								// Returns the index of the vector entry where k should be stored

			unsigned long prime_below(unsigned long);						// Given helper function
			void setPrimes(std::vector<unsigned long> &);					// Given helper function

			static const unsigned int max_prime = 1301081;
			static const unsigned int default_capacity = 11;
	};

#include "hashtable.hpp"
}

#endif
