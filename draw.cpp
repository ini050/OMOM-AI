#include "draw.h"

CDRAW *CDRAW::getInstance()
{
	static CDRAW draw;
	return &draw;
}

CDRAW::CDRAW()
{
	nX = (40 - SIZE - 1) / 2;
	nY = 11 - SIZE / 2;
}

/* ========================================================================== */
/* 화면의 커서를 보이거나 숨기기 */
void CDRAW::CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

/* ========================================================================== */
/* x, y 좌표로 커서를 움직이는 함수 */
void CDRAW::gotoxy(int x, int y) /*커서이동 함수 부분*/
{
    COORD XY = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

/* ========================================================================== */
/* 콘솔 색깔을 지정하는 함수 */
void CDRAW::SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* ========================================================================== */
/* 콘솔 바탕과 글자에 색깔을 지정하는 함수 */
void CDRAW::SetColor(int color, int bgcolor) 
{

    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

void CDRAW::clearBuffer()
{
	while(kbhit()) getch();
}

void CDRAW::Notify(int type)
{
	const char *cNotify[] = {
		" ",
		" ",
		"흑 백 모두 아무 제약이 없이   ", 
		"둘수 있습니다.       ",
		"흑 백 모두 33금수 적용됩니다. ",
		"                     ",
		"흑은 33, 44, 6목을 둘 수 없고,",
		"백은 제약이 없습니다."
	};

    SetColor(GRAY);
    gotoxy(nX *2, nY - 2);
    printf("%s", cNotify[type * 2]);
    gotoxy(nX *2, nY - 1);
    printf("%s", cNotify[type * 2 + 1]);
} 

int CDRAW::GetMenu(char *cTitle)
{
    int x, y, n;
    
    const char *strTitle[] = {
    	"O M O K  G A M E",
    	"고모쿠(GOMOKU) 룰",
    	"일  반(NORMAL) 룰",
    	"렌  주(RENJU)  룰",
		"그   만   하   기"
	};
	
    const char *menu[] = { "    ",
                           "                         ",
                           "  1. ",
                           "                         ",
                           "  2. ",
                           "                         ",
                           "  3. ",
                           "                         ",
                           "  4. "};

    x = strlen(menu[1]);
    y = sizeof(menu) / sizeof(menu[0]);

    x = 40 - x / 2;
    y = 12 - y / 2 - 1;

    system("cls");
    SetColor(GRAY);
    for(int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++)
    {
        gotoxy(x, y + i);
        if(i & 1) printf("%s", menu[i]);
        else printf("%s%s", menu[i], strTitle[i / 2]);
    }

    while(true)
    {
        n = getch();
        if(n == ESC || n == '4') return ESC;
        else if(n >= '1' && n <= '3') break;
    }
	
	n -= '0';
	sprintf(cTitle, "OMOK GAME - %s", strTitle[n]);
    return n;
}

int CDRAW::GetMenu()
{
    int x, y, n;
    
    const char *strTitle[] = {
    	"    O M O K  G A M E",
    	"COMPUTER(BLACK) vs PLAYER",
    	"PLAYER(BLACK) vs COMPUTER",
    	"PLAYER vs PLAYER         ",
		"흑 돌 만  놓 아 보 기    ",
		"백 돌 만  놓 아 보 기    ",
	};
	
    const char *menu[] = { "    ",
                           "                              ",
                           "  1. ",
                           "                              ",
                           "  2. ",
                           "                              ",
                           "  3. ",
                           "                              ",
                           "  4. ",
                           "                              ",
                           "  5. "};

    x = strlen(menu[1]);
    y = sizeof(menu) / sizeof(menu[0]);

    x = 40 - x / 2;
    y = 12 - y / 2 - 1;

    system("cls");
    SetColor(GRAY);
    for(int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++)
    {
        gotoxy(x, y + i);
        if(i & 1) printf("%s", menu[i]);
        else printf("%s%s", menu[i], strTitle[i / 2]);
    }

    while(true)
    {
        n = getch();
        if(n >= '1' && n <= '5') break;
    }
	
    return n - '0';
}

void CDRAW::computerStoneColor(int nColor)
{
	int len;
	const char *strName[] = {
		"COMPUTER ",
		"PLAYER   ",
	};

	const char *strStone = "●";
	len = strlen(strName[0]) + 2;
	
    SetColor(nColor, DARK_YELLOW);
    gotoxy((nX - 1) * 2 - len, nY);
    printf("%s", strStone);
    SetColor(GRAY, DARK_YELLOW);
    printf("%s", strName[0]);
    SetColor(nColor ==  BLACK ? WHITE : BLACK, DARK_YELLOW);
    gotoxy((nX - 1) * 2 - len, nY + 1);
    printf("%s", strStone);
    SetColor(GRAY, DARK_YELLOW);
    printf("%s", strName[1]);
}

void CDRAW::stonePoint(int x, int y)
{
    SetColor(GRAY);
    gotoxy((nX + SIZE + 1) * 2, nY + 1);
    printf("착점 위치 : %c%d ", 'A' + x - 1, 15 - y + 1);
}

// 각종 메시지를 화면에 출력해준다. 
void CDRAW::errMsg(int msg)
{
	msg -= 10;
	const char *str[] = {
		"이미 돌이 놓여 있습니다.\n다른 곳에 착점하세요.",
		"삼삼 입니다.\n다른 곳에 착점하세요.",
		"사사 입니다.\n다른 곳에 착점하세요.",
		"흑은 육목을 둘 수 없습니다.\n다른 곳에 착점하세요.",
		"한 수만 물릴 수 있습니다"
	};
	MessageBox(NULL, str[msg], "Warning!", MB_OK);
}

void CDRAW::showMsg(int msg)
{
	const char *str[] = {
		"흑이 둘 차례입니다.",
		"백이 둘 차례입니다.",
		"       ",
		"흑 승입니다.       ",
		"백 승입니다.       ",
		"무승부입니다.      ",
	};
	
    SetColor(GRAY);
    gotoxy((nX + SIZE + 1) * 2, nY);
    printf("%s", str[msg]);
}


void CDRAW::infoKey()
{
}


bool CDRAW::endMsg(int stone)
{
 	const char *winner[] = {"    흑돌 승! \n한 게임 더 하시겠습니까?     ",
							"    백돌 승! \n한 게임 더 하시겠습니까?     ",
							"    무승부! \n한 게임 더 하시겠습니까?"};
	showMsg(stone + 3);
	if(MessageBox(NULL, winner[stone], "알 림", MB_YESNO) == IDYES) return true;
	else return false; 
}

// 바둑판과 돌을 그린다. 
void CDRAW::printData(int &x, int &y, int type)
{
 	if(x < 1)          x = 1;
	else if(y < 1)     y = 1;
	else if(x > SIZE)  x = SIZE;
	else if(y > SIZE)  y = SIZE;

	const int color[] = {BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK};
    const char *shape[] = {"┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘", "●", "●", "□"};
	
    SetColor(color[type], DARK_YELLOW);
    // 라인의 종류는 9가지 모양을 가지니까 
	// 어떤걸 그려야 할지 좌표를 주고 모양을 가져온다. 
    if(type == LINE) type = getLineNumber(x, y);
    // 라인은 0-8까지 이고, 그 뒤에 돌이 배치되어 있으니 9를 더해준다. 
    else type += 9;
    gotoxy((x + nX - 1) * 2, y + nY - 1);
    printf("%s", shape[type]);
    SetColor(GRAY);
}

// 가로와 세로줄의 좌표를 숫자와 알파벳으로 표시해준다.
// 가로나 세로에 숫자나 아파벳으로 통일하면 좌표를 표시할 때
// 혼동이 올 수 있으니 구분해 표시한다. 
void CDRAW::printNum()
{
    SetColor(BLACK, DARK_YELLOW);
    //x방향 출력 
    for(int i = 0; i < SIZE; i++) 
    {
    	gotoxy((nX + i) * 2, nY + SIZE);
    	printf("%2c", i + 'A');
	}
	//y방향 출력 
    for(int i = 0, j = SIZE; i < SIZE; i++, j--) 
    {
    	gotoxy((nX - 1) * 2, nY + j - 1);
    	printf("%2d", i + 1);
	}
	gotoxy((nX - 1) * 2, nY + SIZE);
	printf("  ");
    SetColor(GRAY);
}

//┌┬┐
//├┼┤
//└┴┘
//순서는 아래와 같이 한다. 
//0 1 2
//┌┬┐
//3 4 5
//├┼┤
//6 7 8
//└┴┘
// 위 모양은 바둑판의 축소판이다
// 바둑판의 모든 모양은 
// 이 9가지 모양만 있으면 그려낼 수 있다. 
// x가 0일때는 왼쪽 줄
// y가 0일때는 윗쪽 행등등 
// x,y값에 따라 모양의 번호를 반환한다. 

// 바둑판 전체를 그려넣고 다시 그려도 되지만
// 그렇게 하면 만약 Size를 19로 하고 싶을때
// 전체를 수정해야 되고, 또한 화면이 깜빡 거릴 수 있어서
// 필요한 곳만 그때그때 그려주려 이런 작업을 한는 것이다. 
int CDRAW::getLineNumber(int x, int y)
{
	// 왼쪽 세로줄 
	if(x == 1)
	{
		// x, y가 다 0이면 왼쪽 상단 모서리 
		if(y == 1) return 0;
		// 왼쪽 하단 모서리 
		else if(y == SIZE) return 6;
		// 왼쪽 세로줄 
		else return 3;
	}
	// 오른쪽 세로줄 
	else if(x == SIZE)
	{
		// 오른쪽 상단 모서리 
		if(y == 1) return 2;
		// 오른쪽 하단 모서리 
		else if(y == SIZE) return 8;
		// 오른쪽 세로줄 
		else return 5;
	}
	// 윗쪽 가로줄
	else if(y == 1) return 1;
	// 아래쪽 가로줄
	else if(y == SIZE) return 7;
	// 마지막 가운데 + 모양 
	else return 4;
}

//게임 시간을 화면에 표시해준다. 
void CDRAW::drawTime(time_t sec)
{
	int hh, mm;
	
    hh = sec / 3600;
    mm = (sec % 3600) / 60;
    sec = sec %= 60;

	SetColor(SKY_BLUE);
	gotoxy(nX * 2 - 2, nY + SIZE +  1);
	printf("%02d : %02d : %02d", hh, mm, sec);
	SetColor(GRAY);
}
