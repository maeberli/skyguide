
package ch.hearc.coursjava.meteofinal.reseau;

import java.rmi.RemoteException;

import ch.hearc.coursjava.meteofinal.afficheur.AfficheurService_I;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.meteo.listener.event.MeteoEvent;

public class AfficheurServiceWrapper implements AfficheurServiceWrapper_I
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public AfficheurServiceWrapper(AfficheurService_I afficheurService)
		{
		this.afficheurService = afficheurService;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override public void printPression(MeteoEvent event) throws RemoteException
		{
		afficheurService.printPression(event);
		}

	@Override public void printAltitude(MeteoEvent event) throws RemoteException
		{
		afficheurService.printAltitude(event);
		}

	@Override public void printTemperature(MeteoEvent event) throws RemoteException
		{
		afficheurService.printTemperature(event);
		}

	@Override
	public void setMeteoServiceOptions(MeteoServiceOptions meteoServiceOptions) throws RemoteException
		{
		afficheurService.setMeteoServiceOptions(meteoServiceOptions);
		}

	@Override
	public void removeTab() throws RemoteException
		{
		afficheurService.removeTab();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private AfficheurService_I afficheurService;
	}
