#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;
#include "camera.h"
#include "shader.h"
glm::mat4 OBJ_ROTATE = glm::mat4(1.0f);
int check = 1;
int rtime,rtime2 ;
#define pi 3.1415926535897932384626433832795

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

static glm::mat4 transform_t = glm::mat4(1.0f);  // identity matrix
glm::vec3 object_position = glm::vec3(0.0f,0.0f,0.0f);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int toggle = 0,toggle2=0;

// camera
Camera camera(glm::vec3(1.0f, 1.0f, 5.0f));

int main() {
	srand(time(0));
	rtime = time(0);
	rtime2 = time(0);
	// glfw: initialize and configure
	int num_vertices, c, i, j;
	glm::vec3 colorArray[10000];
	float theta, r = 0.5;
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

	c = 0;
	theta = (2 * pi) / num_vertices;

	for (i = 0; i < num_vertices - 2; i++) {
		vec_vertices.push_back(r * cos(theta * 0));
		vec_vertices.push_back(r * sin(theta * 0));
		vec_vertices.push_back(0.5);
		vec_vertices.push_back(1.0);
		vec_vertices.push_back(0.0);
		vec_vertices.push_back(0.0);

		vec_vertices.push_back(r * cos(theta * (i + 1)));
		vec_vertices.push_back(r * sin(theta * (i + 1)));
		vec_vertices.push_back(0.5);
		vec_vertices.push_back(0.0);
		vec_vertices.push_back(1.0);
		vec_vertices.push_back(0.0);

		vec_vertices.push_back(r * cos(theta * (i + 2)));
		vec_vertices.push_back(r * sin(theta * (i + 2)));
		vec_vertices.push_back(0.5);
		vec_vertices.push_back(0.0);
		vec_vertices.push_back(0.0);
		vec_vertices.push_back(1.0);
	}

	for (i = 0; i < num_vertices - 2; i++) {
		vec_vertices.push_back(r * cos(theta * 0));
		vec_vertices.push_back(r * sin(theta * 0));
		vec_vertices.push_back(-0.5);
		vec_vertices.push_back(1.0);
		vec_vertices.push_back(0.0);
		vec_vertices.push_back(0.0);

		vec_vertices.push_back(r * cos(theta * (i + 1)));
		vec_vertices.push_back(r * sin(theta * (i + 1)));
		vec_vertices.push_back(-0.5);
		vec_vertices.push_back(0.0);
		vec_vertices.push_back(1.0);
		vec_vertices.push_back(0.0);

		vec_vertices.push_back(r * cos(theta * (i + 2)));
		vec_vertices.push_back(r * sin(theta * (i + 2)));
		vec_vertices.push_back(-0.5);
		vec_vertices.push_back(0.0);
		vec_vertices.push_back(0.0);
		vec_vertices.push_back(1.0);
	}

	for (i = 0; i < num_vertices; i++) {
		if (num_vertices % 2 == 0) {
			if (i % 2 == 0) {
				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);

				vec_vertices.push_back(r *cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);

				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);

				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);
			}
			if (i % 2 == 1) {
				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);
			}
		}else{
			if (i % 3 == 0) {
				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r *cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);
			}
			if (i % 3 == 1) {
				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r *cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);

				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
				vec_vertices.push_back(0.0);
			}
			if (i % 3 == 2) {
				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);

				vec_vertices.push_back(r *cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);

				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);

				vec_vertices.push_back(r * cos(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(r * sin(theta * ((i + 1) % num_vertices)));
				vec_vertices.push_back(-0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);

				vec_vertices.push_back(r * cos(theta * (i)));
				vec_vertices.push_back(r * sin(theta * (i)));
				vec_vertices.push_back(0.5);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(0.0);
				vec_vertices.push_back(1.0);
			}

		}
	}

	unsigned int NUM_VERTICES =
		(num_vertices - 2) * (3) * 2 + 2 * 3 * (num_vertices);

	float vertices[1000000];

	copy(vec_vertices.begin(), vec_vertices.end(), vertices);
	int size = vec_vertices.size();

	for (int k = 0; k < num_vertices + 2; k++) {
		colorArray[k] =
			glm::vec3((rand() % 255) / 255.0f, (rand() % 255) / 255.0f,
					  (rand() % 255) / 255.0f);
	}

	// for (int l = 0; l < size; l = l + 3) {
	// 	if (l % 9 == 0)
	// 		cout << "\n";
	// 	cout.precision(4);
	// 	cout << vertices[l] << " " << vertices[l + 1] << " " << vertices[l + 2]
	// 		 << " \n";
	// }

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
						  (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
						  (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(VAO);

	// glfw.setKeycallback

	// enable depth testing for 3d
	glEnable(GL_DEPTH_TEST);
	int counter = 0;
	// render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);
		
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(toggle){
			OBJ_ROTATE = glm::rotate(OBJ_ROTATE, glm::radians(1.0f),glm::vec3(0.0f,1.0f,0.0f));
		}
		if(toggle2){
			camera.Position += glm::normalize(glm::cross(camera.Front,camera.Up))*glm::vec3(0.1,0.1,0.1);
			camera.Front = glm::normalize( object_position - camera.Position);
		}

		ourShader.use();
		ourShader.setMat4("transform", transform_t);
		ourShader.setMat4("rotate",OBJ_ROTATE);

		// view matrix
		glm::mat4 view;
		if(check == 1)
			view = camera.GetViewMatrix(object_position-camera.Position);
		else
			view = camera.GetViewMatrix(glm::vec3(0.0f));
		ourShader.setMat4("view", view);

		// projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		glBindVertexArray(VAO); 

		glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);

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

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		check = 1;
		camera.Position += glm::vec3(0, 0, -0.1);
		camera.Front = glm::normalize(object_position - camera.Position);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		check = 1;
		camera.Position += glm::vec3(0, 0, 0.1);
		camera.Front = glm::normalize(object_position - camera.Position);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		check = 1;
		camera.Position += glm::vec3(-0.1, 0, 0);
		camera.Front = glm::normalize(object_position - camera.Position);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		check = 1;
		camera.Position += glm::vec3(0.1, 0, 0);
		camera.Front = glm::normalize(object_position - camera.Position);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
		check = 1;
		camera.Position += glm::vec3(0, 0.1, 0);
		camera.Front = glm::normalize(object_position - camera.Position);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
		check = 1;
		camera.Position += glm::vec3(0, -0.1, 0);
		camera.Front = glm::normalize(object_position - camera.Position);
	}

