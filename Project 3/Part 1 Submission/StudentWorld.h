#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include "Actor.h"/////
#include "GameWorld.h"
#include <string>
#include <vector>
using namespace std;

class Actor;
class Socrates;


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
	virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();

	//void addActor(Actor* p);

	void accessMapActors(string actor);
	void addActorToVector(Actor* actor);
	//bool collided(Actor* a1, Actor* a2);
	const vector <Actor*> & returnVec_Actors();
	int returnLevel();
	Socrates* returnSocrates();
	double findDistance(double x1, double y1, double x2, double y2);

	bool overlap(double x, double y);
	bool sprayHit(Actor* a1);
	bool flameHit(Actor* a2);
	void addGoodies();
	void addDirt();
	void addPit();
	void addFood();
	
	int returnMapNumber();

private:
	vector <Actor*> vec_Actors;
	map <string, int> map_Actors;
	Socrates* m_Socrates;
	int L;
};

#endif // STUDENTWORLD_H_
