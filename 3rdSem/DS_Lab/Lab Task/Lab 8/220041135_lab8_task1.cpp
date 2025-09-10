#include <iostream>
#include <unordered_map>

using namespace std;

int hashFunction(int x, int tableSize)
{
    return x % tableSize;
}




void insertLinear(int key, unordered_map<int, int>& hashTable, int tableSize, int& insertedItems)
{
    int index = hashFunction(key, tableSize);
    int attempts = 0;
    while (attempts < 6)
    {
        if (hashTable.find(index) == hashTable.end()) //no collision
        {
            hashTable[index] = key;
            insertedItems++;
            cout << "Inserted : Index-" << index << " (L.F=" << (double)insertedItems / tableSize << ")\n";
            return;
        }
        else // collision
        {
            cout << "Collision: Index-" << index << "\n";
            index = (index + 1) % tableSize;
            attempts++;
        }
    }
    cout << "Input Abandoned\n";
}

void insertQuadratic(int key, unordered_map<int, int>& hashTable, int tableSize, int& insertedItems)
{
    int index = hashFunction(key, tableSize);
    int attempts = 0;
    int i = 1;
    while (attempts < 6)
    {
        if (hashTable.find(index) == hashTable.end()) //no collision ///checking whether index is present in the hash table
        {
            hashTable[index] = key;
            insertedItems++;
            cout << "Inserted : Index-" << index << " (L.F="  << (double)insertedItems / tableSize << ")\n";
            return;
        }
        else // collision
        {
            cout << "Collision: Index-" << index << "\n";
            index = (hashFunction(key, tableSize) + i * i) % tableSize;
            attempts++;
            i++;
        }
    }
    cout << "Input Abandoned\n";
}

void insertDoubleHashing(int key, unordered_map<int, int>& hashTable, int tableSize, int& insertedItems)
{
    int index = hashFunction(key, tableSize);
    int hash2Value = 7-(key%7);
    int attempts = 0;
    int i = 1;
    while (attempts < 6)
    {
        if (hashTable.find(index) == hashTable.end()) //no collision
        {
            hashTable[index] = key;
            insertedItems++;
            cout << "Inserted : Index-" << index << " (L.F="  << (double)insertedItems / tableSize << ")\n";
            return;
        }
        else // collision
        {
            cout << "Collision: Index-" << index << "\n";
            index = (hashFunction(key, tableSize) + i * hash2Value) % tableSize;
            attempts++;
            i++;
        }
    }
    cout << "Input Abandoned\n";
}

int main()
{
    int choice, tableSize, queries;
    cin >> choice >> tableSize >> queries;

    unordered_map<int, int> hashTable;
    int insertedItems = 0;

    for (int i = 0; i < queries; i++)
    {
        int key;
        cin >> key;
        if (choice == 1)
        {
            insertLinear(key, hashTable, tableSize, insertedItems);
        }
        else if (choice == 2)
        {
            insertQuadratic(key, hashTable, tableSize, insertedItems);
        }
        else if (choice == 3)
        {
            insertDoubleHashing(key, hashTable, tableSize, insertedItems);
        }
    }

    return 0;
}
