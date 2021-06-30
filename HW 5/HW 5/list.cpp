void listAll(string path, const Class* c)  // two-parameter overload
{
	//You will write this code.

	if (path == "")
	{
		path = c->name();      //set path to be the name of the Class* object		
	}
	cout << path << endl;      //can't have this inside the if statement; it messes things up
		
	vector<Class*>::const_iterator it;
	for (it = c->subclasses().begin(); it != c->subclasses().end(); it++)
	{
		listAll(path + "=>" + (*it)->name(), *it);
	}
}

