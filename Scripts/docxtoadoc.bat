
if "%2"=="" (
  set SOURCE_NAME="%1.docx"
  set TARGET_NAME="%1.adoc"
) else (
  set SOURCE_NAME=%1
  set TARGET_NAME=%2
)

pandoc -f docx -t asciidoc %SOURCE_NAME% -s --atx-headers -o %TARGET_NAME%