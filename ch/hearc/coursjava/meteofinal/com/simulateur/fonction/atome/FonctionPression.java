
package ch.hearc.coursjava.meteofinal.com.simulateur.fonction.atome;

import ch.hearc.coursjava.meteofinal.com.simulateur.fonction.Fonctions_A;


public class FonctionPression extends Fonctions_A
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override public double f(double t)
		{
		return 50 + 2 * Math.cos(t);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
	}
