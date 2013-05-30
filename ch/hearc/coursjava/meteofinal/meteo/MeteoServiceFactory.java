
package ch.hearc.coursjava.meteofinal.meteo;

import ch.hearc.coursjava.meteofinal.com.simulateur.MeteoServiceSimulateur;

public class MeteoServiceFactory
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	/**
	 * <pre>
	 * Example:
	 * 		Windows : namePort=COM1
	 * 		Linux	: ??
	 * 		Mac 	: ??
	 * </pre>
	 */
	public static MeteoService_I create(String portName)
		{

		// ComConnexion comConnexion = new ComConnexion(portName, new ComOption());
		// MeteoServiceCallback_I meteoService = new MeteoService(comConnexion);
		// comConnexion.setMSC(meteoService);
		// return (MeteoService_I) meteoService;

		return new MeteoServiceSimulateur(portName);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
	}
