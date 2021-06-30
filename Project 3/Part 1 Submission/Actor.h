#ifndef ACTOR_H_
#define ACTOR_H_
#include "GraphObject.h"
#include "StudentWorld.h"
#include <string>
class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(int ImageID, double startX, double startY, int startDirection, int depth, StudentWorld* petriDish, bool damageable);
	virtual ~Actor() = 0;
	bool deadOrAlive();
	virtual void doSomething() = 0;
	void setDead();
	StudentWorld* getWorld();
	bool otherOverlap(const Actor* a1);                  //compare "this" to the Actor* a1
	void setObjectType(std::string s);
	std::string returnObjectType();
	bool otherCollision();
	bool isItDamageable() const;
	void takeDamage(int damage);
	double returnHP();   //used to get HP value to see if organism is dead or not
	double getHP();
	virtual void setHP(double hp);

protected:
	double euclideanDistance(const Actor* actor1);  //get the distance between two Actors, use distance in overlap function

private:
	bool m_alive;
	StudentWorld* m_world;
	int m_ImageID;
	std::string type;
	bool m_damageable;
	double m_health;
};

//===============================================================================================//

class Organism : public Actor
{
public:
	Organism(int ImageID, double startX, double startY, int startDirection, int depth, double HP, StudentWorld* petriDish);
	virtual ~Organism();
	virtual void doSomething() = 0;
	
	 
	//virtual void takeDamage(int damage);
	//virtual void addHP(double amount);
	
private:
	
	
};

class Socrates : public Organism
{
public:
	Socrates(StudentWorld* petriDish);
	virtual ~Socrates();
	virtual void doSomething();
	virtual void addHP(int amount);

	void increaseLives();
	int getSprayAmount();
	void shootSpray();
	int getFlameAmount();
	void shootFlame();
	void increaseFlameAmmo();

private:
	int m_sprayAmmo;
	int m_flameAmmo;
	int m_lives;
	double socratesPositionalAngle;
	
};


class Salmonella : public Organism
{
public:
	Salmonella(int ImageID, double startX, double startY, int startDirection, int depth, StudentWorld* petriDish);
	virtual ~Salmonella();
	virtual void doSomething();
	virtual void setMovementPlanDistance();
	void setDirection();
	bool movementOverlap(const Actor* a1);

private:

};

class aggressiveSalmonella : public Salmonella
{
public:
	aggressiveSalmonella(int ImageID, double startX, double startY, int startDirection, int depth, StudentWorld* petriDish);
	virtual ~aggressiveSalmonella();
	virtual void doSomething();
private:

};

class Ecoli : public Salmonella
{
public:
	Ecoli(int ImageID, double startX, double startY, int startDirection, int depth, StudentWorld* petriDish);
	virtual ~Ecoli();
	virtual void doSomething();
private:

};


//===============================================================================================//
class Projectile : public Actor
{
public:
	Projectile(int ImageID, double startX, double startY, int direction, int depth, StudentWorld* petriDish);
	virtual ~Projectile();
	virtual void doSomething() = 0;
	virtual bool distanceTraveled(double a, double b) = 0;
private:


};

class Flame : public Projectile
{
public:
	Flame(double startX, double startY, int direction, StudentWorld* petriDish);
	virtual ~Flame();
	virtual void doSomething();
	virtual bool distanceTraveled(double a, double b);

	//virtual bool collision();
	//void move();  ?????
private:
	int flameMoveDistance;
	double startingX;
	double startingY;
};

class Spray : public Projectile
{
public:
	Spray(double startX, double startY, int direction, StudentWorld* petriDish);
	virtual ~Spray();
	virtual void doSomething();
	virtual bool distanceTraveled(double a, double b);
	//bool collision();

private:
	int sprayMoveDistance;
	double startingX;
	double startingY;
};


//===============================================================================================//


class Goodies : public Actor
{
public:
	Goodies(int ImageID, double angle, StudentWorld* petriDish);
	virtual ~Goodies();
	virtual void function() = 0;
	virtual void doSomething();
	//int accessLivingTime();
	//int increaseLivingTime();
	//int accessLifetime();
private:
	int livingTime;
	int lifetime;
};

class Fungi : public Goodies
{
public:
	Fungi(StudentWorld* petriDish);
	virtual ~Fungi();
	//virtual void doSomething();
	virtual void function();   //this subtracts 50 points; reduces Socrates's health by 20 
private:

};

class HealthPack : public Goodies
{
public:
	HealthPack(StudentWorld* petriDish);
	virtual ~HealthPack();
	//virtual void doSomething();
	virtual void function();    //this adds 250 points; restores Socrates's health

private:

};

class ExtraLifePack : public Goodies
{
public:
	ExtraLifePack(StudentWorld* petriDish);
	virtual ~ExtraLifePack();
	//virtual void doSomething();
	virtual void function();     //this adds 500 points; gives Socrates an extra life
private:

};

class FlamePack : public Goodies
{
public:
	FlamePack(StudentWorld* petriDish);
	virtual ~FlamePack();
	//virtual void doSomething();
	virtual void function();   //adds five additional flame charges
private:

};


//===============================================================================================//


class Dirt : public Actor
{
public:
	Dirt(double startX, double startY, StudentWorld* petriDish);
	virtual void doSomething();
	virtual ~Dirt();

private:
};

class Food : public Actor
{
public: 
	Food(double startX, double startY, StudentWorld* petriDish);
	virtual void doSomething();
	virtual ~Food();

private:
	bool damageable;
};

class Pit : public Actor
{
public:
	Pit(double startX, double startY, StudentWorld* petriDish);
	virtual void doSomething();
	virtual ~Pit();

private:
	bool damageable;
};

#endif // ACTOR_H_
