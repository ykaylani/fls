#include <cuda_runtime.h>
#include "../lattice/lutcs.h"

__device__ void leqstates(float* __restrict__ feq, float* __restrict__ ldensity, float3* __restrict__ lvelocity, int tcells) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= tcells) return;

    for (int i = 0; i < latSize; i++) {
        int fi =  i * tcells + idx;

        float eiudot = lutDirections[i].x * lvelocity[idx].x + lutDirections[i].y * lvelocity[idx].y + lutDirections[i].z * lvelocity[idx].z;
        float udot = lvelocity[idx].x * lvelocity[idx].x + lvelocity[idx].y * lvelocity[idx].y + lvelocity[idx].z * lvelocity[idx].z;
        feq[fi] = lutWeights[i] * ldensity[idx] * (1 + 3 * eiudot + (9.0f / 2.0f) * (eiudot * eiudot) - (3.0f / 2.0f) * udot); //s is 0.3... in D3Q19
    }
}

__global__ void lstates(float* __restrict__ distF, float* __restrict__ feq, float* __restrict__ ldensity, float3* __restrict__ lvelocity, int tcells) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= tcells) return;

    for (int i = 0; i < latSize; i++) {
        ldensity[idx] += distF[i * tcells + idx];

        float3 r = float3(lutDirections[i].x * distF[i * tcells + idx], lutDirections[i].y * distF[i * tcells + idx], lutDirections[i].z * distF[ i * tcells + idx]);
        lvelocity[idx].x += r.x;
        lvelocity[idx].y += r.y;
        lvelocity[idx].z += r.z;
    }

    float invdensity = 1.0f / fmaxf(ldensity[idx], 1e-20f);
    lvelocity[idx].x *= invdensity;
    lvelocity[idx].y *= invdensity;
    lvelocity[idx].z *= invdensity;

    leqstates(feq, ldensity, lvelocity, tcells);
}