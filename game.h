#ifndef __GAME_H__
#define __GAME_H__

#include "omokfactory.h"

// Game진행을 전담하는 class 
class CGAME
{
private :
	// t1 : 1초마다 화면에 시간을 표시해주기 위한 변수
	// 매초마다 초기화 
	// t2 : 게임이 시작 될때 초기화 하여 
	// 게임이 종료될 때까지 유지하면서 기준시간이 된다. 
	// t3 : 시간제한이 필요할때 사용할 변수 
	time_t  t1, t2, t3;
	//현재 착점을 할 돌
	int     curStone;
	// omok의 x, y와 같은 좌표를 유지한다. 
	int     x, y; 
	
	// 무승부를 알기 위해서 변수가 이렇게 많이 필요하다.
	// 누군가 pass를  하면 passTrigger가 On상태가 된다.
	// 그럼 passCounter가 시작되고
	// 연속으로 백돌과 흑돌이 연속으로 눌렀는지 
	// 아니면 한쪽 돌만 연속으로 pass한 것인지 
	// 판단하기 위하여 stoneState는 배열을 사용함. 
	// 무승부임을 알리는게 의외로 복잡하다. 
	bool    isComputer;
	bool    passTriggerOn; 
	int     passCount;
	int     stoneState[2];

	COMOKFACTORY factory;
	COMOK      *pOmok[2];
	
	bool        checkTie();  
	void        drawTime();
	void        initGame(int mode);
	void        changeStone(int mode); 
	int         getKey();
	int         checkKey(int mode);
	
public :
	CGAME();
	~CGAME() {;}
	
	bool    playGame(int type, int mode);
};

#endif
