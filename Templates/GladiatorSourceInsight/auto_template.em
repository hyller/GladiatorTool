macro GetFileName()
{
	hbuf = GetCurrentBuf()
	fname = GetBufname(hbuf)   //name style:  D:\project\GP_2011_04_11_GSCAN\GP\INFRA\GSCAN\Generic\gscan_online.c

	len = strlen(fname)	
	i = strlen(fname)
	
	while ( i > 0){
		ch = fname[i]
		if(ch == "\\"){
			i = i + 1
			break
		}
		i = i - 1
	}

	sname = ""
	while (i < len){
		sname = Cat(sname , fname[i])
		i = i + 1
	}

	return sname
}

macro IsHeaderFile()
{
	fname = GetFileName()
	len = strlen(fname)	
	i = 0
	while (i < len)
	{		
		ch = fname[i]		
		if(ch == ".")
			break
		i = i + 1
	}
	ch = fname[i + 1]

	if(ch == "h" || ch == "H")
		return 1
	else		
		return 0
}

macro InsertFileTemplate()
{
	var sz 
	
	hbuf = GetCurrentBuf()
	fname = GetFileName()

	len = strlen(fname)	
	i = 0
	
	sz = Cat(sz, "_")
	while (i < len)
	{		
		ch = fname[i]		
		if(ch == ".")
			break;
		sz = Cat(sz, toupper(ch))
		if(islower(ch) && isupper(fname[i + 1])
			sz = Cat(sz, "_")
		i = i + 1
	}
	sz = Cat(sz, "_H_")
	InsBufLine(hbuf, 0, "//---------------------------------------------------------------------------//")
	InsBufLine(hbuf, 1, "//")
	InsBufLine(hbuf, 2, "// SCHNEIDER ELECTRIC : GAIA PROJECT")
	InsBufLine(hbuf, 3, "//")
	InsBufLine(hbuf, 4, "//---------------------------------------------------------------------------//")
	InsBufLine(hbuf, 5, "/// \\file   @fname@")
	InsBufLine(hbuf, 6, "/// \\brief")
	InsBufLine(hbuf, 7, "//---------------------------------------------------------------------------//")

	if(IsHeaderFile()){	
		InsBufLine(hbuf, 8, "#ifndef @sz@")
		InsBufLine(hbuf, 9, "#define @sz@")
		InsBufLine(hbuf, 10, "")
		InsBufLine(hbuf, 11, "#ifdef __cplusplus")
		InsBufLine(hbuf, 12, "extern \"C\"")
		InsBufLine(hbuf, 13, "{")
		InsBufLine(hbuf, 14, "#endif")
		InsBufLine(hbuf, 15, "")
		InsBufLine(hbuf, 16, "")


		AppendBufLine (hbuf, "#ifdef __cplusplus")
		AppendBufLine (hbuf, "}")
		AppendBufLine (hbuf, "#endif")
		AppendBufLine (hbuf, "")
		AppendBufLine (hbuf, "#endif")
	}
}

macro InsertFunctionComment()
{	
	hbuf = GetCurrentBuf()
	i = GetBufLnCur (hbuf);	

	InsBufLine(hbuf, i++, "//-----------------------------------------------------------------------//")
	InsBufLine(hbuf, i++, "/// \\fn : ")
	InsBufLine(hbuf, i++, "///    ")
	InsBufLine(hbuf, i++, "/// \\brief      : None")
	InsBufLine(hbuf, i++, "/// \\param [in] : None")
	InsBufLine(hbuf, i++, "/// \\param [out]: None")
	InsBufLine(hbuf, i++, "/// \\raise error: None")
	InsBufLine(hbuf, i++, "/// \\return     : None")
	InsBufLine(hbuf, i++, "//-----------------------------------------------------------------------//")
}

macro InsertVariableComment()
{	
	hbuf = GetCurrentBuf()
	i = GetBufLnCur (hbuf);	

	InsBufLine(hbuf, i++, "/// \\var  : ")
	InsBufLine(hbuf, i++, "/// \\brief: ")

}

macro InsertDefineComment()
{	
	hbuf = GetCurrentBuf()
	i = GetBufLnCur (hbuf);	

	InsBufLine(hbuf, i++, "/// \\def  : ")
	InsBufLine(hbuf, i++, "/// \\brief: ")
}

