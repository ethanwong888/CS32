#include "provided.h"
#include "ExpandableHashMap.h"
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

class PointToPointRouterImpl
{
public:
	PointToPointRouterImpl(const StreetMap* sm);
	~PointToPointRouterImpl();
	DeliveryResult generatePointToPointRoute(
		const GeoCoord& start,
		const GeoCoord& end,
		list<StreetSegment>& route,
		double& totalDistanceTravelled) const;
private:
	const StreetMap* streetmap;
    auto compare(const GeoCoord&, const GeoCoord&);
};

PointToPointRouterImpl::PointToPointRouterImpl(const StreetMap* sm)
{
	streetmap = sm;
}

PointToPointRouterImpl::~PointToPointRouterImpl()
{

}

DeliveryResult PointToPointRouterImpl::generatePointToPointRoute(
	const GeoCoord& start,
	const GeoCoord& end,
	list<StreetSegment>& route,
	double& totalDistanceTravelled) const
{
	ExpandableHashMap<GeoCoord, bool> encountered;   //used to keep track of the streetsegments that have been encountered
												     //(the bool doesn't really mean anything, its just a placeholder because something has to be there for this thing to construct)
	ExpandableHashMap<GeoCoord, GeoCoord> locationOfPreviousWayPoint;
	totalDistanceTravelled = 0;
	queue<GeoCoord> coordQueue;
	vector<StreetSegment> streetVector;

	vector<StreetSegment> startTest;
	if (streetmap->getSegmentsThatStartWith(start, startTest) == false)  //starting location was not valid (false)
	{
		return BAD_COORD;
	}

	vector<StreetSegment> endTest;
	if (streetmap->getSegmentsThatStartWith(end, endTest) == false)    //destination was not valid (false)
	{
		return BAD_COORD;
	}
	
	coordQueue.push(start);
	

	while (!coordQueue.empty())
	{
		GeoCoord current = coordQueue.front();
		coordQueue.pop();


		if (current == end)   //your current location is the destination, delivery is successful
		{
			GeoCoord ptr = *locationOfPreviousWayPoint.find(end);   
			while (*locationOfPreviousWayPoint.find(ptr) != start)
			{
				vector<StreetSegment> newSeg;
				streetmap->getSegmentsThatStartWith(ptr, newSeg);
				string streetName;
				for (int i = 0; i < newSeg.size(); i++)
				{
					if (newSeg[i].end == *locationOfPreviousWayPoint.find(ptr))
					{
						streetName = newSeg[i].name;
					}
				}

				StreetSegment ss = StreetSegment(ptr, *locationOfPreviousWayPoint.find(ptr), streetName);
				totalDistanceTravelled += distanceEarthMiles(ptr, *locationOfPreviousWayPoint.find(ptr));
				ptr = *locationOfPreviousWayPoint.find(ptr);		//changing the GeoCoord that the ptr is looking at so it goes to one previous
				//route.insert(route.begin(), ss);
				route.push_back(ss);
			}
			route.reverse();
			return DELIVERY_SUCCESS;
		}

		//finding adjacent streets (going out in concentric circles to find the destination)
		if (streetmap->getSegmentsThatStartWith(current, streetVector) == true) //(true)  
		{
			//heuristic for how far away something is from the destination
			auto compare = [&end](const StreetSegment left, const StreetSegment right)
			{
				return distanceEarthMiles(left.end, end) < distanceEarthMiles(right.end, end);
			};

			//sort(streetVector.begin(), streetVector.begin() + min(limit, streetVector.size()), compare);
			sort(streetVector.begin(), streetVector.end(), compare);

			for (int i = 0; i < streetVector.size(); i++)
			{
				if (encountered.find(streetVector[i].end) == nullptr)  //if this streetsegment isn't in the hash map
				{
					encountered.associate(streetVector[i].end, true);  //associate the streetsegment so it appears in the hashmap now
					coordQueue.push(streetVector[i].end);		   //push this GeoCoord into the queue
					locationOfPreviousWayPoint.associate(streetVector[i].end, current);  //associate current GeoCoord with the one that led up to it
				}
			}

		}
	}
	return NO_ROUTE;
}




//******************** PointToPointRouter functions ***************************

// These functions simply delegate to PointToPointRouterImpl's functions.
// You probably don't want to change any of this code.

PointToPointRouter::PointToPointRouter(const StreetMap* sm)
{
	m_impl = new PointToPointRouterImpl(sm);
}

PointToPointRouter::~PointToPointRouter()
{
	delete m_impl;
}

DeliveryResult PointToPointRouter::generatePointToPointRoute(
	const GeoCoord& start,
	const GeoCoord& end,
	list<StreetSegment>& route,
	double& totalDistanceTravelled) const
{
	return m_impl->generatePointToPointRoute(start, end, route, totalDistanceTravelled);
}
