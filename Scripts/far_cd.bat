@echo off
rem brief: Replace string in all files under current directly
rem usage: gfar str_old str_new
rem example: gfar gaia gesp
rem          replace gaia by gesp

fart -r --svn . %1 %2