macro SelfEncapDataGet()
{
	hbuf = GetCurrentBuf();
	hwnd = GetCurrentWnd();
	sel  = GetBufSelText(hbuf);

  if(sel == nil)
  {
    return
  }
	
	oldPattern = "\\(.*=.*\\)\\(@sel@\\)\\(.*;.*\\)";
	newPattern = "\\1\\Get@sel@()\\3";
	lnStart = 0;
	lnLim = GetBufLineCount(hbuf);
	fMatchCase = 0;
	fRegExp = 1;
	fWholeWordsOnly = 0;
	fConfirm = 1;

  ReplaceInBuf(hbuf, oldPattern, newPattern, lnStart, lnLim, fMatchCase, fRegExp, fWholeWordsOnly, fConfirm);  
}

macro SelfEncapDataSet()
{
	hbuf = GetCurrentBuf();
	hwnd = GetCurrentWnd();
	sel  = GetBufSelText(hbuf);

  if(sel == nil)
  {
    return
  }
	
	oldPattern = "\\(\\w*@sel@\\w*=\\)\\(.*\\)\\(;\\)";
	newPattern = "\\Set@sel@(\\2\\);";
	
	lnStart = 0;
	lnLim = GetBufLineCount(hbuf);
	fMatchCase = 0;
	fRegExp = 1;
	fWholeWordsOnly = 0;
	fConfirm = 1;

  ReplaceInBuf(hbuf, oldPattern, newPattern, lnStart, lnLim, fMatchCase, fRegExp, fWholeWordsOnly, fConfirm);  
}

