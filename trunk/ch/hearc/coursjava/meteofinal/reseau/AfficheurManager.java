
package ch.hearc.coursjava.meteofinal.reseau;

import java.net.InetAddress;
import java.rmi.RemoteException;

import ch.hearc.coursjava.meteofinal.afficheur.AffichageOptions;
import ch.hearc.coursjava.meteofinal.afficheur.AfficheurFactory;
import ch.hearc.coursjava.meteofinal.afficheur.AfficheurService_I;
import ch.hearc.coursjava.meteofinal.use.remote.JDialogNetworkInterface;

import com.bilat.tools.reseau.rmi.IdTools;
import com.bilat.tools.reseau.rmi.RmiTools;
import com.bilat.tools.reseau.rmi.RmiURL;


/**
 * <pre>
 * One instance only (Singleton) on PC-Central
 * RMI-Shared
 * </pre>
 */
public class AfficheurManager implements AfficheurManager_I
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	private AfficheurManager() throws RemoteException, Exception
		{
		server();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/**
	 * Remote use
	 */
	@Override
	public RmiURL createRemoteAfficheurService(AffichageOptions affichageOptions, RmiURL meteoServiceRmiURL) throws RemoteException
		{
		System.out.println("Premier test !");
		System.out.println("Premier test !");
		System.out.println("Premier test !");

		MeteoServiceWrapper_I meteoServiceRemote = null;
			// client
			{
			// TODO connecion to meteoService on PC-Local with meteoServiceRmiURL

			/* Matthieu */

			meteoServiceRemote = (MeteoServiceWrapper_I)RmiTools.connectionRemoteObjectBloquant(meteoServiceRmiURL);

			/* END */

			}

			// server
			{
			AfficheurService_I afficheurService = createAfficheurService(affichageOptions, meteoServiceRemote);
			// TODO share afficheurService

			/* Matthieu */
			// Partager l'instance afficheurService avec le client, appelant la méthode.
			// On créer un objet RmiUrl, avec un id, pour l'objet afficheurService.
			RmiURL afficheurServicermiURL = null;
			try
				{
				afficheurServicermiURL = rmiUrl();
				}
			catch (Exception e)
				{
				}
			// On partage l'objet avec le client.

			RmiTools.shareObject(new AfficheurServiceWrapper(afficheurService), afficheurServicermiURL);

			return afficheurServicermiURL; // Retourner le RMI-ID pour une connection distante sur le serveur d'affichage
			/* END */
			}
		}

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	public static synchronized AfficheurManager_I getInstance() throws RemoteException, Exception
		{
		if (INSTANCE == null)
			{
			INSTANCE = new AfficheurManager();
			}

		return INSTANCE;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private AfficheurService_I createAfficheurService(AffichageOptions affichageOptions, MeteoServiceWrapper_I meteoServiceRemote)
		{
		// TODO
		/* Matthieu */
		System.out.println("Appel Rmi du client: createAfficheurService");

		return AfficheurFactory.create(affichageOptions, meteoServiceRemote);


		/* END */
		}

	private void server() throws Exception
		{
		// TODO share this
		/* Matthieu */
		JDialogNetworkInterface dialogNetworkInterface = new JDialogNetworkInterface();
		localhost = dialogNetworkInterface.getInetAddressSelected();
		// On partage le serveur.

		// AFFICHEUR_MANAGER doit être connu des stations météo (client).
		// Même chose pour l'adresse IP du serveur.

		// RmiURL rmiUrlServer = new RmiURL("AFFICHEUR_MANAGER", InetAddress.getLocalHost(), RmiTools.PORT_RMI_DEFAUT);
		RmiURL rmiUrlServer = new RmiURL("AFFICHEUR_MANAGER", localhost, RmiTools.PORT_RMI_DEFAUT);
		// Partage de l'objet.
		RmiTools.shareObject(this, rmiUrlServer);
		/* END */
		}

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	/**
	 * Thread Safe
	 */
	private static RmiURL rmiUrl() throws Exception
		{
		String id = IdTools.createID(PREFIXE);

		/* Matthieu */
		// RmiURL rmiUrl = new RmiURL(id, InetAddress.getLocalHost(), RmiTools.PORT_RMI_DEFAUT);
		RmiURL rmiUrl = new RmiURL(id, localhost, RmiTools.PORT_RMI_DEFAUT);

		return rmiUrl;
		/* END */
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	// Tools

	private static AfficheurManager_I INSTANCE = null;

	private static InetAddress localhost;

	// Tools final
	private static final String PREFIXE = "AFFICHEUR_SERVICE_";

	public static final String RMI_ID = PREFIXE;

	}
