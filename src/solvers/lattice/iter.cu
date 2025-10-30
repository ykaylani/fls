#include <cuda_runtime.h>

__global__ void normalize(float* __restrict__ leq, float* __restrict__ distF, int tcells) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= tcells) return;

    for(int i = 0; i < latSize; i++) {

        distF[i * tcells + idx] += (leq[idx * latSize + i] - distF[idx * latSize + i]) / rtime;
    }
}

__global__ void stream(float* distF, int tcells) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= tcells) return;


}