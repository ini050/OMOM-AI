#ifndef __OMOKFACTORY_H__
#define __OMOKFACTORY_H__

#include "omok.h"

class COMOKFACTORY
{
private :
	COMOK       gomoku_Black;
	COMOK       gomoku_White;
	CNORMAL     general_Black;
	CNORMAL     general_White;
	CBLACKSTONE renju_Black;
	    
	CGOMOKUAI   gomokuAI_Black;
	CGOMOKUAI   gomokuAI_White;
	CJENERALAI  normalAI_Black;
	CJENERALAI  normalAI_White;
	CRENJUAI    renjuAI_Black;

public : 
	COMOKFACTORY()  {}
	~COMOKFACTORY() {}
	
	COMOK *GetInstance(int type, int mode);
};

#endif
