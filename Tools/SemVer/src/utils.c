#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void ChangFileName(char* oldname, char* append, char* newname)
{
  char   prefix[128] = {0};
  char   sufix[128] = {0};
  int i;
  
  for(i = (int)strlen(oldname) - 1; i >= 0; i--)
  {	 
	  if(oldname[i] == '.')
	  {
		memcpy(prefix, oldname, (unsigned int)i);
		memcpy(sufix, &oldname[i+1], (unsigned int)((int)strlen(oldname) - i - 1));		
		break;
	  }
  }	  

  sprintf( newname,"%s_v%s.%s", prefix, (char*)append ,sufix);  
}