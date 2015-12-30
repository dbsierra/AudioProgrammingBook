#include <stdio.h>
#include <stdlib.h>

typedef struct{
	double time;
	double value;
} BREAKPOINT;

BREAKPOINT* get_breakpoints(FILE* fp, long* psize);
BREAKPOINT maxpoint(const BREAKPOINT* points, long npoints);

int main(int argc, char* argv[])
{

	long 		size;
	double		dur;
	BREAKPOINT  point, *points;
	FILE*		fp;

	printf("breakdur: find duration of breakpoint file\n");
	if( argc < 2){
		printf("usageL breakdur inflile.txt \n");
		return 0;
	}
	fp = fopen(argv[1], "r" );
	if( fp == NULL ){
		printf("file incorrect\n");
		return 0;
	}
	size = 0;
	points = get_breakpoints( fp, &size );

	if( points == NULL ){
		printf("No breakpoints read\n");
		fclose(fp);
		return 1;
	}
	else if(size < 2){
		printf("Error: at least two breakpoints required\n");
		fclose(fp);
		return 1;
	}
	else if(points[0].time != 0.0 ){
		printf("first breakpoint must have time 0. \n");
		free(points);
		fclose(fp);
		return 1;
	}

	printf("read %ld breakpoints\n", size);
	dur = points[size-1].time;
	printf("duration: %f seconds\n", dur);
	point = maxpoint(points, size);
	printf( "max val: %f at %f secs\n", point.value, point.time);
	free(points);
	fclose(fp);
	return 0;
}


BREAKPOINT maxpoint(const BREAKPOINT* points, long npoints)
{
	int i;
	BREAKPOINT point;

	point.time = points[0].time;
	point.value = points[0].value;

	for(i=0; i<npoints; i++)
	{
		if(point.value < points[i].value)
		{
			point.value = points[i].value;
			point.time = points[i].time;
		}
	}

	return point;
}

// int scanBreakpointLine(BREAKPOINT &point, char &line, long index ){
// 	int got = sscanf(line, "%lf%lf", point.time, point.value );

// 	else if(got==0)
// 		printf("Line %ld has non-numeric data\n",index+1);
// 	else if(got==1)
// 		printf("Incomplete breakpoint found at point %ld\n",index+1);	
	
// 	return got;
// }

BREAKPOINT* get_breakpoints(FILE* fp, long* psize){

	if( fp == NULL ) return NULL;

	int got;					//return value from reading line
	long npoints = 0, size = 8; //8 breakpoint size, npoints is index
	double lasttime = 0.0;		//the last time value
	char line[80];				//lines from txt file go here!

	//allocate points
	BREAKPOINT* points  = NULL;
	points 				= (BREAKPOINT*) malloc( sizeof(BREAKPOINT) * size );
	if(points == NULL) return NULL;
	
	while( fgets(line,80,fp) )
	{
		got = sscanf(line, "%lf%lf", &points[npoints].time, &points[npoints].value );

		//ERROR CHECKING
		//------------------------------------------------------
		if(got < 0)
			continue;	//empty line
		else if(got==0){
			printf("Line %ld has non-numeric data\n",npoints+1);
			break;
		}
		else if(got == 1){
			printf("Incomplete breakpoint found at point %ld\n",npoints+1);
			break;
		}
		else if( points[npoints].time < lasttime ){
			printf("data error at point %ld: time not increasing\n", npoints+1);
			break;
		}
		//------------------------------------------------------

		lasttime = points[npoints].time;
		
		//incrememnt counter, if we pass 8 breakpoints, need moar memory!
		//------------------------------------------------------
		if( ++npoints == size )
		{
			size += npoints;
			BREAKPOINT* tmp;
			tmp = (BREAKPOINT*)realloc(points, sizeof(BREAKPOINT) *size);

			if( tmp == NULL)
			{
				//rare case that user has no more memory to draw from
				npoints = 0;
				free(points);
				points = NULL;
				break;
			}

			points = tmp;
		}
		//------------------------------------------------------
	}

	if(npoints)
		*psize = npoints;

	return points;

}