//----------------------
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
		check =2;
		transform_t = glm::translate(transform_t, glm::vec3(0, 0.1, 0));
		object_position += glm::vec3(0, 0.1, 0);
		cout<<object_position.x<<" "<<object_position.y<<" "<<object_position.z<<"\n";
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
		check =2;
		transform_t = glm::translate(transform_t, glm::vec3(0, -0.1, 0));
		object_position += glm::vec3(0, -0.1, 0);
		cout<<object_position.x<<" "<<object_position.y<<" "<<object_position.z<<"\n";
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
		check =2;
		transform_t = glm::translate(transform_t, glm::vec3(0.1, 0, 0));
		object_position += glm::vec3(0.1, 0, 0);
		cout<<object_position.x<<" "<<object_position.y<<" "<<object_position.z<<"\n";
	}	
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS){
		check =2;
		transform_t = glm::translate(transform_t, glm::vec3(-0.1, 0, 0));
		object_position += glm::vec3(-0.1, 0, 0);
		cout<<object_position.x<<" "<<object_position.y<<" "<<object_position.z<<"\n";
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS){
		check =2;
		transform_t = glm::translate(transform_t, glm::vec3(0, 0, 0.1));
		object_position += glm::vec3(0, 0, 0.1);
		cout<<object_position.x<<" "<<object_position.y<<" "<<object_position.z<<"\n";
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
		check =2;
		transform_t = glm::translate(transform_t, glm::vec3(0, 0, -0.1));
		object_position += glm::vec3(0, 0, -0.1);
		cout<<object_position.x<<" "<<object_position.y<<" "<<object_position.z<<"\n";
	}
//----------------------
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
		check=1;
		camera.Position = glm::vec3(2, 2, 2);
		camera.Front = glm::normalize(object_position - camera.Position);
	}
		
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
		check=1;
		camera.Position = glm::vec3(2, -2, 2);
		camera.Front = glm::normalize(object_position - camera.Position);
	}

	if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
		float min = 0.3;
		time_t ctime = time(NULL);
		time_t Difference = ctime - rtime;
		if(Difference > min){
			if(toggle){
				toggle = !toggle;
			}else{
				toggle = !toggle;
			}
		}
		rtime = ctime;
	}

	if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
		float min = 0.3;
		time_t ctime = time(NULL);
		time_t Difference = ctime - rtime2;
		if(Difference > min){
			if(toggle2){
				toggle2 = !toggle2;
			}else{
				toggle2 = !toggle2;
			}
		}
		rtime2 = ctime;
	}
				
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width
	// and height will be significantly larger than specified on retina
	// displays.
	glViewport(0, 0, width, height);
}
