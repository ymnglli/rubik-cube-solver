#include "Display.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.000, 0.743, 0.000, // Yellow
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.000, 0.743, 0.000,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.000, 0.743, 0.000,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.000, 0.743, 0.000,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.000, 0.743, 0.000,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.000, 0.743, 0.000,

	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.000, 1.000, 1.000, // White
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.000, 1.000, 1.000,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.000, 1.000, 1.000,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.000, 1.000, 1.000,
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.000, 1.000, 1.000,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.000, 1.000, 1.000,

	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.000, 0.449, 0.000, // Orange
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.000, 0.449, 0.000,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.000, 0.449, 0.000,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.000, 0.449, 0.000,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.000, 0.449, 0.000,
	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.000, 0.449, 0.000,

	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.863, 0.078, 0.235, // Red
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.863, 0.078, 0.235,
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.863, 0.078, 0.235,
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.863, 0.078, 0.235,
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.863, 0.078, 0.235,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.863, 0.078, 0.235,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.180, 0.645, 0.241, // Green
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.180, 0.645, 0.241,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.180, 0.645, 0.241,
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.180, 0.645, 0.241,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.180, 0.645, 0.241,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.180, 0.645, 0.241,

	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.118, 0.465, 1.000, // Blue
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.118, 0.465, 1.000,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.118, 0.465, 1.000,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.118, 0.465, 1.000,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.118, 0.465, 1.000,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.118, 0.465, 1.000
};

glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,  1.0f), // Center
	glm::vec3( 0.0f,  0.0f, -1.0f),
	glm::vec3( 0.0f,  1.0f,  0.0f),
	glm::vec3( 0.0f, -1.0f,  0.0f),
	glm::vec3( 1.0f,  0.0f,  0.0f),
	glm::vec3(-1.0f,  0.0f,  0.0f),
	
	glm::vec3( 0.0f,  1.0f,  1.0f), // Edge
	glm::vec3( 0.0f,  1.0f, -1.0f),
	glm::vec3( 0.0f, -1.0f,  1.0f),
	glm::vec3( 0.0f, -1.0f, -1.0f),
	glm::vec3( 1.0f,  0.0f,  1.0f),
	glm::vec3( 1.0f,  0.0f, -1.0f),
	glm::vec3( 1.0f,  1.0f,  0.0f),
	glm::vec3( 1.0f, -1.0f,  0.0f),
	glm::vec3(-1.0f,  0.0f,  1.0f),
	glm::vec3(-1.0f,  0.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f,  0.0f),
	glm::vec3(-1.0f, -1.0f,  0.0f),
	
	glm::vec3( 1.0f,  1.0f,  1.0f), // Corner
	glm::vec3( 1.0f,  1.0f, -1.0f),
	glm::vec3( 1.0f, -1.0f,  1.0f),
	glm::vec3( 1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f,  1.0f),
	glm::vec3(-1.0f,  1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f,  1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
};

float customVertices[26][sizeof(vertices)];
glm::vec3 customPositions[26][sizeof(cubePositions)];

Display::Display() {
	setUp();
	initWindow();
	initShaders();
	initTextures();
}

Display::~Display() {
	database.destroy();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}

void Display::loop() {
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);
		
		// render
		glClearColor(0.112, 0.112, 0.112, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		shader.use();
		render();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		this_thread::sleep_for(chrono::milliseconds(1));
		glfwPollEvents();
	}
}

