//#include <GL/freeglut_std.h>
//#include <GL/gl.h>
#include<stdio.h>
#include<GL/glut.h>

typedef float point2[2];

point2 v[] = {
    {-1.0, -0.58},
    {1.0, -0.58},
    {0.0, 1.15}
};

int n;

void triangle(point2 a, point2 b, point2 c) {
    glBegin(GL_TRIANGLES);
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
    glEnd();
}

void divide_triangle(point2 a, point2 b, point2 c, int m) {
    point2 v0, v1, v2;

    if(m > 0) {
        for(int j=0; j<2; j++) v0[j] = (a[j] + b[j]) / 2;
        for(int j=0; j<2; j++) v1[j] = (a[j] + c[j]) / 2;
        for(int j=0; j<2; j++) v2[j] = (c[j] + b[j]) / 2;
        divide_triangle(a, v0, v1, m-1);
        divide_triangle(c, v1, v2, m-1);
        divide_triangle(b, v2, v0, m-1);
    } else
        triangle(a, b, c);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    divide_triangle(v[0], v[1], v[2], n);
    glFlush();
}

void init() {
    glMatrixMode(GL_PROGRAM);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
}

void main(int argc, char** argv) {
    printf("Enter number of subdivisions: ");
    scanf("%d", &n);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Some name");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
