//generate equal tempered tables for N-notes to the octave (up to 24)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIDI_MAX 127
#define MIDI_MIN 0
#define FREQ_MIN 0.0

/*
usage iscale [-m] [-i] N startval [outfile.txt]
-m : sets format of startbal as MIDI note, opposed to frequency in Hz
-i : prints the calculated interval as well as the abs freq
-outfile : optional text filename for output
*/

int debug_error( char* s){
	printf("%s\n",s);
	return 1;
}


int main(int argc, char* argv[])
{
	int notes, i;
	int ismidi 			= 0;
	int write_interval 	= 0;
	int err 			= 0;

	double startval, basefreq, ratio;
	FILE* fp;
	double intervals[25];


	//------INPUT------------------------------------------------------------------------------
	//check argument number is correct
	if( argc < 3 )
	{
		printf("insufficient arguments\n");
		printf("Usage: iscale [-m][-i] N startval [outfile.txt]\n");
		return 1;
	}

	//check for first two argument flags, -m and -i, incrementing argument pointer along the way
	while( argc > 1 )
	{

		if( argv[1][0] == '-' )
		{
			char flag = argv[1][1];
			if( flag == 'm' )
				ismidi = 1;
			else if( flag == 'i' )
				write_interval = 1;
			else
			{
				printf("error: unrecognized option %s\n", argv[1]);
				return 1;
			}
			//next arg
			argc--;
			argv++;
		}
		else
			break;
	}

	//if no argumnents, argv[0] still points to program name, otherwise it points to last argument (-m or -i),
	//meaning argv[1] points to N!
	notes = atoi(argv[1]);
	if(notes < 1 || notes > 24)
		return debug_error("error: N out of range. Must be between 1 and 24");
	
	startval = atof(argv[2]);
	if( ismidi && (startval > MIDI_MAX || startval < MIDI_MIN) )
		return debug_error("error : MIDI not in range 0 to 127");
	else if( ismidi == 0 && startval <= FREQ_MIN )
		return debug_error("error : FREQ can't be <= 0");

	//check for optional filename
	fp = NULL;
	if( argc == 4 )
	{
		fp = fopen(argv[3],"w" );
		if( fp==NULL )
		{
			printf("WARNING: unable to create file %s\n", argv[3] );
			perror("");
		}
	}
	//------------------------------------------------------------------------------
	


	//fill array and write to file if ready

	//find basefreq if val is MIDI
	if( ismidi )
	{
		ratio = pow(2.0, 1.0/12.0);
		basefreq = 16.35 * pow(ratio,startval);	//16.35 is Hz of C0
	}
	else
		basefreq = startval;


	//calculate ratio from notes and fill the array
	ratio = pow(2.0,1.0/notes);
	for( i=0; i<=notes; i++)
	{
		intervals[i] = basefreq;
		basefreq *= ratio;
	}


	//-----OUTPUT------
	for(i=0; i<=notes; i++){

		if( write_interval )
			printf("%d:\t%f\t%f\n", i, pow(ratio,i), intervals[i] );
		else
			printf("%d:\t%f\n", i, intervals[i] );
		if(fp)
		{
			if(write_interval)
				err = fprintf(fp, "%d:\t%f\t%f\n", i, pow(ratio,i), intervals[i] );
			else
				err = fprintf(fp, "%d:\t%f\n", i, intervals[i] );
			if( err < 0 )
				break;
		}

	}

	if( err < 0 )
		perror("There was an error writing the file.\n");
	if(fp)
		fclose(fp);
	return 0;

	//------------------------------------------------------------------------------

}