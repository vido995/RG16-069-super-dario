#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 10

static float x_d, y_d; /* Koordinate donjeg desnog ugla Daria */
static float v_yd;/* Komponente vektora brzine skoka Daria*/

static float u_skoku; /* Fleg koji odredjuje da li je Dario vec u skoku*/

/* Deklaracija callback funkcija */
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);

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
    glutKeyboardFunc(on_keyboard);
    
    /*Pocetne koordinate Daria*/
    x_d = 0.05;
    y_d = -0.7;
    
    
    u_skoku = 0;
    
    /* OpenGL inicijalizacija */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);
    
    /* Program ulazi u glavnu petlju */
    glutMainLoop();
    
    return 0;
}

static void on_keyboard(unsigned char key, int x, int y){
    
    switch(key){
        case 27:
            /* Izlazak iz programa - ESC dugme */
            exit(0);
            break;
        
         /* Slucaj kada Dario skace */   
        case 'w':
        case 'W':
            if(!u_skoku){
                v_yd=0.01;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                u_skoku = 1;
            }
            break;
    }
}

static void on_timer(int value){
    
    /* Proverava se da li callback dolazi tajmera za skok Daria */
    if(value == TIMER_ID){
        
        y_d += v_yd;
        if(y_d >= 0.2)
            v_yd *= -1;
        if(y_d <= -0.7){
            u_skoku = 0;
            y_d = -0.7;
        }
        
        
        glutPostRedisplay();
        
        if(u_skoku){
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
        }
    }
}


static void on_display(void){
    
    /* Brise se prethodni sadrzaj prozora */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Iscrtavanje podgloge */
    for(int i=0;i<14;i++){
        glColor3f(0.5,0,0);
        glBegin(GL_TRIANGLES);
            glVertex3f(-1+i*0.15,-0.7,0);
            glVertex3f(-0.85+i*0.15,-0.7,0);
            glVertex3f(-0.85+i*0.15,-0.85,0);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex3f(-1+i*0.15,-0.85,0);
            glVertex3f(-0.85+i*0.15,-0.85,0);
            glVertex3f(-0.85+i*0.15,-1,0);
        glEnd();
        
        glColor3f(0.6,0,0);
        glBegin(GL_TRIANGLES);
            glVertex3f(-1+i*0.15,-0.7,0);
            glVertex3f(-0.85+i*0.15,-0.85,0);
            glVertex3f(-0.85+i*0.15,-85,0);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex3f(-1+i*0.15,-0.85,0);
            glVertex3f(-0.85+i*0.15,-1,0);
            glVertex3f(-0.85+i*0.15,-1,0);
        glEnd();
    }
    
    /* Iscrtavanje plave pozadine */
    /*glColor3f(0.12, 0.17, 0.93);*/
    glColor3f(0.11, 0.56, 1);
    glBegin(GL_POLYGON);
        glVertex3f(-1, 1, 0.9);
        glVertex3f(1, 1, 0.9);
        glVertex3f(1, -1, 0.9);
        glVertex3f(-1, -1, 0.9);
    glEnd();
    
    /*Iscratanje Daria*/
    /*noge*/
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex3f(x_d,y_d,0);
        glVertex3f(x_d,y_d+0.07,0);
        glVertex3f(x_d-0.05,y_d+0.07,0);
        glVertex3f(x_d-0.05,y_d,0);
    glEnd();
    /*telo*/
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
        glVertex3f(x_d,y_d+0.07,0);
        glVertex3f(x_d,y_d+0.13,0);
        glVertex3f(x_d-0.05,y_d+0.13,0);
        glVertex3f(x_d-0.05,y_d+0.07,0);
    glEnd();
    /*ruke*/
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex3f(x_d-0.05,y_d+0.07,0);
        glVertex3f(x_d-0.05,y_d+0.13,0);
        glVertex3f(x_d-0.07,y_d+0.13,0);
        glVertex3f(x_d-0.07,y_d+0.07,0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(x_d,y_d+0.07,0);
        glVertex3f(x_d,y_d+0.13,0);
        glVertex3f(x_d+0.02,y_d+0.13,0);
        glVertex3f(x_d+0.02,y_d+0.07,0);
    glEnd();
    /*glava*/
    glColor3f(0.94,0.32,0.1);
    glBegin(GL_POLYGON);
        glVertex3f(x_d-0.01,y_d+0.13,0);
        glVertex3f(x_d-0.01,y_d+0.16,0);
        glVertex3f(x_d-0.04,y_d+0.16,0);
        glVertex3f(x_d-0.04,y_d+0.13,0);
    glEnd();
    
    
    /* Postavlja se nova slika ne ekran */
    glutSwapBuffers();
}
