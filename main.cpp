#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#define LARGEUR_BASE 100
#define HAUTEUR_BASE 40

#define LARGEUR_BRAS_1 300
#define HAUTEUR_BRAS_1 30

#define LARGEUR_BRAS_2 100
#define HAUTEUR_BRAS_2 20

#define TAILLE_CAISSE 20

#define LARGEUR_ECRAN (LARGEUR_BASE + LARGEUR_BRAS_1 + HAUTEUR_BRAS_2 + 50)
#define HAUTEUR_ECRAN (HAUTEUR_BASE + LARGEUR_BRAS_1 + HAUTEUR_BRAS_2 + 50)

int angle1 = 45;
int angle2 = -20;
int longueur = 50;
sf::RenderWindow window;


void dessineRectangle(double,double);
void dessinerRepere(unsigned int);
void Dessiner();


int main(int argc, char *argv[])
{
	//const unsigned short int LARGEUR_ECRAN=640, HAUTEUR_ECRAN=480;
	window.create(sf::VideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32), "Test OpenGL", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,LARGEUR_ECRAN,0,HAUTEUR_ECRAN); 

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				longueur--;
				if (longueur < 10)
					longueur = 10;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				longueur++;
				if (longueur > 100)
					longueur = 100;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					angle1++;
					if(angle1 > 90)
						angle1 = 90;
				} 
				else 
				{
					angle2++;
					if(angle2 > 90)
						angle2 = 90;
				}

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					angle1--;
					if(angle1 < 10)
						angle1 = 10;
				} 
				else 
				{
					angle2--;
					if(angle2 < -90)
						angle2 = -90;
				}

			}




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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*	glBegin(GL_QUADS);
			glColor3ub(0,0,255);
			glVertex2d(-0.75,-0.75);
			glVertex2d(-0.75,0.75);
			glColor3ub(255,0,0);
			glVertex2d(0.75,0.75);
			glVertex2d(0.75,-0.75);
			glEnd(); */

		Dessiner();	
		dessinerRepere(50);

		glFlush();
		window.display();
	}


	return 0;
}


/*
 *     Dessine un rectangle avec comme point de référence
 *         le milieu du côté gauche
 *         */
void dessineRectangle(double largeur,double hauteur)
{
	glBegin(GL_QUADS);
	glVertex2d(0,-hauteur/2);
	glVertex2d(0,hauteur/2);
	glVertex2d(largeur,hauteur/2);
	glVertex2d(largeur,-hauteur/2);
	glEnd();
}

/*
 *     Dessine le repère actuel pour faciliter
 *         la compréhension des transformations.
 *             Utiliser "echelle" pour avoir un repère bien orienté et positionné
 *                 mais avec une échelle différente.
 *                 */
void dessinerRepere(unsigned int echelle = 1)
{
	glPushMatrix();
	glScalef(echelle,echelle,echelle);
	glBegin(GL_LINES);
	glColor3ub(0,0,255);
	glVertex2i(0,0);
	glVertex2i(1,0);
	glColor3ub(0,255,0);
	glVertex2i(0,0);
	glVertex2i(0,1);
	glEnd();
	glPopMatrix();
}

void Dessiner()
{
	glClear( GL_COLOR_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	/* Je déplace mon répère initial (actuellement
	 *     en bas à gauche de l'écran) */
	glTranslated(LARGEUR_BASE/2,HAUTEUR_BASE,0);

	// La base
	glColor3ub(254,128,1);
	dessineRectangle(LARGEUR_BASE,HAUTEUR_BASE);

	//Je me place en haut au milieu de la base
	glTranslated(LARGEUR_BASE/2,HAUTEUR_BASE/2,0);

	// Le grand bras
	glRotated(angle1,0,0,1);
	glColor3ub(248,230,7);
	dessineRectangle(LARGEUR_BRAS_1,HAUTEUR_BRAS_1);

	// Je me place au bout du grand bras
	glTranslated(LARGEUR_BRAS_1,0,0);

	// Puis m'occupe du petit bras
	glRotated(angle2,0,0,1);
	glColor3ub(186,234,21);
	dessineRectangle(LARGEUR_BRAS_2,HAUTEUR_BRAS_2);

	// Je me place au bout du petit bras
	glTranslated(LARGEUR_BRAS_2,0,0);
	/* J'annule les rotations pour avoir mon repère aligné
	   avec le repère d'origine */
	glRotated(-angle1-angle2,0,0,1);

	// Je dessine le fil
	glColor3ub(255,255,255);
	glBegin(GL_LINES);
	glVertex2i(0,0);
	glVertex2i(0,-longueur);
	glEnd();

	/* Je descends en bas du fil (avec un petit décalage
	   sur X pour anticiper le dessin de la caisse */
	glTranslated(-TAILLE_CAISSE/2,-longueur,0);

	// Et je dessine enfin la caisse
	glColor3ub(175,175,85);
	dessineRectangle(TAILLE_CAISSE,TAILLE_CAISSE);

	glFlush();
	window.display();
}

