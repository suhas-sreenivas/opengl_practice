#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include"VertexBufferLayout.h"






int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "error" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	{

		float positions[] = {
			-0.5f, -0.5f,
			 0.5f,  0.5f,
			 0.5f, -0.5f,

			 -0.5f, 0.5f,
		};

		unsigned int indices[] = {
			0,1,2,
			0,1,3
		};

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb,layout);

		

		IndexBuffer ib(indices, 6);

		Shader shader("res/shaders/basic.shader");
		shader.Bind();

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			if (r > 1.0f) increment = -0.05f;
			if (r < 0.0f) increment = 0.05f;
			r = r + increment;
			/* Render here */
			renderer.Clear();
			
			shader.Bind();

			//glDrawArrays(GL_TRIANGLES, 0, 3);
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
			
			renderer.Draw(va,ib,shader);
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}


	}
	glfwTerminate();
	return 0;
}