//====================================
#include "provided.h"
#include <vector>
using namespace std;

class DeliveryPlannerImpl
{
public:
	DeliveryPlannerImpl(const StreetMap* sm);
	~DeliveryPlannerImpl();
	DeliveryResult generateDeliveryPlan(
		const GeoCoord& depot,
		const vector<DeliveryRequest>& deliveries,
		vector<DeliveryCommand>& commands,
		double& totalDistanceTravelled) const;
private:
	const StreetMap* streetmap;
};



//helper function====================================================================================================================
string AngleOfSegment(double angleOfSegment)
{
	string DIRECTION;
	if (0 <= angleOfSegment && angleOfSegment < 22.5)
	{
		DIRECTION = "east";
	}
	else if (22.5 <= angleOfSegment && angleOfSegment < 67.5)
	{
		DIRECTION = "northeast";
	}
	else if (67.5 <= angleOfSegment && angleOfSegment < 112.5)
	{
		DIRECTION = "north";
	}
	else if (112.5 <= angleOfSegment && angleOfSegment < 157.5)
	{
		DIRECTION = "northwest";
	}
	else if (157.5 <= angleOfSegment && angleOfSegment < 202.5)
	{
		DIRECTION = "west";
	}
	else if (202.5 <= angleOfSegment && angleOfSegment < 247.5)
	{
		DIRECTION = "southwest";
	}
	else if (247.5 <= angleOfSegment && angleOfSegment < 292.5)
	{
		DIRECTION = "south";
	}
	else if (292.5 <= angleOfSegment && angleOfSegment < 337.5)
	{
		DIRECTION = "southeast";
	}
	else if (angleOfSegment >= 337.5)
	{
		DIRECTION = "east";
	}
	return DIRECTION;
}


string AngleBetweenTwoSegments(double angle)
{
	string DIRECTION;
	if (0 <= angle && angle < 22.5)
	{
		DIRECTION = "east";
	}
	else if (22.5 <= angle && angle < 67.5)
	{
		DIRECTION = "northeast";
	}
	else if (67.5 <= angle && angle < 112.5)
	{
		DIRECTION = "north";
	}
	else if (112.5 <= angle && angle < 157.5)
	{
		DIRECTION = "northwest";
	}
	else if (157.5 <= angle && angle < 202.5)
	{
		DIRECTION = "west";
	}
	else if (202.5 <= angle && angle < 247.5)
	{
		DIRECTION = "southwest";
	}
	else if (247.5 <= angle && angle < 292.5)
	{
		DIRECTION = "south";
	}
	else if (292.5 <= angle && angle < 337.5)
	{
		DIRECTION = "southeast";
	}
	else if (angle >= 337.5)
	{
		DIRECTION = "east";
	}
	return DIRECTION;
}



















DeliveryPlannerImpl::DeliveryPlannerImpl(const StreetMap* sm)
{
	streetmap = sm;
}

DeliveryPlannerImpl::~DeliveryPlannerImpl()
{

}

