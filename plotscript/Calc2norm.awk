#!/usr/bin/awk -f

BEGIN{
	FS = " "; 
	sum = 0; error = 0; error_sqr = 0; two_norm = 0;
}
{

	error = $1;
        error_sqr = error * error;
	sum = sum + error_sqr;
	
}
END{
	two_norm = sqrt(sum);
	print two_norm;
}
