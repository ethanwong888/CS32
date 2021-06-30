#include "Map.h"
//#include <iostream>

Map::Map()   //this is the constructor
{
	head = nullptr;
	amount = 0;
}

Map::Map(const Map& other) //this is the copy constructor
{
	head = nullptr;
	amount = 0;
	//amount = other.amount;/////

	for (int i = 0; i < other.size() ; i++)  //iterates through
	{
		ValueType Value;
		KeyType Key;
		other.get(i, Key, Value);  //get information about each of the other nodes
		insert(Key, Value);        //insert the nodes that were obtained in the line above and insert them, creating another linked list
	}
	
}

Map& Map::operator=(const Map& other)  //this is the assignment operator
{
	if (this != &other)  //check for aliasing 
	{
		Map temp = other;    //swap the map with other. other is not changed during the process
		swap(temp);
	}

	return *this;
}

Map::~Map()  //this is the destructor
{
	Node* alternateHead = head;       //want to keep the original head pointer intact
	while (alternateHead != nullptr)  
	{
		Node* destroy;
		destroy = alternateHead;
		alternateHead = alternateHead->next;
		delete destroy;    //loop goes along and destroys each node one-by-one
	}
}

bool Map::empty() const   //this checks whether or not there are any nodes in the linked list
{
	return (head == nullptr);
}

int Map::size() const   //this returns the amount of nodes in the linked list
{
	return amount;
}

bool Map::insert(const KeyType& key, const ValueType& value)  //this adds a node to the list
{
	bool INSERT = true;
	if (contains(key))  //can't insert a node if its key already exists within the list
	{
		INSERT = false;
		return INSERT;
	}

	
	Node* newItem = new Node;       //creating a NEW node
	//newItem = new Node;
	newItem->KEY = key;
	newItem->VALUE = value;
	
	
	if (head != nullptr)
	{
		head->prev = newItem;
	}
	
	newItem->prev = nullptr;  //this inserts the new node into the front
	newItem->next = head;
	

	head = newItem;
	amount = amount + 1;

	return INSERT;   
}

bool Map::update(const KeyType& key, const ValueType& value) //this updates the an existing node's value if it exists within the linked list
{
	bool UPDATE = true;
	Node* alternateHead = head;

	while (alternateHead != nullptr)
	{
		if (alternateHead->KEY == key)   //if the node with the specified key exists within the map
		{
			alternateHead->VALUE = value;  //change its original value to be this new value
			return UPDATE;
		}
		alternateHead = alternateHead->next;
	}

	UPDATE = false;  //if the node could not be found in the linked list or anything goes wrong, return false
	return UPDATE;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)  //inserts a new node (if possible) or updates an existing node (if possible)
{
	bool INSERTORUPDATE = true;
	if (update(key, value))
	{
		;
	}
	else
	{
		insert(key, value);
	}
	
	return INSERTORUPDATE;
}


bool Map::erase(const KeyType& key)  //this will delete a node with a specific key if it exists within the linked list
{
	bool ERASED = true;
	Node* alternateHead = head;
	while (alternateHead != nullptr)
	{
		if (key == alternateHead->KEY)
		{
			if (alternateHead->prev == nullptr)   //deleting the first node
			{
				head = alternateHead->next;   //setting head to point to the second element of the list
				if (head != nullptr)
				{
					head->prev = nullptr;
				}


				delete alternateHead;  //this will delete the first node
				amount = amount - 1;
				return true;
			}

			else if (alternateHead->next == nullptr)   //deleting last node
			{
				Node* leftSide = alternateHead->prev;
				leftSide->next = nullptr;   //this turns the second-to-last element in the linked list to become the last item of the linked list

				delete alternateHead;  //this will delete the last node
				amount = amount - 1;
				return ERASED;

			}

			else    //deleting middle nodes
			{
				Node* leftSide = alternateHead->prev;
				Node* rightSide = alternateHead->next;


				leftSide->next = rightSide;  //pointer preceding the selected node to be deleted changes its "next" value to point to node succeeding the selected node
				rightSide->prev = leftSide;  //pointer succeeding the selected node to be deleted changes its "prev" value to point to node preceding the selected node

											 //this essentially makes the selected node disappear as nothing points to it anymore
				delete alternateHead;        //this will delete the selected node
				amount = amount - 1;
				return ERASED;
			}

		}
		alternateHead = alternateHead->next;
	}
	ERASED = false;
	return ERASED;
}


bool Map::contains(const KeyType& key) const  //this checks if a node with a specific key exists within the linked list
{
	bool CONTAINS = true;
	Node* alternateHead = head;
	while (alternateHead != nullptr)
	{
		if (alternateHead->KEY == key)  //if a node with the specified key is found
		{
			return CONTAINS;            //return true
		}
		alternateHead = alternateHead->next;
	}
	CONTAINS = false;
	return CONTAINS;
}

