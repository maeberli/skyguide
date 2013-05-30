
package ch.hearc.coursjava.meteofinal.reseau;

import java.rmi.Remote;
import java.rmi.RemoteException;

import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.meteo.listener.event.MeteoEvent;

/**
 * <pre>
 * L'objectif est de ne pas poluer l'implementation du AfficheurService avec la moindre trace de RMI.
 * En effet, le AfficheurService n'est pas forcement utilisable en reseau, et son implementation doit etre independante de cette problematique.
 * </pre>
 */
public interface AfficheurServiceWrapper_I extends Remote
	{

	public void printPression(MeteoEvent event) throws RemoteException;

	public void printAltitude(MeteoEvent event) throws RemoteException;

	public void printTemperature(MeteoEvent event) throws RemoteException;

	public void setMeteoServiceOptions(MeteoServiceOptions meteoServiceOptions) throws RemoteException;

	public void removeTab() throws RemoteException;

	}
