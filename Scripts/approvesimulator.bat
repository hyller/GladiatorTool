cd C:\SeWorkspace\wct\zigbee-test-solution-develop
gh pr list
set /P num="Please input pr number(ONLY THE NUMBER): " 
gh pr review %num% --approve
pause