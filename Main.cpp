#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif
#include "stdafx.h"
#include "compute.h"
#include <stdio.h>

 int _tmain(int argc, _TCHAR* argv[]) 
{
	 Compute *komm = new Compute();
	  komm->init();
	  komm->start();
	return 0;
}