DeliveryResult DeliveryPlannerImpl::generateDeliveryPlan(
	const GeoCoord& depot,
	const vector<DeliveryRequest>& deliveries,
	vector<DeliveryCommand>& commands,
	double& totalDistanceTravelled) const
{
	totalDistanceTravelled = 0;
	vector<DeliveryRequest> newDeliveries = deliveries;

	vector<DeliveryRequest>::iterator it;
	for (it = newDeliveries.begin(); it != newDeliveries.end(); it++)
	{
		//depot to the first delivery location===================================================================================
		if (it == newDeliveries.begin())
		{
			list<StreetSegment> tempStreetList1;
			list <StreetSegment> streetList;
			double distance = 0;
			double tempDistance = 0;
			PointToPointRouter* pop = new PointToPointRouter(streetmap);

			//want to check if the route even exists
			if (pop->generatePointToPointRoute(depot, (*it).location, tempStreetList1, tempDistance) == NO_ROUTE)
			{
				//cout << "no\n";
				return NO_ROUTE;
			}
			else if (pop->generatePointToPointRoute(depot, (*it).location, tempStreetList1, tempDistance) == BAD_COORD)
			{
				//cout << "no\n";
				return BAD_COORD;
			}
			//if the route does exist, then
			else
			{
				//cout << "yes\n";
				pop->generatePointToPointRoute(depot, (*it).location, streetList, distance);
			}


			//convert the streetList into a vector (just makes things a bit easier for me down the line)
			vector <StreetSegment> streetVec;
			list<StreetSegment>::iterator it2;
			for (it2 = streetList.begin(); it2 != streetList.end(); it2++)
			{
				//cout << (*it2).start.latitudeText << endl;
				streetVec.push_back(*(it2));
			}

			StreetSegment special;  //used to record the last special/unique streetsegment
			string direction;
			double distanceOfSegment = 0;

			vector <StreetSegment>::iterator it3;
			for (it3 = streetVec.begin(); it3 != streetVec.end(); it3++)
			{
				//first streetsegment is always unique
				if (it3 == streetVec.begin())
				{
					//gets the length of the streetsegment
					distanceOfSegment = distanceOfSegment + distanceEarthMiles((*it3).start, (*it3).end);
					special = (*it3);
				}

				double angleOfSegment = angleOfLine(special);
				direction = AngleOfSegment(angleOfSegment);

				//combines two consecutive streetSegments if they have the same name
				if (it3 != (streetVec.end() - 1) && ((*it3).name == (*(it3 + 1)).name))
				{
					if (it3 != streetVec.begin())
					{
						distanceOfSegment += distanceEarthMiles((*it3).start, (*(it3)).end);
					}
					continue;
				}

				//dealing with two separate streetSegments that have different names
				else if (it3 != (streetVec.end() - 1) && (*it3).name != (*(it3 + 1)).name)  /////
				{
					if (it3 != streetVec.begin())
					{
						distanceOfSegment = distanceOfSegment + distanceEarthMiles((*(it3)).start, (*(it3)).end);
					}

					//adding the "proceed" command for this stretch of street
					DeliveryCommand delivery;
					delivery.initAsProceedCommand(direction, special.name, distanceOfSegment);
					commands.push_back(delivery);
					totalDistanceTravelled = distanceOfSegment + totalDistanceTravelled;
					distanceOfSegment = 0;

					if (it3 != (streetVec.end() - 1))
					{
						//after the above action is completed, the next streetSegment should have a differnt name (adjust "special" accordingly)
						special = (*(it3 + 1));
					}
				}

				//if at the final streetsegment
				if (it3 == (streetVec.end() - 1))
				{
					DeliveryCommand extra;
					double tempDist = distanceEarthMiles((*(streetVec.end() - 1)).end, (*(streetVec.end() - 2)).end);
					extra.initAsProceedCommand(direction, special.name, tempDist);
					commands.push_back(extra);
					totalDistanceTravelled = tempDist + totalDistanceTravelled;
					DeliveryCommand delivery3;
					delivery3.initAsDeliverCommand((*(it)).item);
					commands.push_back(delivery3);
					break;
				}

				DeliveryCommand delivery2;
				double angleOfTurn = angleBetween2Lines(*it3, *(it3 + 1));
				string direction2;
				double angle = angleOfLine(*it3);

				if (angleOfTurn >= 180 && angleOfTurn <= 359)
				{
					delivery2.initAsTurnCommand("right", (*(it3 + 1)).name);
				}

				else if (angleOfTurn >= 1 && angleOfTurn < 180)
				{
					delivery2.initAsTurnCommand("left", (*(it3 + 1)).name);
				}

				else if (angleOfTurn < 1 || angleOfTurn > 359)
				{
					direction2 = AngleBetweenTwoSegments(angle);

					double distanceToProceed = distanceEarthMiles((*(it3 + 1)).start, (*(it3 + 1)).end);
					delivery2.initAsProceedCommand(direction2, (*(it3 + 1)).name, distanceToProceed);
					it3++;
					if (it3 == (streetVec.end() - 1))
					{
						commands.push_back(delivery2);
						DeliveryCommand delivery3;
						delivery3.initAsDeliverCommand(((*(it)).item));
						commands.push_back(delivery3);
						break;
					}
				}
				commands.push_back(delivery2);
			}
			delete pop;
		}
		//end of delivery from depot to first location=========================================================================



		//last delivery point, then return to depot============================================================================
		if (it == (newDeliveries.end() - 1))
		{
			list <StreetSegment> tempStreetList1;
			list <StreetSegment> streetList;
			double distance = 0;
			double tempDistance = 0;
			PointToPointRouter* pop = new PointToPointRouter(streetmap);

			//want to check if the route even exists
			if (pop->generatePointToPointRoute((*it).location, depot, tempStreetList1, tempDistance) == NO_ROUTE)
			{
				return NO_ROUTE;
			}
			else if (pop->generatePointToPointRoute((*it).location, depot, tempStreetList1, tempDistance) == BAD_COORD)
			{
				return BAD_COORD;
			}
			//if the route does exist, then
			else
			{
				pop->generatePointToPointRoute((*it).location, depot, streetList, distance);
			}


			//convert the streetList into a vector (just makes things a bit easier for me down the line)
			vector <StreetSegment> streetVec;
			list<StreetSegment>::iterator it2;
			for (it2 = streetList.begin(); it2 != streetList.end(); it2++)
			{
				streetVec.push_back(*(it2));
			}

			StreetSegment special;  //used to record the last special/unique streetsegment
			string direction;
			double distanceOfSegment = 0;

			vector <StreetSegment>::iterator it3;
			for (it3 = streetVec.begin(); it3 != streetVec.end(); it3++)
			{
				//for the first streetsegment
				if (it3 == streetVec.begin())
				{
					//gets the length of the streetsegment
					distanceOfSegment = distanceOfSegment + distanceEarthMiles((*it3).start, (*it3).end);
					special = *it3;
				}

				double angleOfSegment = angleOfLine(special);
				direction = AngleOfSegment(angleOfSegment);

				//combines two consecutive streetSegments if they have the same name
				if (it3 != (streetVec.end() - 1) && ((*it3).name == (*(it3 + 1)).name))
				{
					if (it3 != streetVec.begin())
					{
						distanceOfSegment += distanceEarthMiles((*it3).start, ((*it3)).end);
					}
					continue;
				}

				//dealing with two separate streetSegments that have different names
				else if (it3 != (streetVec.end() - 1) && ((*it3).name != (*(it3 + 1)).name))
				{
					if (it3 != streetVec.begin())
					{
						distanceOfSegment = distanceOfSegment + distanceEarthMiles((*it3).start, (*(it3)).end);
					}

					//adding the "proceed" command for this stretch of street
					DeliveryCommand delivery;
					delivery.initAsProceedCommand(direction, special.name, distanceOfSegment);
					commands.push_back(delivery);
					totalDistanceTravelled = distanceOfSegment + totalDistanceTravelled;
					distanceOfSegment = 0;

					if (it3 != (streetVec.end() - 1))
					{
						//after the above action is completed, the next streetSegment should have a different name (adjust "special" accordingly)
						special = (*(it3 + 1));
					}
				}


				if (it3 == (streetVec.end() - 1))
				{
					double tempDist = distanceEarthMiles((*(streetVec.end() - 1)).end, (*(streetVec.end() - 2)).end);
					DeliveryCommand extra;
					extra.initAsProceedCommand(direction, special.name, tempDist);
					totalDistanceTravelled = tempDist + totalDistanceTravelled;
					commands.push_back(extra);
					break;
				}

				DeliveryCommand delivery2;
				double angleOfTurn = angleBetween2Lines(*it3, *(it3 + 1));
				string direction2;
				double angle = angleOfLine(*it3);

				if (angleOfTurn >= 180 && angleOfTurn <= 359)
				{
					delivery2.initAsTurnCommand("right", (*(it3 + 1)).name);
				}

				else if (angleOfTurn >= 1 && angleOfTurn < 180)
				{
					delivery2.initAsTurnCommand("left", (*(it3 + 1)).name);
				}

				else if (angleOfTurn < 1 || angleOfTurn > 359)
				{
					direction2 = AngleBetweenTwoSegments(angle);

					double distanceToProceed = distanceEarthMiles((*(it3 + 1)).start, (*(it3 + 1)).end);
					delivery2.initAsProceedCommand(direction2, (*(it3 + 1)).name, distanceToProceed);
					it3++;
					if (it3 == streetVec.end() - 1)
					{
						double tempDist = distanceEarthMiles((*(streetVec.end() - 1)).end, (*(streetVec.end() - 2)).end);
						DeliveryCommand extra;
						extra.initAsProceedCommand(direction, special.name, tempDist);
						totalDistanceTravelled = tempDist + totalDistanceTravelled;
						commands.push_back(extra);
						break;
					}
				}
				commands.push_back(delivery2);
			}
			delete pop;
			break;
		}
		//end of delivery from last destination to depot===================================================================



		//all deliveries in between========================================================================================
		//cout << "Next delivery" << endl;
		list <StreetSegment> tempStreetList1;
		list <StreetSegment> streetList;
		double distance;
		double tempDistance;
		PointToPointRouter* pop = new PointToPointRouter(streetmap);

		//want to check if the route even exists
		if (pop->generatePointToPointRoute((*it).location, (*(it + 1)).location, tempStreetList1, tempDistance) == NO_ROUTE)
		{
			//cout << "no_route\n";
			return NO_ROUTE;
		}
		else if (pop->generatePointToPointRoute((*it).location, (*(it + 1)).location, tempStreetList1, tempDistance) == BAD_COORD)
		{
			//cout << "bad_coord\n";
			return BAD_COORD;
		}
		//if the route does exist, then generate the route
		else
		{
			//cout << "generating\n";
			//cout << (*it).item << " " << (*(it + 1)).item << "\n";
 			pop->generatePointToPointRoute((*it).location, (*(it + 1)).location, streetList, distance);
		}

		//cout << streetList.size() << endl;
		//convert the streetList into a vector (just makes things a bit easier for me down the line)
		vector <StreetSegment> streetVec;
		list<StreetSegment>::iterator it2;
		for (it2 = streetList.begin(); it2 != streetList.end(); it2++)
		{
			//cout << (*it2).start.latitudeText << endl;
			streetVec.push_back(*(it2));
		}

		//cout << streetVec.size() << endl;

		StreetSegment special;  //used to record the last special/unique streetsegment
		string direction;
		double distanceOfSegment = 0;
		bool has_Street_Changed = 0;
		
		DeliveryCommand temp;
		vector <StreetSegment>::iterator it3;
		for (it3 = streetVec.begin(); it3 != streetVec.end(); it3++)
		{
			//getting the first streetSegment
			if (it3 == streetVec.begin())
			{
				//gets the length of the streetsegment
				distanceOfSegment = distanceOfSegment + distanceEarthMiles((*it3).start, (*it3).end);
				special = *it3;
			}

			double angleOfSegment = angleOfLine(special);
			direction = AngleOfSegment(angleOfSegment);

			//combines two consecutive streetSegments if they have the same name
			if (it3 != (streetVec.end() - 1) && ((*it3).name == (*(it3 + 1)).name))
			{
				if (it3 != streetVec.begin())
				{
					distanceOfSegment += distanceEarthMiles((*it3).start, (*(it3)).end);
				}
				continue;
			}

			//dealing with two separate streetSegments that have different names
			else if (it3 != (streetVec.end() - 1) && ((*it3).name != (*(it3 + 1)).name))
			{
				has_Street_Changed = 1;
				if (it3 != streetVec.begin())
				{
					distanceOfSegment = distanceOfSegment + distanceEarthMiles((*it3).start, (*(it3)).end);
				}

				//adding the "proceed" command for this stretch of street
				DeliveryCommand delivery;
				delivery.initAsProceedCommand(direction, special.name, distanceOfSegment);
				temp = delivery;
				commands.push_back(delivery);
				totalDistanceTravelled = distanceOfSegment + totalDistanceTravelled;
				distanceOfSegment = 0;

				if (it3 != (streetVec.end() - 1))
				{
					//after the above action is completed, the next streetSegment should have a different name (adjust "special" accordingly)
					special = (*(it3 + 1));
				}
			}

			//at the final streetsegment, need to deliver now
			if (it3 == (streetVec.end() - 1))
			{
				//cout << (*it3).start.latitudeText << endl;

				//DeliveryCommand extra;
				if (!has_Street_Changed)
				{
					double tempDist = distanceOfSegment + distanceEarthMiles((*(streetVec.end() - 1)).end, (*(streetVec.end() - 2)).end);
					temp.initAsProceedCommand(direction, special.name, tempDist);
					totalDistanceTravelled = tempDist + totalDistanceTravelled;
					commands.push_back(temp);
				}
				else
				{
					double tempDist = distanceEarthMiles((*(streetVec.end() - 1)).end, (*(streetVec.end() - 2)).end);
					temp.initAsProceedCommand(direction, special.name, tempDist);
					totalDistanceTravelled = tempDist + totalDistanceTravelled;
					commands.push_back(temp);
				}
				
				DeliveryCommand delivery3;
				delivery3.initAsDeliverCommand((*(it + 1)).item);
				//cout << "pushing\n";
				commands.push_back(delivery3);
				//cout << "pushed\n";
				break;
			}
			DeliveryCommand delivery2;
			double angleOfTurn = angleBetween2Lines(*it3, *(it3 + 1));
			string direction2;
			double angle = angleOfLine(*it3);

			if (angleOfTurn >= 180 && angleOfTurn <= 359)
			{
				delivery2.initAsTurnCommand("right", (*(it3 + 1)).name);
			}

			else if (angleOfTurn >= 1 && angleOfTurn < 180)
			{
				delivery2.initAsTurnCommand("left", (*(it3 + 1)).name);
			}

			else if (angleOfTurn < 1 || angleOfTurn > 359)
			{
				direction2 = AngleBetweenTwoSegments(angle);

				double distanceToProceed = distanceEarthMiles((*(it3 + 1)).start, (*(it3 + 1)).end);
				delivery2.initAsProceedCommand(direction2, (*(it3 + 1)).name, distanceToProceed);
				it3++;
				if (it3 == (streetVec.end() - 1))
				{
					commands.push_back(delivery2);
					cout << "pushed\n";
					DeliveryCommand delivery3;
					delivery3.initAsDeliverCommand((*(it + 1)).item);
					commands.push_back(delivery3);
					break;
				}
			}

			commands.push_back(delivery2);

		}
		delete pop;

	} //end of giant for loop

	return DELIVERY_SUCCESS;
} //end of function








