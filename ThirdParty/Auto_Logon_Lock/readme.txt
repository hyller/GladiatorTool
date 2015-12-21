======================================================
Auto Login & Lock v1.0
By Kurian Abraham
======================================================

You can have your Windows PC automatically logon to a user account on boot and then lock the desktop so a password is still required.

Some of the reasons you might want to do this are:

* Faster boot time. The additional post-logon start up items are also started after Windows boots. Which means when you press the power button on your PC and come back after a few minutes, its COMPLETELY booted up. No need to wait for additional software to load after you logon.

* Automatically resume downloads etc. when your PC reboots due to a power failure or crash. On XP you could do this by installing the application as a system service. In Vista and 7, Session 0 Isolation makes using a system service a pain, not to mention it's insecure. Just put your applications in the regular Windows Start Up folder and they will be launched after the auto logon.

* It password protects Safe Mode as well. Existing auto logon methods leave Safe Mode unprotected.

* It locks the desktop before Explorer is started. Other methods auto-lock using an autorun/start up entry which leave the PC logged on and unlocked until the autorun entries are executed (which can even take several minutes).

======================================================
Installation
======================================================

Tested on Windows Vista (32-bit & 64-bit), Windows 7 (32-bit & 64-bit).

1) Run "Lock.exe" from the archive to test if the application runs without errors. If all is well your desktop should lock. Logon again and Windows Explorer should be open. You might want to create a System Restore Point before proceeding just to be safe.

2) Copy the files "Lock.exe" and "LockCMD.exe" to your Windows directory. (Ex: C:\Windows)

3) Run "lockcmd.reg" from the archive and click Yes in the dialog box. You must run this while logged on to the account which you want to enable auto logon for.

4) Click Start and type "netplwiz.exe" (Without the quotes) and press Enter.

5) Uncheck the box "Users must enter a user name and password to use this computer" and click OK. Enter the Username and Password of the account you want to enable auto logon for.

6) Reboot your PC to test it.