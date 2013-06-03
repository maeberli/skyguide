package ch.hearc.coursjava.meteofinal.use.local;

import java.sql.Time;
import java.util.List;

import ch.hearc.coursjava.meteofinal.meteo.MeteoPortDetectionServiceFactory;
import ch.hearc.coursjava.meteofinal.meteo.MeteoPortDetectionService_I;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceFactory;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.meteo.MeteoService_I;
import ch.hearc.coursjava.meteofinal.meteo.exception.MeteoServiceException;
import ch.hearc.coursjava.meteofinal.meteo.listener.MeteoListener_I;
import ch.hearc.coursjava.meteofinal.meteo.listener.event.MeteoEvent;


public class UseMeteoServiceAffichageConsole {

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args) {
		try {
			main();
		} catch (MeteoServiceException e) {
			e.printStackTrace();
		}
	}

	public static void main() throws MeteoServiceException {
		
		MeteoPortDetectionService_I portDetectService = MeteoPortDetectionServiceFactory.create();
		
		
		List<String> listMeteoStations = portDetectService.findPortNameMeteo();
		MeteoService_I meteoService = null;
		
		for (String port : listMeteoStations) {
			// create meteoservices in list?
			System.out.println("Port list : " + port);
			System.exit(1);
			//meteoService = MeteoServiceFactory.create(port);
		}
		meteoService = MeteoServiceFactory.create("/dev/tty.SLAB_USBtoUART");

		meteoService.connect();

		meteoService.addMeteoListener(new MeteoListener_I() {

			@Override
			public void temperaturePerformed(MeteoEvent event) {
				System.out.println(event.getMeteoEventType().toString() + " : " + event.getValue() + " @ " + event.getTime() );
			}

			@Override
			public void pressionPerformed(MeteoEvent event) {
				System.out.println(event.getMeteoEventType().toString() + " : " + event.getValue() + " @ " + event.getTime() );
			}

			@Override
			public void altitudePerformed(MeteoEvent event) {
				System.out.println(event.getMeteoEventType().toString() + " : " + event.getValue() + " @ " + event.getTime() );
			}
		});

		scenario(meteoService);
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/**
	 * <pre>
	 * Exemple pour mettre � l'�preuve la logique de fonctionnement
	 * Checker dans la console que la logique verbeuse aficher est correcte
	 * </pre>
	 */
	private static void scenario(MeteoService_I meteoService)
			throws MeteoServiceException {
		MeteoServiceOptions meteoServiceOptions1 = new MeteoServiceOptions(800,
				1000, 1200);
		MeteoServiceOptions meteoServiceOptions2 = new MeteoServiceOptions(100,
				100, 100);

		meteoService.start(meteoServiceOptions1);
		sleep(10000);
		meteoService.disconnect();
		sleep(100);
		meteoService.stop();
		
		meteoService.connect();
		meteoService.start(meteoServiceOptions2);
		sleep(10000);
		meteoService.disconnect();
		sleep(100);
		meteoService.stop();
	}

	private static void sleep(long delayMS) {
		System.out.println("sleep main: " + delayMS);
		try {
			Thread.sleep(delayMS);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
