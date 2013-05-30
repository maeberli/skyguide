
package ch.hearc.coursjava.meteofinal.com.simulateur.fonction.atome;

import ch.hearc.coursjava.meteofinal.com.simulateur.fonction.Fonctions_A;


public class FonctionTemperature extends Fonctions_A
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override public double f(double t)
		{
		return -10 * Math.sin(t);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
	}
