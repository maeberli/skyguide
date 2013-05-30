
package ch.hearc.coursjava.api.reseau.rmi.pc.secret;



public class UsePCSecret
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/**
	 * <pre>
	 * Propri�t�s syst�mes n�cessaires au bon fonctionnement du programme :
	 *
	 * -DrmiPortDistant
	 * -DrmiIpDistant
	 * </pre>
	 */
	public static void main(String[] args)
		{
		main();
		}

	public static void main()
		{
		// R�cup�ration de propri�t�s syst�mes
		int rmiPortDistant = Integer.valueOf(System.getProperty(RMI_PORT_DISTANT));
		String rmiIpDistant = System.getProperty(RMI_IP_DISTANT);

		PCSecret pcSecret = new PCSecret(rmiPortDistant, rmiIpDistant);
		pcSecret.run();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private static final String RMI_PORT_DISTANT = "rmiPortDistant";
	private static final String RMI_IP_DISTANT = "rmiIpDistant";

	}

