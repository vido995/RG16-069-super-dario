#include <GL/glut.h>

/* Deklaracija callback funkcija */
static void on_display(void);

int main(int argc, char **argv){
    
    /* Inicijalizacija GLUT-a */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    /* Kreiranje prozora */
    glutInitWindowSize(800,650);
    glutInitWindowPosition(350,100);
    glutCreateWindow(argv[0]);
    
    /* Registracija callback funkcija */
    glutDisplayFunc(on_display);
    
    /* OpenGL inicijalizacija */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);
    
    /* Program ulazi u glavnu petlju */
    glutMainLoop();
    
    return 0;
}

static void on_display(void){
    
    /* Brise se prethodni sadrzaj prozora */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Iscrtavanje podgloge */
    glColor3f(0.5, 0, 0);
    glBegin(GL_POLYGON);
        glVertex3f(-1, -0.65, 0);
        glVertex3f(1, -0.65, 0);
        glVertex3f(1, -1, 0);
        glVertex3f(-1, -1, 0);
    glEnd();
    
    /* Iscrtavanje plave pozadine */
    /*glColor3f(0.12, 0.17, 0.93);*/
    glColor3f(0.11, 0.56, 1);
    glBegin(GL_POLYGON);
        glVertex3f(-1, 1, 0.9);
        glVertex3f(1, 1, 0.9);
        glVertex3f(1, -1, 0.9);
        glVertex3f(-1, -1, 0.9);
    glEnd();
    
    /* Postavlja se nova slika ne ekran */
    glutSwapBuffers();
}