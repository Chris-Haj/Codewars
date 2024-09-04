#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id;
    double x1;
    double x2;
    double a;
    double b;
} Point;

typedef struct {
    int id;
    double x;
    double y;
} Result;

// Function to calculate x and y coordinates based on t
void calculate_coordinates(Point *p, double t, double* x, double* y) {
    *x = ((p->x2 - p->x1) / 2) * sin(t * M_PI / 2) + (p->x2 + p->x1) / 2;
    *y = p->a * (*x) + p->b;
}

// Function to calculate the Euclidean distance between two points
double calculate_distance(Result p1, Result p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Main function to check the proximity criteria
void check_proximity_criteria(Point* points, int N, int K, double D, int tCount) {
    FILE* output = fopen("output_test.txt", "w");
    if (output == NULL) {
        printf("Error opening output file!\n");
        return;
    }

    for (int i = 0; i <= tCount; i++) {
        double t = 2.0 * i / tCount - 1;
        Result* results = (Result*)malloc(N * sizeof(Result));
        int* satisfied_ids = (int*)malloc(N * sizeof(int));

        // Calculate coordinates for each point at the current t
        for (int j = 0; j < N; j++) {
            results[j].id = points[j].id;
            satisfied_ids[j] = -1; // Initialize with -1
            calculate_coordinates(points+j, t, &results[j].x, &results[j].y);
        }

        int point_counter = 0;
        // Check each point to see if it satisfies the proximity criteria
        for (int j = 0; j < N; j++) {
            int k_counter = 0;

            for (int k = 0; k < N; k++) {
                if (j != k && calculate_distance(results[j], results[k]) < D) {
                    k_counter++;
                    printf("i am point %d , x= %f, y=%f has counter %d, at t=%f\n", results[j].id,results[j].x,results[j].y,k_counter, t);
                    if (k_counter == K) {
                        satisfied_ids[point_counter] = results[j].id;
                        point_counter++;
                        break;
                    }
                }
            }

        }

        // Print all points that satisfy the proximity criteria at this t
        if (point_counter >= 3) {
            fprintf(output, "Points ");
            for (int l = 0; l < point_counter; l++) {
                fprintf(output,"%d, ", satisfied_ids[l]);
            }
            fprintf(output,"satisfy Proximity Criteria at t = %lf\n",t);
        }

        free(results);
        free(satisfied_ids);
    }

    fclose(output);
}

int main() {
    FILE* input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    int N, K, tCount;
    double D;
    fscanf(input, "%d %d %lf %d", &N, &K, &D, &tCount);

    Point* points = (Point*)malloc(N * sizeof(Point));
    for (int i = 0; i < N; ++i) {
        fscanf(input, "%d %lf %lf %lf %lf", &points[i].id, &points[i].x1, &points[i].x2, &points[i].a, &points[i].b);
    }

    fclose(input);

    check_proximity_criteria(points, N, K, D, tCount);

    free(points);
    return 0;
}
