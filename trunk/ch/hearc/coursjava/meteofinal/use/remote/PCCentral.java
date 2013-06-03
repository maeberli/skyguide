
package ch.hearc.coursjava.meteofinal.use.remote;

import ch.hearc.coursjava.meteofinal.reseau.AfficheurManagerFactory;
import ch.hearc.coursjava.meteofinal.reseau.AfficheurManager_I;

public class PCCentral implements PC_I
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public PCCentral()
		{
		// rien
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override public void run()
		{
		try
			{
			server();
			}
		catch (Exception e)
			{
			System.err.println("ERREUR: " + e);

			System.exit(-1);
			}
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void server() throws Exception
		{
		// TODO Auto-generated method stub
		frameGraphe = new JFrameCentrale();

		AfficheurManager_I afficheurManager = AfficheurManagerFactory.create();
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Permet d'ajouter des AfficheurService.
	public static JFrameCentrale frameGraphe;
	}
