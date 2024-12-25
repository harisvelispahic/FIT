#include <iostream>
#include <list>
#include <string>
#include <chrono>
using namespace std;


// For keeping track of slots in linear probing
enum SlotState { EMPTY, OCCUPIED, DELETED };

// There is a third state DELETED, which indicates that there used to be an element there, for the loop to recognize not to end there, but to continue searching for an element, since it shows that an element it is searching for maybe should have been there based on the HashFunction result. 
// Based on that information it continues searching until a Slot is not EMPTY, rather than just being OCCUPIED.
// If there was not the DELETED state, the loop would end on the condition of the element being EMPTY, which is true, but not the desired behaviour, since we want it to loop until it finds the element


struct Slot {
	int key;
	string value;
	SlotState state;

	Slot() {
		state = EMPTY;
	}
};

class HashTable {
public:

	virtual bool IsEmpty() = 0;
	
	virtual int HashFunction(int key) = 0;
	virtual void Resize() = 0;

	virtual void Insert(int key, string value) = 0;
	virtual void Remove(int key) = 0;
	virtual string Search(int key) = 0;
};

class HastTableLinearProbing : public HashTable {
	int counter;
	int capacity;
	double load_factor = 0.75;

	//pair<int, string>* Table;
	Slot* Table;

	int HashFunction(int key) override {
		return key % capacity;
	}

public:

	HastTableLinearProbing(int size)
	{
		counter = 0;
		capacity = size;
		//Table = new pair<int, string>[size];
		Table = new Slot[size];
	}
	~HastTableLinearProbing()
	{
		delete[] Table;
	}


	bool IsEmpty() override {
		return counter == 0;
	}

	void Resize() {
		int oldCapacity = capacity;
		capacity *= 2;
		Slot* oldTable = Table;

		Table = new Slot[capacity];
		counter = 0;

		for (int i = 0; i < oldCapacity; ++i) {
			if (oldTable[i].state == OCCUPIED) {
				Insert(oldTable[i].key, oldTable[i].value);
			}
		}
		delete[] oldTable;
	}


	void Insert(int key, string value) {
		if ((double)counter / capacity > load_factor)
			Resize();

		int position = HashFunction(key);
		
		while (Table[position].state == OCCUPIED) {

			position = (position + 1) % capacity;
		}
		
		Table[position].key = key;
		Table[position].value = value;
		Table[position].state = OCCUPIED;
		
		counter++;
	}

	void Remove(int key) override {
		if (IsEmpty())
			throw exception("Hash set is empty!");

		int position = HashFunction(key);

		while (Table[position].state != EMPTY) {
			if (Table[position].state == OCCUPIED && Table[position].key == key) {
				Table[position].state = DELETED;
				counter--;
				return;
			}
			position = (position + 1) % capacity;
		}
	}


	string Search(int key) override {
		int position = HashFunction(key);

		while (Table[position].state != EMPTY) {
			if (Table[position].state == OCCUPIED && Table[position].key == key) {
				return Table[position].value;
			}
			position = (position + 1) % capacity;
		}

		return "NOT_FOUND";
	}
};


class HashTableChaining : public HashTable {

	int counter;
	int capacity;
	double load_factor = 0.75;
	list<pair<int, string>>* Table;

	int HashFunction(int key) override {
		return key % capacity;
	}

public:

	HashTableChaining(int size)
	{
		counter = 0;
		capacity = size;
		Table = new list<pair<int, string>>[size];
	}
	~HashTableChaining()
	{
		delete[] Table;
	}


	bool IsEmpty() override {
		return counter == 0;
	}

	void Resize() override {

		int oldCapacity = capacity;
		capacity *= 2;

		list<pair<int, string>>* newTable = new list<pair<int, string>>[capacity];

		for (int i = 0; i < oldCapacity; i++) {
			if (!Table[i].empty()) {
				for (auto& entry : Table[i]) {
					int index = HashFunction(entry.first);
					newTable[index].push_back(entry);
				}
			}
		}

		list<pair<int, string>>* deleteTable = Table;
		Table = newTable;
		delete[] deleteTable;
	}


	void Insert(int key, string value) override {
		int index = HashFunction(key);

		// check if key exists in the i-th list

		for (auto& entry : Table[index]) {
			if (entry.first == key) {
				entry.second = value;
				return;
			}
		}

		Table[index].push_back(make_pair(key, value));
		counter++;

		if ((double)counter / capacity > load_factor)
			Resize();
	}

	void Remove(int key) override {
		int index = HashFunction(key);

		if (Table[index].empty())
			return;

		for (auto& entry : Table[index]) {
			if (entry.first == key) {
				Table[index].remove(entry);		// removes all instances of "entry", from list, but since keys are unique, it is fine
				counter--;
				return;
			}
		}
	}

	string Search(int key) override {
		int index = HashFunction(key);
		
		for (auto& entry : Table[index]) {
			if (entry.first == key)
				return entry.second;
		}

		return "NOT_FOUND";
	}

};


void HashTableTester(HashTable& hashTable, const string& tableType) {
    using namespace std::chrono;

    cout << "Testing Hash Table: " << tableType << endl;

    // Insert, remove, search
    hashTable.Insert(1, "One");
    hashTable.Insert(2, "Two");
    hashTable.Insert(3, "Three");

    cout << hashTable.Search(1) << endl;
    cout << hashTable.Search(2) << endl;
    cout << hashTable.Search(3) << endl;

    hashTable.Remove(2);
    cout << hashTable.Search(2) << endl;

    // Stress test
    srand(time(0));
    const int testSize = 100000;

    // Measure time for insertions
    auto startInsert = high_resolution_clock::now();
    for (int i = 0; i < testSize; i++) {
        int key = rand() % 10000;
        hashTable.Insert(key, "Value" + to_string(key));
    }
    auto endInsert = high_resolution_clock::now();
    auto durationInsert = duration_cast<milliseconds>(endInsert - startInsert);
    cout << "Time taken for " << testSize << " insertions: " << durationInsert.count() << " ms" << endl;

    // Measure time for deletions
    auto startRemove = high_resolution_clock::now();
    for (int i = 0; i < testSize; i++) {
        int key = rand() % 10000;
        hashTable.Remove(key);
    }
    auto endRemove = high_resolution_clock::now();
    auto durationRemove = duration_cast<milliseconds>(endRemove - startRemove);
    cout << "Time taken for " << testSize << " deletions: " << durationRemove.count() << " ms" << endl;

    cout << "Stress test completed for " << tableType << "." << endl << endl;
}


int main() {
	HashTableChaining HTC(10);
	HashTableTester(HTC, "Chaining");

	HastTableLinearProbing HTLP(10);
	HashTableTester(HTLP, "Linear Probing");

	return 0;
}