/*
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Map m;
	assert(m.empty());    				// test empty         
	assert(m.size() == 0);				// test size empty
	assert(m.insert("Fred", 123));
	assert(m.insert("Pizza", 234));
	assert(m.size() == 2);				// test size

	assert(m.update("Pizza", 125) && !m.update("Alissa", 2) && m.insert("mofo", 2018) && !m.insert("mofo", 123));			// test that updates and inserts work

	m.insertOrUpdate("Alissa", 239);
	m.insertOrUpdate("BBGURL", 69);
	// test that insertOrUpdate function works
	assert(m.contains("Alissa") && m.contains("BBGURL") && !m.contains("Star Wars"));
	// test that erase works
	cout << "yay" << endl;
	assert(!m.erase("Star Wars") && m.erase("BBGURL") && !m.contains("BBGURL"));
	double value;
	m.get("Pizza", value);
	assert(value == 125);


	Map yay;
	assert(yay.empty());

	std::string foods[26] = {
		 "Sushi", "Poke", "Coffee", "Beans", "Burgers", "Eggplant", "Ramen", "Hot Dog",
		 "Pasta", "Chicken", "Curry", "Tikka Masala", "Squash", "Boba", "Shrimp", "Chips",
		 "Taco", "Burrito", "French Fries", "Milkshakes", "Ice Cream", "Nachos", "Salmon",
		 "Tofu", "Pancakes", "Waffles"
	};
	for (int i = 0; i < 26; i++) {
		yay.insert(foods[i], i * i);
	}

	for (int i = 0; i < 26; i++) {
		std::string key;
		double value;
		yay.get(i, key, value);			// test get function
		assert(key == foods[25 - i] && value == (25 - i) * (25 - i));	// test get
	}
	
	cout << "yay";



	
	int yaySize = yay.size();
	int mSize = m.size();
	yay.swap(m);
	assert(m.size() == yaySize && yay.size() == mSize);	// test sizes swapped
	cout << "yay";
	for (int i = 0; i < 26; i++) {
		std::string key;
		double value;
		m.get(i, key, value);		// test each value got swapped
		assert(key == foods[25 - i] && value == (25 - i) * (25 - i));
	}
	assert(yay.contains("Fred"));	// test value got swapped
	cout << "yay" << endl;
	m.swap(yay);
	for (int i = 0; i < 26; i++) {
		std::string key;
		double value;
		yay.get(i, key, value); 		// check each value got swapped back
		assert(key == foods[25 - i] && value == (25 - i) * (25 - i));
	}
	m.swap(m);	// swap itself and test below
	cout << "yay" << endl;
	Map empty;
	m.swap(empty);	// check swap with an empty map
	assert(m.size() == 0 && !m.contains("Pizza"));


	cout << "yay";


	Map m1, m2, result;
	m1.insert("Fred", 123);
	m1.insert("Ethel", 456);
	m1.insert("Lucy", 789);

	m2.insert("Lucy", 789);
	m2.insert("Ricky", 321);

	assert(combine(m1, m2, result));	// use the examples given in spec
	assert(result.contains("Fred") && result.contains("Lucy"));
	cout << "surprise";
}
*/

/*
int main()
{
	Map m;
	assert(m.empty());    				// test empty         
	assert(m.size() == 0);				// test size empty
	assert(m.insert("Pizza", 123));
	assert(m.insert("Tortilla", 234));
	//assert(m.insert("Cow", 345));
	assert(m.size() == 2);
	assert(m.erase("Pizza"));
	//(!m.erase("Pizza"));
	//assert(m.size() == 2);
	cout << "yay";
}
*/

/*
int main()
{
	Map one;
	Map result;
	result.insert("joe", 456);
	one.insert("Fred", 123);
	one.insert("Ethel", 456);
	one.insert("Lucy", 789);
	one.insert("Ricky", 321);
	reassign(one, result); //this is to test if the reassign works properly
	for (int i = 0; i < result.size(); i++)
	{
		ValueType value;
		KeyType key;
		result.get(i, key, value);
		cout << key << "->"<< value << endl;    //print out values to see if they’re correct
	}

}
*/










