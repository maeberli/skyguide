
package ch.hearc.coursjava.api.reseau.rmi.pc.horloge;



public class UsePCHorloge
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/**
	 * <pre>
	 * Propriétés systèmes nécessaires au bon fonctionnement du programme :
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
		// Récupération de propriétés systèmes
		int rmiPortDistant = Integer.valueOf(System.getProperty(RMI_PORT_DISTANT));
		String rmiIpDistant = System.getProperty(RMI_IP_DISTANT);

		PCHorloge pcHorloge = new PCHorloge(rmiPortDistant, rmiIpDistant);
		pcHorloge.run();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private static final String RMI_PORT_DISTANT = "rmiPortDistant";
	private static final String RMI_IP_DISTANT = "rmiIpDistant";

	}

