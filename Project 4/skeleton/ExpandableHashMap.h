// ExpandableHashMap.h

// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.

#ifndef EXPANDABLEHASHMAP
#define EXPANDABLEHASHMAP
#include <functional>

template<typename KeyType, typename ValueType>
struct Node
{
	Node <KeyType, ValueType>(KeyType key, ValueType value, Node <KeyType, ValueType> *next)
	{
		m_key = key;
		m_value = value;
		m_next = next;
	}
	Node *m_next;
	KeyType m_key;
	ValueType m_value;
};

template<typename KeyType, typename ValueType>
class ExpandableHashMap
{
public:
	ExpandableHashMap(double maximumLoadFactor = 0.5);
	~ExpandableHashMap();
	void reset();
	void cleanup();
	int size() const;
	void associate(const KeyType& key, const ValueType& value);

	  // for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const;

	  // for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const ExpandableHashMap*>(this)->find(key));
	}

	  // C++11 syntax for preventing copying and assignment
	ExpandableHashMap(const ExpandableHashMap&) = delete;
	ExpandableHashMap& operator=(const ExpandableHashMap&) = delete;

private:
	double getLoadFactor();
	unsigned int hash(const GeoCoord& key);
	void cleanup();
	int m_buckets;           //how many buckets (capacity)
	int m_numberOfItems;     //how many are filled
	double m_maxLoad;  
	Node <KeyType, ValueType> ** m_hashTable;  //use double pointer for 2D array
};

<typename KeyType, typename ValueType>
ExpandableHashMap<typename KeyType, typename ValueType>::ExpandableHashMap(double maximumLoadFactor)
{
	m_buckets = 8;
	m_maxLoad = maximumLoadFactor;
	m_numberOfItems = 0;
	for (int i = 0; i < m_hashTable.size(); i++)
	{
		m_hashTable[i] = nullptr;
	}
}

<typename KeyType, typename ValueType>
ExpandableHashMap<typename KeyType, typename ValueType>::~ExpandableHashMap()
{

}

<typename KeyType, typename ValueType>
void ExpandableHashMap<typename KeyType, typename ValueType>::reset()
{
}

<typename KeyType, typename ValueType>
int ExpandableHashMap<typename KeyType, typename ValueType>::size() const
{
    return -999;  // Delete this line and implement this function correctly
}

<typename KeyType, typename ValueType>
void ExpandableHashMap<typename KeyType, typename ValueType>::associate(const KeyType& key, const ValueType& value)
{
}

<typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap<typename KeyType, typename ValueType>::find(const KeyType& key) const
{
    return nullptr;  // Delete this line and implement this function correctly
}

<typename KeyType, typename ValueType>
void ExpandableHashMap<typename KeyType, typename ValueType>::cleanup()
{
	for (int i = 0; i < m_buckets; i++)
	{
		while (m_hashTable[i] != nullptr)
		{
			Node <KeyType, ValueType> *wantToDelete = m_hashTable[i];
			m_hashTable[i] = m_hashTable[i]->next;
			delete wantToDelete;
		}
		m_hashTable[i] = nullptr;
	}
	delete[] m_hashTable;
};

#endif