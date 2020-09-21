/*
	Name: Clayton Jorgensen
	Date: 04/15/2018
	Description: "hashtable.hpp" - Stores the fucntion definitions for the htable class.
*/

/*
	Function: HashTable(size_t size) : Constructor, creates a hash table, where the size of the vector is set to prime_below(size) (where size is default to 101)
*/
template <typename K, typename V> data::HashTable<K, V>::HashTable(size_t size) 
{
	ArrayList.resize(prime_below(size));
	currentSize = 0;
}

/*
	Function: ~HashTable() : Destructor, deletes all elements in hash table
*/
template <typename K, typename V> data::HashTable<K, V>::~HashTable()
{
	clear();  
}

/*
	Function: resizeTable(size_t size) : Destructor, deletes all elements in hash table
*/
template<typename K, typename V> void data::HashTable<K, V>::resizeTable(size_t size)
{
	if (getSize() != size)
	{
		ArrayList.resize(prime_below(size));
		currentSize = 0;
	}
}

/*
	Function: contains(const K & k) const : Checks if key k is in the hash table
*/
template <typename K, typename V> bool data::HashTable<K, V>::contains(const K & k) const
{
	for (auto itr = ArrayList[myhash(k)].begin(); itr != ArrayList[myhash(k)].end(); ++itr)
	{  
		if (itr->first == k)
			return true;  
	}
	return false;
}

/*
	Function: match(const std::pair<K, V> & kv) const : Checks if key-value pair is in the hash table
*/
template <typename K, typename V> bool data::HashTable<K, V>::match(const std::pair<K, V> & kv) const
{
	auto & whichList = ArrayList[myhash(kv.first)];
	return std::find(whichList.begin(), whichList.end(), kv) != whichList.end();
}

/*
	Function: insert(const std::pair<K, V> & kv) : Adds the key-value pair kv into the hash table
*/
template<typename K, typename V> bool data::HashTable<K, V>::insert(const std::pair<K, V> & kv) 
{
	if (!match(kv))
	{
		if (contains(kv.first))
		{
			auto & whichList = ArrayList[myhash(kv.first)];
			for (auto itr = whichList.begin(); itr != whichList.end();)
			{
				if (itr->first == kv.first)
				{
					itr = whichList.erase(itr);
					whichList.insert(itr, kv);
				}
				else
				{
					itr++;
				}
			}
			return true;
		}
		else
		{
			ArrayList[myhash(kv.first)].push_back(kv);
			if (++currentSize > ArrayList.size())
			{
				rehash();
			}
			return true;
		}
	}
	return false;
}

/*
	Function: insert(std::pair<K, V> && kv) : Move version of insert
*/
template<typename K, typename V> bool data::HashTable<K, V>::insert(std::pair<K, V> && kv) 
{
	const std::pair<K, V> kvpair = std::move(kv);
	return insert(kvpair);  
}

/*
	Function: remove(const K & k) : Deletes the key k and the corresponding value if it is in the hash table
*/
template<typename K, typename V> bool data::HashTable<K, V>::remove(const K & k) 
{
	bool flag = false;
	auto & whichList = ArrayList[myhash(k)];
	for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
	{ 
		if (itr->first == k) 
		{
			itr = whichList.erase(itr); 
			--currentSize;
			flag = true;
		}
	}
	return flag;
}

/*
	Function: clear() : Deletes all elements in the hash table by calling makeEmpty
*/
template<typename K, typename V> void data::HashTable<K, V>::clear() 
{
	makeEmpty(); 
}

/*
	Function: load(const char* filename) : Loads the content of the file with name filename into the hash table
*/
template<typename K, typename V> bool data::HashTable<K, V>::load(const char* filename)
{
	std::pair<K, V> kvpair;
	std::ifstream fin;
	fin.open(filename, std::ifstream::in);

	if (!fin)
		return false;

	char wspace;
	while (fin) 
	{
		std::getline(fin, kvpair.first, ' ');

		while (isspace(fin.peek()))
		{
			fin.get(wspace);
		}
		std::getline(fin, kvpair.second, '\n');

		while (isspace(fin.peek()))
		{
			fin.get(wspace);
		}
		insert(kvpair);
	}

	fin.close();
	return true;
}

