/* Using the standard output for printf */
#include <stdio.h>
#include <stdlib.h>
/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
#include <GL/freeglut.h>
/* ADD GLOBAL VARIABLES HERE LATER */

/*
Function: initResources
Receives: void
Returns: int
This function creates all GLSL related stuff
explained in this example
Returns 1, when all is ok, 0 with a displayed error
*/

int initResources(void)
{
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;
	
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char *vs_source =
#ifdef GL_ES_VERSION_2_0
	"#version 100\n" // OpenGL ES 2.0
#else
	"#version 120\n" // OpenGL 2.1
#endif
	"attribute vec2 coord2d;	"
	"void main(void) {		"
	"	gl_Position = vec4(coord2d, 0.0, 1.0);
	"}";
	glShaderSource(vs, 1, &vs_source, NULL);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fs_source =
		"#version 120		\n	"
		"void main(void) {		"
		"	gl_FragColor[0] = 0.0;	"
		"	gl_FragColor[1] = 0.0;	"
		"	gl_FragColor[2] = 2.0;	"
		"}";
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok) {
		fprintf(stderr, "Errorin fragment shader\n");
		return 0;
	}

	return 1;
}

void onDisplay()
{
	/* FILLED IN LATER */
}

void freeResources()
{
	/* FILLED IN LATER */
}

int main(int argc, char* argv[])
{
	/* GLut-related initialising functions */
	glutInit(&argc, argv);
	glutInitContextVersion(2, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("My first triangle");

	/* Extension wrangler initialising */
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	/* When all init functions run without errors
	   the program can initialise the resources */
	if (initResources())
	{
		/* We can display it if everything goes OK */
		glutDisplayFunc(onDisplay);
		glutMainLoop();
	}

	/* If the program exits in the usual way, 
	   free resources and exit with a success */
	freeResources();
	return EXIT_SUCCESS;
}


