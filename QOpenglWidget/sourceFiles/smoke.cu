//#include "headfiles/smoke.h"
//#include "headfiles/cudautilities.hpp"
//
//#include <cuda.h>
//#include <cuda_runtime_api.h>
//#include <device_launch_parameters.h>
//#include <cuda_gl_interop.h>
//
//static __global__ void init_curand_kernel(curandState* state, unsigned int block_size)
//{
//    unsigned int i = threadIdx.x;
//    curand_init(0, i, 0, &state[i]);
//}
//
//static __global__ void init_kernel(curandState* curand_state, Particles* particles)
//{
//    int index = threadIdx.x;
//    particles[index].active = false;
//    particles[index].offset = glm::vec3(0, 0, 0);
//    particles[index].velocity = glm::vec3(&curand_state[index], &curand_state[index], &curand_state[index]);
//}
//
//static __global__ void update_kernel(Particles* particles)
//{
//    int index = threadIdx.x;
//    if (particles[index].active)
//        particles[index].offset += particles[index].velocity;
//}
//
//void Smoke::init_cuda()
//{
//    checkCudaErrors(cudaSetDevice(0));
//    
//    checkCudaErrors(cudaGraphicsGLRegisterBuffer(&position_buffer_resource_, position_buffer_, cudaGraphicsMapFlagsWriteDiscard));
//    checkCudaErrors(cudaMalloc((void**)&curand_state, MAX_PARTICLES * sizeof(curandState)));
//
//    init_curand_kernel<<<1, MAX_PARTICLES>>>(curand_state, MAX_PARTICLES);
//
//    init_kernel<<<1, MAX_PARTICLES>>>(curand_state, particles);
//}
//
//void Smoke::update_cuda()
//{
//    float4* position_buffer;
//
//    checkCudaErrors(cudaSetDevice(0));
//
//    checkCudaErrors(cudaGraphicsMapResources(1, &position_buffer_resource_));
//    checkCudaErrors(cudaGraphicsResourceGetMappedPointer((void **)&position_buffer, nullptr, position_buffer_resource_));
//
//    update_kernel<<<1, MAX_PARTICLES>>>(particles);
//}
//
//void Smoke::free_cuda()
//{
//    checkCudaErrors(cudaSetDevice(0));
//    checkCudaErrors(cudaFree(curand_state));
//    checkCudaErrors(cudaGraphicsUnregisterResource(position_buffer_resource_));
//}
