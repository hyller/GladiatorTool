@echo off
setlocal

perl "%GLADIATOR_HOME%\ThirdParty\Markdown_1.0.1\Markdown.pl" --html4tags %1 >%1.html

endlocal
@echo on