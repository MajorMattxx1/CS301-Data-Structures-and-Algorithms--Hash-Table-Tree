//no idea how to do this one

#pragma once

#include "DictTree.h"
#include<string>
#include<unordered_map>
using namespace std;

template<class KeyType, class ItemType>
class HashTable
{
public:
	HashTable();
	HashTable(int numBuckets);

	void add(KeyType key, ItemType item);
	bool remove(KeyType key);
	ItemType getItem(KeyType key);
	bool contains(KeyType key);
	int size();

	void traverse(void visit(ItemType&));

private:
	const int DEFAULT_BUCKET_NUM = 20;		// How many buckets by default
	DictTree<KeyType, ItemType>** buckets;
	int numBuckets;
	int numElems;							// How many elements stored in entire table
	int getHashIndex(const KeyType& key);
};

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable()
{
	buckets = new DictTree<KeyType, ItemType>*[DEFAULT_BUCKET_NUM];
	numBuckets = DEFAULT_BUCKET_NUM;
	numElems = 0;

	// for each bucket, set the i-th bucket equal to a new DictTree of type <KeyType, ItemType>
}

template<class KeyType, class ItemType>
HashTable<KeyType, ItemType>::HashTable(int numBucks)
{
	// See previous constructor.  Use numBucks instead of DEFAULT_BUCKET_NUM.
	buckets = new DictTree<KeyType, ItemType>*[numBucks];
	numBuckets = numBucks;
	numElems = 0;
}

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::size()
{
	return numElems;
}

template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::add(KeyType key, ItemType item)
{	
	// VERY LITTLE CODE HERE
	// Get the hash bucket Index
	int index = getHashIndex(key);
	// If the hash table does not already contain key
	//    increase numElems by one
	if (buckets[index] == 0)
		numElems++;
	// add key,item to the DictTree at a buckets index
	buckets[index]->key = key;
	buckets[index]->data = item;
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::remove(KeyType key)
{
	// VERY LITTLE CODE HERE
	// Get the hash Index
	int index = getHashIndex(key);
	// If the hash table contains the key
	//    decrease numElems by one
	//    remove the key from buckets[b]
	//    return true
	// else
	//    return false
	if (buckets[index] == key){
		numElems--;
		delete buckets[index]->key;
		return true;
	}
	else
		return false;
}

template<class KeyType, class ItemType>
ItemType HashTable<KeyType, ItemType>::getItem(KeyType key)
{
	// Get the hash bucket Index
	int index = getHashIndex(key);
	// return the item by using getItem on the correct bucket index.
	return buckets->lookupItem(index); //is this how functions from other headers are called?
	// (HINT:  Should only be 2 line of code at most.  1 is plenty.)
}

template<class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::contains(KeyType key)
{
	// Get the hash bucket Index
	int index = getHashIndex(key);

	// Use contains on the correct bucket index to return the correct true false.
	return buckets->contain(index); //is this how functions from other headers are called?
	// (HINT:  Should only be 2 lines of code at most.  1 is plenty.)
}

template<class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::getHashIndex(const KeyType & key)
{
	// This is done... No touching!
	bool touched = true;
	// We are creating a hash function type called hashFunction that hashes "KeyType."
	// First we create an an unordered_map object for our KeyType and ItemType
	unordered_map<KeyType, ItemType> mapper;

	// Then we call the hash_function method to return the hash function
	// for the KeyType and assign it to 'hashFunction'
	typename unordered_map<KeyType, ItemType>::hasher hashFunction = mapper.hash_function();

	// static_cast needed since hashFunction returns an unsigned long
	return static_cast<int>(hashFunction(key) % numBuckets);
}


template<class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::traverse(void visit(ItemType&))
{
	// You should use the traverse function of the DictTree
	buckets->traverse(); //is this how a function from another header is called?
}