/*
	Function: dump() const : Display all entries in the hash table
*/
template<typename K, typename V> void data::HashTable<K, V>::dump() const 
{
	for (int i = 0; i < ArrayList.size(); i++) 
	{
		std::cout << "v[" << i << "]:";

		for (auto itr = ArrayList[i].begin(); itr != ArrayList[i].end(); ++itr)
		{
			if (itr != ArrayList[i].begin())
			{
				std::cout << ':';
			}

			std::cout << itr->first << ' ' << itr->second;
		}
		std::cout << '\n';
	}
}

/*
	Function: getSize() const : Returns the number of elements in the hash table
*/
template<typename K, typename V> int data::HashTable<K, V>::getSize() const
{
	return currentSize;
}

/*
	Function: write_to_file(const char* filename) const : Writes all elements in the hash table into a file with name filename
*/
template<typename K, typename V> bool data::HashTable<K, V>::write_to_file(const char* filename) const 
{
	std::ofstream fout;
	fout.open(filename);

	if (!fout)
		return false;

	for (int i = 0; i < ArrayList.size(); i++) 
	{
		for (auto itr = ArrayList[i].begin(); itr != ArrayList[i].end(); ++itr) 
		{
			fout << itr->first << ' ' << itr->second << '\n';
		}
	}
	fout.close();
	return true;
}

/*
	Function: makeEmpty() : Deletes all elements in the hash table
*/
template<typename K, typename V> void data::HashTable<K, V>::makeEmpty() 
{
	for (auto & thislist : ArrayList) 
	{
		ArrayList.clear(); 
	}
	currentSize = 0;
}

/*
	Function: rehash() : Rehash function, called when the number of elements in the hash table is greater than the size of the vector
*/
template<typename K, typename V> void data::HashTable<K, V>::rehash() 
{
	auto oldList = ArrayList;
	ArrayList.resize(prime_below(2 * ArrayList.size()));

	for (auto & thisList : ArrayList)
		thisList.clear();	

	currentSize = 0;
	for (auto & thisList : oldList) 
	{
		for (auto & kvpair : thisList)
			insert(std::move(kvpair));
	}
}

/*
	Function: myhash(const K & k) const : Returns the index of the vector entry where k should be stored
*/
template<typename K, typename V> size_t data::HashTable<K, V>::myhash(const K & k) const 
{
	std::hash<K> hfunc; 
	return hfunc(k) % ArrayList.size();
}

/*
	Function: prime_below(unsigned long n) : Given helper function
*/
template <typename K, typename V> unsigned long data::HashTable<K, V>::prime_below(unsigned long n)
{
	if (n > max_prime)
	{
		std::cerr << "** input too large for prime_below()\n";
		return 0;
	}
	if (n == max_prime)
	{
		return max_prime;
	}
	if (n <= 1)
	{
		std::cerr << "** input too small \n";
		return 0;
	}

	std::vector <unsigned long> v(n + 1);
	setPrimes(v);

	while (n > 2)
	{
		if (v[n] == 1)
			return n;
		--n;
	}

	return 2;
}

/*
	Function: setPrimes(std::vector<unsigned long>& vprimes) : Given helper function
*/
template <typename K, typename V> void data::HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
	int i = 0;
	int j = 0;

	vprimes[0] = 0;
	vprimes[1] = 0;
	int n = vprimes.capacity();

	for (i = 2; i < n; ++i)
	{
		vprimes[i] = 1;
	}

	for (i = 2; i*i < n; ++i)
	{
		if (vprimes[i] == 1)
		{
			for (j = i + i; j < n; j += i)
			{
				vprimes[j] = 0;
			}
		}
	}
}

