#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "image.h"
#include "Spritesheet.h"
#include "StaticLevel.h"

using std::cout;
using std::endl;

//std::unique_ptr<Spritesheet> sheet;
StaticLevel level;

int screenWidth = 1280;
int screenHeight = 720;

void init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//sheet = Spritesheet::fromXMLFile("res/Tiles/tiles_spritesheet.xml");
	level.loadXMLFile("staticlevels/a1.xml");
}

void display() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//sheet->getSprite("box.png")->draw(500, 500);
	//Sprite(*sheet, 0, 0, 500, 500).draw(10, 10);
	level.draw();
	
	static GLuint bg = loadImage("res/bg.png");
	glBindTexture(GL_TEXTURE_2D, bg);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glTexCoord2i(0, 0);
	glVertex2i(screenWidth, 0);
	glTexCoord2i(1, 0);
	glVertex2i(screenWidth, screenHeight);
	glTexCoord2i(1, 1);
	glVertex2i(0, screenHeight);
	glEnd();
	
	glutSwapBuffers();
	glFlush ();
	glutPostRedisplay();
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0, w, 0, h);
	screenWidth = w;
	screenHeight = h;
	
	/*
	 * Images are loaded upside down.
	 * Rather than flipping them in software once (slow),
	 * we flip them in hardware when they are used (fast).
	 */
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	float multMatrix[16] =
		{1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1};
	glMultMatrixf(multMatrix);
	
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	level.loadXMLFile("staticlevels/a1.xml");
	cout << "reloaded" << endl;
}

void keyboardUp(unsigned char key, int x, int y) {
	
}

void keyboardSpecial(int key, int x, int y) {
	
}

void keyboardSpecialUp(int key, int x, int y) {
	
}

void mouseEvent(int button, int state, int x, int y) {
	cout << button << " " << state << " " << x << " " << 1024 - y << endl;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (screenWidth, screenHeight); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	glutIgnoreKeyRepeat(true);
	
	init();
	
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(keyboardSpecial);
	glutSpecialUpFunc(keyboardSpecialUp);
	glutMouseFunc(mouseEvent);
	glutMainLoop();
	return 0;
}
