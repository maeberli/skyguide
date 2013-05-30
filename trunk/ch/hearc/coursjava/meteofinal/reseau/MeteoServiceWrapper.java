
package ch.hearc.coursjava.meteofinal.reseau;

import java.rmi.RemoteException;

import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.meteo.MeteoService_I;

public class MeteoServiceWrapper implements MeteoServiceWrapper_I
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public MeteoServiceWrapper(MeteoService_I meteoService)
		{
		this.meteoService = meteoService;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override public void start(MeteoServiceOptions meteoServiceOptions) throws RemoteException
		{
		meteoService.start(meteoServiceOptions);
		}

	@Override public void stop() throws RemoteException
		{
		meteoService.stop();
		}

	@Override public boolean isRunning() throws RemoteException
		{
		return meteoService.isRunning();
		}

	@Override public boolean isConnect() throws RemoteException
		{
		return meteoService.isConnect();
		}

	@Override
	public void setMeteoServiceOptions(MeteoServiceOptions meteoServiceOptions) throws RemoteException
		{
		// Rien parce que j'utilise une classe interne anonyme !
		}

	@Override
	public void exitClient() throws RemoteException
		{
		// Rien parce que j'utilise une classe internet anonyme !
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Inputs
	private MeteoService_I meteoService;
	}
