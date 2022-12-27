// ParallelMatrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <omp.h>

using namespace std;

const int matrix_size = 2000;
const int maxThreads = 4;

void fillMatrix(int** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = rand() % 100;
        }
    }
}

int** createMatrix(int n) {
    int** matrix = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * n);
    }

    return matrix;
}

int main(int argc, char** argv) {
    auto matrix1 = createMatrix(matrix_size);
    auto matrix2 = createMatrix(matrix_size);
    auto result = createMatrix(matrix_size);
    fillMatrix(matrix1, matrix_size);
    fillMatrix(matrix2, matrix_size);

    srand(time(NULL));

    cout << "Starting programm" << endl;

    for (int t = 1; t <= maxThreads; t++)
    {
        auto threadsNum = t;
        omp_set_num_threads(threadsNum);
        int i, j, k;
        unsigned int start_time = clock();
#pragma omp parallel for private(i, j, k)
        for (i = 0; i < matrix_size; i++) {
            for (j = 0; j < matrix_size; j++) {
                result[i][j] = 0;
                for (k = 0; k < matrix_size; k++) {
                    result[i][j] += (matrix1[i][k] * matrix2[k][j]);
                }
            }
        }
        cout << t << " threads; " << (clock() - start_time) / 1000 << " seconds runtime" << endl;

    }
    return 0;
}
