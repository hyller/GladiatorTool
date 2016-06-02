REM Convert .Docx file to Ascii doc file

set SOURCE_NAME="%*"
set TARGET_NAME="%*.adoc"

pandoc -f docx -t asciidoc %SOURCE_NAME% -s --atx-headers -o %TARGET_NAME%
