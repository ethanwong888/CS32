#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>


#include <stdio.h> 
#include <stdlib.h> 
#include<time.h> 

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
	L = 1;
	map_Actors["Dirt"] = 0;
	//map of actors??? stores the number of each actor (
}

int StudentWorld::init()
{
	m_Socrates = new Socrates(this);
	addDirt();
	addPit();
	addFood();
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

    /*decLives();*/
    /*return GWSTATUS_PLAYER_DIED;*/

	addGoodies();

	vector<Actor*>::iterator it = vec_Actors.begin();
	for (it = vec_Actors.begin(); it != vec_Actors.end();)  //checking for collisions
	{
		if ((*it)->returnObjectType() == "Dirt")
		{
			advance(it, map_Actors["Dirt"] + /*map_Actors["Pit"]*/ + map_Actors["Food"]);  ////////////
		}

		if ((*it)->otherCollision() == true)
		{
			(*it)->setDead();
		}
		it++;
	}

	m_Socrates->doSomething();

	if (m_Socrates->returnHP() <= 0)
	{
		m_Socrates->setDead();
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}

	for (it = vec_Actors.begin(); it != vec_Actors.end(); )
	{
		(*it)->doSomething();
		if ((*it)->deadOrAlive() == false)
		{
			accessMapActors((*it)->returnObjectType());   
			//cout << "Died: " << (*it)->returnObjectType() << endl;

			delete *it;
			it = vec_Actors.erase(it);
		}
		else
		{
			it++;
		}
	}

	ostringstream oss;
	oss.setf(ios::fixed);
	oss.precision(0);
	oss << "Score: " << getScore() << "  ";
	oss << "Level: " << getLevel() << "  ";
	oss << "Lives: " << getLives() << "  ";
	oss << "Health: " << m_Socrates->returnHP() << "  ";
	oss << "Sprays: " << m_Socrates->getSprayAmount() << "  ";
	oss << "Flames: " << m_Socrates->getFlameAmount();
	setGameStatText(oss.str());
	
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	vector<Actor*>::iterator it;
	for (it = vec_Actors.begin(); it < vec_Actors.end(); it++)
	{
		delete* it;
		it = vec_Actors.erase(it);
	}

	if (m_Socrates != nullptr)
	{
		delete m_Socrates;
		m_Socrates = nullptr;
	}
}


StudentWorld::~StudentWorld()
{
	cleanUp();
}


void StudentWorld::accessMapActors(string actor)
{
	map_Actors[actor] -= 1;
}


void StudentWorld::addActorToVector(Actor* actor)
{
	vec_Actors.push_back(actor);
}

const vector <Actor*> & StudentWorld::returnVec_Actors()
{
	return vec_Actors;
}

int StudentWorld::returnLevel()
{
	return L;
}

Socrates* StudentWorld::returnSocrates()
{
	return m_Socrates;
}

double StudentWorld::findDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void StudentWorld::addGoodies()
{
	//double angle = (rand() % 360 * (3.1415926535 / 180));

	int chanceFungus = min(510 - getLevel() * 10, 200);
	int randomFungus = randInt(0, chanceFungus);
	if (randomFungus == 0)
	{
		//create a new fungus
		Fungi* newFungi = new Fungi(this);
		addActorToVector(newFungi);
	}

	int chanceGoodie = min(510 - getLevel() * 10, 250);
	int randomGoodie = randInt(0, chanceGoodie);
	if (randomGoodie == 0)
	{
		int random = randInt(1, 10);

		//cout << "Added goodie" << endl;
		if (random <= 6)
		{
			//create a new restore health goodie
			HealthPack* newHealthPack = new HealthPack(this);
			addActorToVector(newHealthPack);
		}

		else if (random <= 9 && random > 6)
		{
			//create a new flame thrower goodie
			FlamePack* newFlamePack = new FlamePack(this);
			addActorToVector(newFlamePack);
		}

		else
		{
			//create a new extra life goodie
			ExtraLifePack* newExtraLifePack = new ExtraLifePack(this);
			addActorToVector(newExtraLifePack);
		}
	}
}

bool StudentWorld::sprayHit(Actor* a1)
{
	vector<Actor*>::iterator it = vec_Actors.begin();
	while (it != vec_Actors.end())
	{
		if ((*it)->isItDamageable() && findDistance((*it)->getX(), (*it)->getY(), (a1)->getX(), (a1)->getY() <= 2.0 * SPRITE_RADIUS) 
			&& ((*it)->returnObjectType() == "Dirt" || (*it)->returnObjectType() == "FlamePack" ||
			(*it)->returnObjectType() == "ExtraLifePack" || (*it)->returnObjectType() == "HealthPack" ||
				(*it)->returnObjectType() == "Fungi"))
		{
			(*it)->setDead();
			return true;
		}

		else if ((*it)->isItDamageable() && findDistance((*it)->getX(), (*it)->getY(), (a1)->getX(), (a1)->getY() <= 2.0 * SPRITE_RADIUS)
			&& ((*it)->returnObjectType() == "AggressiveSalmonella" || (*it)->returnObjectType() == "Ecoli"
				|| (*it)->returnObjectType() == "Salmonella"))
		{
			(*it)->takeDamage(-2);
			return true;
		}

		else
		{
			it++;
		}
	}
	return false;
}


