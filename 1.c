#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

GLint X1, Y1, X2, Y2;

void LineBres(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    int dx = abs(X2 - X1), dy = abs(Y2 - Y1); // Calculate the differences in x and y
    int p = 2 * dy - dx; // Initial decision parameter
    int twoDy = 2 * dy, twoDyDx = 2 * (dy - dx); // Constant terms for decision parameter updates
    int x, y;

    // Determine the starting point
    if (X1 > X2) {
        x = X2;
        y = Y2;
        X2 = X1;
    } else {
        x = X1;
        y = Y1;
    }

    glBegin(GL_POINTS); // Start specifying points
    glVertex2i(x, y); // Draw the first point

    // Draw the rest of the line
    while (x < X2) {
        x++;
        if (p < 0)
            p += twoDy;
        else {
            y++;
            p += twoDyDx;
        }
        glVertex2i(x, y); // Draw the point
    }
    glEnd(); // End specifying points
    glFlush(); // Ensure all OpenGL commands are executed
}

void Init()
{
    glClearColor(1.0, 1.0, 1.0, 0); // Set the clear color to white
    glColor3f(0.0, 0.0, 0.0); // Set the drawing color to black
    glPointSize(4.0); // Set the size of points to be drawn
    glViewport(0, 0, 50, 50); // Set the viewport size
    glMatrixMode(GL_PROJECTION); // Select the projection matrix
    glLoadIdentity(); // Reset the projection matrix
    gluOrtho2D(0, 50, 0, 50); // Set the orthographic projection
}

void main(int argc, char **argv)
{
    // Get the line endpoints from the user
    printf("Enter two points for draw lineBresenham:\n");
    printf("\nEnter point1 (X1, Y1): ");
    scanf("%d%d", &X1, &Y1);
    printf("\nEnter point2 (X2, Y2): ");
    scanf("%d%d", &X2, &Y2);

    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set the display mode
    glutInitWindowSize(300, 400); // Set the window size
    glutInitWindowPosition(0, 0); // Set the window position
    glutCreateWindow("LineBresenham"); // Create the window
    Init(); // Initialize OpenGL state
    glutDisplayFunc(LineBres); // Set the display callback function
    glutMainLoop(); // Enter the GLUT event processing loop
}
