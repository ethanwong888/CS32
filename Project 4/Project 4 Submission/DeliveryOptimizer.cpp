#include "provided.h"
#include <vector>
using namespace std;

class DeliveryOptimizerImpl
{
public:
	DeliveryOptimizerImpl(const StreetMap* sm);
	~DeliveryOptimizerImpl();
	void optimizeDeliveryOrder(
		const GeoCoord& depot,
		vector<DeliveryRequest>& deliveries,
		double& oldCrowDistance,
		double& newCrowDistance) const;
};

DeliveryOptimizerImpl::DeliveryOptimizerImpl(const StreetMap* sm)
{
}

DeliveryOptimizerImpl::~DeliveryOptimizerImpl()
{
}

void DeliveryOptimizerImpl::optimizeDeliveryOrder(
	const GeoCoord& depot,
	vector<DeliveryRequest>& deliveries,
	double& oldCrowDistance,
	double& newCrowDistance) const
{
	oldCrowDistance = 0;  // Delete these lines and implement this function correctly
	vector<DeliveryRequest>::iterator it;
	for (it = deliveries.begin(); it != deliveries.end(); it++)
	{
		if (it == deliveries.begin())
		{
			oldCrowDistance = oldCrowDistance + distanceEarthMiles(depot, (*it).location);
		}	

		if (it == deliveries.end() - 1)
		{
			oldCrowDistance = oldCrowDistance + distanceEarthMiles((*it).location, depot);
			break;
		}
		oldCrowDistance = oldCrowDistance + distanceEarthMiles((*it).location, ((*(it + 1)).location));
	}
	newCrowDistance = oldCrowDistance;
}

//******************** DeliveryOptimizer functions ****************************

// These functions simply delegate to DeliveryOptimizerImpl's functions.
// You probably don't want to change any of this code.

DeliveryOptimizer::DeliveryOptimizer(const StreetMap* sm)
{
	m_impl = new DeliveryOptimizerImpl(sm);
}

DeliveryOptimizer::~DeliveryOptimizer()
{
	delete m_impl;
}

void DeliveryOptimizer::optimizeDeliveryOrder(
	const GeoCoord& depot,
	vector<DeliveryRequest>& deliveries,
	double& oldCrowDistance,
	double& newCrowDistance) const
{
	return m_impl->optimizeDeliveryOrder(depot, deliveries, oldCrowDistance, newCrowDistance);
}
