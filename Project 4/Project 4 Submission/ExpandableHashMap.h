// ExpandableHashMap.h

// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.

#ifndef EXPANDABLEHASHMAP
#define EXPANDABLEHASHMAP
#include <functional>


//template<typename KeyType, typename ValueType>
//unsigned int hasher(const KeyType& k);  //prototype mentioned in the spec

template<typename KeyType, typename ValueType>
class ExpandableHashMap
{
public:
	ExpandableHashMap(double maximumLoadFactor = 0.5);
	~ExpandableHashMap();
	void reset();
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
	int m_buckets;           //how many buckets (capacity)
	int m_numberOfItems;     //how many are filled
	double m_maxLoad;

	double calculateLoadFactor();  //this is my own function
	void cleanup();  //this is my own function

	struct Node
	{
		KeyType k;
		ValueType v;
		Node* next;
	};

	Node** bucketPtr;
};

template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::ExpandableHashMap(double maximumLoadFactor)
{
	m_buckets = 8;
	m_maxLoad = maximumLoadFactor;
	m_numberOfItems = 0;

	//creating a linked list with everything pointing to nullptr at first
	bucketPtr = new Node * [m_buckets];
	for (int i = 0; i < m_buckets; i++)
	{
		bucketPtr[i] = nullptr;
	}
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::cleanup()   //deletes everything (basically destructs)
{
	for (int i = 0; i < m_buckets; i++)
	{
		Node* ptr = bucketPtr[i];
		while (ptr != nullptr)
		{
			Node* deleteThis = ptr;
			ptr = ptr->next;
			delete deleteThis;
		}
	}
	delete[] bucketPtr;
}


template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::~ExpandableHashMap() { cleanup(); }

template<typename KeyType, typename ValueType>
void ExpandableHashMap< KeyType, ValueType>::reset()
{
	cleanup();

	m_numberOfItems = 0;
	m_buckets = 8;

	bucketPtr = new Node * [m_buckets];  //basically just constructing the thing over from scratch
	for (int i = 0; i < m_buckets; i++)
	{
		bucketPtr[i] = nullptr;
	}
}

template<typename KeyType, typename ValueType>
int ExpandableHashMap<KeyType, ValueType>::size() const
{
	//returns the amount of associations in the map
	return m_numberOfItems;
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
	unsigned int hasher(const KeyType & k);			//prototype mentioned in the spec

	//case where the hash table doesn't need to be resized
	ValueType* val = find(key);  //val = v
	if (val != nullptr)
	{
		*val = value;
		return;
	}


	//case where the table has to be resized
	double newLoadFactor = (((1.0 * m_numberOfItems) + 1.0) / (1.0 * m_buckets));
	if (newLoadFactor >= m_maxLoad || calculateLoadFactor() == m_maxLoad)
	{
		//have to make copies of the previous data
		int oldSize = m_buckets;
		Node** oldTable = bucketPtr;

		//have to create a new table to store data in
		m_buckets = m_buckets * 2;
		bucketPtr = new Node * [m_buckets];
		for (int i = 0; i < m_buckets; i++)
		{
			bucketPtr[i] = nullptr;
		}

		//have to copy over the data from the old table to the new table
		for (int j = 0; j < oldSize; j++)
		{
			if (oldTable[j] != nullptr) //if there is data in this spot, then
			{
				Node* deleteThis;
				Node* newData = oldTable[j];
				while (newData != nullptr)
				{
					//get a new hash and bucketIndex
					unsigned int Index = hasher(newData->k);
					int bucketIndex = Index % m_buckets;

					//insert a new node into the corresponding bucket (with the appropriate data inside it)
					Node* entryNode = new Node;
					entryNode->k = newData->k;
					entryNode->v = newData->v;
					entryNode->next = bucketPtr[bucketIndex];
					bucketPtr[bucketIndex] = entryNode;

					//delete the old entry now
					deleteThis = newData;
					newData = newData->next;
					delete deleteThis;
				}
			}
		}
		delete[] oldTable;
	}

	//determine hash and the new bucket for the item to associate with
	unsigned int Index = hasher(key);
	int bucketIndex = Index % m_buckets;

	//insert the new node into the corresponding bucket
	Node* freshNode = new Node;
	freshNode->v = value;
	freshNode->k = key;
	freshNode->next = bucketPtr[bucketIndex];
	bucketPtr[bucketIndex] = freshNode;
	m_numberOfItems++;
}

template<typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap<KeyType, ValueType>::find(const KeyType& key) const
{
	unsigned int hasher(const KeyType & k);			//prototype mentioned in the spec
	unsigned int Index = hasher(key);				//index to find the thing you're looking for
	int bucketIndex = Index % m_buckets;

	Node* search = bucketPtr[bucketIndex];

	for (; search != nullptr; )
	{
		if (search->k == key)
		{
			return &(search->v);  //& is so that it is modifiable
		}

		else
		{
			search = search->next;
		}
	}
	return nullptr;
}

template<typename KeyType, typename ValueType>
double ExpandableHashMap<KeyType, ValueType>::calculateLoadFactor()
{
	double loadFactor = (1.0 * m_numberOfItems) / (1.0 * m_buckets);  //multiply by 1.0 to make it a double
	return loadFactor;
}

#endif
