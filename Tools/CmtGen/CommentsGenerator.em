macro _GetCurLineText( )
{
  hbuf = GetCurrentBuf( );
  line = GetBufLnCur( hbuf );
  text = GetBufLine( hbuf, line );

  return( text );
}

macro _GetCurLineTextWithoutSemicolon( )
{
  text = _GetCurLineText( );
  ich  = RFindString( text, ";" );

  if ( ich != "X" )
  {
    text = strmid( text, 0, ich );
  }

  return( text );
}

macro _GetFileName( )
{
  hbuf = GetCurrentBuf( );

  fname = GetBufname( hbuf ) //name style:  D:\dirname\filename.c;

          len = strlen( fname );
  i           = strlen( fname );

  while ( i > 0 )
  {
    ch = fname[i];
    if ( ch == "\\" )
    {
      i = i + 1;
      break;
    }
    i = i - 1;
  }

  sname = "";
  while ( i < len )
  {
    sname = Cat( sname, fname[i] );
    i     = i + 1;
  }

  return( sname );
}

macro _IsHeaderFile( )
{
  fname = _GetFileName( );
  len   = strlen( fname );
  i     = 0;

  while ( i < len )
  {
    ch = fname[i];
    if ( ch == "." )
    {
      break;
    }
    i = i + 1;
  }
  ch = fname[i + 1];

  if ( ( ch == "h" ) || ( ch == "H" ) )
  {
    return( 1 );
  }
  else
  {
    return( 0 );
  }
}

macro _CmtGenIfDefCpp( line )
{
  hbuf  = GetCurrentBuf( );
  fname = _GetFileName( );

  if ( !_IsHeaderFile( ) )
  {
    return;
  }

  headname = "";
  len      = strlen( fname );
  i        = 0;
  while ( i < len )
  {
    ch = fname[i];
    if ( ch == "." )
    {
      break;
    }

    headname = Cat( headname, toupper( ch ) );
    if ( islower( ch ) && isupper( fname[i + 1] ) )
    {
      headname = Cat( headname, "_" );
    }
    i = i + 1;
  }

  headname = Cat( headname, "_H" );

  InsBufLine( hbuf, line++, "#ifndef @headname@" );
  InsBufLine( hbuf, line++, "#define @headname@" );
  InsBufLine( hbuf, line++, "" );
  InsBufLine( hbuf, line++, "#ifdef __cplusplus" );
  InsBufLine( hbuf, line++, "  extern \"C\" {" );
  InsBufLine( hbuf, line++, "#endif" );
  InsBufLine( hbuf, line++, "" );
  InsBufLine( hbuf, line++, "" );

  AppendBufLine( hbuf, "#ifdef __cplusplus" );
  AppendBufLine( hbuf, "  }" );
  AppendBufLine( hbuf, "#endif" );
  AppendBufLine( hbuf, "" );
  AppendBufLine( hbuf, "#endif" );
}

macro _CmtGenHeadinfo( )
{
  hbuf     = GetCurrentBuf( );
  tempname = "sourcefileheadinformation";

  line     = 0;
  hbuftemp = OpenBuf( tempname );
  if ( hbuftemp != hNil )
  {
    count = GetBufLineCount( hbuftemp );
    line  = 0;
    while ( line < count )
    {
      linestr = GetBufLine( hbuftemp, line );
      InsBufLine( hbuf, line++, linestr );
    }
  }
  else
  {
    InsBufLine( hbuf, line++, "//----------------------------------------------------------------------------//" );
  }

  return( line );
}

macro _CmtGenFileBrief( line )
{
  hbuf  = GetCurrentBuf( );
  fname = _GetFileName( );

  InsBufLine( hbuf, line++, "/// \\file   @fname@" );
  InsBufLine( hbuf, line++, "/// \\brief  " );
  InsBufLine( hbuf, line++, "//----------------------------------------------------------------------------//" );

  return( line );
}

macro CmtGenFile( )
{
  line = _CmtGenHeadinfo( );

  line = _CmtGenFileBrief( line );

  _CmtGenIfDefCpp( line );
}

macro CmtGenFunction( )
{
  hbuf = GetCurrentBuf( );
  i    = GetBufLnCur( hbuf );
  text = _GetCurLineTextWithoutSemicolon( );

  InsBufLine( hbuf, i++, "//----------------------------------------------------------------------------//" );
  InsBufLine( hbuf, i++, "/// \\fn     @text@" );
  InsBufLine( hbuf, i++, "///    " );
  InsBufLine( hbuf, i++, "/// \\brief  None" );
  InsBufLine( hbuf, i++, "/// \\param  [in]  " );
  InsBufLine( hbuf, i++, "/// \\param  [out] " );
  InsBufLine( hbuf, i++, "/// \\error  None" );
  InsBufLine( hbuf, i++, "/// \\return None" );
  InsBufLine( hbuf, i++, "//----------------------------------------------------------------------------//" );
}

macro CmtGenFunctionBrief( )
{
  hbuf = GetCurrentBuf( );
  i    = GetBufLnCur( hbuf );
  text = _GetCurLineTextWithoutSemicolon( );

  InsBufLine( hbuf, i++, "//----------------------------------------------------------------------------//" );
  InsBufLine( hbuf, i++, "/// \\fn     @text@" );
}

macro _CmtGenPreamble( type )
{
  hbuf = GetCurrentBuf( );
  i    = GetBufLnCur( hbuf );
  text = GetBufSelText( hbuf );

  InsBufLine( hbuf, i++, "/// \\@type@ @text@" );
  InsBufLine( hbuf, i++, "/// \\brief  " );
}

// \class     to document a class
// \struct    to document a C-struct.
// \union     to document a union.
// \enum      to document an enumeration type.
// \fn        to document a function.
// \var       to document a variable or typedef or enum value.
// \def       to document a #define.
// \typedef   to document a type definiition.
// \file      to document a file.
// \namespace to document a namespace.
// \package   to document a Java package.
// \interface to document an IDL interface.
// \brief
macro CmtGenPreamble( )
{
  line = _GetCurLineText( );

  if ( FindString( line, "#define" ) != "X" )
  {
    _CmtGenPreamble( "def   " );
  }
  else if ( FindString( line, "enum" ) != "X" )
  {
    _CmtGenPreamble( "enum  " );
  }
  else if ( FindString( line, "struct" ) != "X" )
  {
    _CmtGenPreamble( "struct" );
  }
  else if ( FindString( line, "typedef" ) != "X" )
  {
    _CmtGenPreamble( "typedef" );
  }
  else if ( FindString( line, ";" ) != "X" )
  {
    _CmtGenPreamble( "var   " );
  }
  else if ( FindString( line, "class" ) != "X" )
  {
    _CmtGenPreamble( "class " );
  }
  else if ( FindString( line, "union" ) != "X" )
  {
    _CmtGenPreamble( "union " );
  }
  else
  {
    _CmtGenPreamble( "      " );
  }
}
