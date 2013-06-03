
package ch.hearc.coursjava.meteofinal.afficheur.real;

import ch.hearc.coursjava.meteofinal.afficheur.AffichageOptions;
import ch.hearc.coursjava.meteofinal.afficheur.AfficheurService_I;
import ch.hearc.coursjava.meteofinal.meteo.MeteoServiceOptions;
import ch.hearc.coursjava.meteofinal.meteo.listener.event.MeteoEvent;
import ch.hearc.coursjava.meteofinal.reseau.MeteoServiceWrapper_I;
import ch.hearc.coursjava.meteofinal.use.remote.PCCentral;
import ch.hearc.coursjava.meteofinal.use.remote.PanelStationMeteo;

public class AfficheurService implements AfficheurService_I
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public AfficheurService(AffichageOptions affichageOptions, MeteoServiceWrapper_I meteoServiceRemote)
		{
		this.affichageOptions = affichageOptions;
		this.meteoServiceRemote = meteoServiceRemote;

		this.panelStationMeteo = PCCentral.frameGraphe.openNewTab(meteoServiceRemote);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override public void printPression(MeteoEvent event)
		{
		this.panelStationMeteo.getPanelGraphePression().getGraphe().addToDataset(event.getTime(), event.getValue());
		this.panelStationMeteo.getPanelGraphePression().getGraphe().toAffichage();
		this.panelStationMeteo.updateAffichageOptions();
		this.panelStationMeteo.getPanelGraphePression().repaint();
		}

	@Override public void printAltitude(MeteoEvent event)
		{
		this.panelStationMeteo.getPanelGrapheAltitude().getGraphe().addToDataset(event.getTime(), event.getValue());
		this.panelStationMeteo.getPanelGrapheAltitude().getGraphe().toAffichage();
		this.panelStationMeteo.updateAffichageOptions();
		this.panelStationMeteo.getPanelGrapheAltitude().repaint();
		}

	@Override public void printTemperature(MeteoEvent event)
		{
		this.panelStationMeteo.getPanelGrapheTemperature().getGraphe().addToDataset(event.getTime(), event.getValue());
		this.panelStationMeteo.getPanelGrapheTemperature().getGraphe().toAffichage();
		this.panelStationMeteo.updateAffichageOptions();
		this.panelStationMeteo.getPanelGrapheTemperature().repaint();
		}

	@Override
	public void setMeteoServiceOptions(MeteoServiceOptions meteoServiceOptions)
		{
		this.panelStationMeteo.setMeteoServiceOptions(meteoServiceOptions);
		}

	@Override
	public void removeTab()
		{
		PCCentral.frameGraphe.removeStationMeteo(panelStationMeteo);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private AffichageOptions affichageOptions;
	private MeteoServiceWrapper_I meteoServiceRemote;

	private PanelStationMeteo panelStationMeteo;
	}
