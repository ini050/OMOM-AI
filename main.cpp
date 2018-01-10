// 오목 프로그램에 도전 1016년 12월 2일 08시 45분 
// 처음 목표는 화면에 바둑판을 그리고
// 원하는 위치에 바둑알을 그려 넣는다.
// 게임이 진행되는 동안 승패 여부를 검사한다.
// 모든 룰은 무시하고 
// 5줄 연속으로 돌이 놓이면 승리로 간주한다. 
// 승패가 갈리면 게임을 종료하고 
// "흑"이 또는 "백"이 승리 하였다고 알린다.
// 한번더 할 것인지 물어본다.

// 착수할 때 실수할 수 있으니 
// 한번의 무르기를 인정한다. 

// 마지막 착수 지점을 빈공간에 좌표로 표시해준다. 


#include "game.h"

int main()
{
	int   type, mode;
	char  cTitle[128];
	CGAME game;
	
	pDraw()->CursorView(HIDE);
	while(true)
	{
		SetConsoleTitle("OMOK GAME - Made by LJW");
		type = pDraw()->GetMenu(cTitle);
		if(type == ESC) break;
		else SetConsoleTitle(cTitle);
		mode = pDraw()->GetMenu();
		
		while(game.playGame(type, mode));
	}

	pDraw()->CursorView(SHOW);
	return 0;
}
