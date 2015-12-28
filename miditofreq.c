#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double stringToMIDI( char* note ){
	char letter = note[0];
	char octave = note[1] -'0';
	char sign = 0;

	if( strlen(note) == 3)
		sign = note[2];

	if( sign == '#' )
		sign = '1'-'0';
	else if( sign == 'b' || sign == 'B' )
		sign = -1*('1'-'0');

	int base = 0;
	switch(letter)
	{
		case 'C':case 'c':
			base = 0;
			break;
		case 'D':case 'd':
			base = 2;
			break;
		case 'E':case 'e':
			base = 4;
			break;
		case 'F':case 'f':
			base = 5;
			break;
		case 'G':case 'g':
			base = 7;
			break;
		case 'A':case 'a':
			base = 9;
			break;
		case 'B':case 'b':
			base = 11;
			break;
		default:
			base = 0;
	}

	return base + octave*12 + sign;
}

//return frequency that is raised or lowered by n semitones
double semiTone( double frequency, float n ){
	return frequency * pow(2, n/12);
}

int main(int argc, char* argv[])
{
	double c0 = 16.35;	;
	int midinote;

	//printf("%f\n", stringToMIDI("D0#") );

	//error handling for command line arguments
	if( argc != 2){
		printf("%s\n", "miditofreq : converts MIDI note to frequency" );
		printf("%s\n", "usage: miditofreq MIDInote" );
		printf("%s\n", "range: 0 <= MIDInote <= 127" );
		return 1;
	}

	midinote = atoi(argv[1]);
	if(midinote < 0 || midinote > 127 ){
		printf("%s\n", "midi note is not in the range 0 - 127" );
		return 1;
	}

	//calculate value  
	printf( "frequency of MIDI note %d = %f\n", midinote, semiTone( c0, midinote));
	return 0;

}


