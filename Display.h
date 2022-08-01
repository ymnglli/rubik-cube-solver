#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <random>
#include <thread>
#include <queue>
#include <chrono>
/* remove comment to enable colored outputs (only on Windows), as well
   as all the commented code in the solve function in Display.cpp (line 666)
   #include <windows.h>*/
#include "shader.h"
#include "Solver.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 1920
#define HEIGHT 1080
#define DURATION 0.5f
#define ZOOM 8.0f
#define LENGTH 5

enum face {f, b, u, d, r, l};
enum direction {rup, rdown, rright, rleft};

class Display {
	public:
		Display();
		~Display();
		void loop();
		void	rotate(face rotatingFace, bool clockwise_, bool doubleMove_);
		void	rotateWholeCube(direction currDir);
		void	solve();
		void	scramble();
	private:
		GLFWwindow* window;
		unsigned int VBO, VAO;
		unsigned int texture, logo;
		glm::mat4 currModelState[26];
		glm::mat4 prevModelState[26];
		glm::mat4 prevTransformState[26];
		glm::mat4 currTransformState[26];
		glm::vec3 refPos[26];
		float delay[26];
		Shader shader;
		Cube cube;
		Solver solver;
		Database database;
		
		bool animating = true;
		bool rotating = false;
		bool solving = false;
		bool scrambling = false;
		bool rotatingCube = false;
		bool solved = false;
		bool clockwise;
		bool doubleMove;
		face currFace;
		direction currDirection;
		
		queue<uint8_t> solutionQueue;
		queue<uint8_t> scrambleQueue;
		queue<direction> checkSidesQueue;
		queue<direction> currCheckSidesQueue;
		
		glm::mat4 model;
		glm::vec3 pos;
		glm::mat4 transform;
		
		void swapPos();
		void swapPosCube();
		void rotateNext(uint8_t i);
		void rotateCubeNext(uint8_t i);
		void solveNext();
		void scrambleNext();
		void rotateNextMove(uint8_t nextMove);

		void X();
		void Y();
		void FCW();
		void BCW();
		void UCW();
		void DCW();
		void RCW();
		void LCW();
		
		void	render();
		void	animate(uint8_t i);
		void	initWindow();
		void	initShaders();
		void	initTextures();
		void	setUp();
		void	randomizeDelay(uint8_t i);
		float	easeOutQuint(float currTime, float start, float delta, float duration);
		float	easeOutQuart(float currTime, float start, float delta, float duration);
		float	easeOutQuad(float currTime, float start, float delta, float duration);
		void	processInput(GLFWwindow *window);
		void	onKeyPress();
};
