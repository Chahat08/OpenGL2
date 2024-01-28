#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Shader.h"
#include "Positions.h"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void setCubeModelMatrices(Shader &shader) {
	for (int i = 0; i < 10; ++i) {
		glm::mat4 model(1.0f);
		model = glm::translate(model, cubePositions[i]);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0, 0.3, 0.5));
		shader.setUniformMatrix4float("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}


void setCameraViewMatrix(Shader &shader) {
	const float radius = 30.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view(glm::lookAt(
		glm::vec3(camX, 0.0f, camZ),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	));

	shader.setUniformMatrix4float("view", view);
}

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Title", NULL, NULL);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "max nr of vertex attribs supp: " << nrAttributes << std::endl;

	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	std::cout << "vendor: " << vendor << std::endl;
	std::cout << "renderer: " << renderer << std::endl;

	Shader shader("vertexShaderSource.vert", "fragmentShaderSource.frag");


	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans = glm::mat4(1.0f); // identity matrix
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//vec = trans * vec;
	//std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// transformations
	//glm::mat4 trans(1.0f);
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	//shader.use();
	//unsigned int transformLoc = glGetUniformLocation(shader.getID(), "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	//glm::mat4 model = glm::mat4(1.0f);
	////model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//glm::mat4 view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	//glm::mat4 projection = glm::mat4(1.0f);
	//projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.f, 0.1f, 100.0f);

	//glm::vec3 cameraPos(0.0f, 0.0f, 3.0f); // camera located 3.0f away from screen towards us
	//glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f); // camera looking at the origin
	//glm::vec3 cameraDirection(glm::normalize(cameraPos - cameraTarget)); //vector from the camera to the target gives its direction
	//glm::vec3 up(0.0f, 1.0f, 0.0f);
	//glm::vec3 cameraRight(glm::normalize(glm::cross(up, cameraDirection)));
	//glm::vec3 cameraUp(glm::cross(cameraDirection, cameraRight));

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glm::mat4 trans(1.0f); // identity matrix
		//trans = glm::translate(trans, glm::vec3(0.25f, 0.25f, 0.0f));
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		/*glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, -0.5f));*/

		//glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.f, 0.1f, 100.0f);

		shader.use();
		//shader.setUniformMatrix4float("model", model);
		shader.setUniformMatrix4float("projection", projection);

		glBindVertexArray(VAO);
		setCameraViewMatrix(shader);
		setCubeModelMatrices(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shader.del();

	glfwTerminate();

	return 0;
}