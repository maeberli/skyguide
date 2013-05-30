
package ch.hearc.coursjava.meteofinal.use.remote;

import com.bilat.tools.reseau.rmi.RmiTools;

public class UsePCCentral
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args)
		{
		main();
		}

	public static void main()
		{
		new PCCentral().run();

		RmiTools.afficherAllShareObject(RmiTools.PORT_RMI_DEFAUT);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
