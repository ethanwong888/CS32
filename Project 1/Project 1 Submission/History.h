#ifndef History_BANG
#define History_BANG
#include "globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;

private:
	int m_nRows;
	int m_nCols;
	int gameHistory[MAXROWS][MAXCOLS];
};

#endif