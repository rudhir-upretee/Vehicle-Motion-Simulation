#!/usr/bin/awk -f

BEGIN{
	FS = ":"; lineCnt = 1; 
	sum = 0; sum_sqr = 0; time = 0; acclr = 0; variance = 0;
}
{

if(lineCnt <= vehCnt)
	{
	time = $1;
	acclr = $4;
	sum = sum + acclr;
	sum_sqr = sum_sqr + acclr * acclr;

	lineCnt++;
	}

if(lineCnt == vehCnt+1)
	{
	lineCnt = 1;

	variance = (sum_sqr - ((sum*sum)/vehCnt))/(vehCnt-1)
	print time, variance
	sum = 0;
	sum_sqr = 0;
	}
}
END{
}
