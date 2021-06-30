//GOOOD 


//#include <cassert>
//#include <iostream>
//
//
//using namespace std;
//
//bool somePredicate(double x)
//{
//	return x < 0;
//}


// Return true if the somePredicate function returns false for at
// least one of the array elements; return false otherwise.
bool anyFalse(const double a[], int n)
{
	if (n <= 0)
	{
		return false;
	}

	if (somePredicate(a[0]) == false)
	{
		return true;
	}

	return anyFalse(a + 1, n - 1);  //"shrinks" the size of the array that the function works on
}



// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
	if (n <= 0)
	{
		return 0;
	}

	if (somePredicate(a[0]) == true)
	{
		return 1 + countTrue(a + 1, n - 1); //adds one, "shrinks" the size of the array that the function works on
	}

	else
	{
		return countTrue(a + 1, n - 1);  //"shrinks" the size of the array that the function works on
	}
}



// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}

	if (somePredicate(a[0]) == true)
	{
		return 0;
	}

	else
	{
		int p = firstTrue(a + 1, n - 1);  //"shrinks" the size of the array that the function works on until it reaches the last element

		if (p == -1)
		{
			return -1;
		}

		else
		{
			return 1 + p;
		}
	}

}


// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int positionOfSmallest(const double a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}

	if (n == 1)
	{
		return 0;
	}

	int position = positionOfSmallest(a + 1, n - 1);  //recursive

	if (a[0] < a[1 + position])
	{
		return 0;
	}
	else
	{
		return 1 + position;
	}
}



// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not contain
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool contains(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0)
	{
		return true;
	}

	if (n1 <= 0)
	{
		return false;
	}

	if (a1[0] == a2[0])
	{
		return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);  //checking the remainders of the arrays
	}

	return contains(a1 + 1, n1 - 1, a2, n2);
}

//int main()
//{
//	double a[4] = { 1, 9, 8, 6 };
//	assert(positionOfSmallest(a, 4) == 0);
//double b[4] = { 5, 5, 6, 0 };  //last is smallest
//assert(positionOfSmallest(b, 4) == 3);
//
//
//	double c[4] = { 5, 0, 6, 7 };
//	assert(positionOfSmallest(c, 4) == 1);  //middle is smallest
//
//	assert(positionOfSmallest(a, 0) == -1);
//	assert(positionOfSmallest(a, -10) == -1);
//	assert(positionOfSmallest(a, 1) == 0);
//
//
//
//	double a1[7] = { 10, 50, 40, 20, 50, 40, 30 };  //this is the true case
//	double a2[3] = { 50, 20, 30 };
//	assert(contains(a1, 7, a2, 3) == true);
//
//
//	  //this is the true case
//	assert(contains(a1, 7, a2, 3) == true);
//
//
//
//	double b1[7] = { 10, 50, 40, 20, 50, 40, 30 };  //this is the false case
//	double b2[3] = { 50, 30, 20 };
//	assert(contains(b1, 7, b2, 3) == false);
//
//		//this is the false case
//	assert(contains(b1, 7, b2, 3) == false);
//
//
//
//
//	double arr[3] = { 1, 1, -3 };
//	cout << firstTrue(arr, 3) << endl;
//
//cout << "passed tests" << endl;
//}