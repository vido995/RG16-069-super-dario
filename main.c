#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 10


static float y_d; /* y-koordinata Daria */
static float v_yd;/* Komponente vektora brzine skoka Daria*/

static float u_skoku=0; /* Fleg koji odredjuje da li je Dario vec u skoku*/
static float fleg=0; /* Fleg koji oznacava da li treba da padne sa prepreke na pdologu */


static void iscrtajPodlogu(void);
static void iscrtajDaria(void);
static void osvetljenje(void);
static void iscrtajPrereku(void);

/* Deklaracija callback funkcija */
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);
static void on_reshape(int width, int height);

static float brojac=0; /* Fleg od koje zavisi pozicija podloge i prepreka, kako se ovaj fleg povecava tako se podloga i prepreke transliraju u levo */

/* Komponente za podlogu */
GLfloat ambient_podloga1[] = { 0.5, 0, 0, 1 };
GLfloat diffuse_podloga1[] = { 0.5, 0.0, 0, 1 };

GLfloat ambient_podloga2[] = { 0.6, 0, 0, 1 };
GLfloat diffuse_podloga2[] = { 0.6, 0.0, 0, 1 };

/* Komponente za Daria */
GLfloat ambient_noge[] = {1,1,1,1};
GLfloat diffuse_noge[] = {1,1,1,1};

GLfloat ambient_telo[] = {0,0,1,1};
GLfloat diffuse_telo[] = {0,0,1,1};

GLfloat ambient_ruke[] = {1,0,0,1};
GLfloat diffuse_ruke[] = {1,0,0,1};

GLfloat ambient_glava[] = {0.94,0.32,0.1,1};
GLfloat diffuse_glava[] = {0.94,0.32,0.1,1};

GLfloat ambient_prepreka[] = {0,1,0,1};
GLfloat diffuse_prepreka[] = {0,1,0,1};

GLfloat ambient_prepreka1[] = {0.96,0.87,0.01,1};
GLfloat diffuse_prepreka1[] = {0.96,0.87,0.01,1};

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
    glutReshapeFunc(on_reshape);
    
    /*Pocetne koordinate Daria*/
    y_d = -11.75;
    
    
    /* OpenGL inicijalizacija */
    glClearColor(0.03, 0.42, 0.72, 0);
    glEnable(GL_DEPTH_TEST);
    
    osvetljenje();
    
    /* Program ulazi u glavnu petlju */
    glutMainLoop();
    
    return 0;
}

static void on_reshape(int width, int height){
    
    /* Postavlja se viewport */
    glViewport(0, 0, width, height);
    
    /* Postavljaju se parametri projekcije */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 100);
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
                v_yd=0.1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                u_skoku = 1;
            }
            break;
            
        case 'd':
        case 'D':
            /* Naredni uslovi sprecavaju da Dario prolazi kroz prepreke */
            if(brojac >= 13 && brojac <= 15.9 && y_d <= -7.95)
                break;
            else if(brojac >= 58 && brojac <= 60.9 && y_d <= -7.95)
                break;
            else if(brojac >= 88 && brojac <= 90.9 && y_d <= -7.95)
                break;
            else if(brojac >= 138 && brojac <= 140.9 && y_d <= -7.95)
                break;
            else if(brojac >= 173 && brojac <= 175.9 && y_d <= -7.95)
                break;
            else if(brojac >= 228 && brojac <= 230.9 && y_d <= -7.95)
                break;
            /* slucajevi za lebdece prepreke */
            else if(brojac >= 28.55 && brojac <= 32.75 && y_d <= -2.67 && y_d >= -5.35)
                break;
            else if(brojac >= 45.05 && brojac <= 47.75 && y_d <= -2.67 && y_d >= -5.35)
                break;
            else if(brojac >= 105.05 && brojac <= 110.75 && y_d <= -2.67 && y_d >= -5.35)
                break;
            else{
                brojac += 0.1;
                glutPostRedisplay();
                break;
            }
    }
}

static void on_timer(int value){
    
    /* Proverava se da li callback dolazi tajmera za skok Daria */
    if(value == TIMER_ID){
        
        y_d += v_yd;
        if(y_d >= 0.2)
            v_yd *= -1;
        
        if(y_d <= -11.75){
            u_skoku = 0;
            y_d = -11.75;
        }
        
        
        glutPostRedisplay();
        
        if(u_skoku){
            glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
        }
    }
    /* Slucaj pozivanje funckije on_timer kada Dario pada sa prepreke */
    if(value == 2){
        y_d -= v_yd;
        
        if(y_d <= -11.75){
            u_skoku = 0;
            y_d = -11.75;
            fleg = 0;
        }
        
        glutPostRedisplay();
        
        if(u_skoku){
            glutTimerFunc(TIMER_INTERVAL, on_timer, 2);
        }
    }
}

static void osvetljenje(){
        
        /* Ukljucije se osvetljenje */
        glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	/* Komponente osvetljenja */
	GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1};
	GLfloat light_diffuse[] = {1, 1, 1, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	GLfloat shiness = 30;
	glMaterialf(GL_FRONT, GL_SHININESS, shiness);

	/* Pozicija izvora svetlosti */
	GLfloat light_position[] = {20, 15, 5, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

static void iscrtajPodlogu(void){
    
    /* Iscrtavanje podgloge */
    for(int i=0;i<100;i++){
        
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_podloga1);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_podloga1);
            glTranslatef(i*-3.6,0,0);
            glutSolidCube(1.8);
            glTranslatef(1.8,-1.8,0);
            glutSolidCube(1.8);
        glPopMatrix();

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_podloga2);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_podloga2);
            glTranslatef(i*-3.6+1.8,0,0);
            glutSolidCube(1.8);
            glTranslatef(1.8,-1.8,0);
            glutSolidCube(1.8);
        glPopMatrix();
    }
}