bool StudentWorld::flameHit(Actor* a1)
{
	vector<Actor*>::iterator it = vec_Actors.begin();
	while (it != vec_Actors.end())
	{
		if ((*it)->isItDamageable() && findDistance((*it)->getX(), (*it)->getY(), (a1)->getX(), (a1)->getY() <= 2.0 * SPRITE_RADIUS))
		{
			(*it)->setDead();
			return true;
		}

		else if ((*it)->isItDamageable() && findDistance((*it)->getX(), (*it)->getY(), (a1)->getX(), (a1)->getY() <= 2.0 * SPRITE_RADIUS))
		{
			(*it)->takeDamage(-5);
			return true;
		}

		else
		{
			it++;
		}
	}
	return false;
}


bool StudentWorld::overlap(double x, double y)
{
	vector<Actor*>::iterator it;
	for (it = vec_Actors.begin(); it != vec_Actors.end(); it++)
	{
		//cout << "(" << x << "," << y << ")" << "  " << (*it)->getX() << ' ' << (*it)->getY() << endl;
		if (findDistance((*it)->getX(), (*it)->getY(), x, y) <= SPRITE_WIDTH)
			return true;
	}
	return false;
}

void StudentWorld::addDirt()
{
	for (int i = 0; i < max(180 - 20 * L, 20); i++)   //adding in the piles of dirt
	{
		//double r = randInt(0, 120);       //random radius
		//double theta = randInt(0, 360);   //random angle (in degrees)

		//double xBound = r * cos(theta) + 128;   //setting the bounds for x
		//double yBound = r * sin(theta) + 128;   //setting the bounds for y

		double r = 120 * sqrt((double) rand() / RAND_MAX);
		double theta = ((double)rand() / RAND_MAX) * 2 * 3.1415;

		double xBound = r * cos(theta) + 128;   //setting the bounds for x
		double yBound = r * sin(theta) + 128;   //setting the bounds for y

		vec_Actors.push_back(new Dirt(xBound, yBound, this));
		map_Actors["Dirt"] += 1;
	}
}

void StudentWorld::addPit()
{
	for (int i = 0; i < L; i++)   //adding in the pit(s)
	{
		double r = randInt(0, 120);       //random radius
		double theta = randInt(0, 360);   //random angle (in degrees)

		double xBound = r * cos(theta) + 128;   //setting the bounds for x
		double yBound = r * sin(theta) + 128;   //setting the bounds for y

		while (overlap(xBound, yBound) == true)   //while it's overlapping, create new coordinates
		{
			//cout << " repeat pit" << endl;

			r = randInt(0, 120);       //random radius
			theta = randInt(0, 360);   //random angle (in degrees)

			xBound = r * cos(theta) + 128;   //setting the bounds for x
			yBound = r * sin(theta) + 128;   //setting the bounds for y
		}

		//cout << xBound << " " << yBound << endl;

		Pit* pit = new Pit(xBound, yBound, this);
		vec_Actors.push_back(pit);
		map_Actors["Pit"] += 1;
		//cout << "spawned\n";		
	}
}

void StudentWorld::addFood()
{
	for (int i = 0; i < min(5 * L, 25); i++)   //adding in the food(s)
	{
		double r = randInt(0, 120);       //random radius
		double theta = randInt(0, 360);   //random angle (in degrees)

		double xBound = r * cos(theta) + 128;   //setting the bounds for x
		double yBound = r * sin(theta) + 128;   //setting the bounds for y

		while (overlap(xBound, yBound) == true)   //while it's overlapping, create new coordinates
		{
			//cout << " repeat pizza" << xBound << ' ' << yBound << endl;
			r = randInt(0, 120);       //random radius
			theta = randInt(0, 360);   //random angle (in degrees)

			xBound = r * cos(theta) + 128;   //setting the bounds for x
			yBound = r * sin(theta) + 128;   //setting the bounds for y

			//cout << "new coordinates: " << xBound << ' ' << yBound << endl;
		}
		Food* food = new Food(xBound, yBound, this);
		vec_Actors.push_back(food);
		map_Actors["Food"] += 1;
		//cout << returnMapNumber() << endl;
	}
}


int StudentWorld::returnMapNumber()
{
	return map_Actors["Food"];
}
