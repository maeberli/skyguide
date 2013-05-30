
package ch.hearc.coursjava.meteofinal.afficheur;

import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.meteo.listener.event.MeteoEvent;


public interface AfficheurService_I
	{

	public void printPression(MeteoEvent event);

	public void printAltitude(MeteoEvent event);

	public void printTemperature(MeteoEvent event);

	public void setMeteoServiceOptions(MeteoServiceOptions meteoServiceOptions);

	public void removeTab();

	}
