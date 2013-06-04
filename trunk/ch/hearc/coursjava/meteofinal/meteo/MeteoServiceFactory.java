package ch.hearc.coursjava.meteofinal.meteo;

import ch.hearc.coursjava.meteofinal.com.logique.MeteoServiceCallback_I;
import ch.hearc.coursjava.meteofinal.com.real.MeteoService;
import ch.hearc.coursjava.meteofinal.com.real.com.ComConnexion;
import ch.hearc.coursjava.meteofinal.com.real.com.ComOption;
import ch.hearc.coursjava.meteofinal.com.simulateur.MeteoServiceSimulateur;

public class MeteoServiceFactory {

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
	public static MeteoService_I create(String portName) {

		if ("Simulateur".equals(portName)) {
			return new MeteoServiceSimulateur(portName);
		}
		 else {

			ComConnexion comConnexion = new ComConnexion(portName,
					new ComOption());
			MeteoServiceCallback_I meteoService = new MeteoService(comConnexion);
			comConnexion.setMSC(meteoService);
			return (MeteoService_I) meteoService;
		}
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
}
