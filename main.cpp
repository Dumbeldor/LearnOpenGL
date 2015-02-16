#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#define LARGEUR_ECRAN 640
#define HAUTEUR_ECRAN 480

sf::RenderWindow window;
double angleZ = 0;
double angleX = 0;

void Dessiner();

int main(int argc, char *argv[])
{
	//const unsigned short int LARGEUR_ECRAN=640, HAUTEUR_ECRAN=480;
	window.create(sf::VideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32), "Test OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70,(double)LARGEUR_ECRAN/HAUTEUR_ECRAN, 1, 1000);
	glEnable(GL_DEPTH_TEST);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// on stoppe le programme
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				// on ajuste le viewport lorsque la fenêtre est redimensionnée
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}
		angleZ++;
		angleX++;
		Dessiner();

	}


	return 0;
}

void Dessiner()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	gluLookAt(3,4,2,0,0,0,0,0,1);

	glRotated(angleZ,0,0,1);
	glRotated(angleX,1,0,0);

	glBegin(GL_QUADS);


	glColor3ub(255,0,0);
	glVertex3d(1,1,1);
	glVertex3d(1,1,-1);
	glVertex3d(-1,1,-1);
	glVertex3d(-1,1,1);

	glColor3ub(0,255,0);
	glVertex3d(1,-1,1);
	glVertex3d(1,-1,-1);
	glVertex3d(1,1,-1);
	glVertex3d(1,1,1);

	glColor3ub(0,0,255);
	glVertex3d(-1,-1,1);
	glVertex3d(-1,-1,-1);
	glVertex3d(1,-1,-1);
	glVertex3d(1,-1,1);

	glColor3ub(255,255,0); //face jaune
	glVertex3d(-1,1,1);
	glVertex3d(-1,1,-1);
	glVertex3d(-1,-1,-1);
	glVertex3d(-1,-1,1);

	glColor3ub(0,255,255); //face cyan
	glVertex3d(1,1,-1);
	glVertex3d(1,-1,-1);
	glVertex3d(-1,-1,-1);
	glVertex3d(-1,1,-1);

	glColor3ub(255,0,255); //face magenta
	glVertex3d(1,-1,1);
	glVertex3d(1,1,1);
	glVertex3d(-1,1,1);
	glVertex3d(-1,-1,1);

	glEnd();

	glFlush();
	window.display();
}
