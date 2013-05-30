
package ch.hearc.coursjava.meteofinal.afficheur.simulateur;

import ch.hearc.coursjava.meteofinal.afficheur.AfficheurService_I;
import ch.hearc.coursjava.meteofinal.afficheur.simulateur.moo.AfficheurServiceMOO;
import ch.hearc.coursjava.meteofinal.afficheur.simulateur.vue.JFrameAfficheurService;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.meteo.listener.event.MeteoEvent;
import ch.hearc.coursjava.meteofinal.reseau.MeteoServiceWrapper_I;

public class AfficheurServiceSimulateur implements AfficheurService_I
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	/**
	 * n = #data to print
	 */
	public AfficheurServiceSimulateur(String titre, int n, MeteoServiceWrapper_I meteoServiceRemote)
		{
		afficheurServiceMOO = new AfficheurServiceMOO(titre, n, meteoServiceRemote);
		meteoServiceOptions = new MeteoServiceOptions(1000, 1000, 1000, 1000);
		jFrameAfficheurService = new JFrameAfficheurService(afficheurServiceMOO, meteoServiceOptions);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override public void printAltitude(MeteoEvent event)
		{
		afficheurServiceMOO.printAltitude(event);
		jFrameAfficheurService.refresh();
		}

	@Override public void printTemperature(MeteoEvent event)
		{
		afficheurServiceMOO.printTemperature(event);
		jFrameAfficheurService.refresh();
		}

	@Override public void printPression(MeteoEvent event)
		{
		afficheurServiceMOO.printPression(event);
		jFrameAfficheurService.refresh();
		}

	@Override
	public void setMeteoServiceOptions(MeteoServiceOptions meteoServiceOptions)
		{
		jFrameAfficheurService.setMeteoServiceOptions(meteoServiceOptions);

		System.out.println("setMeteoServiceOptions !");
		System.out.println(meteoServiceOptions.toString());
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private AfficheurServiceMOO afficheurServiceMOO;
	private JFrameAfficheurService jFrameAfficheurService;

	private MeteoServiceOptions meteoServiceOptions;

	}
