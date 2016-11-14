#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#include<math.h>

#include <stdlib.h>
#include<iostream>

// declare global

GLfloat Ocx, Ocy, Ocz;
GLfloat vupx, vupy, vupz;
GLfloat lAtx, lAty, lAtz;

GLuint x, y, z;

GLfloat top, bottom, left, right, nearr, farr;

// dimensoes dos objetos

GLfloat tamTampox, tamTampoy, tamTampoz;
GLfloat tamPernax,tamPernay,tamPernaz;

GLfloat sala[3];

GLfloat salaCentro[3];

GLfloat coefDist;

void showStatus(){
    system("clear | cls");
    std::cout << "Oc = [" << Ocx << ", " << Ocy << ", " << Ocz << "]" << std::endl;
    std::cout << "LookAt = [" << lAtx << ", " << lAty << ", " << lAtz << "]" << std::endl;
    std::cout << "Vup = [" << vupx << ", " << vupy << ", " << vupz << "]" << std::endl;
    std::cout << "centro da sala = [" << salaCentro[x] << ", " << salaCentro[y] << ", " << salaCentro[z] << "]" << std::endl;
}

void init(){

    x = 0; y = 1; z = 2;

    coefDist = 1.0;

    sala[x] = 5;
    sala[y] = 5;
    sala[z] = 5;

    salaCentro[x] = sala[x]/2;
    salaCentro[y] = sala[y]/2;
    salaCentro[z] = sala[z]/2;

    Ocx = salaCentro[x] - coefDist;
    Ocy = salaCentro[y] - coefDist;
    Ocz = salaCentro[z] - coefDist;

    lAtx = salaCentro[x] + coefDist;
    lAty = 0;
    lAtz = salaCentro[z] + coefDist;

    tamTampox = 1.2;
    tamTampoy = 0.1;
    tamTampoz = 2.5;

    vupx = Ocx + 1;
    vupy = Ocy + 1;
    vupz = Ocz + 1;

    top = 1;
    bottom = -1;
    left = -1.5;
    right = 1.5;
    nearr = 0.5;
    farr = 20;

}


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(left, right, bottom, top, nearr, farr);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{

    showStatus();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(Ocx,Ocy, Ocz, lAtx, lAty, lAtz,vupx, vupy,vupz);

    // fazendo o tampo da mesa
    glPushMatrix();
        glTranslatef(salaCentro[x], tamPernay + tamTampoy/2, salaCentro[z]);
        glScalef(tamTampox, tamTampoy, tamTampoz);
        makeCube(1);
    glPopMatrix();

    // desenhando as pernas

    for(int it = 1; it <= 2; it++){
            /*aqui, achando o tamanho da diagonal da mesa por pitagoras*/
        GLfloat diagTampo = pow ( pow(tamTampox,2) + pow(tamTampoz,2) , 0.5 ) / 2;

    // perna 1 xou 3
        glPushMatrix();
            glTranslatef(salaCentro[x] + pow(-1,it)*diagTampo, tamPernay/2, salaCentro[z] + pow(-1,it)*diagTampo);

            glScalef(tamPernax, tamPernay, tamPernaz);
            makeCube(1);
        glPopMatrix();

    // perna 2 xou 4
        glPushMatrix();
            glTranslatef(salaCentro[x] - pow(-1,it)*diagTampo, tamPernay/2, salaCentro[z] + pow(-1,it)*diagTampo);

            glScalef(tamPernax, tamPernay, tamPernaz);
            makeCube(1);
        glPopMatrix();

    }

    glutSwapBuffers();
}

void makeCube(GLfloat siz){
    GLfloat d = siz/2;
// sentido anti-horario
    glBegin(GL_TRIANGLE_STRIP);
        /* 0 1 2, 2 3 0*/
        glVertex3f(d,d,d);
        glVertex3f(d,d,-d);
        glVertex3f(-d,d,-d);

        glVertex3f(-d,d,-d);
        glVertex3f(-d,d,d);
        glVertex3f(d,d,d);

    glEnd();

    // parte de baixo
    d = d*(-1);

    glBegin(GL_TRIANGLE_STRIP);
        /* 0 1 2, 2 3 0*/
        glVertex3f(d,d,d);
        glVertex3f(d,d,-d);
        glVertex3f(-d,d,-d);

        glVertex3f(-d,d,-d);
        glVertex3f(-d,d,d);
        glVertex3f(d,d,d);

    glEnd();

    // direita: x positivo
    d = d*(-1);

    glBegin(GL_TRIANGLE_STRIP);
        /* 0 1 2, 2 3 0*/
        glVertex3f(d,d,d);
        glVertex3f(d,-d,d);
        glVertex3f(d,-d,-d);

        glVertex3f(d,-d,-d);
        glVertex3f(d,d,-d);
        glVertex3f(d,d,d);

    glEnd();

    // lado esquerdo: x negativo
    d = d*(-1);

    glBegin(GL_TRIANGLE_STRIP);
        /* 0 1 2, 2 3 0*/
        glVertex3f(d,d,d);
        glVertex3f(d,-d,d);
        glVertex3f(d,-d,-d);

        glVertex3f(d,-d,-d);
        glVertex3f(d,d,-d);
        glVertex3f(d,d,d);

    glEnd();

    // frente: z positivo
    d = d*(-1);

    glBegin(GL_TRIANGLE_STRIP);
        /* 0 1 2, 2 3 0*/
        glVertex3f(d,d,d);
        glVertex3f(-d,d,d);
        glVertex3f(-d,-d,d);

        glVertex3f(-d,-d,d);
        glVertex3f(d,-d,d);
        glVertex3f(d,d,d);

    glEnd();

    // tras: z negativo
    d = d*(-1);

    glBegin(GL_TRIANGLE_STRIP);
        /* 0 1 2, 2 3 0*/
        glVertex3f(d,d,d);
        glVertex3f(-d,d,d);
        glVertex3f(-d,-d,d);

        glVertex3f(-d,-d,d);
        glVertex3f(d,-d,d);
        glVertex3f(d,d,d);

    glEnd();

}

GLfloat delta = 0.5;

static void key(unsigned char key, int x, int y){
    switch (key)
    {
        case 'w':
            Ocx = Ocx + delta;
            Ocy = Ocy + delta;
            Ocz = Ocz + delta;

            lAtx = lAtx + delta;
            lAty = lAty + delta;
            lAtz = lAtz + delta;

            break;
        case 's':
            Ocx = Ocx - delta;
            Ocy = Ocy - delta;
            Ocz = Ocz - delta;

            lAtx = lAtx - delta;
            lAty = lAty - delta;
            lAtz = lAtz - delta;

            break;
    }

    glutPostRedisplay();
}

static void idle(void){
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[]){
    init();
    glutInit(argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("rubs");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
