#ifndef SDATA
#define SDATA

class sdatal {
    public:
        float* distF = nullptr;
        float* ldensity = nullptr;
        float3* lvelocity = nullptr;
        float* leq = nullptr;

        void init(int3 lattice);
        void destroy();
};

inline void sdatal::init(int3 latticeSize)
{
    cudaMalloc(&distF, latticeSize.x * latticeSize.y * latticeSize.z * 19 * sizeof(float));
    cudaMalloc(&leq, latticeSize.x * latticeSize.y * latticeSize.z * 19 * sizeof(float));

    cudaMalloc(&ldensity, latticeSize.x * latticeSize.y * latticeSize.z * sizeof(float));
    cudaMalloc(&lvelocity, latticeSize.x * latticeSize.y * latticeSize.z * sizeof(float3));
}

inline void sdatal::destroy()
{
    cudaFree(distF);
    cudaFree(ldensity);
    cudaFree(lvelocity);
    cudaFree(leq);
    distF = nullptr;
    ldensity = nullptr;
    lvelocity = nullptr;
    leq = nullptr;
}

#endif SDATA