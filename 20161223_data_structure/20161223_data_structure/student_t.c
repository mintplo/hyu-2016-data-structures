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
	FILE *fp;
	courseT* cs106A;
	char buffer[30];
	int i;
	int mathSum = 0;
	int scienceSum = 0;
	int litSum = 0;

	cs106A = (courseT *)malloc(sizeof(courseT));
	cs106A->numEnrolled = 0;

	if (fp = fopen(argv[1], "r")) {
		fscanf(fp, "%d", &cs106A->numEnrolled);

		for (i = 0; i < cs106A->numEnrolled; i++) {
			fscanf(fp, "%s %d %d %d",
				buffer,
				&cs106A->students[i].literature,
				&cs106A->students[i].math,
				&cs106A->students[i].sicence
			);

			cs106A->students[i].name = (char *)calloc(30, sizeof(char));
			memcpy(cs106A->students[i].name, buffer, 30);
		}

		fclose(fp);

		if (fp = fopen(argv[2], "w")) {
			fputs("Name\tLiter\tMath\tSic\tAve\n", fp);

			for (i = 0; i < cs106A->numEnrolled; i++) {
				fprintf(fp, "%s\t%03d\t%03d\t%03d\t%.2f\n",
					cs106A->students[i].name,
					cs106A->students[i].literature,
					cs106A->students[i].math,
					cs106A->students[i].sicence,
					(float)(cs106A->students[i].literature + cs106A->students[i].math + cs106A->students[i].sicence) / (float)cs106A->numEnrolled
				);
			}

			fputs("Ave\t", fp);
			for (i = 0; i < cs106A->numEnrolled; i++) {
				litSum += cs106A->students[i].literature;
				mathSum += cs106A->students[i].math;
				scienceSum += cs106A->students[i].sicence;
			}

			fprintf(fp, "%.02f\t%.02f\t%.02f\t%.02f\n",
				(float)(litSum) / cs106A->numEnrolled,
				(float)(mathSum) / cs106A->numEnrolled,
				(float)(scienceSum) / cs106A->numEnrolled,
				(float)(litSum + mathSum + scienceSum) / (float)(cs106A->numEnrolled * 3)
			);

			fclose(fp);
		}
		else {
			fprintf(stderr, "File Write Error!");
		}
	}
	else {
		fprintf(stderr, "File Read Error!");
	}

	free(cs106A);

	return;
}
