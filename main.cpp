
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



void boxciz(double);
void cylinderciz();
void trianglesciz(double);

int sayig;
int sayib;
int rot = 0;
int roty = 0;
int rotval = 0;


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}


static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, 8.0, 0, 0.0, 0, 0.0, 1.0, 0.0);

    if(roty==1)
    {
        glRotated(rotval,0,1,0);

    }

    trianglesciz(a);
    boxciz(a);
    cylinderciz();
    for(i = 0; i<sayig;i++)
    {
        glTranslated(-2,0,0);

    trianglesciz(a);
    boxciz(a);
    cylinderciz();
    }

    glutPostRedisplay();
    glutSwapBuffers();
}

void trianglesciz(double a)
{
    glColor3d(1,0,0);



    glPushMatrix();


    if(rot == 1){
        glRotated(a,0,0,-1); // z ekseninde döndürür
    }

    for(int i=0;i<5;i++){
            glRotatef(72,0,0,1.0);
            glBegin (GL_TRIANGLES);
            glVertex3f (0, 0, 0.1);
            glVertex3f (1.5,-0.5,0.1 );
            glVertex3f (1.5,0.5,0.1);
            glEnd();
        }

    glPopMatrix();





}
void boxciz(double a)
{

    glColor3d(0,0,1);

    glPushMatrix();
        glTranslated(0,-2.6,0);

        glRotated(-10,0,1,0);
        glScaled(1,0.6,0.6);
        glutSolidCube(1);

    glPopMatrix();

}

void cylinderciz()
{
    glColor3d(1,1,1);
    glPushMatrix();
        glTranslated(0,-2.6,0);
        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(quadratic,0.1f,0.1f,3.0f,32,32);
    glPopMatrix();

}



static void key(unsigned char key, int x, int y)
{


    glutPostRedisplay();

    	switch (key) { // klavyeden alýnan deðerlere göre ekanda görüntü hareket ediyor ya da iþletiliyor.

	case 'r': // z ekseninde dondurulur.

		if(rot == 1)
            rot=0;
        else
            rot=1;

		break;
	case 'a': // y ekseninde sola dondurulur.
        roty = 1;
        if(rotval <=87)
        rotval-=1;


		break;
    case 'd': //y ekseninde saga dondurulur.
		roty = 1;
		if(rotval >=-87)
        rotval+=1;

		break;
    case 'g': //vantilator sayisi artar.
        sayig++;
    break;
    case 'h': //vantilator sayisi azalir.
        sayig--;
    break;

    }
}
static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Pervane");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
