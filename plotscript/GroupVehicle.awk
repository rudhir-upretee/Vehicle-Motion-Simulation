#!/usr/bin/awk -f

BEGIN{FS = ":"; lineCnt = 1; 
}
{
if(NR >= lineStart)
	{
	if(lineCnt == (vehCnt+1))
		{
		lineCnt = 1;
		}
	if(lineCnt == 1)
		{
		print $0
		}
	lineCnt++;
	}
}
END{
}
