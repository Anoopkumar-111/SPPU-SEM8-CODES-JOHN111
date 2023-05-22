#include <stdio.h>
%%cu
#include <iostream>



// Kernel function to perform vector addition
__global__ void vectorAddition(float* a, float* b, float* c, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < size) {
        c[tid] = a[tid] + b[tid];
    }
}


int main() {
    int size = 1000000;

    // Allocate and initialize the vectors on the host
    float* h_a = new float[size];
    float* h_b = new float[size];
    float* h_c = new float[size];
    
    for (int i = 0; i < size; i++) {
        h_a[i] = i;
        h_b[i] = i;
    }

    // Allocate memory for the vectors on the device
    float* d_a, * d_b, * d_c;
    cudaMalloc((void**)&d_a, size * sizeof(float));
    cudaMalloc((void**)&d_b, size * sizeof(float));
    cudaMalloc((void**)&d_c, size * sizeof(float));

    // Copy the input vectors from host to device memory
    cudaMemcpy(d_a, h_a, size * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size * sizeof(float), cudaMemcpyHostToDevice);

    // Launch the vector addition kernel
    int threadsPerBlock = 256;
    int blocksPerGrid = (size + threadsPerBlock - 1) / threadsPerBlock;
    
    vectorAddition<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, size);

    // Copy the result vector from device to host memory
    cudaMemcpy(h_c, d_c, size * sizeof(float), cudaMemcpyDeviceToHost);

    // Print the first few elements of the result vector
    for (int i = 0; i < 10; i++) {
        printf("%.2f ", h_c[i]);
    }
    printf("\n");

    // Free device and host memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);


    delete[] h_a;
    delete[] h_b;
    delete[] h_c;

    return 0;
}
