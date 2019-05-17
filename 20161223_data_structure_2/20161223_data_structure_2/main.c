#define _CRT_SECURE_NO_WARNINGS
#define MAX_ENROLL 5
#define NUM_HW 6
#define NUM_EXAMS 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char* name;
	int literature;
	int math;
	int sicence;
} studentT;

typedef struct {
	studentT students[MAX_ENROLL];
	int numEnrolled;
} courseT;

void main(int argc, char** argv) {
	FILE *fr;
	FILE *fw;
	courseT* cs106 = NULL;
	courseT* temp = NULL;
	char buffer[30];
	int i;
	int mathSum = 0;
	int scienceSum = 0;
	int litSum = 0;

	// free를 하기 위해서는 처음 malloc해서 얻은 주소값을 그대로 갖고 있어야한다.
	cs106 = (courseT *)malloc(2 * sizeof(courseT));

	fr = fopen(argv[1], "r");
	fw = fopen(argv[2], "w");

	if (!fr || !fw) {
		fprintf(stderr, "File IO Error!");
	}

	temp = cs106;

	while (!feof(fr)) {
		mathSum = 0;
		scienceSum = 0;
		litSum = 0;

		fgets(buffer, 30, fr);
		fputs(buffer, fw);

		fscanf(fr, "%d\n", &cs106->numEnrolled);

		for (i = 0; i < cs106->numEnrolled; i++) {
			fscanf(fr, "%s %d %d %d\n",
				buffer,
				&cs106->students[i].literature,
				&cs106->students[i].math,
				&cs106->students[i].sicence
			);

			mathSum += cs106->students[i].math;
			scienceSum += cs106->students[i].sicence;
			litSum += cs106->students[i].literature;
		}

		fprintf(fw, "%d %d %d\n", (litSum / cs106->numEnrolled), (mathSum / cs106->numEnrolled), (scienceSum / cs106->numEnrolled));
		fgets(buffer, 30, fr);

		cs106++;
	}

	fclose(fr);
	fclose(fw);

	free(temp);

	return;
}
