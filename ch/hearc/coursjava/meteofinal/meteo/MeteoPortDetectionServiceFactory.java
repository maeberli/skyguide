
package ch.hearc.coursjava.meteofinal.meteo;

import ch.hearc.coursjava.meteofinal.com.real.com.MeteoPortDetectionService;


public class MeteoPortDetectionServiceFactory
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

	public static MeteoPortDetectionService_I create()
		{
		// TODO

		// Provisoire
		return (MeteoPortDetectionService_I)MeteoPortDetectionService.getInstance();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
	}
