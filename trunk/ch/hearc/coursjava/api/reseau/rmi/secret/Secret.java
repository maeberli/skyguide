
package ch.hearc.coursjava.api.reseau.rmi.secret;

import java.rmi.RemoteException;

import com.bilat.tools.reseau.rmi.RmiTools;
import com.bilat.tools.reseau.rmi.RmiURL;



public class Secret implements Secret_I
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public Secret(String secret) throws RemoteException
		{
		this.secret = new SecretSafe(secret);

		RmiTools.shareObject(this, RMI_URL);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public String toString()
		{
		return secret.toString();
		}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	@Override
	public SecretSafe getSecretSafe() throws RemoteException
		{
		return secret;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input/Output
	private SecretSafe secret;

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	// Tools
	public static final String RMI_ID = Secret.class.getSimpleName(); // Ne fonctionne que si on ne possède qu'une instance
	private static final int RMI_PORT = RmiTools.PORT_RMI_DEFAUT;
	private static final RmiURL RMI_URL = new RmiURL(RMI_ID, RMI_PORT);

	}

