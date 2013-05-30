
package ch.hearc.coursjava.api.reseau.rmi.pc.horloge;

import java.net.InetAddress;
import java.rmi.RemoteException;

import ch.hearc.coursjava.api.reseau.rmi.horloge.Horloge;
import ch.hearc.coursjava.api.reseau.rmi.secret.Secret;
import ch.hearc.coursjava.api.reseau.rmi.secret.Secret_I;

import com.bilat.tools.reseau.rmi.RmiTools;
import com.bilat.tools.reseau.rmi.RmiURL;



public class PCHorloge
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public PCHorloge(int rmiPortDistant, String rmiIpDistant)
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
	 * Partage l'horloge
	 */
	private void serverSide()
		{
		try
			{
			Horloge horloge = new Horloge();
			RmiTools.afficherAllShareObject(RmiTools.PORT_RMI_DEFAUT);
			}
		catch (RemoteException e)
			{
			System.err.println("Horloge non partagée.");
			e.printStackTrace();
			}
		}

	/**
	 * PARTIE CLIENT
	 *
	 * Se connecte et récupère le secret
	 */
	private void clientSide()
		{
		Secret_I secret = connexionRemoteSecret();
		work(secret);
		}

	private void work(Secret_I secret)
		{
		try
			{
			System.out.println(secret.getSecretSafe().getSecret());
			}
		catch (RemoteException e)
			{
			System.err.println("Connexion perdue.");
			e.printStackTrace();
			}
		}

	private Secret_I connexionRemoteSecret()
		{
		try
			{
			InetAddress serveurInetAdress = InetAddress.getByName(rmiIpDistant);
			RmiURL rmiUrl = new RmiURL(Secret.RMI_ID, serveurInetAdress, rmiPortDistant);
			return (Secret_I) RmiTools.connectionRemoteObjectBloquant(rmiUrl);
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

