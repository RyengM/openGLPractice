#include <../assets/cuda/wakeFlame.cuh>
#include <myTools/currentWakeFlameData.h>
#include <myTools/cudaUtility.h>

#include <cuda.h>
#include <curand_kernel.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <myTools/cudaUtility.h>

curandState_t* states;

__global__ void init_curand_state(unsigned int seed, curandState_t* states) {
	int col = blockDim.x * blockIdx.x + threadIdx.x;
	int row = blockDim.y * blockIdx.y + threadIdx.y;
	int size = int(ceil(sqrtf(float(PARTICLE_NUM))));

	if (row > size - 1 || col > size - 1)
		return;

	auto i = col + row * size;
	curand_init(seed, i, 0, &states[i]);
}

void initialize_flame(CurrentWakeFlameData::wakeFlameParticle* _flame,
	CurrentWakeFlameData::CurrentData& _current)
{
	int size = int(ceil(sqrtf(PARTICLE_NUM)));
	dim3 block_size(BLOCK_SIZE, BLOCK_SIZE);
	dim3 grid_size(static_cast<unsigned int>(ceil(size / float(block_size.x))),
		static_cast<unsigned int>(ceil(size / float(block_size.y))));

	checkCudaErrors(cudaMalloc(reinterpret_cast<void**>(&states), PARTICLE_NUM * sizeof(curandState_t)));
	init_curand_state<<<grid_size, block_size>>>(time(nullptr), states);

	glm::mat4 translate_to_mtx = translate(glm::mat4(1.f), -_current.position);
	glm::mat4 rotate_mtx = rotate(glm::mat4(1.f), glm::radians(-_current.angle.x), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 translate_back_mtx = translate(glm::mat4(1.f), _current.position);
	glm::mat4 transform_mtx = translate_back_mtx * rotate_mtx * translate_to_mtx;

	initialize_flame_kernel<<<grid_size, block_size>>>(_flame, _current, size, states, transform_mtx);

	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());
}

__global__ void initialize_flame_kernel(CurrentWakeFlameData::wakeFlameParticle* _flame,
	CurrentWakeFlameData::CurrentData _current,int size, curandState_t* states, glm::mat4 transform)
{
	int col = blockDim.x * blockIdx.x + threadIdx.x;
	int row = blockDim.y * blockIdx.y + threadIdx.y;

	if (row > size - 1 || col > size - 1)
		return;
	
	int i = col + row * size;
	initialize_single_particle(_flame, i, _current, states[i], transform);
}

__device__ void initialize_single_particle(CurrentWakeFlameData::wakeFlameParticle* _flame, int index,
	CurrentWakeFlameData::CurrentData _current,curandState_t state, glm::mat4 transform)
{
	glm::vec3 position(curand_uniform(&state), curand_uniform(&state), curand_uniform(&state));
	position = transform * glm::vec4(position, 1.0f);
	
	_flame[index].active = true;
	_flame[index].x = position.x;
	_flame[index].y = position.y;
	_flame[index].z = position.z;
	_flame[index].r = curand_uniform(&state);
	_flame[index].g = curand_uniform(&state);
	_flame[index].b = curand_uniform(&state);
	_flame[index].dim = 0.5;
}

void update_flame(CurrentWakeFlameData::wakeFlameParticle* _flame, CurrentWakeFlameData::CurrentData& _current,
			float* verticesArray) {
	int size = int(ceil(sqrtf(PARTICLE_NUM)));
	dim3 block_size(BLOCK_SIZE, BLOCK_SIZE);
	dim3 grid_size(static_cast<unsigned int>(ceil(size / float(block_size.x))),
		static_cast<unsigned int>(ceil(size / float(block_size.y))));

	glm::mat4 translate_to_mtx = translate(glm::mat4(1.f), -_current.position);
	glm::mat4 rotate_mtx = rotate(glm::mat4(1.f), glm::radians(-_current.angle.x), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 translate_back_mtx = translate(glm::mat4(1.f), _current.position);
	glm::mat4 transform_mtx = translate_back_mtx * rotate_mtx * translate_to_mtx;

	printf("WTF???\n");
	update_flame_kernel<<<grid_size, block_size>>>(_flame, _current, verticesArray, size, states, transform_mtx);
}

__global__ void update_flame_kernel(CurrentWakeFlameData::wakeFlameParticle* _flame,
	CurrentWakeFlameData::CurrentData _current, float* verticesArray, int size,
    curandState_t* states, glm::mat4 transform)
{
    int col = blockDim.x * blockIdx.x + threadIdx.x;
    int row = blockDim.y * blockIdx.y + threadIdx.y;

    int i = col + row * size;
	printf("(%d)", i);
    update_single_particle(_flame, i, _current, verticesArray, states[i], transform);
}

__device__ void update_single_particle(CurrentWakeFlameData::wakeFlameParticle* _flame, int index,
	CurrentWakeFlameData::CurrentData current,float* verticesArray,
	curandState_t state, glm::mat4 transform)
{
	printf("(%f,%f,%f)", _flame[index].x, _flame[index].y, _flame[index].z);
	glm::vec3 position(curand_uniform(&state), curand_uniform(&state), curand_uniform(&state));
	//position = transform * glm::vec4(position, 1.0f);
	_flame[index].active = true;
	_flame[index].x = position.x;
	_flame[index].y = position.y;
	_flame[index].z = position.z;
	_flame[index].r = curand_uniform(&state);
	_flame[index].g = curand_uniform(&state);
	_flame[index].b = curand_uniform(&state);
	_flame[index].dim = 0.5;

	update_verticesArray(_flame, verticesArray, index);
}

__device__ void update_verticesArray(CurrentWakeFlameData::wakeFlameParticle* _flame,
	float* verticesArray, int index)
{

	printf("(%f,%f,%f)", _flame[index].x, _flame[index].y, _flame[index].z);
	verticesArray[9 * index + 0] = _flame[index].x;
	verticesArray[9 * index + 1] = _flame[index].y;
	verticesArray[9 * index + 2] = _flame[index].z;

	verticesArray[9 * index + 3] = _flame[index].r / 1;
	verticesArray[9 * index + 4] = _flame[index].g / 2;
	verticesArray[9 * index + 5] = _flame[index].b / 3;

	verticesArray[9 * index + 6] = 0.f;
	verticesArray[9 * index + 7] = 0.f;

	verticesArray[9 * index + 8] = _flame[index].dim;
}
