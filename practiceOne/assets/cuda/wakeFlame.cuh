#ifndef _WAKE_FLAME_CUH_
#define _WAKE_FLAME_CUH_

#include <glm/glm.hpp>
#include <cuda_runtime.h>
#include <curand_kernel.h>

#include <myTools/wakeFlame.h>

#define BLOCK_SIZE 16

__global__ void init_curand_state(
	unsigned int seed, curandState_t* states);

void initialize_flame(CurrentWakeFlameData::wakeFlameParticle* _flame,
	CurrentWakeFlameData::CurrentData& _current);

__global__ void initialize_flame_kernel(
	CurrentWakeFlameData::wakeFlameParticle* _flame,
	CurrentWakeFlameData::CurrentData _current,
	int size, curandState_t* states, glm::mat4 transform);

__device__ void initialize_single_particle(
	CurrentWakeFlameData::wakeFlameParticle* _flame, int index,
	CurrentWakeFlameData::CurrentData _current,
	curandState_t state, glm::mat4 transform);

void update_flame(CurrentWakeFlameData::wakeFlameParticle* _flame, 
	CurrentWakeFlameData::CurrentData& _current, float* verticesArray);

__global__ void update_flame_kernel(CurrentWakeFlameData::wakeFlameParticle* _flame,
	CurrentWakeFlameData::CurrentData _current, float* verticesArray, int size,
	curandState_t* states, glm::mat4 transform);

__device__ void update_single_particle(CurrentWakeFlameData::wakeFlameParticle* _flame, int index,
	CurrentWakeFlameData::CurrentData current, float* d_vertices_array,
	curandState_t state, glm::mat4 transform);

__device__ void update_verticesArray(CurrentWakeFlameData::wakeFlameParticle* _flame,
	float* verticesArray, int index);

#endif