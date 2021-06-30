//#include <cassert>
//#include <iostream>
//using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
// then for this value of a2     the function must return
//	10 20 40			1
//	10 40 30			2
//	20 10 40			0
//	50 40 30			3
int countContains(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0)
	{
		return 1;   //The empty sequence appears in a
					// sequence of length n1 in 1 way, even if n1 is 0.
	}

	if (n1 <= 0)
	{
		return 0;  //0 because there is nothing in the first array for the second array to be compared to
	}

	if (a1[0] == a2[0])
	{
		int current = countContains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
		int nextIndex = countContains(a1 + 1, n1 - 1, a2, n2);

		return current + nextIndex;
	}

	return countContains(a1 + 1, n1 - 1, a2, n2);	
}

void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

	  // Rearrange the elements of the array so that all the elements
	  // whose value is > separator come before all the other elements,
	  // and all the elements whose value is < separator come after all
	  // the other elements.  Upon return, firstNotGreater is set to the
	  // index of the first element in the rearranged array that is
	  // <= separator, or n if there is no such element, and firstLess is
	  // set to the index of the first element that is < separator, or n
	  // if there is no such element.

	  // In other words, upon return from the function, the array is a
	  // permutation of its original value such that
	  //   * for 0 <= i < firstNotGreater, a[i] > separator
	  //   * for firstNotGreater <= i < firstLess, a[i] == separator
	  //   * for firstLess <= i < n, a[i] < separator
	  // All the elements > separator end up in no particular order.
	  // All the elements < separator end up in no particular order.
void separate(double a[], int n, double separator,
	int& firstNotGreater, int& firstLess)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	//  Every element earlier than position firstNotGreater is > separator
	//  Every element from position firstNotGreater to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstLess-1 is not known yet
	//  Every element at position firstLess or later is < separator

	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while (firstUnknown < firstLess)
	{
		if (a[firstUnknown] < separator)
		{
			firstLess--;
			exchange(a[firstUnknown], a[firstLess]);
		}
		else
		{
			if (a[firstUnknown] > separator)
			{
				exchange(a[firstNotGreater], a[firstUnknown]);
				firstNotGreater++;
			}
			firstUnknown++;
		}
	}
}


// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
	if (n <= 1)
	{
		return;
	}

	else
	{
		int fng;  //first not greater
		int fl;   //first less

		separate(a, n, a[n / 2], fng, fl);

		order(a, fng);		    //this sorts the elements BEFORE the separator
		order(a + fl, n - fl);  //this sorts everything after the separator
			
	}
}

//int main()
//{
//	const double a1[] = {10, 50, 40, 20, 50, 40, 30};
//
//	const double a2[] = { 10, 20, 40 };  //1
//	const double a3[] = { 10, 40, 30 };  //2
//	const double a4[] = { 20, 10, 40 };  //0
//	const double a5[] = { 50, 40, 30 };  //3
//	
//	assert(countContains(a1, 7, a2, 3) == 1);
//	assert(countContains(a1, 7, a3, 3) == 2);
//	assert(countContains(a1, 7, a4, 3) == 0);
//	assert(countContains(a1, 7, a5, 3) == 3);
//
//	assert(countContains(a1, 0, a5, 3) == 0);   //n1 == 0
//	assert(countContains(a1, 7, a5, 0) == 1);   //n2 == 0
//	assert(countContains(a1, 0, a5, 0) == 1);   //n3 == 0
//
//
//
//	double b[] = { 8, 2, 6, 9, 3, 5 }; //normal unsorted array
//	order(b, 6);
//	for (int i = 0; i < 6; i++)
//	{
//		cout << b[i] << endl; 		
//	}
//	cout << endl;
//
//	double b1[] = { 4, 3, 2, 1 };  //already sorted array
//	order(b1, 4);
//	for (int i = 0; i < 4; i++)
//	{
//		cout << b1[i] << endl;	
//	}
//	cout << endl;
//
//	double b2[] = { 4, 3, 2, 1 };  //empty array
//	order(b2, 0);
//	for (int i = 0; i < 4; i++)
//	{
//		cout << b2[i] << endl;
//	}
//	cout << endl;
//
//	double b3[] = { 4 };  //just one element
//	order(b3, 1);
//	for (int i = 0; i < 1; i++)
//	{
//		cout << b3[i] << endl;
//	}
//	cout << endl;
//
//	cout << "passed tests!!!" << endl;
//}