void Display::render() {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(25.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -13.0f));
	view = glm::rotate(view, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(-35.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	glBindVertexArray(VAO);
	
	for (uint8_t i = 0; i < 26; i++) {
		pos = cubePositions[i];
		model = prevModelState[i];
		transform = prevTransformState[i];
		if (animating)
			animate(i);
		else {
			if (solving)
				solveNext();
			if (scrambling)
				scrambleNext();
			if (rotating)
				rotateNext(i);
			if (rotatingCube)
				rotateCubeNext(i);
		}
		(i == 0)? glBindTexture(GL_TEXTURE_2D, logo) : glBindTexture(GL_TEXTURE_2D, texture);			
		glBufferData(GL_ARRAY_BUFFER, sizeof(customVertices[i]), customVertices[i], GL_STATIC_DRAW);
		model = glm::translate(model, pos);
		shader.setMat4("model", model);
		shader.setMat4("transform", transform);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void Display::rotateNext(uint8_t i) {
	pos = cubePositions[i];
	model = prevModelState[i];
	glm::mat4 curr = prevModelState[i];
	glm::vec3 axis;
	float animationAngle;
	float totalAngle;
	bool applicable;
	if (doubleMove) {
		animationAngle = easeOutQuad(glfwGetTime(), 0.0f, -180.0f, DURATION);
		totalAngle = -180.0f;
	} else {
		if (clockwise) {
			animationAngle = easeOutQuart(glfwGetTime(), 0.0f, -90.0f, DURATION);
			totalAngle = -90.0f;
		} else {
			animationAngle = easeOutQuart(glfwGetTime(), 0.0f, 90.0f, DURATION);
			totalAngle = 90.0f;
		}
	}
	if (glfwGetTime() > DURATION) {
		rotating = false;
		memcpy(prevModelState, currModelState, sizeof(currModelState));
		swapPos();
	}
	switch (currFace) {
		case f:
			axis = glm::vec3(0.0f, 0.0f, 1.0f);
			applicable = (refPos[i].z > 0.5)? true : false;
			break;
		case b:
			axis = glm::vec3(0.0f, 0.0f, 1.0f);
			animationAngle *= -1;
			totalAngle *= -1;
			applicable = (refPos[i].z < -0.5)? true : false;
			break;
		case u:
			axis = glm::vec3(0.0f, 1.0f, 0.0f);
			applicable = (refPos[i].y > 0.5)? true : false;
			break;
		case d:
			axis = glm::vec3(0.0f, 1.0f, 0.0f);
			animationAngle *= -1;
			totalAngle *= -1;
			applicable = (refPos[i].y < -0.5)? true : false;
			break;
		case r:
			axis = glm::vec3(1.0f, 0.0f, 0.0f);
			applicable = (refPos[i].x > 0.5)? true : false;
			break;
		case l:
			axis = glm::vec3(1.0f, 0.0f, 0.0f);
			animationAngle *= -1;
			totalAngle *= -1;
			applicable = (refPos[i].x < -0.5)? true : false;
			break;
	}
	if (applicable) {
		model = glm::rotate(glm::mat4(1.0f), glm::radians(animationAngle), axis) * model;
		currModelState[i] = glm::rotate(glm::mat4(1.0f), glm::radians(totalAngle), axis) * curr;
	}
}

void Display::rotateCubeNext(uint8_t i) {
	glm::mat4 curr = prevTransformState[i];
	glm::vec3 axis;
	float animationAngle;
	float totalAngle;
	bool applicable;
	
	if (clockwise) {
		animationAngle = easeOutQuart(glfwGetTime(), 0.0f, -90.0f, DURATION);
		totalAngle = -90.0f;
	} else {
		animationAngle = easeOutQuart(glfwGetTime(), 0.0f, 90.0f, DURATION);
		totalAngle = 90.0f;
	}
	if (glfwGetTime() > DURATION) {
		rotatingCube = false;
		memcpy(prevTransformState, currTransformState, sizeof(currTransformState));
	}
	switch (currDirection) {
		case rup:
			axis = glm::vec3(1.0f, 0.0f, 0.0f);
			break;
		case rdown:
			axis = glm::vec3(1.0f, 0.0f, 0.0f);
			break;
		case rright:
			axis = glm::vec3(0.0f, 1.0f, 0.0f);
			break;
		case rleft:
			axis = glm::vec3(0.0f, 1.0f, 0.0f);
			break;
	}
	transform = glm::rotate(glm::mat4(1.0f), glm::radians(animationAngle), axis) * transform;
	currTransformState[i] = glm::rotate(glm::mat4(1.0f), glm::radians(totalAngle), axis) * curr;
}

void Display::animate(uint8_t i) {
	model = glm::mat4(1.0f);
	if (glfwGetTime() <= 4) {
		model = glm::rotate(model, glm::radians(easeOutQuint(glfwGetTime(), 120.0f, -120.0f, 4.0f)), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(easeOutQuint(glfwGetTime(), 420.0f, -420.0f, 4.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(easeOutQuint(glfwGetTime(), 20.0f, -20.0f, 4.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
		
		float d = delay[i];
		if (glfwGetTime() < d)
			pos = cubePositions[i] * ZOOM;
		else if (glfwGetTime() > d && glfwGetTime() < d + 1.0f) {
			pos = glm::vec3(easeOutQuint(glfwGetTime() - d, cubePositions[i].x * ZOOM, -cubePositions[i].x * (ZOOM - 1), 1.0f),
			easeOutQuint(glfwGetTime() - d, cubePositions[i].y * ZOOM, -cubePositions[i].y * (ZOOM - 1), 1.0f),
			easeOutQuint(glfwGetTime() - d, cubePositions[i].z * ZOOM, -cubePositions[i].z * (ZOOM - 1), 1.0f));
		} else
			pos = cubePositions[i];
	} else {
		animating = false;
		pos = cubePositions[i];
	}
}

void Display::initWindow() {
	if (!glfwInit())
		std::cout << "bad" << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	window = glfwCreateWindow(WIDTH, HEIGHT, "Rubix", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize glew" << std::endl;
	}
	glEnable(GL_DEPTH_TEST);
}

void Display::initShaders() {
	shader = Shader("vertex.vert", "fragment.frag");
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void Display::initTextures() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("res/border.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);
	glGenTextures(1, &logo);
	glBindTexture(GL_TEXTURE_2D, logo);
	data = stbi_load("res/logoBorder.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);
	shader.use();
	shader.setInt("texture", 0);
}

void Display::setUp() {
	database.allocateMemory();
	database.loadDatabase();
	for (uint8_t i = 0; i < 26; i++) {
		currModelState[i] = glm::mat4(1.0f);
		prevModelState[i] = glm::mat4(1.0f);
		currTransformState[i] = glm::mat4(1.0f);
		prevTransformState[i] = glm::mat4(1.0f);
		randomizeDelay(i);
	}
	
	checkSidesQueue = queue<direction>();
	for (uint8_t i = 0; i < 8; i++)
		checkSidesQueue.push(rright);
	for (uint8_t i = 0; i < 8; i++)
		checkSidesQueue.push(rup);
	currCheckSidesQueue = checkSidesQueue;
	
	memcpy(refPos, cubePositions, sizeof(cubePositions));
	float black[] = {0.000, 0.000, 0.000};
	for (int i = 0; i < 26; i++) {
		memcpy(customVertices[i], vertices, sizeof(vertices));
		if (cubePositions[i].x == 0) {
			 for (uint8_t j = 0; j < 6; j++) {
				 memcpy(&(customVertices[i][101 + j * 8]), black, sizeof(black));
				 memcpy(&(customVertices[i][149 + j * 8]), black, sizeof(black));
			}
		} if (cubePositions[i].y == 0) {
			 for (uint8_t j = 0; j < 6; j++) {
				 memcpy(&(customVertices[i][196 + j * 8]), black, sizeof(black));
				 memcpy(&(customVertices[i][245 + j * 8]), black, sizeof(black));
			}
		} if (cubePositions[i].z == 0) {
			 for (uint8_t j = 0; j < 6; j++) {
				 memcpy(&(customVertices[i][5 + j * 8]), black, sizeof(black));
				 memcpy(&(customVertices[i][53 + j * 8]), black, sizeof(black));
			}
		} if (cubePositions[i].x == 1) {
			 for (uint8_t j = 0; j < 6; j++)
				 memcpy(&(customVertices[i][101 + j * 8]), black, sizeof(black));
		} if (cubePositions[i].y == 1) {
			 for (uint8_t j = 0; j < 6; j++)
				 memcpy(&(customVertices[i][196 + j * 8]), black, sizeof(black));
		} if (cubePositions[i].z == 1) {
			 for (uint8_t j = 0; j < 6; j++)
				 memcpy(&(customVertices[i][5 + j * 8]), black, sizeof(black));
		} if (cubePositions[i].x == -1) {
			 for (uint8_t j = 0; j < 6; j++)
				 memcpy(&(customVertices[i][149 + j * 8]), black, sizeof(black));
		} if (cubePositions[i].y == -1) {
			 for (uint8_t j = 0; j < 6; j++)
				 memcpy(&(customVertices[i][245 + j * 8]), black, sizeof(black));
		} if (cubePositions[i].z == -1) {
			 for (uint8_t j = 0; j < 6; j++)
				 memcpy(&(customVertices[i][53 + j * 8]), black, sizeof(black));
		}
	}
}

void Display::randomizeDelay(uint8_t i) {
	if (i < 6) {
		delay[i] = (20 + (rand() % static_cast<int>(50 - 20 + 1))) / 100.0f;
	} else if (i > 5 && i < 18) {
		delay[i] = (80 + (rand() % static_cast<int>(100 - 80 + 1))) / 100.0f;
	} else if (i > 17 && i < 26) {
		delay[i] = (110 + (rand() % static_cast<int>(150 - 110 + 1))) / 100.0f;
	}
}

float Display::easeOutQuint(float currTime, float start, float delta, float duration) {
	currTime /= duration;
	currTime--;
	return -delta * (currTime * currTime * currTime * currTime - 1) + start;
}

float Display::easeOutQuart(float currTime, float start, float delta, float duration) {
	currTime /= duration;
	currTime--;
	return -delta * (currTime * currTime * currTime * currTime - 1) + start;
}

float Display::easeOutQuad(float currTime, float start, float delta, float duration) {
	currTime /= duration;
	return -delta * currTime * (currTime - 2) + start;
}

void Display::rotate(face rotatingFace, bool clockwise_, bool doubleMove_) {
	rotating = true;
	glfwSetTime(0);
	clockwise = clockwise_;
	doubleMove = doubleMove_;
	currFace = rotatingFace;
}

void Display::rotateWholeCube(direction currDir) {
	if (!rotating && !animating && !rotatingCube && !scrambling) {
		rotatingCube = true;
		glfwSetTime(0);
		currDirection = currDir;
		switch (currDir) {
			case rup:
				clockwise = true;
				break;
			case rdown:
				clockwise = false;
				break;
			case rright:
				clockwise = false;
				break;
			case rleft:
				clockwise = true;
				break;
		}
	}
}

void Display::swapPos() {
	void (Display::*displayFunc)();
	switch (currFace) {
		case f:
			displayFunc = &Display::FCW;
			break;
		case b:
			displayFunc = &Display::BCW;
			break;
		case u:
			displayFunc = &Display::UCW;
			break;
		case d:
			displayFunc = &Display::DCW;
			break;
		case r:
			displayFunc = &Display::RCW;
			break;
		case l:
			displayFunc = &Display::LCW;
			break;
	}
	if (doubleMove) {
		(this->*displayFunc)();
		(this->*displayFunc)();
	} else  {
		if (clockwise) {
			(this->*displayFunc)();
		} else {
			(this->*displayFunc)();
			(this->*displayFunc)();
			(this->*displayFunc)();
		}
	}
}

void Display::swapPosCube() {
	void (Display::*displayFunc)();
	switch (currDirection) {
		case rup:
			displayFunc = &Display::X;
			break;
		case rdown:
			displayFunc = &Display::X;
			break;
		case rright:
			displayFunc = &Display::Y;
			break;
		case rleft:
			displayFunc = &Display::Y;
			break;
	}
	if (clockwise) {
		(this->*displayFunc)();
	} else {
		(this->*displayFunc)();
		(this->*displayFunc)();
		(this->*displayFunc)();
	}
}

void Display::X() {
	for (uint8_t i = 0; i < 26; i++)
		refPos[i] = glm::rotate(refPos[i], glm::radians(-90.0f), glm::vec3(1, 0, 0));
}

void Display::Y() {
	for (uint8_t i = 0; i < 26; i++)
		refPos[i] = glm::rotate(refPos[i], glm::radians(-90.0f), glm::vec3(0, 1, 0));
}

void Display::FCW() {
	cube.FCW();
	for (uint8_t i = 0; i < 26; i++) {
		if (refPos[i].z > 0.5) {
			refPos[i] = glm::rotate(refPos[i], glm::radians(-90.0f), glm::vec3(0, 0, 1));
		}
	}
}

void Display::BCW() {
	cube.BCW();
	for (uint8_t i = 0; i < 26; i++) {
		if (refPos[i].z < -0.5) {
			refPos[i] = glm::rotate(refPos[i], glm::radians(90.0f), glm::vec3(0, 0, 1));
		}
	}
}

void Display::UCW() {
	cube.UCW();
	for (uint8_t i = 0; i < 26; i++) {
		if (refPos[i].y > 0.5) {
			refPos[i] = glm::rotate(refPos[i], glm::radians(-90.0f), glm::vec3(0, 1, 0));
		}
	}
}

void Display::DCW() {
	cube.DCW();
	for (uint8_t i = 0; i < 26; i++) {
		if (refPos[i].y < -0.5) {
			refPos[i] = glm::rotate(refPos[i], glm::radians(90.0f), glm::vec3(0, 1, 0));
		}
	}
}

void Display::RCW() {
	cube.RCW();
	for (uint8_t i = 0; i < 26; i++) {
		if (refPos[i].x > 0.5) {
			refPos[i] = glm::rotate(refPos[i], glm::radians(-90.0f), glm::vec3(1, 0, 0));
		}
	}
}

void Display::LCW() {
	cube.LCW();
	for (uint8_t i = 0; i < 26; i++) {
		if (refPos[i].x < -0.5) {
			refPos[i] = glm::rotate(refPos[i], glm::radians(90.0f), glm::vec3(1, 0, 0));
		}
	}
}

void Display::solveNext() {
	if (!solutionQueue.empty()) {
		if (!rotating) {
			uint8_t nextMove = solutionQueue.front();
			solutionQueue.pop();
			rotateNextMove(nextMove);
			solved = true;
		}
	} else {
		if (glfwGetTime() > DURATION) {
			if (!currCheckSidesQueue.empty() && solved) {
				direction nextDir = currCheckSidesQueue.front();
				currCheckSidesQueue.pop();
				rotateWholeCube(nextDir);
			} else {
				solving = false;
				solved = false;
				currCheckSidesQueue = checkSidesQueue;
			}
		}
			
	}
}

void Display::scrambleNext() {
	if (!scrambleQueue.empty()) {
		if (!rotating) {
			uint8_t nextMove = scrambleQueue.front();
			scrambleQueue.pop();
			rotateNextMove(nextMove);
		}
	} else {
		if (glfwGetTime() > DURATION)
			scrambling = false;
	}
}

void Display::rotateNextMove(uint8_t nextMove) {
	face currFace_;
	bool clockwise_;
	bool doubleMove_;
	switch (nextMove / 3) {
		case 0:
			currFace_ = f;
			break;
		case 1:
			currFace_ = b;
			break;
		case 2:
			currFace_ = u;
			break;
		case 3:
			currFace_ = d;
			break;
		case 4:
			currFace_ = r;
			break;
		case 5:
			currFace_ = l;
			break;
	}
	switch (nextMove % 3) {
		case 0:
			clockwise_ = true;
			doubleMove_ = false;
			break;
		case 1:
			clockwise_ = false;
			doubleMove_ = false;
			break;
		case 2:
			clockwise_ = true;
			doubleMove_ = true;
			break;
	}
	rotate(currFace_, clockwise_, doubleMove_);
}

void Display::solve() {
	if (!solving) {
		if (!scrambling) {
			//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			float elapsedTime = 0;
			string unit = "millisecond";
			uint8_t color = 11;
			string s;
			solving = true;
			auto start = std::chrono::high_resolution_clock::now();
			string solution = solver.solve(cube, database);
			auto stop = std::chrono::high_resolution_clock::now();
			solutionQueue = solver.getSolutionQueue();
			elapsedTime = (std::chrono::duration_cast<std::chrono::milliseconds>(stop - start)).count();
			if (elapsedTime <= 0) {
				elapsedTime = (std::chrono::duration_cast<std::chrono::microseconds>(stop - start)).count();
				unit = "microsecond";
				color = 13;
			} else if (elapsedTime >= 1000) {
				elapsedTime = (std::chrono::duration_cast<std::chrono::seconds>(stop - start)).count();
				unit = "second";
				color = 10;
			}
			std::cout << "solution: " << solution << std::endl;
			s = (elapsedTime == 1)? "" : "s";
			std::cout << "elapsed time: ";
			//SetConsoleTextAttribute(hConsole, color);
			std::cout <<  elapsedTime << " " << unit << s << std::endl;
			//SetConsoleTextAttribute(hConsole, 7);
			std::cout << "number of moves: " << solutionQueue.size() << std::endl;
		}
	} else {
		solving = false;
		currCheckSidesQueue = checkSidesQueue;
	}
}

void Display::scramble() {
	if (!scrambling) {
		if (!solving) {
			scrambling = true;
			string scramble = solver.generateScramble(LENGTH);
			std::cout << "scramble: " << scramble << std::endl;
			scrambleQueue = solver.getScrambleQueue();
		}
	} else {
		scrambling = false;
	}
}

void Display::processInput(GLFWwindow *window) {
	if (!rotating && !animating && !rotatingCube && !scrambling) {
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
				rotate(f, true, false);
			else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
				rotate(f, true, true);
			else
				rotate(f, false, false);
		} if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
				rotate(b, true, false);
			else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
				rotate(b, true, true);
			else
				rotate(b, false, false);
		} if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
				rotate(u, true, false);
			else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
				rotate(u, true, true);
			else
				rotate(u, false, false);
		} if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
				rotate(d, true, false);
			else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
				rotate(d, true, true);
			else
				rotate(d, false, false);
		} if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
				rotate(r, true, false);
			else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
				rotate(r, true, true);
			else
				rotate(r, false, false);
		} if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
				rotate(l, true, false);
			else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
				rotate(l, true, true);
			else
				rotate(l, false, false);
		}
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	Display* thisDisplay = (Display*) glfwGetWindowUserPointer(window);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		thisDisplay->solve();
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		thisDisplay->scramble();
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		thisDisplay->rotateWholeCube(rup);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		thisDisplay->rotateWholeCube(rdown);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		thisDisplay->rotateWholeCube(rright);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		thisDisplay->rotateWholeCube(rleft);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
};
