macro GetFileName()
{
	hbuf = GetCurrentBuf()
	//name style:  D:\project\GP_2011_04_11_GSCAN\GP\INFRA\GSCAN\Generic\gscan_online.c
	fname = GetBufname(hbuf)   

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

macro CmtGenFile()
{
	var sz 
	
	hbuf = GetCurrentBuf()
	fname = GetFileName()
	tempname = "sourcefileheadinformation"
	

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

	line = 0;
	hbuftemp = OpenBuf (tempname)
	if(hbuftemp != hNil)	
	{
		count = GetBufLineCount(hbuftemp); 
		line = 0;
		while(line < count)
		{
			linestr = GetBufLine(hbuftemp,line);
			InsBufLine(hbuf,line++,linestr); 
		}	
	}
	else
	{
		InsBufLine(hbuf, line++, "//---------------------------------------------------------------------------//")
	}
	
	InsBufLine(hbuf, line++, "/// \\file   @fname@")
	InsBufLine(hbuf, line++, "/// \\brief")
	InsBufLine(hbuf, line++, "//---------------------------------------------------------------------------//")

	if(IsHeaderFile()){	
		InsBufLine(hbuf, line++, "#ifndef @sz@")
		InsBufLine(hbuf, line++, "#define @sz@")
		InsBufLine(hbuf, line++, "")
		InsBufLine(hbuf, line++, "#ifdef __cplusplus")
		InsBufLine(hbuf, line++, "extern \"C\"")
		InsBufLine(hbuf, line++, "{")
		InsBufLine(hbuf, line++, "#endif")
		InsBufLine(hbuf, line++, "")
		InsBufLine(hbuf, line++, "")


		AppendBufLine (hbuf, "#ifdef __cplusplus")
		AppendBufLine (hbuf, "}")
		AppendBufLine (hbuf, "#endif")
		AppendBufLine (hbuf, "")
		AppendBufLine (hbuf, "#endif")
	}
}

macro CmtGenFunction()
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

macro CmtGenVariable()
{	
	hbuf = GetCurrentBuf()
	i = GetBufLnCur (hbuf);	

	InsBufLine(hbuf, i++, "/// \\var  : ")
	InsBufLine(hbuf, i++, "/// \\brief: ")

}

macro CmtGenDefinition()
{	
	hbuf = GetCurrentBuf()
	i = GetBufLnCur (hbuf);	

	InsBufLine(hbuf, i++, "/// \\def  : ")
	InsBufLine(hbuf, i++, "/// \\brief: ")
}