#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	KeyType k;
	ValueType v;
	Map hello; //Initiate a new map without specification


	assert(hello.empty()); //Check that hello has no nodes
	assert(hello.size() == 0); //Same as above (test multiple functions)
	assert(hello.erase("joke") == false); //Check that there's nothing to delete
	assert(hello.contains("troll") == false); //Check that there's nothing contained
	assert(hello.insert("Head", 0));
	assert(!hello.empty()); //Check that hello is no longer empty
	assert(hello.size() == 1); //Check that the single node has been inserted
	assert(hello.contains("Head")); //Check that inserted nodes are contained
	assert(!hello.insert("Head", 1)); //Check that duplicate keys cannot be inserted
	assert(hello.size() == 1); //Check that the size has not changed
	hello.get("Head", v);
	assert(v == 0); //Check that the node with key "Head" is holding the right value

	assert(!hello.erase("blah")); //Check that a node that does not exist cannot be erased
	assert(hello.update("Head", 9)); //Check that the node with key "Head" is found and updated
	hello.get("Head", v);
	assert(v == 9); //Check that that node is holding the updated value

	assert(hello.insert("Between", 8)); //Check that another node can be inserted
	hello.get("Between", v);
	assert(v == 8); //Check that that node is holding the right value
	hello.insertOrUpdate("Tail", 11);
	hello.insertOrUpdate("Between", 10);
	assert(hello.size() == 3); //Check that the right number of nodes exists
	for (int i = 0; i < hello.size(); i++)
	{
		hello.get(i, k, v);
		cerr << k << "->" << v << endl; //Should print out keys and values such that Head->9; Between->10; Tail->11
	}
	assert(hello.contains("Head") && hello.contains("Between") && hello.contains("Tail"));
	//Make sure the right nodes are contained
	assert(!hello.contains("head")); //Check that other nodes are not considered contained
	cout << "Passed basic tests involving one map." << endl;






	//Testing copy constructor and equals operand
	Map helloCopy1(hello); //test that the copy constructor makes an exact copy of the map
	assert(helloCopy1.size() == 3); //Check that the right number of nodes exists

	for (int i = 0; i < helloCopy1.size(); i++)
	{

		helloCopy1.get(i, k, v);
		cerr << k << "->" << v << endl; //Should print out keys and values such that Head->9; Between->10; Tail->11
	}
	Map helloCopy2 = hello; //test that the copy constructor makes an exact copy of the map
	assert(helloCopy2.size() == 3); //Check that the right number of nodes exists
	for (int i = 0; i < helloCopy2.size(); i++)
	{
		helloCopy2.get(i, k, v);
		cerr << k << "->" << v << endl; //Should print out keys and values such that Head->9; Between->10; Tail->11
	}
	while (!helloCopy2.empty())
	{
		helloCopy2.get(0, k, v);
		helloCopy2.erase(k); //Check that the map can be emptied by erase
		cerr << k << "->" << v << " removed from helloCopy2" << endl;
	}
	Map blank; //Create a blank map
	helloCopy1 = blank;
	assert(helloCopy1.empty()); //Check that equals operand works for empty maps
	Map anotherBlank(blank);
	assert(anotherBlank.empty()); //Chcek that copy constructor works for empty maps
	cout << "Passed basic tests involving copy constructor and equals operand." << endl;








	Map oneNode;
	oneNode.insert("blah", 1);
	Map copyOneNode(oneNode); //Test the copy constructor with only one node
	assert(copyOneNode.size() == 1); //Check that the size is correct
	assert(copyOneNode.contains("blah")); //Check that the key is contained in the new map
	Map goodbye;
	hello.swap(goodbye); //Swap hello with an empty map
	assert(hello.empty()); //Make sure the amount of elements has switched
	assert(goodbye.size() == 3);
	for (int i = 0; i < goodbye.size(); i++)
	{
		goodbye.get(i, k, v);
		cerr << k << "->" << v << endl;
	}
	goodbye.swap(hello); //Swap hello and goodbye back to normal
	assert(goodbye.empty());
	assert(hello.size() == 3);
	for (int i = 0; i < hello.size(); i++)
	{
		hello.get(i, k, v);

		cerr << k << "->" << v << endl; //Verify that hello and the original goodbye are the same
	}
	cout << "Passed swap tests." << endl;







	assert(hello.erase("Between")); //Check that the middle node is removed and size is updated
	assert(hello.size() == 2);
	assert(hello.erase("Tail")); //Check that the tail node can be removed
	assert(hello.size() == 1);
	assert(hello.erase("Head"));
	assert(hello.empty()); //Check that the head node can be removed (when it's the last one)
	assert(hello.insert("new head", 5));
	assert(hello.insert("new tail", 6));
	assert(hello.erase("new head")); //Check that the head node can be removed (when it's NOT the last node)
	assert(hello.size() == 1);
	cout << "Passed erase tests." << endl;




	Map firstMap;
	firstMap.insert("one", 1); //Should be included in combine
	firstMap.insert("two", 2); //Should be included in combine
	firstMap.insert("three", 3); //Should be included in combine, since the values in first / secondMap equal
	firstMap.insert("four", 4); //Should NOT be included in combine, since the values in first / secondMap differ
	Map secondMap;
	secondMap.insert("three", 3);
	secondMap.insert("four", 10); //Inconsistent value! Should not be in combined Map
	secondMap.insert("five", 5);
	Map answer;
	assert(combine(firstMap, secondMap, answer) == false);
	assert(answer.size() == 4); //Check that the right number of nodes exist
	for (int i = 0; i < answer.size(); i++)
	{
		answer.get(i, k, v);
		cerr << k << "->" << v << endl;
	}
	assert(combine(firstMap, secondMap, secondMap) == false); //Check that combine works in face of aliasing
	assert(secondMap.size() == 4);
	for (int i = 0; i < secondMap.size(); i++)
	{
		secondMap.get(i, k, v);
		cerr << k << "->" << v << endl;
	}
	Map simpleOne;
	simpleOne.insert("blah", 1);

	Map simpleTwo;
	simpleTwo.insert("bleh", 2);
	Map simpleThree;
	assert(combine(simpleOne, simpleTwo, simpleThree)); //Check that combine returns true for unique keys
	assert(simpleThree.size() == 2);
	assert(simpleThree.contains("blah") && simpleThree.contains("bleh")); //Check for the correct pairs
	Map random;
	assert(random.insert("eek", 0) && random.insert("aah", 1));
	assert(random.size() == 2);
	Map blankMap;
	Map blankResult;
	combine(random, blankMap, blankResult); //test subtract with an empty Map as m2
	assert(blankResult.size() == 2 && blankResult.contains("eek") &&
		blankResult.contains("aah"));
	combine(blankMap, random, blankResult); //test subtract with an empty Map as m1
	assert(blankResult.size() == 2 && blankResult.contains("eek") &&
		blankResult.contains("aah"));
	cout << "Passed combine tests." << endl;


	cout << "Passed all of my tests." << endl;
}









