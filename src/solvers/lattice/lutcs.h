#pragma once

extern constexpr int latSize = 19;
extern __constant__ float rtime = 0.6;

extern __constant__ float lutWeights[latSize] = {1.0f/3.0f, // center
    1.0f/18.0f, 1.0f/18.0f, 1.0f/18.0f, 1.0f/18.0f, 1.0f/18.0f, 1.0f/18.0f, // neighbors
    1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f}; // diagonals

extern __constant__ float3 lutDirections[latSize] = {float3(0,0,0), // center
    float3(1,0,0), float3(-1, 0, 0), float3(0,1,0), float3(0,-1,0), float3(0,0,1), float3(0,0,-1), // neighbors
    float3(1,1,0), float3(-1,1,0), float3(1,-1,0), float3(-1,-1,0), //xy diagonal
    float3(1,0,1), float3(-1,0,1), float3(1,0,-1), float3(-1,0,-1), //xz diagonal
    float3(0,1,1), float3(0,-1,1), float3(0,1,-1), float3(0,-1,-1)}; // yz diagonal