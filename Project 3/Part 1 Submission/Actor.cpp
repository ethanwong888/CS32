#include "Actor.h"
#include <cmath>

#include "StudentWorld.h"

//Actor ================================================================================================
Actor::Actor(int ImageID, double startX, double startY, Direction startDirection, int depth, StudentWorld* petriDish, bool damageable)
	: GraphObject(ImageID, startX, startY, startDirection, depth)
{
	m_alive = true;
	m_world = petriDish;
	m_ImageID = ImageID;
	m_damageable = damageable;
}

Actor::~Actor()
{

}

void Actor::doSomething()/////////////////////////
{

}

bool Actor::deadOrAlive()   //true for alive, false for dead
{
	return m_alive;
}

void Actor::setDead()
{
	m_alive = false;
}

StudentWorld* Actor::getWorld()
{
	return m_world;
}

void Actor::setObjectType(string s)
{
	type = s;
}

string Actor::returnObjectType()
{
	return type;
}

double Actor::getHP()
{
	return m_health;
}


double Actor::euclideanDistance(const Actor* actor1)
{
	double x1 = this->getX();
	double y1 = this->getY();
	double x2 = actor1->getX();
	double y2 = actor1->getY();

	double distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	return distance;
}

//bool Actor::otherOverlap(const Actor* a1)
//{
//	if (euclideanDistance(this, a1) <= 8)
//	{
//		return true;
//	}
//}

bool Actor::otherCollision()
{
	vector<Actor*>::const_iterator it = getWorld()->returnVec_Actors().begin();
	while (it != getWorld()->returnVec_Actors().end())
	{
		if (((*it)->deadOrAlive() == true && deadOrAlive() == true) &&
			!((*it)->returnObjectType() == "Dirt" && returnObjectType() == "Dirt") && 
			(((*it)->returnObjectType() == "Dirt" && returnObjectType() == "Flame") ||
			((*it)->returnObjectType() == "Dirt" && returnObjectType() == "Spray")) &&
			(*it)->isItDamageable() == true && isItDamageable() == false)
			//((*it)->returnObjectType() == "Flame" && (*it)->isItDamageable() == true) &&
			//((*it)->returnObjectType() == "Spray" && (*it)->isItDamageable() == true))

		{
			if (euclideanDistance(*it) <= 8)
			{
				(*it)->setDead();
				return true;
			}
		}
		it++;
	}
	return false;
}

bool Actor::isItDamageable() const
{
	return m_damageable;
}

void Actor::takeDamage(int damage)
{
	m_health = m_health - damage;

	if (returnHP() <= 0)
	{
		setDead();
	}
}

double Actor::returnHP()
{
	return m_health;
}

void Actor::setHP(double hp)
{
	m_health = hp;
}


//Organism =======================================================================================================
Organism::Organism(int ImageID, double startX, double startY, Direction startDirection, int depth, double HP, StudentWorld* petriDish)
	:Actor(ImageID, startX, startY, startDirection, depth, petriDish, false)
{
	setHP(HP);
}

Organism::~Organism()
{

}

//double Organism::returnHP()
//{
//	return m_healthPoints;
//}

//void Organism::setHP(int healthPoints)
//{
//	m_health = healthPoints;
//}

//void Organism::takeDamage(int damage)
//{
//	m_healthPoints = m_healthPoints - damage;
//	
//	if (returnHP() <= 0)
//	{
//		setDead();
//	}
//}


//Socrates ==================================================================================================================
Socrates::Socrates(StudentWorld* petriDish)
	:Organism(IID_PLAYER, 0, 128, 0, 0, 100, petriDish) 
{
	socratesPositionalAngle = 3.1415926535;
	m_sprayAmmo = 20;
	m_flameAmmo = 5;///////////////////////////
	m_lives = 3;
	setHP(100);
	setObjectType("Socrates");
}

Socrates::~Socrates()
{
	getWorld()->accessMapActors("Socrates");
}

void Socrates::doSomething()
{
	if (deadOrAlive() == false)
	{
		return;
	}

	int x;
	if (getWorld()->getKey(x))
	{
		switch (x)
		{
		case KEY_PRESS_SPACE:
			if (m_sprayAmmo >= 1)
			{
				shootSpray();							
			}
			break;

		case KEY_PRESS_ENTER:
			if (m_flameAmmo >= 1)
			{
				shootFlame();				
			}
			break;

		case KEY_PRESS_LEFT:    //counterclockwise
		{
			socratesPositionalAngle += ((3.1415926535 / 180) * 5);    //convert 5 degrees to radians	
			moveTo((128 * cos(socratesPositionalAngle) + 128), (128 * sin(socratesPositionalAngle) + 128));
			setDirection(getDirection() + 5);
			
			break;
		}		

		case KEY_PRESS_RIGHT:  //clockwise
		{
			socratesPositionalAngle -= ((3.1415926535 / 180) * 5);    //convert 5 degrees to radians
			moveTo((128 * cos(socratesPositionalAngle)+128), (128 * sin(socratesPositionalAngle))+128);
			setDirection(getDirection() - 5);
			
			break;
		}
		break;
		}		
	}

	else
	{
		if (m_sprayAmmo < 20)
			m_sprayAmmo++;
	}

}

