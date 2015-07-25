#ifndef _UTILS_H_
  #define _UTILS_H_

#ifdef __cplusplus
    extern "C"
    {
#endif

  int Utils_ReadFile( char* filename,  char* buf,int   size );
  int Utils_WriteFile( char* filename, char* buf,int   size );
  int Utils_CopyFile( char* filename, char* newname );
  void ChangFileName(char* oldname, char* append, char* newname);

#ifdef __cplusplus
    }
#endif
#endif