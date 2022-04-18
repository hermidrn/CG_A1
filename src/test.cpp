#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <math.h>
#include <chrono>

float depth = 0.02f;
float height = -0.5f;
float xTank;
float yTank;
float xBall;
float yBall;
float angle;
float pi = 3.1416;
bool s, isShooting, bounce;
float initialX, initialY;

std::vector<glm::vec3> tankGun = {
glm::vec3(0.0f, 0.0f, 0.0f),
glm::vec3(0.008f, -0.008f, 0.0f),
glm::vec3(0.08f, 0.01f, 0.0f),
glm::vec3(0.06f, 0.03f, 0.0f),
};

std::vector<glm::vec3> tankBody = {
glm::vec3(0.0f, 0.0f, 0.0f),
glm::vec3(0.34f, 0.0f, 0.0f),
glm::vec3(0.34f, 0.12f, 0.0f),
glm::vec3(0.0f, 0.12f, 0.0f),
};

std::vector<glm::vec3> ground = {
glm::vec3(-1.0f, -1.0f, 0.0f),
glm::vec3(1.0f, -1.0f, 0.0f),
glm::vec3(1.0f, height, 0.0f),
glm::vec3(-1.0f, height, 0.0f),
};

void shoot(void) {
	// Cannon ball
	float rCannon = 0.015;
	glColor3f(0.32f, 0.0f, 0.44f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 360; i++) {
		angle = i * pi / 180;
		glVertex3f(rCannon * cos(angle) + xBall, rCannon * sin(angle) + yBall, 0.0f);
	}
	glEnd();
	glFlush();
	//
}

void cloud(float x, float y) {
	float rxCloud = 0.09;
	float ryCloud = 0.07;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 360; i++) {
		angle = i * pi / 180;
		glVertex3f(rxCloud * cos(angle) + x, ryCloud * sin(angle) - 0.02f + y, 0.0f);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 360; i++) {
		angle = i * pi / 180;
		glVertex3f(rxCloud * cos(angle) + 0.1f + x, ryCloud * sin(angle) + y, 0.0f);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 360; i++) {
		angle = i * pi / 180;
		glVertex3f(rxCloud * cos(angle) + 0.03f + x, ryCloud * sin(angle) + 0.07f + y, 0.0f);
	}
	glEnd();
	glFlush();
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	// Ground
	glColor3f(0.72f, 1.0f, 0.52f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < ground.size(); i++) {
		glVertex3f(ground[i][0], ground[i][1], ground[i][2]);
	}
	glEnd();
	glFlush();

	// Clouds
	cloud(0.0f, 0.2f);
	cloud(-0.7f, 0.5f);
	cloud(0.4f, 0.7f);

	// *********** START OF TANK ***********

	// Body
	glColor3f(0.96f, 0.72f, 0.8f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < ground.size(); i++) {
		glVertex3f(tankBody[i][0] + xTank, tankBody[i][1] + yTank + 0.04f, tankBody[i][2]);
	}
	glEnd();
	glFlush();

	// Gun
	glColor3f(0.91f, 0.28f, 0.49f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < ground.size(); i++) {
		glVertex3f(tankGun[i][0] + 0.2f + xTank, tankGun[i][1] + 0.15f + yTank + 0.04f, tankGun[i][2]);
	}
	glEnd();
	glFlush();

	// Hat
	float rHat = 0.07;
	glColor3f(0.96f, 0.72f, 0.8f);
	glBegin(GL_POLYGON);
	for (size_t i = 0; i < 180; i++) {
		angle = i * pi / 180;
		glVertex3f(rHat * cos(angle) + 0.15f + xTank, rHat * sin(angle) + 0.12f + yTank + 0.04f, 0.0f);
	}
	glEnd();
	glFlush();

	// Wheels
	float rSmiley = 0.02;
	float rEyes = 0.005;
	float rWheel = 0.04;
	float w[3];
	w[0] = 0.09;
	for (size_t i = 0; i < 2; i++) {
		w[i + 1] = w[i] + 2 * rWheel;
	}

	for (size_t j = 0; j < 3; j++) {
		glColor3f(0.91f, 0.28f, 0.49f);
		glBegin(GL_POLYGON);
		for (size_t i = 0; i < 360; i++) {
			angle = i * pi / 180;
			glVertex3f(rWheel * cos(angle) + w[j] + xTank, rWheel * sin(angle) + yTank + 0.04f, 0.0f);
		}
		glEnd();
		// Smiley mouth
		glColor3f(0.92f, 1.0f, 0.47f);
		glBegin(GL_POLYGON);
		for (size_t i = 180; i < 360; i++) {
			angle = i * pi / 180;
			glVertex3f(rSmiley * cos(angle) + w[j] + xTank, rSmiley * sin(angle) + yTank + 0.04f - 0.005f, 0.0f);
		}
		glEnd();
		// Smiley left eye
		glBegin(GL_POLYGON);
		for (size_t i = 0; i < 360; i++) {
			angle = i * pi / 180;
			glVertex3f(rEyes * cos(angle) + w[j] + xTank - 0.015f, rEyes * sin(angle) + yTank + 0.04f + 0.01f, 0.0f);
		}
		glEnd();
		// Smiley right eye
		glBegin(GL_POLYGON);
		for (size_t i = 0; i < 360; i++) {
			angle = i * pi / 180;
			glVertex3f(rEyes * cos(angle) + w[j] + xTank + 0.015f, rEyes * sin(angle) + yTank + 0.04f + 0.01f, 0.0f);
		}
		glEnd();
		glFlush();
	}
	// *********** END OF TANK ***********

	// Cannonball
	if (s) {
		xBall = xTank + 0.2f + 0.07f;
		yBall = yTank + 0.15f + 0.04f + 0.02f;
		initialX = xBall;
		initialY = yBall;
		s = false;
		isShooting = true;
		glutPostRedisplay();
	}
	else if (isShooting && yBall > height) {
		shoot();
		Sleep(20);
		xBall += 0.01f;
		yBall = (initialY + 0.1f) - 2.5f * pow(xBall - (initialX + 0.2f), 2);
		glutPostRedisplay();

		if (xBall >= 1.0f) {
			bounce = true;
			isShooting = false;
		}
	}
	else if (bounce) {
		initialX = xBall;
		initialY = yBall;
		bounce = false;
		glutPostRedisplay();
	}else if (yBall > height) {
		shoot();
		Sleep(20);
		xBall -= 0.01f;
		yBall = (initialY + 0.1f) - 2.5f * pow(xBall - (initialX + 0.2f), 2);
		glutPostRedisplay();
	}

}

void keyboard(unsigned char key, int x, int y)
{
	if (key == ' ')
		s = true;
	glutPostRedisplay();
}

void specialkeyboard(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_RIGHT:
			if (xTank < (1 - 0.34))
				xTank += 0.01;
			break;
		case GLUT_KEY_LEFT:
			if (xTank > -1)
				xTank -= 0.01;
			break;
	}
	glutPostRedisplay();
}

void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(650, 650);
	glutCreateWindow("Kirby tank");

	// Initial coordinate of the tank's reference model
	// and initial overall values.
	xTank = -0.51;
	yTank = 0 - 0.04f + depth + height;
	s = false;
	isShooting = false;
	bounce = false;
	yBall = -1.0f;

	glutDisplayFunc(renderScene);
	glutSpecialFunc(specialkeyboard);
	glutKeyboardFunc(keyboard);
	
	glClearColor(0.54f, 0.8f, 1.0f, 1.0f);
	glewInit();
	glutMainLoop();

}