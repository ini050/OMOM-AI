#include "game.h"

CGAME::CGAME()
{
}

// 게임이 시작할때 필요한 변수들을 초기화 하고,
// 화면에 표시해준다. 
void CGAME::initGame(int mode)
{
	x = y = CENTER;
	t1 = t2 = clock();
	passTriggerOn = false;
	passCount = 0;
	stoneState[0] = 0;
	stoneState[1] = 0;
	drawTime();
	if(mode == 2) isComputer = true;
	else isComputer = false;
	if(mode == 4) curStone = BLACK_STONE;
	else curStone = WHITE_STONE;
	if(mode == 5) pDraw()->printData(x, y, WHITE_STONE);
	else pDraw()->printData(x, y, BLACK_STONE);
	if(mode == 1) pDraw()->computerStoneColor(BLACK);
	else if(mode == 2) pDraw()->computerStoneColor(WHITE);
	pDraw()->stonePoint(x, y);
	pDraw()->showMsg(curStone);
	if(mode == 5) pOmok[curStone]->initOmok(WHITE_STONE);
	else pOmok[curStone]->initOmok(BLACK_STONE);
	pOmok[curStone]->cursorView(x, y); 
	pDraw()->clearBuffer();
}

// main함수에서 이 함수를 호출하면 게임이 시작된다. 
bool CGAME::playGame(int type, int mode)
{
	int result;
	system("cls");
	
	pOmok[0] = factory.GetInstance(type * 10 + 0, mode);
	pOmok[1] = factory.GetInstance(type * 10 + 1, mode);
	pDraw()->Notify(type);
	initGame(mode);
	while(true)
	{
		// 1초마다 화면에 시간을 표시한다. 
		if(clock() - t1 >= 1000) drawTime();
		
		result = checkKey(mode);
		switch(result)
		{
			
			//추가기능 : 키보드에서 ESC 입력시 게임종료 
			//추가이유 : 기존 방식에서는 창의 x 버튼을 눌러 종료시키는 방법밖에 없어 불편함을 겪어 추가함
			case FINISH   : return false;
			
			//수정기능 : 게임종료 메시지 YES,NO 출력 
			//추가이유 : 게임종료시 게임종료가아닌 재게임을 원하여 수 
    		case FIVEMOK  : return pDraw()->endMsg(curStone);
    		
			// 착수가 불가능한 곳은 그 이유를 알린다. 
			case OCCUPIED :
			case SAMSAM   :
			case SASA     :
			case SIXMOK   : 
			case NOTUNDO  : 
				pDraw()->errMsg(result); 
				pOmok[curStone]->setBoard(x, y); 
				break;
			//착수가 됐거나, 한수 물렸을 때 돌을 바꾼다.  
			case PASS     : if(!passTriggerOn) passTriggerOn = true;
							stoneState[curStone]++;
							if(mode == 1 || mode == 2) stoneState[(curStone + 1) % 2]++;
			case CHANGE   : changeStone(mode); break;
			default       : break;
		}
		pOmok[curStone]->cursorView(x, y);
		if(checkTie()) return pDraw()->endMsg(TIED);
		Sleep(20);
	}
}

// 흑과 백의 둘 차례를 바꾼다. 
void CGAME::changeStone(int mode)
{
	// 흑백 둘이니 더해서 2로 나누면 교환이 된다. 
	if(mode == 4) curStone = BLACK_STONE;
	else if(mode == 5) curStone = WHITE_STONE;
	else curStone = (curStone + 1) % 2;
	
	//컴퓨터와 둘때 차례를 알리기 위한 변수의 상태 변경 
	if(mode == 1 || mode == 2) isComputer = !isComputer;
	// 현재 둘 차례를 알려준다. 
	pDraw()->showMsg(curStone);
	if(passTriggerOn) passCount++;
}

bool CGAME::checkTie()
{
	if(!passTriggerOn) return false;

	bool isTied = false;
	if(passCount == 2)
	{
		if(stoneState[0] == 1 && stoneState[1] == 1) isTied = true;
		passTriggerOn = false;
		passCount     = 0;
		stoneState[0] = 0;  
		stoneState[1] = 0;  
	}
	return isTied;
}

// 1 초마다 화면에 시간을 표시한다. 
void CGAME::drawTime()
{
	time_t sec = (clock() - t2) / 1000;
	pDraw()->drawTime(sec);
	t1 = clock();   
}


int CGAME::getKey()
{
	int ch = getch();
	if(ch == 0 || ch == 0xE0) ch = getch();

	return ch;
}

int CGAME::checkKey(int mode)
{
    int ch, dx, dy;;
    if(isComputer) return pOmok[curStone]->placement(x, y, curStone);
	else if(kbhit()) ch = getKey();
    else return 0;
    dx = dy = 0;
    switch(ch)
    {
    	case ESC   : return FINISH;
    	
		case UP    : --dy; break;
		case DOWN  : ++dy; break;
    	case LEFT  : --dx; break;
		case RIGHT : ++dx; break;

        
		case DEL   : return PASS;
        case ' '   : return pOmok[curStone]->placement(x, y, curStone);
        case 'r'   : 
        case 'R'   :
        	if(mode == 1 || mode == 2)
        	{
	        	pOmok[curStone]->redo(); 
	        	pOmok[(curStone + 1) % 2]->redo(); 
			}
			else return pOmok[curStone]->redo(); 
        case 'u'   : 
        case 'U'   : 
        	if(mode == 1 || mode == 2)
        	{
	        	pOmok[curStone]->undo(); 
	        	pOmok[(curStone + 1) % 2]->undo(); 
			}
			else return pOmok[curStone]->undo(); 
			

			
        default    : break;
	}
    pOmok[curStone]->setBoard(x, y);
    y += dy;
    x += dx;
    pDraw()->printData(x, y, CURSOR);

    return 0;
}
