
package ch.hearc.coursjava.gui.controlprincipal;


/**
 *
 * @author Diego
 *
 */
public class UseFrameCP
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
		int n = 10;//Integer.valueOf(System.getProperty("n"));
		assert(n >= 1 && n<= 100);
		new JFrameCP(n);
		}
	}

