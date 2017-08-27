介绍：

udpc/udps是简单测试UDP的命令工具。可以测试运行UDP/IP协议的物联网设备。

udpc工具可以发送UDP报文到指定的IP地址以及端口。
udps工具可以接收本地指定端口的UDP报文。



使用：


1. 启动UDP服务器

udps 777
udp server utility 0.5.0 (c) 零一物联网工作室, zeroone.taobao.com
正在打开以及绑定套接字...
完成
等待报文...


2. 通过UDP客户端连接

udpc 127.0.0.1
udp client utility 0.5.0 (c) 零一物联网工作室, zeroone.taobao.com
打开以及绑定本地套接字在端口=1777...准备好
远程UDP连接: IP-address=127.0.0.1, port=777
输入命令; 或Enter发送命令, ESC退出