bool Map::get(const KeyType& key, ValueType& value) const  //this sets VALUE to value if the specified key belongs to a node existing in the linked list
{
	bool GET = true;
	if (contains(key))
	{
		Node* alternate = head;
		while (alternate->KEY != key)
		{
			alternate = alternate->next;
		}
		value = alternate->VALUE;
		return GET;
	}

	else   //if the node with the specified key doesn't exist in the linked list, do nothing and return false
	{
		GET = false;
		return GET;
	}
}

bool Map::get(int i, KeyType& key, ValueType& value) const  //get to the i'th element of the linked list and set VALUE and KEY to equal value and key, respectively
{
	bool GET = true;

	if (i >= 0 && i < size())  //check if i is in bounds 
	{
		Node* alternateHead = head;
		for (int c = 0; c < i; c++)
		{
			alternateHead = alternateHead->next;
		}
		
		key = alternateHead->KEY;       //changing KEY to equal key
		value = alternateHead->VALUE;   //changing VALUE to equal value

		return GET;
	}

	else  //if i is not in bounds, do nothing and return false
	{
		GET = false;
		return GET;
	}
}


/*
TEMPLATE FOR SWAP FUNCTION --- swap function implemented below is based on this concept
	temp = a;
	a = b;
	b = temp;
*/
void Map::swap(Map& other)  //this will excahnge the contents of two maps 
{
	Node* alternateHead = head;
	head = other.head;
	other.head = alternateHead;

	int alternateAmount = size();
	amount = other.amount;
	other.amount = alternateAmount;
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
	bool outcome = true;
	Map temp1 = m1;            //helps to prevent aliasing errors
	Map temp2 = m2;
	result = temp1;            //make result contain all the same elements as m1
	

	for (int i = 0; i < temp2.size(); i++)
	{
		ValueType v;
		KeyType k;
		temp2.get(i, k, v);    //loop to get all the objects from m2

		if (result.contains(k))   //if the result contains the key, get the value from that node (to be used for comparison)
		{
			ValueType v2;
			result.get(k, v2);

			if (v != v2)    //if the two values are not equal, then the nodes must be deleted
			{
				result.erase(k);
				outcome = false;
			}
		}
		else
			result.insert(k, v);	//if there was no matching key, just insert the node
	}
	return outcome;
}



void reassign(const Map& m, Map& result)
{

	if (m.size() == 1)  //if there's only one pair, result just contains that pair
	{
		Map temp = m;
		result = temp;
		return;
	}
	
	Map temp = m;
	result = temp;   //this makes m and result identical; also prevents aliasing problems

	for (int i = 0; i < m.size(); i++)
	{
		
		ValueType v1;
		KeyType k1;

		ValueType v2;
		KeyType k2;

		if (i == (m.size() - 1))   //swapping the value from last element with value from first element
		{
			m.get(i, k1, v1);
			m.get(i - m.size() + 1, k2, v2);

			v1 = v2;

			result.update(k1, v1);

			break;
		}


		m.get(i, k1, v1);   //loop through and exchange value with value from element succeeding the current one
		m.get(i + 1, k2, v2);

		v1 = v2;

		result.update(k1, v1);   

	}
	return;
}



/*
bool Map::erase(const KeyType& key)  //this will delete a node with a specific key if it exists within the linked list
{
	bool ERASED = true;
	Node* alternateHead = head;
	while (alternateHead != nullptr)
	{
		if (key == alternateHead->KEY)
		{
			if (alternateHead->prev == nullptr)   //deleting the first node
			{
				head = alternateHead->next;   //setting head to point to the second element of the list

				delete alternateHead;  //this will delete the first node
				amount = amount - 1;
				return true;
			}

			else if (alternateHead->next == nullptr)   //deleting last node
			{
				Node* leftSide = alternateHead->prev;
				leftSide->next = nullptr;   //this turns the second-to-last element in the linked list to become the last item of the linked list

				delete alternateHead;  //this will delete the last node
				amount = amount - 1;
				return ERASED;

			}

			else    //deleting middle nodes
			{
				Node* leftSide = alternateHead->prev;
				Node* rightSide = alternateHead->next;

				leftSide->next = rightSide;  //pointer preceding the selected node to be deleted changes its "next" value to point to node succeeding the selected node
				rightSide->prev = leftSide;  //pointer succeeding the selected node to be deleted changes its "prev" value to point to node preceding the selected node

											 //this essentially makes the selected node disappear as nothing points to it anymore
				delete alternateHead;        //this will delete the selected node
				amount = amount - 1;
				return ERASED;
			}

		}
		alternateHead = alternateHead->next;
	}
	ERASED = false;
	return ERASED;
}
*/