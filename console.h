#ifndef __CONSOLE_H__
#define __CONSOLE_H__

// 1단계 console game을 만들기 위한 기본 Data를 복사해온다.
// 이 부분은 굳이 이해하려거나 외울 필요는 없다.
// 필요할 때마다 복사해 가져다 쓰면 된다. 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define BACK_SPACE       8
#define	ENTER   		13
#define	ESC				27
#define UP				72
#define DOWN			80
#define LEFT			75
#define RIGHT			77
#define PAGE_UP			73
#define PAGE_DOWN		81
#define DEL	    		83

enum {
	BLACK,			/*  0 : 까망 */
	DARK_BLUE,		/*  1 : 어두운 파랑 */
	DARK_GREEN,		/*  2 : 어두운 초록 */
	DARK_SKY_BLUE,	/*  3 : 어두운 하늘 */
	DARK_RED,		/*  4 : 어두운 빨강 */
	DARK_VIOLET,	/*  5 : 어두운 보라 */
	DARK_YELLOW,	/*  6 : 어두운 노랑 */
	GRAY,			/*  7 : 회색 */
	DARK_GRAY,		/*  8 : 어두운 회색 */
	BLUE,			/*  9 : 파랑 */
	GREEN,			/* 10 : 초록 */
	SKY_BLUE,		/* 11 : 하늘 */
	RED,			/* 12 : 빨강 */
	VIOLET,			/* 13 : 보라 */
	YELLOW,			/* 14 : 노랑 */
	WHITE,			/* 15 : 하양 */
};

#endif
