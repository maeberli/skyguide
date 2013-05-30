
package ch.hearc.coursjava.meteofinal.afficheur;

import ch.hearc.coursjava.meteofinal.afficheur.real.AfficheurService;
import ch.hearc.coursjava.meteofinal.reseau.MeteoServiceWrapper_I;


public class AfficheurFactory
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	/**
	 * n : #data to print/memorize
	 */
	public static AfficheurService_I create(AffichageOptions affichageOptions, MeteoServiceWrapper_I meteoServiceRemote)
		{
		//return null; // TODO

		return new AfficheurService(affichageOptions, meteoServiceRemote);

		// Provisoire
		// return new AfficheurServiceSimulateur(affichageOptions, meteoServiceRemote);
		// return new AfficheurServiceSimulateur("Simulateur", 100, meteoServiceRemote);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