void Socrates::addHP(int amount)
{
	if (returnHP() + amount > 100) 
	{
		setHP(100);
	}
	else 
	{		
		setHP(returnHP() + amount);
	}
}

void Socrates::increaseLives()
{
	m_lives++;
}

void Socrates::shootSpray()
{
	//double playerPosX = getX();
	//double playerPosY = getY();
	double endX;
	double endY;

	getPositionInThisDirection(getDirection(), 2 * SPRITE_RADIUS, endX, endY);

	Spray* newSpray = new Spray(endX, endY, getDirection(), getWorld());

	getWorld()->addActorToVector(newSpray);
	getWorld()->playSound(SOUND_PLAYER_SPRAY);
	m_sprayAmmo--;	
}


int Socrates::getSprayAmount()
{
	return m_sprayAmmo;
}

void Socrates::shootFlame()
{
	// add the 16 flame actors into the studentworld
	//double playerPosX = getX();
	//double playerPosY = getY();
	double endX;
	double endY;

	for (int i = 0; i < 16; i++)
	{
		getPositionInThisDirection(getDirection() + (i * 22), 2 * SPRITE_RADIUS, endX, endY);
		Flame* newFlame = new Flame(endX, endY, getDirection() + (i * 22), getWorld());
		getWorld()->addActorToVector(newFlame);
	}
		
	getWorld()->playSound(SOUND_PLAYER_FIRE);
	m_flameAmmo--;
}

int Socrates::getFlameAmount()
{
	return m_flameAmmo;
}

void Socrates::increaseFlameAmmo()
{
	m_flameAmmo += 5;
}

//Dirt =======================================================================================================
Dirt::Dirt(double startX, double startY, StudentWorld* petriDish)
	:Actor(IID_DIRT, startX, startY, 0, 1, petriDish, true)
{
	setObjectType("Dirt");
}

void Dirt::doSomething()
{
	
}

Dirt::~Dirt()
{
	
}


//Projectiles ========================================================================================================
Projectile::Projectile(int ImageID, double startX, double startY, int direction, int depth, StudentWorld* petriDish)
	:Actor(ImageID, startX, startY, direction, depth, petriDish, false)
{

}
Projectile::~Projectile()
{

}



Flame::Flame(double startX, double startY, int direction,  StudentWorld* petriDish)
	:Projectile(IID_FLAME, startX, startY, direction, 1, petriDish)
{
	startingX = startX;
	startingY = startY;
	flameMoveDistance = 32;
	setObjectType("Flame");
}

Flame::~Flame()
{
	getWorld()->accessMapActors("Flame");
}

void Flame::doSomething()
{
	if (deadOrAlive() == false)
	{
		return;
	}
	
	moveForward(SPRITE_RADIUS * 2);

	if (Flame::distanceTraveled(startingX, startingY) == false)
	{
		setDead();
		getWorld()->accessMapActors("Flame");
	}

	//if (getWorld()->flameHit(this) == true)
	//{
	//	setDead();
	//	return;
	//}
}

bool Flame::distanceTraveled(double a, double b)
{
	double x1 = getX();
	double y1 = getY();
	
	double distance = sqrt(pow((x1 - a), 2) + pow((y1 - b), 2));

	if (distance >= 32)
	{
		return false;
	}
	return true;
}


Spray::Spray(double startX, double startY, int direction,StudentWorld* petriDish)
	:Projectile(IID_SPRAY, startX, startY, direction, 1, petriDish)
{
	startingX = startX;
	startingY = startY;
	sprayMoveDistance = 112;
	setObjectType("Spray");
}

Spray::~Spray()
{
	getWorld()->accessMapActors("Spray");
}

void Spray::doSomething()
{
	if (deadOrAlive() == false)
	{
		return;
	}

	moveForward(SPRITE_RADIUS * 2);

	if (Spray::distanceTraveled(startingX, startingY) == false)
	{
		setDead();
		getWorld()->accessMapActors("Spray");	
	}
	
	//if (getWorld()->sprayHit(this) == true)
	//{
	//	setDead();
	//	return;
	//}
}

bool Spray::distanceTraveled(double a, double b)
{
	double x1 = getX();
	double y1 = getY();

	double distance = sqrt(pow((x1 - a), 2) + pow((y1 - b), 2));

	if (distance >= 112)
	{
		return false;
	}
	return true;
}



