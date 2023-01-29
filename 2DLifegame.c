#include<GL/glut.h>
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include"user.h"
int window_w = 640;
int window_h = 640;
int points[max_point][2];
int dispoints[max_point][2];
unsigned long long ee = ULLONG_MAX;
unsigned long long ii = ee >> 1;
unsigned long long base =ee ^ii;
unsigned long long mask = ~(base | 1);
unsigned long long bord1[64] = { 0 };
unsigned long long bord2[64] = { 0 };
int flug;
int gene = 0;
//--------------------------------------------------ライフゲーム計算用
void poo( unsigned long long x[64]) {
printf("----------------------------------------\n");
		for (int i = 63; i >-1; i--)
		{
			for (int j = 0; j < 64; j++)
			{
				printf("%llu", (x[i] >> j) & 1);
			}
			printf("\n");
		}
}
void check() {
	bord1[0] = 0;
	bord1[63] = 0;
	bord2[0] = 0;
	bord2[63] = 0;
	if (gene % 2) {
		for (int i = 1; i < 63; i++){
			unsigned long long c = bord1[i];
			unsigned long long e = c << 1;
			unsigned long long w = c >> 1;
			unsigned long long n = bord1[i - 1];
			unsigned long long ne = bord1[i - 1] << 1;
			unsigned long long nw = bord1[i - 1] >> 1;
			unsigned long long s = bord1[i + 1];
			unsigned long long se = bord1[i + 1] << 1;
			unsigned long long sw = bord1[i + 1] >> 1;

			unsigned long long s0 = ~(nw | n);
			unsigned long long s1 = nw ^ n;
			unsigned long long s2 = nw & n;

			unsigned long long s3 = s2 & ne;
			s2 = (s2 & ~ne) | (s1 & ne);
			s1 = (s1 & ~ne) | (s0 & ne);
			s0 = s0 & ~ne;

			s3 = (s3 & ~w) | (s2 & w);
			s2 = (s2 & ~w) | (s1 & w);
			s1 = (s1 & ~w) | (s0 & w);
			s0 = s0 & ~w;

			s3 = (s3 & ~e) | (s2 & e);
			s2 = (s2 & ~e) | (s1 & e);
			s1 = (s1 & ~e) | (s0 & e);
			s0 = s0 & ~e;

			s3 = (s3 & ~sw) | (s2 & sw);
			s2 = (s2 & ~sw) | (s1 & sw);
			s1 = (s1 & ~sw) | (s0 & sw);
			s0 = s0 & ~sw;

			s3 = (s3 & ~s) | (s2 & s);
			s2 = (s2 & ~s) | (s1 & s);
			s1 = (s1 & ~s) | (s0 & s);
			s0 = s0 & ~s;

			s3 = (s3 & ~se) | (s2 & se);
			s2 = (s2 & ~se) | (s1 & se);
			s1 = (s1 & ~se) | (s0 & se);
			s0 = s0 & ~se;
			bord2[i] = mask & ((bord1[i] & (s2 | s3)) | (~bord1[i] & s3));
		}
	}
	else
	{
		for (int i = 1; i < 63; i++)
		{
			unsigned long long c = bord2[i];
			unsigned long long e = c << 1;
			unsigned long long w = c >> 1;
			unsigned long long n = bord2[i - 1];
			unsigned long long ne = bord2[i - 1] << 1;
			unsigned long long nw = bord2[i - 1] >> 1;
			unsigned long long s = bord2[i + 1];
			unsigned long long se = bord2[i + 1] << 1;
			unsigned long long sw = bord2[i + 1] >> 1;

			unsigned long long s0 = ~(nw | n);
			unsigned long long s1 = nw ^ n;
			unsigned long long s2 = nw & n;

			unsigned long long s3 = s2 & ne;
			s2 = (s2 & ~ne) | (s1 & ne);
			s1 = (s1 & ~ne) | (s0 & ne);
			s0 = s0 & ~ne;

			s3 = (s3 & ~w) | (s2 & w);
			s2 = (s2 & ~w) | (s1 & w);
			s1 = (s1 & ~w) | (s0 & w);
			s0 = s0 & ~w;

			s3 = (s3 & ~e) | (s2 & e);
			s2 = (s2 & ~e) | (s1 & e);
			s1 = (s1 & ~e) | (s0 & e);
			s0 = s0 & ~e;

			s3 = (s3 & ~sw) | (s2 & sw);
			s2 = (s2 & ~sw) | (s1 & sw);
			s1 = (s1 & ~sw) | (s0 & sw);
			s0 = s0 & ~sw;

			s3 = (s3 & ~s) | (s2 & s);
			s2 = (s2 & ~s) | (s1 & s);
			s1 = (s1 & ~s) | (s0 & s);
			s0 = s0 & ~s;

			s3 = (s3 & ~se) | (s2 & se);
			s2 = (s2 & ~se) | (s1 & se);
			s1 = (s1 & ~se) | (s0 & se);
			s0 = s0 & ~se;
			bord1[i] = mask & ((bord2[i] & (s2 | s3)) | (~bord2[i] & s3));
		}
	}
	if (gene % 2)
	{
		poo(bord2);
	}
	else
	{
		poo(bord1);
	}
}
//-------------------------------------------------------出力用
void dot() {
	glColor3d(1.0, 1.0, 0.65);
	glBegin(GL_QUADS);
	if (gene % 2) {
		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 64; j++) {
				int d = (bord2[i] >> j) & 1;
				if (d) {
					glVertex2i(j * 10, i * 10);
					glVertex2i(j * 10, i * 10 + 10);
					glVertex2i(j * 10 + 10, i * 10 + 10);
					glVertex2i(j * 10 + 10, i * 10);
				}
			}
		}
	}
	else {
		for (int i = 0; i < 64; i++) {
			for (int j = 0; j < 64; j++) {
				int d = (bord1[i] >> j) & 1;
				if (d) {
					glVertex2i(j * 10, i * 10);
					glVertex2i(j * 10, i * 10 + 10);
					glVertex2i(j * 10 + 10, i * 10 + 10);
					glVertex2i(j * 10 + 10, i * 10);
				}
			}
		}
	}
	glEnd();
	glFlush();
}
void frame() {
	glColor3d(0.0, 0.125, 0.22);
	glBegin(GL_LINES);
	for (int i = 0; i <= window_w / 10; i++) {
		glVertex2i((int)i * 10, 0);
		glVertex2i((int)i * 10, 2000);
	}
	for (int i = 0; i <= window_h / 10; i++) {
		glVertex2i(0, (int)i * 10);
		glVertex2i(2000, (int)i * 10);
	}
	glEnd();

	glFlush();
}
int num(int s) {
	return (s-s%10);
}
void idle() {
	glutPostRedisplay();
}
void Init() {
	glClearColor(0.0, 0.21, 0.38, 1.0);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if ((GENE >= gene) && (gene > 0)) {
		check();
		dot();
		gene++;
	}
	else {
		dot();
	}

	frame();

	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)w, 0.0, (double)h);
	window_w = w;
	window_h = h;
}
void mouse(int button,int state,int x,int y) {
	y = hight - window_h + y;
	if ((button == GLUT_LEFT_BUTTON)&&(state == GLUT_DOWN)&&(gene == 0)) {	
		if (y>=0) {
			bord1[num(hight - y) / 10] ^= base >> (63 - num(x) / 10);
			bord2[num(hight - y) / 10] ^= base >> (63 - num(x) / 10);
			printf("\n(%d %d)\n", 63 - num(x) / 10, num(hight - y) / 10);
			for (int j = 0; j < 64; j++) {
				printf("%lld", ((bord1[num(hight - y) / 10]) >> j) & 1);
			}
			printf("\n");
		}
		else {
			printf("invalid!!");
		}
		glutPostRedisplay();
	}
	else if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		printf("!!");
		gene++;
	}
}
int main(int argc,char** argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(window_w,window_h);
	glutCreateWindow("test");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	Init();
	glutMainLoop();
}
