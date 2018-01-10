#include "omokfactory.h"

COMOK *COMOKFACTORY::GetInstance(int type, int mode)
{
	type = mode * 100 + type;
	switch(type)
	{
		case 110 : return &gomokuAI_Black;
		case 131 :
		case 111 : return &gomoku_White;
		case 120 : return &normalAI_Black;
		case 121 : return &general_White;
		case 130 : return &renjuAI_Black;

		case 210 : return &gomoku_Black;
		case 231 :
		case 211 : return &gomokuAI_White;
		case 220 : return &general_Black;
		case 221 : return &normalAI_White;
		case 230 : return &renju_Black;

		case 410 :
		case 510 :
		case 310 : return &gomoku_Black;
		case 431 :
		case 531 :
		case 331 :
		case 411 :
		case 511 :
		case 311 : return &gomoku_White;
		case 420 :
		case 520 :
		case 320 : return &general_Black;
		case 421 :
		case 521 :
		case 321 : return &general_White;
		case 430 :
		case 530 :
		case 330 : return &renju_Black;
	}
}
