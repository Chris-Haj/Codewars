
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    int id;
    double x1;
    double x2;
    double a;
    double b;
} PointParams;

typedef struct {
    int id;
    double x;
    double y;
} Point;

void calculatePoint(Point *p, double t, PointParams *para) {
    p->x = ((para->x2 - para->x1) / 2.0) * sin(t * M_PI / 2.0) + (para->x2 + para->x1) / 2.0;
    p->y = para->a * p->x + para->b;
}

double calculateDistance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}


int main() {
    int N, K, TCount;
    double D;
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile == NULL) {
        printf("Error opening file!\n");
        return -1;
    }

    fscanf(inputFile, "%d %d %lf %d", &N, &K, &D, &TCount);
    PointParams params[N];
    for (int i = 0; i < N; i++) {
        fscanf(inputFile, "%d %lf %lf %lf %lf", &params[i].id, &params[i].x1, &params[i].x2, &params[i].a, &params[i].b);
    }
    fclose(inputFile);

    FILE *outputFile = fopen("Output.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file!\n");
        return -1;
    }


    int foundAny = 0;
    int pointCounter = 0;
    for (int i = 0; i <= TCount; i++) {
        double t = (2.0 * i / TCount) - 1;
        Point points[N];
        int countIDs[N];
        int count = 0;

        for (int j = 0; j < N; j++) {
            calculatePoint(&points[j], t, &params[j]);
            points[j].id = pointCounter++;
        }

        for (int j = 0; j < N; j++) {
            int closePoints = 0;
            for (int k = 0; k < N; k++) {
                if (j != k && calculateDistance(points[j], points[k]) < D) {
                    if (closePoints < K) {
                        countIDs[closePoints++] = params[k].id;
                    }
                }
            }

            if (closePoints >= K) {
                if (count == 0) {
                    fprintf(outputFile, "Points ");
                }
                fprintf(outputFile, "%d, ", params[j].id + i*N);
                count++;
                if (count == 3) {
                    fprintf(outputFile, "satisfy Proximity Criteria at t%d = %f\n",i+1, t);
                    foundAny = 1;
                    break;
                }
            }
        }
    }

    if (!foundAny) {
        fprintf(outputFile, "There were no 3 points found for any t.\n");
    }

    fclose(outputFile);
    return 0;
}