static void iscrtajDaria(void){

    /*noge*/
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_noge);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_noge);
        glScalef(1,1.2,1);
        glutSolidCube(1);
    glPopMatrix();
        
        /*telo*/
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_telo);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_telo);
        glTranslatef(0,1.1,0);
        glutSolidCube(1);
    glPopMatrix();
    
    /*ruke*/
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_ruke);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_ruke);
        glTranslatef(-0.7,1.2,0);
        glScalef(0.4,0.8,0.5);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.7,1.2,0);
        glScalef(0.4,0.8,0.5);
        glutSolidCube(1);
    glPopMatrix();
    
    /*glava*/
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_glava);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_glava);
        glTranslatef(0,1.9,0);
        glutSolidCube(0.6);
    glPopMatrix();
    
}
/* zelena prepreka */
void iscrtajPrereku(){
        
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_prepreka);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_prepreka);
        glRotatef(90,1,0,0);
        gluCylinder(quadric,1,1,2.8,32,8);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0.4,0); 
        glRotatef(90,1,0,0);
        gluCylinder(quadric,1.2,1.2,0.5,32,8);
        gluDisk(quadric,0,1.2,10,10);
    glPopMatrix();
}

/* zuta prepreka */
void iscrtajPrereku2(){
    
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_prepreka1);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_prepreka1);
        glutSolidCube(1.5);
    glPopMatrix();
}

static void on_display(void){
    
    /* Brise se prethodni sadrzaj prozora */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Podesava se vidna tacka */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,1,-28,0,0,0,0,1,0);
    
    /* Naredni uslovi omogucavaju da se skok zaustavi na podlozi */
    if(brojac >= 13.1 && brojac <= 16.7 && y_d <= -7.95){
        u_skoku = 0;
        y_d = -7.95;
        fleg=1;
        
    }
    else if(brojac >= 58.1 && brojac <= 61.7 && y_d <= -7.95){
        u_skoku = 0;
        y_d = -7.95;
        fleg=1;
    }
    else if(brojac >= 88.1 && brojac <= 91.7 && y_d <= -7.95){
        u_skoku = 0;
        y_d = -7.95;
        fleg=1;
    }
    else if(brojac >= 138.1 && brojac <= 141.7 && y_d <= -7.95){
        u_skoku = 0;
        y_d = -7.95;
        fleg=1;
    }
    else if(brojac >= 173.1 && brojac <= 176.7 && y_d <= -7.95){
        u_skoku = 0;
        y_d = -7.95;
        fleg=1;
    } 
    else if(brojac >= 228.1 && brojac <= 231.7 && y_d <= -7.95){
        u_skoku = 0;
        y_d = -7.95;
        fleg=1;
    }
    /* slucajevi za lebdece podloge */
    else if(brojac >= 28.55 && brojac <= 32.75 && y_d <= -2.65 && y_d >= -5.35){
        u_skoku = 0;
        y_d = -2.65;
        fleg=1;
    }
    else if(brojac >= 45.05 && brojac <= 47.75 && y_d <= -2.65 && y_d >= -5.35){
        u_skoku = 0;
        y_d = -2.65;
        fleg=1;
    }
    else if(brojac >= 105.05 && brojac <= 110.75 && y_d <= -2.65 && y_d >= -5.35){
        u_skoku = 0;
        y_d = -2.65;
        fleg=1;
    }
    else if(fleg){
        v_yd = 0.1;
        glutTimerFunc(TIMER_INTERVAL, on_timer, 2);
    }

    /* Iscrtavanje Daria */
    glPushMatrix();
        glTranslatef(0,y_d,0);
        iscrtajDaria();
    glPopMatrix();
    
    /* Iscrtavanje podloge */
    glPushMatrix();
        glTranslatef(brojac+25,-13.25,0);
        iscrtajPodlogu();
    glPopMatrix();
    
    /* Iscrtavanje zelenih prepreka */
    glPushMatrix();
        glTranslatef(brojac-15,-9.15,-0.6);
        iscrtajPrereku();
        glTranslatef(-45,0,0);
        iscrtajPrereku();
        glTranslatef(-30,0,0);
        iscrtajPrereku();
        glTranslatef(-50,0,0);
        iscrtajPrereku();
        glTranslatef(-35,0,0);
        iscrtajPrereku();
        glTranslatef(-55,0,0);
        iscrtajPrereku();
    glPopMatrix();
    
    /* Iscrtavanje lebdecih prepreka */
    glPushMatrix();
        glTranslatef(brojac-30,-4,0);
        iscrtajPrereku2();
        glTranslatef(-1.5,0,0);
        iscrtajPrereku2();
        glTranslatef(-15,0,0);
        iscrtajPrereku2();
        glTranslatef(-60,0,0);
        iscrtajPrereku2();
        glTranslatef(-1.5,0,0);
        iscrtajPrereku2();
        glTranslatef(-1.5,0,0);
        iscrtajPrereku2();
    glPopMatrix();
    
    /* Postavlja se nova slika na ekran */
    glutSwapBuffers();
}
