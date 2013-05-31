
package ch.hearc.coursjava.meteofinal.use.remote;

import javax.swing.UIManager;

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
		try
			{
			UIManager.setLookAndFeel("com.jtattoo.plaf.acryl.AcrylLookAndFeel");
			}
		catch (Exception e)
			{
			System.out.println("[UsePCLocal] Set look and feel failed !");
			}

		new PCCentral().run();

		RmiTools.afficherAllShareObject(RmiTools.PORT_RMI_DEFAUT);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
