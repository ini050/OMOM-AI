#ifndef __COMOKAI_H__
#define __COMOKAI_H__

#include "omokrule.h"

struct Point
{
	int x, y;
};

class COMOKAI
{
protected :
	int nBoard[SIZE + 2][SIZE + 2];
	int nWeight[SIZE + 2][SIZE + 2];
	
	bool isOpenFour;
	
	Point      l, r; //left top, right bottom;
	COMOKRULE *pRule;
	
public :
	COMOKAI();
	virtual ~COMOKAI() {}
	
	void SetBoard(int (*arr)[SIZE + 2], COMOKRULE *pr);
	virtual void play(int &x, int &y, int nStone);

protected :
	int   IsOpenThree(int x, int y, int nStone, int nDir);
	int   IsThree(int x, int y, int nStone, int nDir);
	int   IsOpenTwo(int x, int y, int nStone, int nDir);
	int   IsTwo(int x, int y, int nStone, int nDir);
	int   IsFour(int x, int y, int nStone, int nDir);
	int   IsOpenFour(int x, int y, int nStone, int nDir);
	int   yourOpenFour(int x, int y, int nStone, int nDir);
	int   OpenFour(int x, int y, int nStone, int nDir);
	bool  IsFourThree(int x, int y, int nStone);
	bool  IsDoubleFour(int x, int y, int nStone);
	bool  IsDoubleThree(int x, int y, int nStone);
	bool  IsFive(int x, int y, int nStone);
	bool  IsSix(int x, int y, int nStone);
	void  fillWeight(int nStone, bool isRenju);
	void  initWeight();
	void  GetRect(Point &p1, Point &p2);
	void  setRect();
	bool  findPutPoint(int &x, int &y, int nStone, bool (COMOKAI::*fp)(int, int, int));
	bool  IsEmpty(int x, int y, int nStone);
	virtual void findPutOnPoint(int &x, int &y, int nStone);
};

class CNORMALAI : public COMOKAI
{
public :
	virtual void play(int &x, int &y, int nStone);

protected :
	virtual void  findPutOnPoint(int &x, int &y, int nStone);
};

class CRENJUBLACK : public COMOKAI
{
public :
	virtual void play(int &x, int &y, int nStone);

protected :
	virtual void  findPutOnPoint(int &x, int &y, int nStone);
};

#endif
