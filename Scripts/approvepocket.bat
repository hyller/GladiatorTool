cd C:\SeWorkspace\Lianyungang\Pocket\
gh pr list
set /P num="Please input pr number(ONLY THE NUMBER): " 
gh pr review %num% --approve
pause