#include "provided.h"
#include "ExpandableHashMap.h"
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
using namespace std;


unsigned int hasher(const GeoCoord& g)
{
	return std::hash<std::string>()(g.latitudeText + g.longitudeText);
}

//unsigned int hasher()
//{
//	//overloaded function
//}

class StreetMapImpl
{
public:
	StreetMapImpl();
	~StreetMapImpl();
	bool load(string mapFile);
	bool getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const;
private:
	ExpandableHashMap <GeoCoord, vector<StreetSegment>>* m_ptr;
};

StreetMapImpl::StreetMapImpl()
{
	m_ptr = new ExpandableHashMap<GeoCoord, vector<StreetSegment>>();
}

StreetMapImpl::~StreetMapImpl()
{
	delete m_ptr;
	m_ptr = nullptr;
}

bool StreetMapImpl::load(string mapFile)
{
	//ifstream infile("C:/Users/e1234/OneDrive/Desktop/skeleton/mapdata.txt");
	ifstream infile(mapFile);

	if (!infile)
	{
		return false;
	}

	std::string str;
	int k;
	string startLatitude, startLongitude, endLatitude, endLongitude, newline;
	while (getline(infile, str))
	{
		infile >> k;   //reading in the number of street segments from the .txt file 
		infile.ignore(10000, '\n');

		for (int i = 0; i < k; i++)   //get the latitudes and longitudes based on how many there are associated with that street segment
		{
			infile >> startLatitude;
			infile >> startLongitude;
			infile >> endLatitude;
			infile >> endLongitude;
			infile.ignore(10000, '\n');
			//infile >> newline;

			GeoCoord start = GeoCoord(startLatitude, startLongitude);
			GeoCoord end = GeoCoord(endLatitude, endLongitude);

			//convert starting and ending GeoCoord to a streetsegment
			StreetSegment s = StreetSegment(start, end, str);
			StreetSegment f = StreetSegment(end, start, str);


			//find() and then push back into the vector of street segments
			vector<StreetSegment>* a = m_ptr->find(start);
			
			if (a == nullptr)
			{		
				vector<StreetSegment> newVec;
				newVec.push_back(s);
				m_ptr->associate(start, newVec);
			} 
			else
			{
				a->push_back(s);
				m_ptr->associate(start, *a);
			}
			  //push back a streetsegment into the vector

			vector<StreetSegment>* b = m_ptr->find(end);
			if (b == nullptr)
			{
				vector<StreetSegment> newVec;
				newVec.push_back(f);
				m_ptr->associate(end, newVec);
			}

			else
			{
				b->push_back(f);
				m_ptr->associate(end, *b);
			}
		}
	}
	return true;  
}

bool StreetMapImpl::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
	//retrieve all of the StreetSegments and reversed
	//StreetSegments whose start geo - coordinate matches the GeoCoord parameter gc, and place
	//them in the segs reference parameter

	//unsigned int bucketIndex = hasher(gc);
	if (m_ptr->find(gc) != nullptr)
	{
		segs = *m_ptr->find(gc);
		return true;
	}
	return false;
}

//******************** StreetMap functions ************************************

// These functions simply delegate to StreetMapImpl's functions.
// You probably don't want to change any of this code.

StreetMap::StreetMap()
{
	m_impl = new StreetMapImpl;
}

StreetMap::~StreetMap()
{
	delete m_impl;
}

bool StreetMap::load(string mapFile)
{
	return m_impl->load(mapFile);
}

bool StreetMap::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
	return m_impl->getSegmentsThatStartWith(gc, segs);
}
