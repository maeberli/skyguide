
package ch.hearc.coursjava.meteofinal.use.local;

import ch.hearc.coursjava.meteofinal.afficheur.AffichageOptions;
import ch.hearc.coursjava.meteofinal.afficheur.AfficheurFactory;
import ch.hearc.coursjava.meteofinal.afficheur.AfficheurService_I;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceFactory;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.meteo.MeteoService_I;
import ch.hearc.coursjava.meteofinal.meteo.exception.MeteoServiceException;
import ch.hearc.coursjava.meteofinal.meteo.listener.MeteoAdapter;
import ch.hearc.coursjava.meteofinal.meteo.listener.event.MeteoEvent;
import ch.hearc.coursjava.meteofinal.reseau.MeteoServiceWrapper;
import ch.hearc.coursjava.meteofinal.reseau.MeteoServiceWrapper_I;

import com.bilat.tools.reseau.rmi.RmiTools;

public class UseMeteoServiceAffichageGui
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args) throws MeteoServiceException
		{
		//main();
		}

	public static void main() throws MeteoServiceException
		{
		String portName = "COM1";
		String titre = RmiTools.getLocalHost() + " " + portName;

		MeteoService_I meteoService = MeteoServiceFactory.create(portName);

		MeteoServiceWrapper_I meteoServiceWrapperForRemoteAccess = new MeteoServiceWrapper(meteoService);

		AffichageOptions affichageOptions = new AffichageOptions(3, titre);
		final AfficheurService_I afficheurService = AfficheurFactory.create(affichageOptions, meteoServiceWrapperForRemoteAccess);

		meteoService.connect();

		// Liason entre les deux services d'affichage : MeteoService_I et AfficheurService_I
		meteoService.addMeteoListener(new MeteoAdapter()
			{

				@Override public void temperaturePerformed(MeteoEvent event)
					{
					afficheurService.printTemperature(event);
					afficheurService.printAltitude(event);
					afficheurService.printPression(event);
					}

			});

		MeteoServiceOptions meteoServiceOptions = new MeteoServiceOptions(800, 1000, 1200);
		meteoService.start(meteoServiceOptions);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
