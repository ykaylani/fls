#include <cuda_runtime.h>
#include "../../../include/internal/llutcs.h"

__global__ void collide(float* __restrict__ leq, float* __restrict__ distF, int tcells) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= tcells) return;

    #pragma unroll
    for(int i = 0; i < latSize; i++) {

        distF[i * tcells + idx] += (leq[i * tcells + idx] - distF[i * tcells + idx]) / rtime;
    }
}

__global__ void stream(float* distF, int tcells, float* out) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= tcells) return;

    #pragma unroll
    for (int i = 0; i < latSize; i++) {
        out[i * tcells + idx] = distF[i * tcells + (idx + lutOffsets[i])];
    }
}