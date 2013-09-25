#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "image.h"
#include "Spritesheet.h"

std::unique_ptr<Spritesheet> sheet;

void init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	sheet = Spritesheet::fromTextFile("res/Player/p1_spritesheet.txt");
}

void display() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//drawSprite(*sheet->getSprite("p1_front"), 500, 500);
	drawSprite(Sprite(*sheet, 0, 0, 500, 500), 10, 10);
	
	glutSwapBuffers();
	glFlush ();
	glutPostRedisplay();
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0, w, 0, h);
	
	
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
	
}

void keyboardUp(unsigned char key, int x, int y) {
	
}

void keyboardSpecial(int key, int x, int y) {
	
}

void keyboardSpecialUp(int key, int x, int y) {
	
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1280, 1024); 
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
	glutMainLoop();
	return 0;
}
