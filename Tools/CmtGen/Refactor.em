macro _ReplaceInBufRegex(hbuf, oldPattern, newPattern)
{
	lnStart = 0;
	lnLim = GetBufLineCount(hbuf);
	fMatchCase = 0;
	fRegExp = 1;
	fWholeWordsOnly = 0;
	fConfirm = 1;

  ReplaceInBuf(hbuf, oldPattern, newPattern, lnStart, lnLim, 
               fMatchCase, fRegExp, fWholeWordsOnly, fConfirm); 
}

macro _CreateGetDataFunction(hbuf, name)
{
	AppendBufLine( hbuf, "void Get@name@( void )" )
	AppendBufLine( hbuf, "{" )
	AppendBufLine( hbuf, "  return @name@;" )
	AppendBufLine( hbuf, "}" )
}

macro SelfEncapDataGet()
{
	hbuf = GetCurrentBuf()
	sel  = GetBufSelText(hbuf)

  if(sel == nil)
  {
    return
  }
	
	oldPattern = "\\(.*=.*\\)\\(@sel@\\)\\(.*;.*\\)"
	newPattern = "\\1\\Get@sel@()\\3"

  _ReplaceInBufRegex(hbuf, oldPattern, newPattern)

  _CreateGetDataFunction(hbuf, sel)
}

macro _CreateSetDataFunction(hbuf, name)
{
	AppendBufLine( hbuf, "void Set@name@( var )" )
	AppendBufLine( hbuf, "{" )
	AppendBufLine( hbuf, "  @name@ = var;" )
	AppendBufLine( hbuf, "}" )
}

macro SelfEncapDataSet()
{
	hbuf = GetCurrentBuf( )
	sel  = GetBufSelText(hbuf)

  if(sel == nil)
  {
    return
  }
	
	oldPattern = "\\(\\w*@sel@\\w*=\\)\\(.*\\)\\(;\\)"
	newPattern = "\\Set@sel@(\\2\\);"
	
	_ReplaceInBufRegex(hbuf, oldPattern, newPattern)
	
  _CreateSetDataFunction(hbuf, sel)
}

macro ExtractFunction()
{
	hbuf = GetCurrentBuf();
	hwnd = GetCurrentWnd();
	sel = GetWndSel(hwnd);

  // Create extracted fucntion
	AppendBufLine( hbuf, "void extractedfunction( void )" )
	AppendBufLine( hbuf, "{" )
	iLine = sel.lnFirst
  while (iLine <= sel.lnLast)
	{
		szLine = GetBufLine(hbuf, iLine)
		AppendBufLine(hbuf, szLine)
		iLine = iLine + 1
	}
	AppendBufLine( hbuf, "}" )
  
	iLine = sel.lnFirst; // Save line number
	
	cut // Delete origin code block

  // Call extracted function
	InsBufLine( hbuf, iLine, "extractedfunction( );" )
}