////helper function====================================================================================================================
//string AngleOfSegment(double angleOfSegment)
//{
//	string DIRECTION;
//	if (0 <= angleOfSegment && angleOfSegment < 22.5)
//	{
//		DIRECTION = "east";
//	}
//	else if (22.5 <= angleOfSegment && angleOfSegment < 67.5)
//	{
//		DIRECTION = "northeast";
//	}
//	else if (67.5 <= angleOfSegment && angleOfSegment < 112.5)
//	{
//		DIRECTION = "north";
//	}
//	else if (112.5 <= angleOfSegment && angleOfSegment < 157.5)
//	{
//		DIRECTION = "northwest";
//	}
//	else if (157.5 <= angleOfSegment && angleOfSegment < 202.5)
//	{
//		DIRECTION = "west";
//	}
//	else if (202.5 <= angleOfSegment && angleOfSegment < 247.5)
//	{
//		DIRECTION = "southwest";
//	}
//	else if (247.5 <= angleOfSegment && angleOfSegment < 292.5)
//	{
//		DIRECTION = "south";
//	}
//	else if (292.5 <= angleOfSegment && angleOfSegment < 337.5)
//	{
//		DIRECTION = "southeast";
//	}
//	else if (angleOfSegment >= 337.5)
//	{
//		DIRECTION = "east";
//	}
//	return DIRECTION;
//}
//
//
//string AngleBetweenTwoSegments(double angle)
//{
//	string DIRECTION;
//	if (0 <= angle && angle < 22.5)
//	{
//		DIRECTION = "east";
//	}
//	else if (22.5 <= angle && angle < 67.5)
//	{
//		DIRECTION = "northeast";
//	}
//	else if (67.5 <= angle && angle < 112.5)
//	{
//		DIRECTION = "north";
//	}
//	else if (112.5 <= angle && angle < 157.5)
//	{
//		DIRECTION = "northwest";
//	}
//	else if (157.5 <= angle && angle < 202.5)
//	{
//		DIRECTION = "west";
//	}
//	else if (202.5 <= angle && angle < 247.5)
//	{
//		DIRECTION = "southwest";
//	}
//	else if (247.5 <= angle && angle < 292.5)
//	{
//		DIRECTION = "south";
//	}
//	else if (292.5 <= angle && angle < 337.5)
//	{
//		DIRECTION = "southeast";
//	}
//	else if (angle >= 337.5)
//	{
//		DIRECTION = "east";
//	}
//	return DIRECTION;
//}

















//******************** DeliveryPlanner functions ******************************

// These functions simply delegate to DeliveryPlannerImpl's functions.
// You probably don't want to change any of this code.

DeliveryPlanner::DeliveryPlanner(const StreetMap* sm)
{
	m_impl = new DeliveryPlannerImpl(sm);
}

DeliveryPlanner::~DeliveryPlanner()
{
	delete m_impl;
}

DeliveryResult DeliveryPlanner::generateDeliveryPlan(
	const GeoCoord& depot,
	const vector<DeliveryRequest>& deliveries,
	vector<DeliveryCommand>& commands,
	double& totalDistanceTravelled) const
{
	return m_impl->generateDeliveryPlan(depot, deliveries, commands, totalDistanceTravelled);
}

