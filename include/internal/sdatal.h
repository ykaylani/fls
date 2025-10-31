#ifndef SDATA
#define SDATA

class sdatal {
    public:
        float* distf = nullptr; // turns into temp on streaming step
        float* fdist = nullptr; // is used for the final write when streaming

        float* ldensity = nullptr;
        float3* lvelocity = nullptr;
        float* leq = nullptr;

        void init(int3 lattice);
        void destroy();
};

inline void sdatal::init(int3 latticeSize)
{
    cudaMalloc(&distf, latticeSize.x * latticeSize.y * latticeSize.z * 19 * sizeof(float));
    cudaMalloc(&fdist, latticeSize.x * latticeSize.y * latticeSize.z * 19 * sizeof(float));
    cudaMalloc(&leq, latticeSize.x * latticeSize.y * latticeSize.z * 19 * sizeof(float));

    cudaMalloc(&ldensity, latticeSize.x * latticeSize.y * latticeSize.z * sizeof(float));
    cudaMalloc(&lvelocity, latticeSize.x * latticeSize.y * latticeSize.z * sizeof(float3));
}

inline void sdatal::destroy()
{
    cudaFree(distf);
    cudaFree(fdist);
    cudaFree(ldensity);
    cudaFree(lvelocity);
    cudaFree(leq);
    distf = nullptr;
    fdist = nullptr;
    ldensity = nullptr;
    lvelocity = nullptr;
    leq = nullptr;
}

#endif SDATA