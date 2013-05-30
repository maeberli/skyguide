
package ch.hearc.coursjava.meteofinal.com.real.com;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import ch.hearc.coursjava.meteofinal.com.real.com.trame.TrameEncoder;
import ch.hearc.coursjava.meteofinal.meteo.MeteoPortDetectionService_I;
import ch.hearc.coursjava.meteofinal.meteo.exception.MeteoServiceException;

public class MeteoPortDetectionService implements MeteoPortDetectionService_I
	{

	private MeteoPortDetectionService()
		{

		}

	public static synchronized MeteoPortDetectionService_I getInstance()
		{
		if (INSTANCE == null)
			{
			INSTANCE = new MeteoPortDetectionService();
			}

		return INSTANCE;
		}

	@Override
	public List<String> findPortNameMeteo()
		{
		List<String> listMeteoPorts = new ArrayList<String>();
		for(String port:findPortSerie())
			{
			if (isStationMeteoAvailable(port))
				{
				listMeteoPorts.add(port);
				}
			}
		return listMeteoPorts;
		}

	@Override
	public List<String> findPortNameMeteo(List<String> listPortExcluded)
		{
		// TODO Auto-generated method stub
		return null;
		}

	@Override
	public List<String> findPortSerie()
		{

		List<String> list = new ArrayList<String>();

		Enumeration portList = CommPortIdentifier.getPortIdentifiers();

		while(portList.hasMoreElements())
			{
			CommPortIdentifier portId = (CommPortIdentifier)portList.nextElement();
			if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL)
				{
				// ping card?
				list.add(portId.getName());
				}
			}

		return list;
		}

	@Override
	public boolean isStationMeteoAvailable(String portName)
		{
		SerialPort serialPort = null;
		ComOption comOption = new ComOption();
		OutputStream os = null;
		BufferedReader reader = null;
		CommPortIdentifier portId = null;
		try
			{
			portId = CommPortIdentifier.getPortIdentifier(portName);
			}
		catch (NoSuchPortException e1)
			{
			// TODO Auto-generated catch block
			e1.printStackTrace();
			}

		try
			{
			serialPort = (SerialPort)portId.open("MS" + portName, 1000);
			comOption.applyTo(serialPort);
			serialPort.notifyOnDataAvailable(true);

			os = serialPort.getOutputStream();
			reader = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
			os.write(TrameEncoder.coder("010000"));
			serialPort.addEventListener(new SerialPortEventListener()
				{

					@Override
					public void serialEvent(SerialPortEvent event)
						{
						switch(event.getEventType())
							{
							case SerialPortEvent.DATA_AVAILABLE:
								System.out.println("Cool");
								break;
							}
						}
				});

			}
		catch (Exception e)
			{
			try
				{
				throw new MeteoServiceException(e.getClass().getName());
				}
			catch (MeteoServiceException e1)
				{
				// TODO Auto-generated catch block
				e1.printStackTrace();
				}
			}
		try
			{
			Thread.sleep(1000);
			}
		catch (InterruptedException e)
			{
			// TODO Auto-generated catch block
			e.printStackTrace();
			}
		serialPort.notifyOnDataAvailable(false);
		serialPort.removeEventListener();
		serialPort.close();
		return true;
		}

	// Tools
	private static MeteoPortDetectionService_I INSTANCE = null;
	private List<String> listPortExcluded;

	}
