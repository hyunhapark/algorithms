#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "sort.h"

#define MEASURE_TIME


int
main(int argc, char **argv){

	int mode=0;
	char buf[4098];
	int size = INIT_SIZE;
	int *arr = malloc(sizeof(int) * size);
	int cnt = 0;
	int i;
	struct timeval tv1, tv2;

	if (argc < 2) {
		fprintf(stderr, "Usage : %s [type]\n", argv[0]);
		fprintf(stderr, "  * type : bubble, insertion, selection, quick, merge, heap\n");
		free(arr);
		return 1;
	} else if (argc >= 3) {
		fprintf(stderr, "[Warn] too many arguments.\n");
	} else { /* argc == 2 */
		int len = strlen(argv[1]);
		for (i=0;i<len;i++)
			argv[1][i] |= 0x20; /* to lowercase. */

		if (!strcmp(argv[1], "bubble")) {
			mode = MODE_BUBBLE;
		} else if (!strcmp(argv[1], "insertion")) {
			mode = MODE_INSERTION;
		} else if (!strcmp(argv[1], "selection")) {
			mode = MODE_SELECTION;
		} else if (!strcmp(argv[1], "quick")) {
			mode = MODE_QUICK;
		} else if (!strcmp(argv[1], "merge")) {
			mode = MODE_MERGE;
		} else if (!strcmp(argv[1], "heap")) {
			mode = MODE_HEAP;
		} else {
			fprintf(stderr, "type %s is unknown.\n", argv[1]);
			return 1;
		}
	}

	while(1) {
		if ( fgets(buf, 4096, stdin)==0 )
			break;
		sscanf(buf, "%d", &arr[cnt++]);
		if (cnt >= size) {
			size <<= 1;
			if (size < 0) {
				fprintf(stderr, "Input is too big.\n");
				free(arr);
				return 2;
			}
			arr = realloc(arr, sizeof(int) * size);
		}
	}

	if ( ferror(stdin) ){
		fprintf(stderr, "[Warn] stdin error.\n");
	}

	//size, arr
	gettimeofday(&tv1, NULL);
	sort (mode, cnt, arr);
	gettimeofday(&tv2, NULL);
	int sec = tv2.tv_sec - tv1.tv_sec, usec = tv2.tv_usec - tv1.tv_usec;
	if ( usec < 0 ){
		usec += 1000000;
		sec -= 1;
	}

	for(i=0; i<cnt; i++){
		printf("%d\n", arr[i]);
	}

#ifdef MEASURE_TIME
	fprintf(stderr, "Time elapsed : %d.%06d (s)\n",sec, usec);
#endif

	free(arr);
	return 0;
}
