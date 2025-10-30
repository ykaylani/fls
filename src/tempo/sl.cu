#include "../../include/internal/sdatal.h"
#include "../solvers/lattice/llocals.cu"
#include "../solvers/lattice/iter.cu"

const int3 lattice = int3(128,128,128);

int tcells = lattice.x * lattice.y * lattice.z;
int blocksize = 512;
int gridSize = (tcells + blocksize - 1) / blocksize;

void klbm() {

    sdatal data; data.init(lattice);
    lstates<<<gridSize, blocksize>>>(data.distF, data.leq, data.ldensity, data.lvelocity, tcells, true);
    normalize<<<gridSize, blocksize>>>(data.leq, data.distF, tcells);
    data.destroy();
}

int main() {

    klbm();
    return 0;
}

