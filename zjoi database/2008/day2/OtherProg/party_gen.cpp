#include <cstdio>

void	printData(const char* fileName , int n , int m , int k)
{
	FILE*	fout = fopen(fileName , "w");
	fprintf(fout , "%d %d %d\n" , n , m , k);
	fclose(fout);
}

int	main()
{
	printData("party.0.in" , 3 , 6 , 4);
	printData("party.1.in" , 10 , 15 , 6);
	printData("party.2.in" , 16 , 19 , 7);
	printData("party.3.in" , 35 , 33 , 10);
	printData("party.4.in" , 50 , 51 , 12);
	printData("party.5.in" , 119 , 109 , 20);
	printData("party.6.in" , 103 , 109 , 7);
	printData("party.7.in" , 150 , 139 , 10);
	printData("party.8.in" , 105 , 109 , 5);
	printData("party.9.in" , 150 , 150 , 19);

	return 0;
}
