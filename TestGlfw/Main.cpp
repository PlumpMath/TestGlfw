#include <iostream>

#include "glad/glad.h"

// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Error.h"
#include "Breakout.h"
#include "GLCommon.h"
#include "SoundEngine.h"
#include "IGame.h"
#include "CPUVerts.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
double calcFPS(GLFWwindow* window, double theTimeInterval = 1.0);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
double mouse_x, mouse_y;
std::unique_ptr<IGame> m_Game;

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		
	}
}

// The MAIN function, from here we start the application and run the game loop
int main()
{
	SoundEngine soundEngine;
	soundEngine.Init();
	/*auto sound1 = soundEngine.LoadSound("sounds/bell.wav");
	sound1->Play();

	auto sound2 = soundEngine.LoadSound("sounds/getout.ogg");
	sound2->Play();

	Sleep(1000);

	sound2->Stop();

	Sleep(500);

	sound2->Play();*/

	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);	

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glCheckError();

	// Define the viewport dimensions
	GLCall(glViewport(0, 0, WIDTH, HEIGHT));
	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_MULTISAMPLE));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_Game = std::make_unique<CPUVerts>(WIDTH, HEIGHT);
	//m_Game = std::make_unique<Breakout>(WIDTH, HEIGHT);
	GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	m_Game->Init();
	glfwSwapInterval(0);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		calcFPS(window);

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		m_Game->ProcessInput(deltaTime, mouse_x, mouse_y);

		m_Game->Update(deltaTime);
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		// Render
		// Clear the colorbuffer
		
		m_Game->Render();
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


double calcFPS(GLFWwindow* window, double theTimeInterval)
{
	// Static values which only get initialised the first time the function runs
	static double t0Value = glfwGetTime(); // Set the initial time to now
	static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
	static double fps = 0.0;           // Set the initial FPS value to 0.0

									   // Get the current time in seconds since the program started (non-static, so executed every time)
	double currentTime = glfwGetTime();

	// Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
	// Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
	if (theTimeInterval < 0.1)
	{
		theTimeInterval = 0.1;
	}
	if (theTimeInterval > 10.0)
	{
		theTimeInterval = 10.0;
	}

	// Calculate and display the FPS every specified time interval
	if ((currentTime - t0Value) > theTimeInterval)
	{
		// Calculate the FPS as the number of frames divided by the interval in seconds
		fps = (double)fpsFrameCount / (currentTime - t0Value);

		// If the user specified a window title to append the FPS value to...
		// Convert the fps value into a string using an output stringstream
		std::ostringstream stream;
		stream << fps;
		std::string fpsString = stream.str();

		// Append the FPS value to the window title details
		std::string theWindowTitle = " | FPS: " + fpsString;

		glfwSetWindowTitle(window, theWindowTitle.c_str());//;std::cout << "FPS: " << fps << std::endl;

		// Reset the FPS frame counter and set the initial time to be now
		fpsFrameCount = 0;
		t0Value = glfwGetTime();
	}
	else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
	{
		fpsFrameCount++;
	}

	// Return the current FPS - doesn't have to be used if you don't want it!
	return fps;
}