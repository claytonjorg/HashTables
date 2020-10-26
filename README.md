# HashTables
Implementation of a HashTable, and password server.

### Description
Implement a hash table ADT and other supporting user interfaces. Pass server is an implementation of this hashtable to be used to store user account data (i.e. username, password, etc...). The pass server allows the user to change their passwords, write to files, dump the hashtable, and more. The pass server also contains two different types: shashproj and hashproj. The difference is shashproj hides the users inputed password while hashproj shows the password in the command line. 

### Class HashTable Header
- Public HashTable interfaces (T is the template parameter, i.e., the generic data type)

```
HashTable(size_t size = 101): Constructor. A hash table, where the size of the vector is set to prime_below(size) (where size is default  to 101), where prime_below() is a private member function of the HashTable.
~HashTable(): destructor. Deletes all elements in hash table.
bool contains(const T &x): Checks if x is in the hash table.
bool insert(const T & x): Adds x into the hash table. Doesn't add x if x is already in the hash table. Returns true if x is inserted; returns false otherwise.
bool insert (T &&x): Moves version of insert.
bool remove(const T &x): Deletes x if it is in the hash table. Returns true if x is deleted, returns false otherwise.
void clear(): Deletes all elements in the hash table.
bool load(const char *filename): Loads the contents of the file with name filename into the hash table. In the file, each line contains a single value is inserted into the hash table.
void dump(): Displays all entries in the hash table. Elements in one entry of the hash table (linked list) are separated by the tab character ("\t")
bool write_to_file(const char *filename): Writes all elements in the hash table into a file with name filename. Each element occupies one line.
```

- Private HashTable interfaces (T is the template parameter)

```
void makeEmpty(): Deletes all elements in the hash table. The public interface clear() will call this function.
void rehash(): Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
size_t myhash(const T &x): Returns the index of the vector entry where x should be stored. 
unsigned long prime_below (unsigned long): Determines the proper prime numbers used in setting up the vector size.
void setPrimes(vector<unsigned long>&): Determines the proper prime numbers used in setting up the vector size.
```

### 
