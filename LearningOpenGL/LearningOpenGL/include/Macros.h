#pragma once

#include <GL_Lib.h>
#include <Shader.h>

//struct Vertex
//{
//public:
//	glm::vec3 position;
//	glm::vec4 color;
//};

struct MVP
{
	//ID of Uniform
	GLuint modelID, viewID, projectionID, normalMatrixID;
	glm::mat4 model, view, proj;
	glm::vec3 eyePos;
	glm::vec3 forwardDir;
	int keyCode = -1;

	glm::mat4 normalMatrix()
	{
		return	glm::transpose(glm::inverse(glm::mat3(view * model)));
	}

	void updateUniformLocId(FOGrP::Shader* shader)
	{
		// Get uniform locations
		modelID = shader->GetUniformLocation("model");
		viewID = shader->GetUniformLocation("view");
		projectionID = shader->GetUniformLocation("projection");

		//****************/
		normalMatrixID = shader->GetUniformLocation("normalMatrix");
	}
};

#ifndef PI
#define PI (float)3.14159265359
#endif

#ifndef STRINGIFY 
#define STRINGIFY(A) #A
#endif

//SAME AS STRINGIFY, but with a version preprocessor command
#ifndef GLSL
#define GLSL(version, A) "#version " #version "\n" #A
#endif  

#ifndef RAND
#define RAND (1.0 * rand() / (RAND_MAX))
#endif

#ifndef GENVERTEXARRAYS
#define GENVERTEXARRAYS(n,id) if(GLEW_APPLE_vertex_array_object)glGenVertexArraysAPPLE(1,id);\
	else if (GLEW_ARB_vertex_array_object) glGenVertexArrays(n,id)
#endif

#ifndef BINDVERTEXARRAY
#define BINDVERTEXARRAY(id) if(GLEW_APPLE_vertex_array_object)glBindVertexArrayAPPLE(id);\
	else if (GLEW_ARB_vertex_array_object) glBindVertexArray(id)
#endif


