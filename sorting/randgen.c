#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv){

	long long cnt=0;
	int from=0, to=RAND_MAX;

	if(argc==1 || argc==3){
		goto usage;
	}else if(argc==4){
		int len1 = strlen(argv[2]), len2 = strlen(argv[3]);
		if (len1>10 || len2>10
				|| (len1==10 && argv[2][0]>'2')
				|| (len2==10 && argv[3][0]>'2') ) goto overflow;
		if ( !sscanf(argv[2], "%d", &from)
				|| !sscanf(argv[3], "%d", &to)
				|| from>to ) goto usage;
	}
	if (!sscanf(argv[1], "%lld", &cnt) || cnt<0) goto usage;
	if (strlen(argv[1])>=20) goto overflow;

	srand(time(NULL));

	if(from==0 && to==RAND_MAX){
		while(cnt--) printf("%d\n",rand());
	}else{
		while(cnt--) printf("%d\n", (rand()%(to-from+1)) + from);
	}

	return 0;
usage:
	fprintf(stderr, "Usage: %s <number of generation> [range from] [range to]\n", argv[0]);
	return 1;
overflow:
	fprintf(stderr, "Error: Number is too big.\n");
	return 2;
}
