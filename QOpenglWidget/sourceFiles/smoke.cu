//#include "headfiles/smoke.h"
//#include "headfiles/cudautilities.hpp"
//
//#include <cuda.h>
//#include <cuda_runtime_api.h>
//#include <device_launch_parameters.h>
//#include <cuda_gl_interop.h>
//
//static __global__ void init_curand_kernel(curandstate* state, size_t block_size)
//{
//    size_t i = threadidx.x;
//    curand_init(0, i, 0, &state[i]);
//}
//
//static __global__ void init_kernel(curandstate* curand_state, particles* particles)
//{
//    int index = threadidx.x;
//    particles[index].active = false;
//    particles[index].offset = glm::vec3(0, 0, 0);
//    particles[index].velocity = glm::vec3(&curand_state[index], &curand_state[index], &curand_state[index]);
//}
//
//static __global__ void update_kernel(particles* particles)
//{
//    int index = threadidx.x;
//    if (particles[index].active)
//        particles[index].offset += particles[index].velocity;
//}
//
//void smoke::init_cuda()
//{
//    checkcudaerrors(cudasetdevice(0));
//
//    checkcudaerrors(cudagraphicsglregisterbuffer(&position_buffer_resource_, position_buffer_, cudagraphicsmapflagswritediscard));
//    checkcudaerrors(cudamalloc((void**)&curand_state, max_particles * sizeof(curandstate)));
//
//    init_curand_kernel<<<1, max_particles>>>(curand_state, max_particles);
//
//    init_kernel<<<1, max_particles>>>(curand_state, particles);
//}
//
//void smoke::update_cuda()
//{
//    float4* position_buffer;
//
//    checkcudaerrors(cudasetdevice(0));
//
//    checkcudaerrors(cudagraphicsmapresources(1, &position_buffer_resource_, null));
//    checkcudaerrors(cudagraphicsresourcegetmappedpointer((void **)&position_buffer, nullptr, position_buffer_resource_));
//
//    update_kernel<<<1, max_particles>>>(particles);
//}
//
//void smoke::free_cuda()
//{
//    checkcudaerrors(cudasetdevice(0));
//    checkcudaerrors(cudafree(curand_state));
//    checkcudaerrors(cudagraphicsunregisterresource(position_buffer_resource_));
//}