//Goodies ================================================================================================================
Goodies::Goodies(int ImageID, double angle, StudentWorld* petriDish)
	:Actor(ImageID, 128 * cos(angle) + 128, 128 * sin(angle) + 128, 0, 1, petriDish, true)
{
	int L = getWorld()->returnLevel();
	lifetime = max(rand() % (300 - 10 * L), 50);
	livingTime = 0;
	//std::cout << lifetime << endl;
}

Goodies::~Goodies()
{

}

void Goodies::function()
{

}

//int Goodies::accessLivingTime()
//{
//	return livingTime;
//}
//
//int Goodies::increaseLivingTime()
//{
//	livingTime++;
//	return livingTime;
//}
//
//int Goodies::accessLifetime()
//{
//	return lifetime;
//}

void Goodies::doSomething()
{
	//cout << livingTime << endl;
	if (livingTime >= lifetime)
	{
		//cout << " dying" << endl;
		setDead();
	}

	if (deadOrAlive() == false)
	{
		return;
	}

	if (euclideanDistance(getWorld()->returnSocrates()) <= 8)
	{
		//cout << "COLLIDED" << endl;
		function();
	}

	livingTime++;
}



Fungi::Fungi(StudentWorld* petriDish)
	:Goodies(IID_FUNGUS, (rand() % 360 * (3.1415926535 / 180)), petriDish)
{
	setObjectType("Fungi");
}

Fungi::~Fungi()
{
	getWorld()->accessMapActors("Fungi");
}

//void Fungi::doSomething()
//{
//
//}

void Fungi::function()
{
	//this subtracts 50 points; reduces Socrates's health by 20
	getWorld()->increaseScore(-50);
	setDead();
	getWorld()->returnSocrates()->addHP(-20);
	return;
}



HealthPack::HealthPack(StudentWorld* petriDish)
	:Goodies(IID_RESTORE_HEALTH_GOODIE, (rand() % 360 * (3.1415926535 / 180)), petriDish)
{
	setObjectType("HealthPack");
	
}

HealthPack::~HealthPack()
{
	getWorld()->accessMapActors("HealthPack");
}

//void HealthPack::doSomething()
//{
//
//}

void HealthPack::function()
{
	//this adds 250 points; restores Socrates's health
	getWorld()->increaseScore(250);
	setDead();
	getWorld()->playSound(SOUND_GOT_GOODIE);
	getWorld()->returnSocrates()->setHP(100);
}


ExtraLifePack::ExtraLifePack(StudentWorld* petriDish)
	:Goodies(IID_EXTRA_LIFE_GOODIE, (rand() % 360 * (3.1415926535 / 180)), petriDish)
{
	setObjectType("ExtraLifePack");
}

ExtraLifePack::~ExtraLifePack()
{
	getWorld()->accessMapActors("ExtraLifePack");
}

//void ExtraLifePack::doSomething()
//{
//
//}

void ExtraLifePack::function()
{
	//this adds 500 points; gives Socrates an extra life
	getWorld()->increaseScore(500);
	setDead();
	getWorld()->playSound(SOUND_GOT_GOODIE);
	getWorld()->returnSocrates()->increaseLives();
}



FlamePack::FlamePack(StudentWorld* petriDish)
	:Goodies(IID_FLAME_THROWER_GOODIE, (rand() % 360 * (3.1415926535 / 180)), petriDish)
{
	setObjectType("FlamePack");
}

FlamePack::~FlamePack()
{
	getWorld()->accessMapActors("FlamePack");
}

//void FlamePack::doSomething()
//{
//
//}

void FlamePack::function()
{
	//adds five additional flame charges
	getWorld()->increaseScore(300);
	setDead();
	getWorld()->playSound(SOUND_GOT_GOODIE);
	getWorld()->returnSocrates()->increaseFlameAmmo();
}


//Pit =====================================================================================================================
Pit::Pit(double startX, double startY, StudentWorld* petriDish)
	:Actor(IID_PIT, startX, startY, 0, 1, petriDish, false)
{
	setObjectType("Pit");
	damageable = false;
}

void Pit::doSomething()
{
	//release bacteria and die after all bacteria have been released
}

Pit::~Pit()
{
	getWorld()->accessMapActors("Pit");
}


//Food =====================================================================================================================
Food::Food(double startX, double startY, StudentWorld* petriDish)
	:Actor(IID_FOOD, startX, startY, 90, 1, petriDish, false)
{
	setObjectType("Food");
	damageable = false;
}

void Food::doSomething()
{
	//sits around forever
}

Food::~Food()
{
	getWorld()->accessMapActors("Food");
}



