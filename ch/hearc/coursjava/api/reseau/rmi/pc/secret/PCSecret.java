
package ch.hearc.coursjava.api.reseau.rmi.pc.secret;

import java.net.InetAddress;
import java.rmi.RemoteException;

import ch.hearc.coursjava.api.reseau.rmi.horloge.Horloge;
import ch.hearc.coursjava.api.reseau.rmi.horloge.Horloge_I;
import ch.hearc.coursjava.api.reseau.rmi.secret.Secret;

import com.bilat.tools.reseau.rmi.RmiTools;
import com.bilat.tools.reseau.rmi.RmiURL;



public class PCSecret
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public PCSecret(int rmiPortDistant, String rmiIpDistant)
		{
		this.rmiPortDistant = rmiPortDistant;
		this.rmiIpDistant = rmiIpDistant;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public void run()
		{
		/*
		 * Attention, l'ordre est important !
		 * clientSide tente de se connecter avec une boucle infinie
		 * il faut donc lancer serverSide avant clientSide,
		 * sinon il ne sera jamais exécuté
		 */
		serverSide();
		clientSide();
		}


	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/**
	 * PARTIE SERVEUR
	 *
	 * Partage le secret
	 */
	private void serverSide()
		{
		try
			{
			Secret secret = new Secret("Mon secret");
			RmiTools.afficherAllShareObject(RmiTools.PORT_RMI_DEFAUT);
			}
		catch (RemoteException e)
			{
			System.err.println("Secret non partagé.");
			e.printStackTrace();
			}
		}

	/**
	 * PARTIE CLIENT
	 *
	 * Se connecte et récupère l'horloge
	 */
	private void clientSide()
		{
		Horloge_I horloge = connexionRemoteHorloge();
		work(horloge);
		}

	private void work(Horloge_I horloge)
		{
		try
			{
			System.out.println(horloge.getTime().toString());

			new JFrameHorloge(horloge);
			}
		catch (RemoteException e)
			{
			System.err.println("Connexion perdue.");
			e.printStackTrace();
			}
		}

	private Horloge_I connexionRemoteHorloge()
		{
		try
			{
			InetAddress serveurInetAdress = InetAddress.getByName(rmiIpDistant);
			RmiURL rmiUrl = new RmiURL(Horloge.RMI_ID, serveurInetAdress, rmiPortDistant);
			return (Horloge_I) RmiTools.connectionRemoteObjectBloquant(rmiUrl);
			}
		catch (Exception e)
			{
			System.err.println("Connexion impossible.");
			e.printStackTrace();
			return null;
			}
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private int rmiPortDistant;
	private String rmiIpDistant;

	}

