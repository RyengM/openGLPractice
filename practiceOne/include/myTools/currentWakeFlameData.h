#ifndef _CURRENT_WAKEFLAME_DATA_
#define _CURRENT_WAKEFLAME_DATA_

#include <glm/glm.hpp>
#include <cuda_gl_interop.h>

class CurrentWakeFlameData
{
public:
	
	//parameter for single particle
	struct wakeFlameParticle {
		//position
		float x = 0;
		float y = 0;
		float z = 0;
		//color
		float r = 0;
		float g = 0;
		float b = 0;
		//the rate of decay
		float dim = 0;
		//falg for activate
		bool active = false;
	};

	class RenderData
	{
	public:
		unsigned int vbo = 0;
		unsigned int vao = 0;
		unsigned int program_id = 0;

		float* verticesArray = nullptr;
		wakeFlameParticle* _flame = nullptr;
		cudaGraphicsResource* cuda_vbo_resource = nullptr;
	};

	//parameter for current wakeFlame info
	class CurrentData
	{
	public:
		glm::vec3 position;
		glm::vec3 angle;
		RenderData renderData;
	};

private:

};

#endif


