#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){

	int cnt=0;
	sscanf(argv[1], "%d", &cnt);
	srand(time(NULL));

	while(cnt--){
		printf("%d\n",rand());
	}

	return 0;
}
