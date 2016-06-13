REM Convert .Docx file to Ascii doc file

set SOURCE_NAME="%~1"
set TARGET_NAME="%~2"

pandoc -f docx -t asciidoc %SOURCE_NAME% -s --atx-headers -o %TARGET_NAME%
