#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;
#include "camera.h"
#include "shader.h"

#define pi 3.1415926535897932384626433832795

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(1.0f, 1.0f, 10.0f));

int main() {
	srand(time(0));
	// glfw: initialize and configure
	int num_vertices, c,i,j;
	glm::vec3 colorArray[10000];
	float theta,r=0.5;
	cin >> num_vertices;
	vector<float> vec_vertices;
	

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow *window =
		glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	Shader ourShader("../src/vertex.shader", "../src/fragment.shader");

	float L = 0.5;
	float k = 0.5;
	// set up vertex data (and buffer(s)) and configure vertex attributes

	// 	float vertices[] = {
	//  Top face
	//         0.0f/k, 0.6f/k, 0.5f*L/k, 1.0, 0.0, 0.0,        // A
	//         -0.4f/k, -0.5f/k, 0.5f*L/k, 0.0, 0.0, 1.0,        // B
	//         0.4f/k, -0.5f/k, 0.5f*L/k, 0.0, 1.0, 0.0,        // C
	//         // Bottom face
	//         0.0f/k, 0.6f/k, -0.5f*L/k, 1.0, 0.0, 0.0,        // D
	//         -0.4f/k, -0.5f/k, -0.5f*L/k, 0.0, 0.0, 1.0,        // E
	//         0.4f/k, -0.5f/k, -0.5f*L/k, 0.0, 1.0, 0.0,        // F
	//         // Rectangle ACFD
	//         0.0f/k, 0.6f/k, 0.5f*L/k, 1.0, 0.0, 0.0,        // A
	//         0.4f/k, -0.5f/k, 0.5f*L/k, 0.0, 1.0, 0.0,        // C
	//         0.0f/k, 0.6f/k, -0.5f*L/k, 1.0, 0.0, 0.0,        // D
	//         0.4f/k, -0.5f/k, -0.5f*L/k, 0.0, 1.0, 0.0,        // F
	//         0.4f/k, -0.5f/k, 0.5f*L/k, 0.0, 1.0, 0.0,        // C
	//         0.0f/k, 0.6f/k, -0.5f*L/k, 1.0, 0.0, 0.0,        // D
	//         // Rectangle ABED
	//         0.0f/k, 0.6f/k, 0.5f*L/k, 1.0, 0.0, 0.0,        // A
	//         -0.4f/k, -0.5f/k, 0.5f*L/k, 0.0, 0.0, 1.0,        // B
	//         0.0f/k, 0.6f/k, -0.5f*L/k, 1.0, 0.0, 0.0,        // D
	//         0.0f/k, 0.6f/k, -0.5f*L/k, 1.0, 0.0, 0.0,        // D
	//         -0.4f/k, -0.5f/k, -0.5f*L/k, 0.0, 0.0, 1.0,        // E
	//         -0.4f/k, -0.5f/k, 0.5f*L/k, 0.0, 0.0, 1.0,        // B
	//         // Rectangle BCFE
	//         -0.4f/k, -0.5f/k, 0.5f*L/k, 0.0, 0.0, 1.0,        // B
	//         0.4f/k, -0.5f/k, 0.5f*L/k, 0.0, 1.0, 0.0,        // C
	//         -0.4f/k, -0.5f/k, -0.5f*L/k, 0.0, 0.0, 1.0,        // E
	//         0.4f/k, -0.5f/k, -0.5f*L/k, 0.0, 1.0, 0.0,        // F
	//         0.4f/k, -0.5f/k, 0.5f*L/k, 0.0, 1.0, 0.0,        // C
	//         -0.4f/k, -0.5f/k, -0.5f*L/k, 0.0, 0.0, 1.0,        // E
	// 	};

	float vertices[10000];
	c = 0;
	theta = (2 * pi) / num_vertices;

	for (i = 0; i < num_vertices-2; i++) {
		vec_vertices.push_back(r*cos(theta*0));
		vec_vertices.push_back(r*sin(theta*0));
		vec_vertices.push_back(0.5);

		vec_vertices.push_back(r*cos(theta*(i+1)));
		vec_vertices.push_back(r*sin(theta*(i+1)));
		vec_vertices.push_back(0.5);

		vec_vertices.push_back(r*cos(theta*(i+2)));
		vec_vertices.push_back(r*sin(theta*(i+2)));
		vec_vertices.push_back(0.5);
	}

	for (i = 0; i < num_vertices-2; i++) {
		vec_vertices.push_back(r*cos(theta*0));
		vec_vertices.push_back(r*sin(theta*0));
		vec_vertices.push_back(-0.5);

		vec_vertices.push_back(r*cos(theta*(i+1)));
		vec_vertices.push_back(r*sin(theta*(i+1)));
		vec_vertices.push_back(-0.5);

		vec_vertices.push_back(r*cos(theta*(i+2)));
		vec_vertices.push_back(r*sin(theta*(i+2)));
		vec_vertices.push_back(-0.5);
	}

	for (i = 0; i < num_vertices-1; i++) {
		vec_vertices.push_back(r*cos(theta*(i)));
		vec_vertices.push_back(r*sin(theta*(i)));
		vec_vertices.push_back(0.5);

		vec_vertices.push_back(r*cos(theta*(i+1)));
		vec_vertices.push_back(r*sin(theta*(i+1)));
		vec_vertices.push_back(0.5);

		vec_vertices.push_back(r*cos(theta*(i+1)));
		vec_vertices.push_back(r*sin(theta*(i+1)));
		vec_vertices.push_back(-0.5);

		vec_vertices.push_back(r*cos(theta*(i)));
		vec_vertices.push_back(r*sin(theta*(i)));
		vec_vertices.push_back(-0.5);

		vec_vertices.push_back(r*cos(theta*(i+1)));
		vec_vertices.push_back(r*sin(theta*(i+1)));
		vec_vertices.push_back(-0.5);

		vec_vertices.push_back(r*cos(theta*(i)));
		vec_vertices.push_back(r*sin(theta*(i)));
		vec_vertices.push_back(0.5);
	}

	copy(vec_vertices.begin(),vec_vertices.end(),vertices);

	unsigned int NUM_VERTICES = (num_vertices-2)*3*2 + 2*3*num_vertices;

	for(int k = 0 ; k < num_vertices +2 ; k++){
		colorArray[k] = glm::vec3((rand()%255)/255.0f, (rand()%255)/255.0f, (rand()%255)/255.0f);
	}

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s),
	// and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
						  (void *)0);
	glEnableVertexAttribArray(0);


	// note that this is allowed, the call to glVertexAttribPointer registered
	// VBO as the vertex attribute's bound vertex buffer object so afterwards we
	// can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally
	// modify this VAO, but this rarely happens. Modifying other VAOs requires a
	// call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
	// VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// enable depth testing for 3d
	glEnable(GL_DEPTH_TEST);
	int counter=0;
	// render loop
	while (!glfwWindowShouldClose(window)) {
		// print stuff for better understanding
		/*
		printf("\n");
		printf("Camera Position: %0.3f %0.3f %0.3f\n", camera.Position.x,
			   camera.Position.y, camera.Position.z);
		*/

		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// make transformations
		glm::mat4 transform = glm::mat4(1.0f);  // identity matrix
												// Rotation
		glm::vec3 OBJ_ROTATE = glm::vec3(1.0f, 1.0f, 1.0f);
		transform = glm::rotate(transform, (float)glfwGetTime(), OBJ_ROTATE);

		ourShader.use();
		ourShader.setMat4("transform", transform);

		counter = (num_vertices-2) * 3 * 3 * 2;
		int p;
		for(p = 0 ; p <num_vertices; p++){
			glm::vec3 color = colorArray[p];
			ourShader.setVec3("khush", color);

			glDrawArrays(GL_TRIANGLES, counter,6);
			counter+=18;
		}
		
		glm::vec3 color = colorArray[p++];
		ourShader.setVec3("khush", color);
		glDrawArrays(GL_TRIANGLES, 0,3*(num_vertices-2));

		color = colorArray[p++];
		ourShader.setVec3("khush", color);
		glDrawArrays(GL_TRIANGLES, 18*(num_vertices-2),3*(num_vertices-2));
		

		

		// view matrix
		glm::mat4 view = camera.GetViewMatrix(glm::vec3(0.0f));
		ourShader.setMat4("view", view);

		// projection matrix
		glm::mat4 projection = glm::perspective(
			glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
			0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		glBindVertexArray(VAO);  // seeing as we only have a single VAO there's
		// no need to bind it every time, but we'll do
		// so to keep things a bit more organized
		
		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse
		// moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width
	// and height will be significantly larger than specified on retina
	// displays.
	glViewport(0, 0, width, height);
}
