#include <headFiles/Smoke.h>

#include <cuda_gl_interop.h>
#include <iostream>

// cuda_gl_interop.h has included cuda_runtime_api.h and gl.h

__global__ void test_kernel()
{

}

void crazy()
{
    test_kernel<<<1, 1>>>();   
    std::cout << "Hello World!\n" << std::endl;  
}