#include "../../include/internal/sdatal.h"
#include "../solvers/lattice/llocals.cu"
#include "../solvers/lattice/liter.cu"
#include "../../include/internal/ldef.h"

int tcells = lattice.x * lattice.y * lattice.z;
int blocksize = 512;
int gridSize = (tcells + blocksize - 1) / blocksize;

bool mainBuffer = false;

void klbm(bool init) {

    sdatal data; data.init(lattice);

    if (mainBuffer) {
        mainBuffer = false;
        lstates<<<gridSize, blocksize>>>(data.distf, data.leq, data.ldensity, data.lvelocity, tcells, init);
        collide<<<gridSize, blocksize>>>(data.leq, data.distf, tcells);
        stream<<<gridSize, blocksize>>>(data.distf, tcells, data.fdist);
    }
    else {
        mainBuffer = true;
        lstates<<<gridSize, blocksize>>>(data.fdist, data.leq, data.ldensity, data.lvelocity, tcells, init);
        collide<<<gridSize, blocksize>>>(data.leq, data.fdist, tcells);
        stream<<<gridSize, blocksize>>>(data.fdist, tcells, data.distf);
    }

    data.destroy();
}

int main() {

    klbm(true);
    return 0;
}

