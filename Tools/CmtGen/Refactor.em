macro _ReplaceInBufRegex( hbuf, oldPattern, newPattern )
{
  lnStart         = 0;
  lnLim           = GetBufLineCount( hbuf );
  fMatchCase      = 0;
  fRegExp         = 1;
  fWholeWordsOnly = 0;
  fConfirm        = 1;

  ReplaceInBuf( hbuf, oldPattern, newPattern, lnStart, lnLim,
                fMatchCase, fRegExp, fWholeWordsOnly, fConfirm );
}

macro RefactorGetData( )
{
  hbuf = GetCurrentBuf( );
  sel  = GetBufSelText( hbuf );

  if ( sel == nil )
  {
    return;
  }

  oldPattern = "\\(.*=.*\\)\\(@sel@\\)\\(.*;.*\\)";
  newPattern = "\\1\\Get@sel@()\\3";

  _ReplaceInBufRegex( hbuf, oldPattern, newPattern );

  AppendBufLine( hbuf, "void Get@sel@( void )" );
  AppendBufLine( hbuf, "{" );
  AppendBufLine( hbuf, "  return @sel@;" );
  AppendBufLine( hbuf, "}" );
}

macro RefactorSetData( )
{
  hbuf = GetCurrentBuf( );
  sel  = GetBufSelText( hbuf );

  if ( sel == nil )
  {
    return;
  }

  oldPattern = "\\(\\w*@sel@\\w*=\\)\\(.*\\)\\(;\\)";
  newPattern = "\\Set@sel@(\\2\\)";

  _ReplaceInBufRegex( hbuf, oldPattern, newPattern );

  AppendBufLine( hbuf, "void Set@sel@( var )" );
  AppendBufLine( hbuf, "{" );
  AppendBufLine( hbuf, "  @sel@ = var;" );
  AppendBufLine( hbuf, "}" );
}

macro RefactorExtractMethod( )
{
  hbuf = GetCurrentBuf( );
  hwnd = GetCurrentWnd( );
  sel  = GetWndSel( hwnd );

  // Create extracted fucntion
  AppendBufLine( hbuf, "void extractedfunction( void )" );
  AppendBufLine( hbuf, "{" );
  iLine = sel.lnFirst;
  while ( iLine <= sel.lnLast )
  {
    szLine = GetBufLine( hbuf, iLine );
    AppendBufLine( hbuf, szLine );
    iLine = iLine + 1;
  }
  AppendBufLine( hbuf, "}" );

  iLine = sel.lnFirst; // Save line number

  cut; // Delete origin code block

  // Call extracted function
  InsBufLine( hbuf, iLine, "extractedfunction( );" );
}

macro RefactorMisraConstU( )
{
  hbuf = GetCurrentBuf( );

  // Constant like 0xff, 0x10, white space at the end
  oldPattern = "\\(\\w0[xX][0-9a-fA-F]+\\)\\([\\w;,]\\)";
  newPattern = "\\1\\u\\2\\";
  _ReplaceInBufRegex( hbuf, oldPattern, newPattern );

  // Constant like 0xff, 0x10, white space at the end
  oldPattern = "\\(\\w0[xX][0-9a-fA-F]+\\)\\w";
  newPattern = "\\1\\u\\s";
  _ReplaceInBufRegex( hbuf, oldPattern, newPattern );

  // Constant like 0xff, 0x10, and at the end of the line
  oldPattern = "\\(\\w0[xX][0-9a-fA-F]+$\\)";
  // Add u at the end
  newPattern = "\\1\\u";
  _ReplaceInBufRegex( hbuf, oldPattern, newPattern );

  // Constant like 10, 356, ; or , at the end
  oldPattern = "\\(\\w[0-9]+\\)\\([;,]\\)";
  newPattern = "\\1\\u\\2\\";
  _ReplaceInBufRegex( hbuf, oldPattern, newPattern );

  // Constant white space at the end
  oldPattern = "\\(\\w[0-9]+\\)\\w";
  newPattern = "\\1\\u\\s";
  _ReplaceInBufRegex( hbuf, oldPattern, newPattern );

  // Constant at the end of the line
  oldPattern = "\\(\\w[0-9]+$\\)";
  // Add u at the end
  newPattern = "\\1\\u";
  _ReplaceInBufRegex( hbuf, oldPattern, newPattern );
}

// Add Bracket for define, for example
// Before:  #define XXX YYY ZZZ
// After :  #define XXX ( YYY ZZZ )
macro RefactorDefineAddBracket( )
{
  hbuf = GetCurrentBuf( );

  oldPattern = "\\(\\#define\\w+.+\\w+\\)\\(.+[^)]$\\)";
  newPattern = "\\1\\( \\2\\ )";
  _ReplaceInBufRegex( hbuf, oldPattern, newPattern );
}
