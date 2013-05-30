
package ch.hearc.coursjava.meteofinal.use.remote;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.rmi.RemoteException;

import ch.hearc.coursjava.meteofinal.afficheur.AffichageOptions;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceFactory;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.meteo.MeteoService_I;
import ch.hearc.coursjava.meteofinal.meteo.exception.MeteoServiceException;
import ch.hearc.coursjava.meteofinal.meteo.listener.MeteoListener_I;
import ch.hearc.coursjava.meteofinal.meteo.listener.event.MeteoEvent;
import ch.hearc.coursjava.meteofinal.reseau.AfficheurManager_I;
import ch.hearc.coursjava.meteofinal.reseau.AfficheurServiceWrapper_I;
import ch.hearc.coursjava.meteofinal.reseau.MeteoServiceWrapper_I;

import com.bilat.tools.reseau.rmi.IdTools;
import com.bilat.tools.reseau.rmi.RmiTools;
import com.bilat.tools.reseau.rmi.RmiURL;

public class PCLocal implements PC_I
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public PCLocal(MeteoServiceOptions meteoServiceOptions, String portCom, AffichageOptions affichageOptions, RmiURL rmiURLafficheurManager)
		{
		this.meteoServiceOptions = meteoServiceOptions;
		this.portCom = portCom;
		this.affichageOptions = affichageOptions;
		this.rmiURLafficheurManager = rmiURLafficheurManager;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public void run()
		{
		try
			{
			server(); // avant
			}
		catch (Exception e)
			{
			System.err.println("[PCLocal :  run : server : failed");
			e.printStackTrace();
			}

		try
			{
			client(); // après
			}
		catch (RemoteException e)
			{
			System.err.println("[PCLocal :  run : client : failed");
			e.printStackTrace();
			}
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------*\
	|*				server			*|
	\*------------------------------*/

	private void server() throws MeteoServiceException, RemoteException
		{
		// TODO Auto-generated method stub

		}

	/*------------------------------*\
	|*				client			*|
	\*------------------------------*/

	private void client() throws RemoteException
		{
		final MeteoService_I meteoService = MeteoServiceFactory.create(portCom);

		MeteoServiceWrapper_I meteoServiceWrapper = new MeteoServiceWrapper_I()
			{

				@Override
				public void stop() throws RemoteException
					{
					meteoService.stop();
					}

				@Override
				public void start(MeteoServiceOptions meteoServiceOptions) throws RemoteException
					{
					meteoService.start(meteoServiceOptions);
					}

				@Override
				public boolean isRunning() throws RemoteException
					{
					return meteoService.isRunning();
					}

				@Override
				public boolean isConnect() throws RemoteException
					{
					return meteoService.isConnect();
					}
			};

		String name = IdTools.createID("METEO_SERVICE_");
		RmiURL rmiUrlMeteoService = new RmiURL(name, RmiTools.PORT_RMI_DEFAUT);
		RmiTools.shareObject(meteoServiceWrapper, rmiUrlMeteoService);

		RmiURL rmiUrlAfficheurManager = null;
		try
			{
			rmiUrlAfficheurManager = new RmiURL("AFFICHEUR_MANAGER", InetAddress.getByName("localhost"), RmiTools.PORT_RMI_DEFAUT);
			}
		catch (UnknownHostException e)
			{
			}
		AfficheurManager_I afficheurManager = (AfficheurManager_I)RmiTools.connectionRemoteObjectBloquant(rmiURLafficheurManager);

		RmiURL rmiUrlAfficheurService = afficheurManager.createRemoteAfficheurService(affichageOptions, new RmiURL(name, RmiTools.getLocalHost(), RmiTools.PORT_RMI_DEFAUT));

		InetAddress localhost = null;
		try
			{
			localhost = InetAddress.getByName("localhost");
			}
		catch (UnknownHostException e)
			{
			}

		final AfficheurServiceWrapper_I afficheurService = (AfficheurServiceWrapper_I)RmiTools.connectionRemoteObjectBloquant(new RmiURL(rmiUrlAfficheurService.getIdObjectRMI(), localhost, RmiTools.PORT_RMI_DEFAUT));

		meteoService.addMeteoListener(new MeteoListener_I()
			{

				@Override
				public void temperaturePerformed(MeteoEvent event)
					{
					try
						{
						afficheurService.printTemperature(event);
						// afficheurServiceLocal.printTemperature(event);
						}
					catch (RemoteException e)
						{
						}
					}

				@Override
				public void pressionPerformed(MeteoEvent event)
					{
					try
						{
						afficheurService.printPression(event);
						// afficheurServiceLocal.printPression(event);
						}
					catch (RemoteException e)
						{
						}
					}

				@Override
				public void altitudePerformed(MeteoEvent event)
					{
					try
						{
						afficheurService.printAltitude(event);
						// afficheurServiceLocal.printAltitude(event);
						}
					catch (RemoteException e)
						{
						}
					}
			});

		try
			{
			meteoService.connect();
			}
		catch (MeteoServiceException e)
			{
			}
		meteoService.start(meteoServiceOptions);

		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Inputs
	private MeteoServiceOptions meteoServiceOptions;
	private String portCom;
	private AffichageOptions affichageOptions;
	private RmiURL rmiURLafficheurManager;

	// Tools
	}
