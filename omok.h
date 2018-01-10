#ifndef __OMOK_H__
#define __OMOK_H__

#include "draw.h"
#include "omokrule.h"
#include "omokai.h"

struct UndoInfo
{
	int x, y;
	int nStone;
};

class COMOK
{
protected :
	static int  arrBoard[SIZE + 2][SIZE + 2];
	static int  x, y;
	
	// Undo와 Redo를 위한 top pointer 
	static int  uTop, rTop; 
	// last 착수점 
	static int  lx, ly;
	
	// 커서의 깜박임을 구현하기 위한 시간
	static time_t t1, t2; 

	static UndoInfo uInfo[SIZE * SIZE];
	static UndoInfo rInfo[SIZE * SIZE];
	
	COMOKRULE orule;
	
	bool    isOccupy();
	bool    checkSamSam();
	void    undoSet(int nStone);
	void    drawBoard();
	void    saveBoard(int stone);
	void    setXY(int ax, int ay);

public :
	COMOK();
	virtual ~COMOK(){;}
	
	void setBoard(int x, int y);
	void cursorView(int x, int y);
	void initOmok(int nStone);
	void initBoard(int nStone);
	int  undo();
	int  redo();

	virtual int placement(int ax, int ay, int stone); 
};

class CBLACKSTONE : public COMOK
{
private :
	
public :
	CBLACKSTONE();
	~CBLACKSTONE(){;}
	
	virtual int placement(int ax, int ay, int stone); 
};

class CNORMAL : public COMOK
{
private :
	CNORMALRULE nrule; 
	
public :
	CNORMAL();
	~CNORMAL(){;}
	
	virtual int placement(int ax, int ay, int stone); 
};

class CGOMOKUAI : public COMOK
{
private :
	COMOKAI ai;
	
public :
	virtual int placement(int ax, int ay, int stone); 
};

class CJENERALAI : public COMOK
{
private :
	CNORMALRULE nrule; 
	CNORMALAI   ai;
	
public :
	virtual int placement(int ax, int ay, int stone); 
};

class CRENJUAI : public COMOK
{
private :
	CRENJUBLACK ai;
	
public :
	virtual int placement(int ax, int ay, int stone); 
};

#endif


