
package ch.hearc.coursjava.meteofinal.use.remote;

import javax.swing.UIManager;



public class UsePCLocal
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
			UIManager.setLookAndFeel("com.jtattoo.plaf.noire.NoireLookAndFeel");
			}
		catch (Exception e)
			{
			System.out.println("[UsePCLocal] Set look and feel failed !");
			}

		new JFrameLocal();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
