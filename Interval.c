#include <stdio.h>

//translate name to number
int nameToPc(char name){
	switch(name){
		case 'C':case 'c':
			return 0;
		case 'D':case 'd':
			return 2;
		case 'E':case 'e':
			return 4;
		case 'F':case 'f':
			return 5;
		case 'G':case 'g':
			return 7;
		case 'A':case 'a':
			return 9;
		case 'B':case 'b':
			return 11;
		default:	//error code
			return 100;

	}
}

int main()
{
	
	char note1, note2, dummy;

	int interval;

	//in case user doesn't hit enter between notes and puts them in the same line of input
	printf("Enter two natural notes.\nfirst note: ");
	scanf("%c%c", &note1, &dummy);

	printf("second note: ");
	scanf("%c", &note2);

	//to calculate the interval, we call nameToPC to translate
	interval = nameToPc(note2) - nameToPc(note1);
	if( interval > 20 || interval < -11){
		printf("either %c or %c are invalid notes", note1, note2);
		return -1;
	}
	if(interval < 0) interval += 12;
	else if(interval > 11) interval -= 12;

	printf("%d semitones up or %d semitones down\n", interval, interval ? 12-interval : 0);
}
