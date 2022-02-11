#define GLEW_STATIC


#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

const char* verterxShaderSource =
" #version 330 core                                         \n"
" layout (location = 0) in vec3 aPos;                       \n"
" void main(){                                              \n"
"     gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}     \n";

const char* fragmentShaderSource =
" #version 330 core                                         \n"
" out vec4 FragColor;                                       \n"
" void main(){                                              \n"
"     FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}            \n";

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	printf("OpenGL Test 01\n");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Window", nullptr, nullptr);
	if (window == nullptr)
	{
		printf("OpenGL Create Window Fialed\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW Init Fialed\n");
		glfwTerminate();
		return -1;
	}

	glViewport(0 ,0 ,800, 600);

	/* 创建VAO */
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/* 创建VBO */
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* 将数据绑定到VBO上面去 */
	/* GL_STREAM_DRAW : the data is set only once and used by the GPU at most a few times*/
	/* GL_STATIC_DRAW : the data is set only once and used by the GPU at most a few times*/
	/* GL_DYNAMIC_DRAW : the data is changed a lot and used many times. */
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &verterxShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/* 将Shader组成Program */
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	/* 设置0号特征值 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		/* 处理输入等事件 */
		processInput(window);

		/* 渲染 */
		glClearColor(0.1f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}