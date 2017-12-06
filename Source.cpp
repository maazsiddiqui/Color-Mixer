// Maaz Siddiqui
// Project 2: Color Mixer

#include <gl/glut.h>
#include<string>
using namespace std;

void drawBitmapText(char *string, float x, float y, float z) {
	char *c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void colorNumDisplay(float colr, int pos) {
	int current = colr * 255;
	string current_value = to_string(current);
	for (int i = 0; i < current_value.length(); i++) {
		glRasterPos2i(pos, 560);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, current_value.at(i));
		pos += 12;
	}
}

class Slider {
	public:
		int x, y;
		bool selected = false;
		char sliderColor;
		
		Slider(int X, int Y, char color) {
			x = X;
			y = Y;
			sliderColor = color;
		}
		
		void create() {
			if (selected) {
				glColor3f(0.5, 0.5, 0.5);
			}
			else if (sliderColor == 'r') {
				glColor3f(1.0, 0.0, 0.0);
			}
			else if (sliderColor == 'g') {
				glColor3f(0.0, 1.0, 0.0);
			}
			else if (sliderColor == 'b') {
				glColor3f(0.0, 0.0, 1.0);
			}
			glBegin(GL_QUADS);
			glVertex2i(x, y);
			glVertex2i(x + 35, y);
			glVertex2i(x + 35, y + 20);
			glVertex2i(x, y + 20);
			glEnd();
		}

};

Slider redSlider(85, 262, 'r');
Slider greenSlider(185, 262, 'g');
Slider blueSlider(285, 262, 'b');
int width = 800.f, height = 800.f;
float redColor = 0.0f, greenColor = 0.0f, blueColor = 0.0f;
float inter_l1 = 0.0f, inter_l2 = 0.0f, inter_l3 = 0.0f;
float inter_r1 = 0.0f, inter_r2 = 0.0f, inter_r3 = 0.0f;
float color_array[3];


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLineWidth(3.0f);
	
	// draw color lines
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(102, 272);
	glVertex2i(102, 528);

	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(202, 272);
	glVertex2i(202, 528);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(302, 272);
	glVertex2i(302, 528);
	glEnd();
	
	glBegin(GL_QUADS);
	
	// color box
	glColor3f(redColor, greenColor, blueColor);
	glVertex2i(400, 600);
	glVertex2i(650, 600);
	glVertex2i(650, 370);
	glVertex2i(400, 370);

	// gradient box
	glColor3f(inter_l1, inter_l2, inter_l3);
	glVertex2i(400, 300);
	glVertex2i(400, 225);
	glColor3f(inter_r1, inter_r2, inter_r3);
	glVertex2i(700, 225);
	glVertex2i(700, 300);
	glEnd();
	
	// create RGB sliders
	redSlider.create();
	greenSlider.create();
	blueSlider.create();

	// set text
	glColor3f(1.0, 1.0, 1.0);
	drawBitmapText("Current Color", 400, 615, 0);
	drawBitmapText("Gradient", 400, 315, 0);

	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2i(92, 230);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');

	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2i(192, 230); 
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');

	glColor3f(0.0, 0.0, 1.0);
	glRasterPos2i(292, 230);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'B');

	glColor3f(1.0, 0.0, 0.0); 
	colorNumDisplay(redColor, 89);

	glColor3f(0.0, 1.0, 0.0);
	colorNumDisplay(greenColor, 189);
	
	glColor3f(0.0, 0.0, 1.0);
	colorNumDisplay(blueColor, 289);
	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {
	
	switch (key) {
		
	case 'r':	// r key is pressed on keyboard
		inter_r1 = redColor;
		inter_r2 = greenColor;
		inter_r3 = blueColor;
		break;
		
	case 'l':	// l is pressed on keyboard
		inter_l1 = redColor;
		inter_l2 = greenColor;
		inter_l3 = blueColor;
		break;
	}

	glutPostRedisplay();

}

void sliderSelected(int x, int y, Slider &current_tab, float &shade) {
	float currentColor = 0.f;

	if ((height - y - 1)>current_tab.y && (height - y - 1)<current_tab.y + 20 && x>current_tab.x && x<current_tab.x + 30) {
		current_tab.selected = true;
		return;
	}

	else if (y > 270 && y <= 529) {
		current_tab.y = ((float)height - y - 10.f);
		currentColor = ((float)height - y - 272.f) / 256.f;
		current_tab.selected = true;
		shade = currentColor;
	}

	else if (y < 271 && y > 260) {
		current_tab.y = ((float)height - 272.f - 10);
		currentColor = ((float)height - 271.f - 272.f) / 256.f;
		shade = currentColor;
	}

	else if (y > 529 && y <540) {
		current_tab.y = ((float)height - 529.f - 10);
		currentColor = ((float)height - 529.f - 272.f) / 256.f;
		shade = currentColor;
	}

	return;
}

// set color from gradient window
void colorReset(int x, int y) {
	glutSwapBuffers();	// clear buffer
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color_array);
	redSlider.y = color_array[0] * 256 + 272;
	greenSlider.y = color_array[1] * 256 + 272;
	blueSlider.y = color_array[2] * 256 + 272;
	redColor = color_array[0];
	greenColor = color_array[1];
	blueColor = color_array[2];
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		//left mouse button is pressed
		if (state == GLUT_DOWN) {
			if (x > 84 && x < 114) {
				sliderSelected(x, y, redSlider, redColor);
			}
			else if (x > 184 && x < 214) {
				sliderSelected(x, y, greenSlider, greenColor);
			}
			else if (x > 284 && x < 314) {
				sliderSelected(x, y, blueSlider, blueColor);
			}
			else if (x > 400 && x < 700 && (height - y - 1)>225 && (height - y - 1) < 300) {
				colorReset(x, (height - y - 1));
			}
		}
		else {
			redSlider.selected = false;
			blueSlider.selected = false;
			greenSlider.selected = false;
		}
		break;
	}

	glutPostRedisplay();
}

float sliderTab(int x, int y, Slider &current_tab) {
	float current_shade = 0.f;
	
	if (y > 270 && y <= 529) {
		current_tab.y = ((float)height - y - 10);
		current_shade = ((float)height - y - 272.f) / 256.f;
	}
	else if (y < 271) {
		current_tab.y = ((float)height - 272.f - 10);
		current_shade = ((float)height - 271.f - 272.f) / 256.f;
	}
	else if (y > 529) {
		current_tab.y = ((float)height - 529.f - 10);
		current_shade = ((float)height - 529.f - 272.f) / 256.f;
	}
	return current_shade;
}

void motion(int x, int y) {
	if (x > 49 && x < 151 && redSlider.selected) {
		redColor = sliderTab(x, y, redSlider);
	}
	else if (x > 149 && x < 251 && greenSlider.selected) {
		greenColor = sliderTab(x, y, greenSlider);
	}
	else if (x > 149 && x < 351 && blueSlider.selected) {
		blueColor = sliderTab(x, y, blueSlider);
	}
	glutPostRedisplay();
}


void main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Color Mixer");
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glColor3f(1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMainLoop();
}