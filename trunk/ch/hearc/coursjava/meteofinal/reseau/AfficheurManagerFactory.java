
package ch.hearc.coursjava.meteofinal.reseau;


public class AfficheurManagerFactory
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	public static AfficheurManager_I create() throws Exception
		{
		return  AfficheurManager.getInstance();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
