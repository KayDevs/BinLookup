#include <stdio.h>

int main(int argc, char** argv) {
	//binary representation of the president's affiliations, in chronological order
	//FDR-Obama, total 13
	//1 = democrat, 0 = republican
	//1101100100101 = 6949
	int parties = 6949;
	const char* names[13] = {"roosevelt", "truman", "eisenhower", "kennedy", "johnson", "nixon", "ford", "carter", "reagan", "bush", "clinton", "bush", "obama"};


	int i;
	for(i = 1; i <= 13; ++i) {
		int party = parties >> 13 - i & 1;
		//*(argv + 1) == *(1 + argv), so argv[1] == 1[argv]
		//party is 0 or 1. 
		//bitwise NOT converts 0000 to 1111, which is -1 in two's complement
		////because leading bit is 1, we know it's negative, and ~(1111 - 1) = ~(1110) = 0001
		//bitwise NOT converts 0001 to 1110, which is -2 in two's complement
		////because leading bit is 1, we know it's negative, and ~(1110 - 1) = ~(1101) = 0010
		//so by subtracting this value, we essentially convert 0 and 1 to 1 and 2. 
		//all for the sake of offsetting the command line arguments by 1.
		printf("%s is a %s\n", names[i - 1], 1[argv - ~party]);  // == puts(argv[2 + party])
	}

	//so to determine a party, we hash argv[1] as an integer and lookitup in the table.
	//since sizeof(char) == sizeof(int) / 4 , it only takes the first 4 chars of the argument.
	int lookup = *(int*)1[argv];
	//but this number doesn't mean anything on its own. it has to be converted into an index.
	//each of these names, since they are unique, has a unique hash value.
	//(except bush but bush and bush are both republicans so who tf cares)
	for(i = 0; i < 13; ++i) {
		int l = *(int*)(names[i]);
		//these are big fucking numbers so I'm just gonna divide them so that they fit within a 32 bit index
		l %= 32;
		//note: doing so makes reagan and roosevelt both 18, but, they're both republicans so it's cool
		//note: also clinton and carter are both 3, but they're also both democrats
		printf("name: %s, value: %d\n", names[i], l);
	}

	//now that they're each given a unique value in a 32 bit set, we need another binary table (like the 6949 above)
	//that has their party affiliations not in chronlogical order, but in order of the indices produced above.
	//the binary looks like this (I did this by hand):
	//[1101 1001 1111 1101 1101 1] [111 1111 1111]
	//the first box is the first 20 indexes where the presidents exist (with ones for indices without an associated president)
	//the second box is padding.
	//the above binary converted to decimal is 3657293823. That's our table.
	//confirmation:
	for(i = 1; i <= 32; ++i) {
		if(i != 1 && (i - 1) % 4 == 0) printf(" ");
		printf("%d", 3657293823 >> 32 - i & 1);
	}
	printf("\n");

	//and the president's respective affiliations can be looked up via bitshifting...
	for(i = 0; i < 13; ++i) {
		int index = *(int*)(names[i]);
		index %= 32;
		int party = 3657293823 >> (31 - index) & 1;
		printf("%s, at index %d, is %d\n", names[i], index, party); 
		printf("%s, at index %d, is a %s\n", names[i], index, argv[2+party]); 
	}

	puts(1[argv-~(int)(3657293823>>31-*(int*)1[argv]%32&1)]); //all flumped together into this garbage

}