#ifndef __DRAW_H__
#define __DRAW_H__

#include "console.h"

// 바둑판의 크기를 매크로로 정의 하자
// 바둑판의 크기는 19 X 19이지만 
// 오목판의 경우 15 X 15라 한다. 
// x와 y의 크기가 같으니 하나만 정의 
#define SIZE       15
#define CENTER     ((SIZE + 2) / 2)
#define FINISH    -1
#define TIED       2

// 바둑판은 배경은 녹색, 줄은 검은 색으로 한다.
// 바둑돌은 흰색과 검은색으로 한다.
enum {BLACK_STONE, WHITE_STONE, CURSOR, BLACKWIN, WHITEWIN, TIE, LINE, WALL}; 
enum {OCCUPIED = 10, SAMSAM, SASA, SIXMOK, NOTUNDO, FIVEMOK, CHANGE, PASS};
enum {HIDE, SHOW};

// 화면을 그려줄 Draw class를 만든다.
// 이 class도 이전 사용하였던 걸 수정하여 재 사용한다. 
class CDRAW
{
private :
	CDRAW();
	~CDRAW() {;}
	// 게임보드의 좌상단 위치 
	int nX, nY;
	
public :
	static CDRAW *getInstance();
	int    getLineNumber(int x, int y);
	int    GetMenu(char *cTitle);
	int    GetMenu();
	void   printData(int &x, int &y, int type);
	void   printNum();
	void   drawTime(time_t sec);
	void   showMsg(int msg);
	void   errMsg(int msg);
	bool   endMsg(int stone);
	void   CursorView(char show);
	void   gotoxy(int x, int y);
	void   SetColor(int color);
	void   SetColor(int color, int bgcolor);
	void   infoKey();
	void   Notify(int type); 
	void   computerStoneColor(int nColor);
	void   stonePoint(int x, int y);
	void   clearBuffer();
};

#endif

#define pDraw CDRAW::getInstance

