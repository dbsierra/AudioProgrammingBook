#include <stdio.h>

int main()
{
	int note, i;

	printf("Please enter the key (in pich-class number, 0-11): ");

	scanf("%d", &note);

	//make sure note is not negative
	if( note < -1000) note = 0;
	while(note < 0) note += 12;

	//build the scale
	for( i=0; i<7; i++)
	{
		//transalte pitch-class to note name
		if(note%12==0) printf("C ");
		else if(note%12 ==1) printf("C# ");
		else if(note%12 ==2) printf("D ");
		else if(note%12 ==3) printf("D# ");
		else if(note%12 ==4) printf("E ");
		else if(note%12 ==5) printf("F ");
		else if(note%12 ==6) printf("F# ");
		else if(note%12 ==7) printf("G ");
		else if(note%12 ==8) printf("G# ");
		else if(note%12 ==9) printf("A ");
		else if(note%12 ==10) printf("A# ");
		else printf("B ");
		
		//next pitch, jump 2 semitones unless we are on the 3rd step
		if( i != 2) note += 2;
		else note++;
	}

	printf("\n");
	return 0;

}