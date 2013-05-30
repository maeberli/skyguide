
package ch.hearc.coursjava.api.reseau.rmi.horloge;

import java.rmi.RemoteException;
import java.util.Date;

import com.bilat.tools.reseau.rmi.RmiTools;
import com.bilat.tools.reseau.rmi.RmiURL;



public class Horloge implements Horloge_I
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public Horloge() throws RemoteException
		{
		RmiTools.shareObject(this, RMI_URL);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public String toString()
		{
			return new Date(System.currentTimeMillis()).toString();
		}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	@Override
	public Date getTime() throws RemoteException
		{
		return new Date(System.currentTimeMillis());
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	public static final String RMI_ID = Horloge.class.getSimpleName();
	private static final int RMI_PORT = RmiTools.PORT_RMI_DEFAUT;
	private static final RmiURL RMI_URL = new RmiURL(RMI_ID, RMI_PORT);

	}

