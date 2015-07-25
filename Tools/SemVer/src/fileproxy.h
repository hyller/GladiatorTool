#ifndef _FILEPROXY_H_
  #define _FILEPROXY_H_

#ifdef __cplusplus
    extern "C"
    {
#endif

  int FileProxy_ReadVersion( char* filename,  char* buf,int   size );
  int FileProxy_WriteVersion( char* filename, char* buf,int   size );
  int FileProxy_CopyFile( char* filename, char* newname );

#ifdef __cplusplus
    }
#endif
#endif