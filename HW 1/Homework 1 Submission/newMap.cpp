#include "newMap.h"
#include <iostream>
using namespace std;

Map::Map()    //constructor
{
	reserved = 0;
	map_count = DEFAULT_MAX_ITEMS;
	p1 = new set[DEFAULT_MAX_ITEMS];
}

Map::Map(int MAXIMUM)
{
	if (MAXIMUM < 0)
	{
		exit(1);
	}
	reserved = 0;
	map_count = MAXIMUM;
	p1 = new set[map_count];
}

Map::~Map()
{
	delete[] p1;
}

Map::Map(const Map& other)      //copy constructor
{
	map_count = other.map_count;
	reserved = other.reserved;
	p1 = new set[map_count];

	for (int i = 0; i < map_count; i++)
	{
		p1[i] = other.p1[i];
	}


}

Map& Map::operator=(const Map& rhs)  //assignment operator
{
	if (this == &rhs)
	{
		return *this;
	}

	delete[] p1;
	map_count = rhs.map_count;
	reserved = rhs.reserved;
	p1 = new set[rhs.map_count];

	for (int i = 0; i < map_count; i++)
	{
		p1[i] = rhs.p1[i];
	}


	return *this;
}

bool Map::empty() const
{
	if (reserved == 0)
		return true;
	else
		return false;
}

int Map::size() const
{
	return reserved;
}

bool Map::insert(const KeyType& key, ValueType& value)
{
	if (reserved == map_count)
	{
		return false;
	}

	for (int x = 0; x < reserved; x++)
	{
		if (p1[x].KEY == key)
			return false;
	}

	p1[reserved].KEY = key;
	p1[reserved].VALUE = value;
	reserved = reserved + 1;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	for (int y = 0; y < reserved; y++)
	{
		if (p1[y].KEY == key)
		{
			p1[y].VALUE = value;
			return true;
		}

	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	for (int z = 0; z < reserved; z++)
	{
		if (p1[z].KEY == key)
		{
			p1[z].VALUE = value;
			return true;
		}

	}

	if (reserved == map_count)
	{
		return false;
	}

	else
	{
		p1[reserved].KEY = key;
		p1[reserved].VALUE = value;
		map_count = map_count + 1;
		return true;
	}

}


bool Map::erase(const KeyType& key)
{
	for (int a = 0; a < reserved; a++)
	{
		if (p1[a].KEY == key)
		{
			for (int b = a; b < reserved - a; b++)
			{
				p1[b] = p1[b + 1];
			}
			reserved = reserved - 1;
			return true;
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const
{
	for (int c = 0; c < reserved; c++)
	{
		if (p1[c].KEY == key)
			return true;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	for (int c = 0; c < reserved; c++)
	{
		if (p1[c].KEY == key)
		{
			value = p1[c].VALUE;
			return true;
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i < reserved && i >= 0)
	{
		key = p1[i].KEY;
		value = p1[i].VALUE;
		return true;
	}
	return false;
}


void Map::swap(Map& other) /////////////
{	
	Map temp(other);
	other = *this;
	*this = temp;	
}




