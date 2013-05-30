
package ch.hearc.coursjava.meteofinal.com.simulateur.fonction.atome;

import ch.hearc.coursjava.meteofinal.com.simulateur.fonction.Fonctions_A;


public class FonctionAltitude extends Fonctions_A
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override public double f(double t)
		{
		return 1000 + 3000 * Math.sin(t);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
	}
