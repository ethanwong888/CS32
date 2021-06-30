
//GOOOD


//Your declarations and implementations would go here
//#include <iostream>
//#include <string>
//using namespace std;

class Event
{
public:
	Event(string e)
		:m_name(e)
	{}

	virtual ~Event()
	{}

	virtual string need() const = 0;

	virtual string name() const
	{
		return m_name;
	}

	virtual bool isSport() const = 0;


private: 
	string m_name;
};



class BasketballGame : public Event
{
public:
	BasketballGame(string n)
		:Event(n)
	{}

	virtual ~BasketballGame()
	{
		cout << "Destroying the " << name() << " basketball game" << endl;
	}

	virtual string need() const
	{
		return "hoops";
	}

	virtual bool isSport() const
	{
		return true;
	}

private:
	string basketball;
};



class HockeyGame : public Event
{
public:
	HockeyGame(string p)
		:Event(p)
	{}

	virtual ~HockeyGame()
	{
		cout << "Destroying the " << name() << " hockey game" << endl;
	}

	virtual string need() const
	{
		return "ice";
	}

	virtual bool isSport() const
	{
		return true;
	}

private:
	string hockey;
};



class Concert : public Event
{
public: 
	Concert(string m, string concertType)
		:Event(m), whatType(concertType)
	{}

	virtual ~Concert()
	{
		cout << "Destroying the " << name() << " " << whatType << " concert" << endl;
	}

	virtual string need() const
	{
		return "a stage";
	}

	virtual bool isSport() const
	{
		return false;
	}


private:
	string whatType;
};


void display(const Event* e)
{
	cout << e->name() << ": ";
	if (e->isSport())
		cout << "(sport) ";
	cout << "needs " << e->need() << endl;
}

//int main()
//{
//	Event* events[4];
//	events[0] = new BasketballGame("Lakers vs. Suns");
//	// Concerts have a name and a genre.
//	events[1] = new Concert("Banda MS", "banda");
//	events[2] = new Concert("KISS", "hard rock");
//	events[3] = new HockeyGame("Kings vs. Flames");
//
//	cout << "Here are the events." << endl;
//	for (int k = 0; k < 4; k++)
//		display(events[k]);
//
//	// Clean up the events before exiting
//	cout << "Cleaning up." << endl;
//	for (int k = 0; k < 4; k++)
//		delete events[k];
//}