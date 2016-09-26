# cse2022-160926.
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 800;
const int height = 580;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

/*void glfwGetCursorPos(GLFWwindow *  window,double *  xpos,	double *  ypos)
{//circle
	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{
			const int  xpos = 100, ypos = 450;
			const int r = 50;

			if (sqrt((xpos - a)*(xpos - a) + (ypos - b)*(ypos - b)) < r)
				drawPixel(a, b, 0.0f, 1.0f, 0.0f);
			if (sqrt((xpos - a)*(xpos - a) + (ypos - b)*(ypos - b)) < 48)
				drawPixel(a, b, 1.0f, 1.0f, 1.0f);
		}

	}


}
*/

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i1 == i0)
	{
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing



	//TODO: try moving object
}

void drawCircle(double c1, double c2, int r1,int r2)
{
	
	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{

			if (sqrt((c1 - a)*(c1 - a) + (c2 - b)*(c2 - b)) < r1)
				drawPixel(a, b, 1.0f, 0.0f, 0.0f);
			if (sqrt((c1 - a)*(c1 - a) + (c2 - b)*(c2 - b)) < r2)
				drawPixel(a, b, 1.0f, 1.0f, 1.0f);
		}

	}
}
void drawChangeCircle(double c1,double c2)
{
	int r = 50;
	for (int a = 0; a < width; a++)
	{
		for (int b = 0; b < height; b++)
		{

			if (sqrt((c1- a)*(c1 - a) + (c2 - b)*(c2 - b)) < r)
				drawPixel(a, b, 0.0f, 0.0f, 1.0f);
			if (sqrt((c1 - a)*(c1 - a) + (c2 - b)*(c2 - b)) < 48)
				drawPixel(a, b, 1.0f, 1.0f, 1.0f);
		}

	}
}
int main(void)
{
	double xpos, ypos;
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();
	
		//circle 1
		drawCircle(100, 450,50,48);
		glfwGetCursorPos(  window, &xpos, &ypos);
		double f1 = (xpos - 100)*(xpos - 100) + (ypos - 105)*(ypos - 105) - 50*50;
		if (f1 <= 0.0)
        drawChangeCircle(100, 450);
		//if (xpos >= 50 && xpos <= 150 && ypos >= 60 && ypos <= 150)
			
        for (int i = 0; i < 5; i++) 
		{
			drawLine(70, 428 + i, 130, 468 + i, 1.0f, 0.0f, 0.0f);
		}

		//circle 2
		drawCircle(250, 450,50,48);
		double f2 = (xpos - 250)*(xpos - 250) + (ypos - 105)*(ypos - 105) - 50 * 50;
		if (f2 <= 0.0)
		//if (xpos >= 200 && xpos <= 300 && ypos >= 60 && ypos <= 150)
			drawChangeCircle(250, 450);
		drawCircle(250, 450, 25, 20);

		//circle 3
		drawCircle(400, 450,50,48);
		double f3 = (xpos - 400)*(xpos - 400) + (ypos - 105)*(ypos - 105) - 50 * 50;
		if (f3 <= 0.0)
		if (xpos >= 350 && xpos <= 450 && ypos >= 60 && ypos <= 150)
			drawChangeCircle(400, 450);
		drawLine(380, 425, 420, 425, 1.0f, 0.0f, 0.0f);
		drawLine(380, 475, 420, 475, 1.0f, 0.0f, 0.0f);
		drawLine(380, 425, 380, 475, 1.0f, 0.0f, 0.0f);
		drawLine(420, 425, 420, 475, 1.0f, 0.0f, 0.0f);

		//circle 4
		drawCircle(550, 450,50,48);
		double f4 = (xpos - 550)*(xpos - 550) + (ypos - 105)*(ypos - 105) - 50 * 50;
		if (f4 <= 0.0)
			drawChangeCircle(550, 450);
		drawLine(530, 425, 570, 475, 1.0f, 0.0f, 0.0f);
		drawLine(530, 475, 570, 425, 1.0f, 0.0f, 0.0f);
		for (int i = 0; i < 2; i++) {

			drawLine(530, 425 +i, 570, 475 + i, 1.0f, 0.0f, 0.0f);
			drawLine(530, 475 + i, 570, 425 + i, 1.0f, 0.0f, 0.0f);
		}

		//circle 5
		drawCircle(700, 450,50,48);
		double f5 = (xpos - 700)*(xpos - 700) + (ypos - 105)*(ypos - 105) - 50 * 50;
		if (f5 <= 0.0)
			drawChangeCircle(700, 450);
		drawLine(700, 430, 700, 475, 1.0f, 0.0f, 0.0f);
		drawLine(680, 445, 700, 430, 1.0f, 0.0f, 0.0f);
		drawLine(700, 430, 720, 445, 1.0f, 0.0f, 0.0f);

		//circle 6
		drawCircle(100, 250, 50, 48);
		double f6 = (xpos - 100)*(xpos - 100) + (ypos - 300)*(ypos - 300) - 50 * 50;
		if (f6 <= 0.0)
			drawChangeCircle(100, 250);
		drawLine(70, 250, 120, 250, 1.0f, 0.0f, 0.0f);
		drawLine(100, 270, 120, 250, 1.0f, 0.0f, 0.0f);
		drawLine(100, 230,120, 250, 1.0f, 0.0f, 0.0f);

		//circle 7
		drawCircle(250, 250, 50, 48);
		double f7 = (xpos - 250)*(xpos - 250) + (ypos - 300)*(ypos - 300) - 50 * 50;
		if (f7 <= 0.0)
			drawChangeCircle(250, 250);drawLine(235, 255, 265, 255, 1.0f, 0.0f, 0.0f);
		for (int i = 0; i < 2; i++) {
			
			drawLine(220, 225+i, 250, 280 + i, 1.0f, 0.0f, 0.0f);
			drawLine(250, 280 + i, 280, 225 + i, 1.0f, 0.0f, 0.0f);
		}



		//circle 8
		drawCircle(400, 250, 50, 48);
		double f8 = (xpos - 400)*(xpos - 400) + (ypos - 300)*(ypos - 300) - 50 * 50;
		if (f8 <= 0.0)
			drawChangeCircle(400, 250);
		drawLine(400, 220, 400, 280, 1.0f, 0.0f, 0.0f);

		//circle 9
		drawCircle(550, 250, 50, 48);
		double f9 = (xpos - 550)*(xpos - 550) + (ypos - 300)*(ypos - 300) - 50 * 50;
		if (f9 <= 0.0)
			drawChangeCircle(550, 250);
		drawLine(530, 250, 580, 250, 1.0f, 0.0f, 0.0f);
     	for (int i = 0; i < 2; i++) {
			
			drawLine(530, 250 + i, 540, 270 + i, 1.0f, 0.0f, 0.0f);
			drawLine(530, 250 + i, 540, 230 + i, 1.0f, 0.0f, 0.0f);
		}
		//circle 10
		drawCircle(700, 250, 50, 48);
		double f10 = (xpos - 700)*(xpos - 700) + (ypos - 300)*(ypos - 300) - 50 * 50;
		if (f10 <= 0.0)
			drawChangeCircle(700, 250);
		drawLine(700, 220, 700, 270, 1.0f, 0.0f, 0.0f);
		for (int i = 0; i < 2; i++) {
			drawLine(680, 250+i, 700, 270 + i, 1.0f, 0.0f, 0.0f);
			drawLine(700, 270 + i, 720, 250 + i, 1.0f, 0.0f, 0.0f);
		}

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}


