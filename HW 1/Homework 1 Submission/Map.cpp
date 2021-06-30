#include <iostream>
#include "Map.h"
using namespace std;

Map::Map()
{
	map_count = 0;
}

bool Map::empty() const
{
	if (map_count == 0)
		return true;
	else 
		return false;
}

int Map::size() const
{
	return map_count;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (map_count == DEFAULT_MAX_ITEMS)
	{
		return false;
	}

	for (int x = 0; x < map_count; x++)
	{
		if (MAP[x].KEY == key)
			return false;
	}

	MAP[map_count].KEY = key;
	MAP[map_count].VALUE = value;
	map_count = map_count + 1;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	for (int y = 0; y < map_count; y++)
	{
		if (MAP[y].KEY == key)
		{
			MAP[y].VALUE = value;
			return true;
		}

	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	for (int z = 0; z < map_count; z++)
	{
		if (MAP[z].KEY == key)
		{
			MAP[z].VALUE = value;
			return true;
		}

	}

	if (map_count == DEFAULT_MAX_ITEMS)
	{
		return false;
	}
	
	else
	{
		MAP[map_count].KEY = key;
		MAP[map_count].VALUE = value;
		map_count = map_count + 1;
	}
	return true;
}

bool Map::erase(const KeyType& key)
{
	for (int a = 0; a < map_count; a++)
	{
		if (MAP[a].KEY == key)
		{
			for (int b = a; b < map_count - a; b++)
			{
				MAP[b] = MAP[b + 1];
			}
			map_count = map_count - 1;
			return true;
		}
	}
	return false;
}


bool Map::contains(const KeyType& key) const
{
	for (int c = 0; c < map_count; c++)
	{
		if (MAP[c].KEY == key)
			return true;
	}
	return false;
}


bool Map::get(const KeyType& key, ValueType& value) const
{
	for (int c = 0; c < map_count; c++)
	{
		if (MAP[c].KEY == key)
		{
			value = MAP[c].VALUE;
			return true;
		}
	}
	return false;
}


bool Map::get(int i, std::string& key, ValueType& value) const
{
	if (i < map_count && i >= 0)
	{
		key = MAP[i].KEY;
		value = MAP[i].VALUE;
		return true;
	}
	return false;
}

/*  template for swap function
	temp = a;
	a = b;
	b = temp
*/

void Map::swap(Map& other)
{
	Map temp;
	temp = other;


	other.map_count = map_count;
	for (int d = 0; d < map_count; d++)
	{
		other.MAP[d].VALUE = MAP[d].VALUE;
		other.MAP[d].KEY = MAP[d].KEY;
	}

	map_count = temp.map_count;
	for (int e = 0; e < map_count; e++)
	{
		MAP[e].VALUE = temp.MAP[e].VALUE;
		MAP[e].KEY = temp.MAP[e].KEY;
	}
}




