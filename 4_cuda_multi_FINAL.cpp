#include <stdio.h>

#define N 16

// Kernel function to perform matrix multiplication
__global__ void matrixMultiplication(int* a, int* b, int* c) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    int sum = 0;
    for (int k = 0; k < N; k++) {
        sum += a[row * N + k] * b[k * N + col];
    }

    c[row * N + col] = sum;
}



int main() {
    int size = N * N;

    // Allocate and initialize the matrices on the host
    int* h_a = new int[size];
    int* h_b = new int[size];
    int* h_c = new int[size];

    for (int i = 0; i < size; i++) {
        h_a[i] = i;
        h_b[i] = i;
    }

    // Allocate memory for the matrices on the device
    int* d_a, * d_b, * d_c;
    cudaMalloc((void**)&d_a, size * sizeof(int));
    cudaMalloc((void**)&d_b, size * sizeof(int));
    cudaMalloc((void**)&d_c, size * sizeof(int));

    // Copy the input matrices from host to device memory
    cudaMemcpy(d_a, h_a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size * sizeof(int), cudaMemcpyHostToDevice);

    // Set the grid and block dimensions
    dim3 blockDim(4, 4);
    dim3 gridDim(4, 4);

    // Launch the matrix multiplication kernel
    matrixMultiplication<<<gridDim, blockDim>>>(d_a, d_b, d_c);

    // Copy the result matrix from device to host memory
    cudaMemcpy(h_c, d_c, size * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the result matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", h_c[i * N + j]);
        }
        printf("\n");
    }

    // Free device and host memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);


    delete[] h_a;
    delete[] h_b;
    delete[] h_c;

    return 0;
}
