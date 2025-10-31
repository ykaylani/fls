#pragma once
#include "../../include/internal/ldef.h"

extern __constant__ float lutWeights[latSize] = {1.0f/3.0f, // center
    1.0f/18.0f, 1.0f/18.0f, 1.0f/18.0f, 1.0f/18.0f, 1.0f/18.0f, 1.0f/18.0f, // neighbors
    1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f}; // diagonals

extern __constant__ float3 lutDirections[latSize] = {float3(0,0,0), // center
    float3(1,0,0), float3(-1, 0, 0), float3(0,1,0), float3(0,-1,0), float3(0,0,1), float3(0,0,-1), // neighbors
    float3(1,1,0), float3(-1,1,0), float3(1,-1,0), float3(-1,-1,0), //xy diagonal
    float3(1,0,1), float3(-1,0,1), float3(1,0,-1), float3(-1,0,-1), //xz diagonal
    float3(0,1,1), float3(0,-1,1), float3(0,1,-1), float3(0,-1,-1)}; // yz diagonal

__constant__ int lutOffsets[19] = {0, 1, -1, lattice.x, -lattice.x, lattice.x*lattice.y, -lattice.x*lattice.y,1+lattice.x, -1+lattice.x, 1-lattice.x, -1-lattice.x,1+lattice.x*lattice.y, -1+lattice.x*lattice.y, 1-lattice.x*lattice.y, -1-lattice.x*lattice.y,lattice.x+lattice.x*lattice.y, -lattice.x+lattice.x*lattice.y, lattice.x-lattice.x*lattice.y, -lattice.x-lattice.x*lattice.y};