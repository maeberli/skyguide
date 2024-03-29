
package ch.hearc.coursjava.meteofinal.com.real;

import ch.hearc.coursjava.meteofinal.com.logique.MeteoService_A;
import ch.hearc.coursjava.meteofinal.com.real.com.ComConnexions_I;
import ch.hearc.coursjava.meteofinal.meteo.exception.MeteoServiceException;


/**
 * <pre>
 * Repousse les requ�tes sur comConnexion et transforme les Exceptions en MeteoServiceException
 * Aucune trace de javacomm ici, toute cette problematique est encapsuler dans l'objet implementant ComConnexions_I (separation des couches)
 * </pre>
 */
public class MeteoService extends MeteoService_A
	{

	public MeteoService(ComConnexions_I comConnexion)
		{
		super(comConnexion.getNamePort());

		this.comConnexion = comConnexion;
		}

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/**
	 * assynchrone, when data "value" received , must call altitudePerformed(value) of MeteoServiceCallback_I
	 */
	@Override protected void askAltitudeAsync() throws MeteoServiceException
		{
		try
			{
			comConnexion.askAltitudeAsync();
			}
		catch (Exception e)
			{
			throw new MeteoServiceException("[MeteoService] askAltitudeAsync failure", e);
			}
		}

	/**
	 * assynchrone, when data "value" received , must call pressionPerformed(value) of MeteoServiceCallback_I
	 */
	@Override protected void askPressionAsync() throws MeteoServiceException
		{
		try
			{
			comConnexion.askPressionAsync();
			}
		catch (Exception e)
			{
			throw new MeteoServiceException("[MeteoService] : askPressionAsync failure", e);
			}
		}

	/**
	 * assynchrone, when data "value" received , must call temperaturePerformed(value) of MeteoServiceCallback_I
	 */
	@Override protected void askTemperatureAsync() throws MeteoServiceException
		{
		try
			{
			comConnexion.askTemperatureAsync();
			}
		catch (Exception e)
			{
			throw new MeteoServiceException("[MeteoService] : askTemperatureAsync failure", e);
			}
		}

	@Override protected void connectHardware() throws MeteoServiceException
		{
		try
			{
			comConnexion.connect();
			}
		catch (Exception e)
			{
			throw new MeteoServiceException("[MeteoService] : connect failure", e);
			}

		}

	@Override protected void disconnectHardware() throws MeteoServiceException
		{
		try
			{
			comConnexion.disconnect();
			}
		catch (Exception e)
			{
			throw new MeteoServiceException("[MeteoService] : disconnect failure", e);
			}

		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private ComConnexions_I comConnexion;

	}
