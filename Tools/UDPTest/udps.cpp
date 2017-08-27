#include <assert.h>
#include <stdio.h>
#include <conio.h>
#include <winsock2.h> // for Windows sockets
#include <time.h> // for clock()
#include <math.h>
#include "version.h"

//............................................................................
static SOCKET socketOpen( unsigned short localPortNum )
{
  // initialize Windows sockets
  static WSADATA wsaData;
  int            wsaErr = WSAStartup( MAKEWORD( 2, 0 ), &wsaData );

  if ( wsaErr == SOCKET_ERROR )
  {
    fprintf( stderr, "不能初始化Windows套接字.\n"
                     "库错误 %d.", wsaErr );
    return( INVALID_SOCKET );
  }

  SOCKET sock = socket( AF_INET, SOCK_DGRAM, 0 ); // UDP socket
  if ( sock == INVALID_SOCKET )
  {
    fprintf( stderr, "创建UDP套接字失败" );
    WSACleanup( );
    return( INVALID_SOCKET );
  }

  // set the socket to non-blocking mode.
  ULONG ioctl_opt = 1;
  if ( ioctlsocket( sock, FIONBIO, &ioctl_opt ) == SOCKET_ERROR )
  {
    fprintf( stderr, "套接字配置失败.\n"
                     "Windows套接字错误 %d.",
             WSAGetLastError( ) );
    WSACleanup( );
    return( INVALID_SOCKET );
  }

  struct sockaddr_in local;
  memset( &local, 0, sizeof( local ) );
  local.sin_family      = AF_INET;
  local.sin_addr.s_addr = INADDR_ANY;
  local.sin_port        = htons( localPortNum );

  // bind() associates a local address and port combination with the
  // socket just created. This is most useful when the application is a
  // server that has a well-known port that clients know about in advance.
  if ( bind( sock, ( struct sockaddr* )&local, sizeof( local ) )
       == SOCKET_ERROR )
  {
    fprintf( stderr, "绑定服务器套接字错误.\n" );
    WSACleanup( );
    return( INVALID_SOCKET );
  }

  return( sock ); // no error message, i.e. success
}

static char l_pkt[256]; // packet received frorm the UDP socket

//............................................................................
int main( int argc, char *argv[] )
{
  printf( "udp server utility %s (c) 零一物联网工作室, zeroone.taobao.com\n", VERSION );
  if ( argc != 2 )
  {
    fprintf( stderr, "usage: udps <port>\n" );
    return( -1 );
  }

  unsigned short port;
  if ( sscanf( argv[1], "%hd", &port ) != 1 )
  {
    fprintf( stderr, "错误的端口号: %s\n", argv[2] );
    return( -2 );
  }

  printf( "正在打开以及绑定套接字...\n" );
  static SOCKET sock = socketOpen( port );
  if ( sock == INVALID_SOCKET )
  {
    return( -3 );
  }
  printf( "完成\n" );

  printf( "等待报文..." );
  for (;; )
  {
    if ( kbhit( ) )
    {
      break; // terminate
    }

    fd_set readSet;
    FD_ZERO( &readSet );
    FD_SET( sock, &readSet );

    struct timeval delay;
    delay.tv_sec  = 0;
    delay.tv_usec = 200 * 1000;

    int nfound = ::select( 0, &readSet, 0, 0, &delay );
    if ( nfound > 0 )
    {
      struct sockaddr from;
      int             fromSize = sizeof( from );
      int             nrec     = recvfrom( sock, l_pkt, sizeof( l_pkt ), 0,
                                           &from, &fromSize );
      if ( nrec == SOCKET_ERROR )
      {
        fprintf( stderr, "recvfrom()失败.\n"
                         "Windows套接字错误 %d.",
                 WSAGetLastError( ) );
      }
      else if ( nrec > 0 )
      {
        printf( "\n接收: %s\n", ( char const* )l_pkt );
        sendto( sock, l_pkt, nrec, 0,
                ( struct sockaddr* )&from, fromSize );
        printf( "回复\n" );
      }
    }
  }

  closesocket( sock );
  printf( "完成.\n" );

  return( 0 );
}
