package ch.hearc.coursjava.meteofinal.com.real.com;

import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import ch.hearc.coursjava.meteofinal.com.real.com.trame.TrameDecoder;
import ch.hearc.coursjava.meteofinal.com.real.com.trame.TrameEncoder;
import ch.hearc.coursjava.meteofinal.meteo.MeteoPortDetectionService_I;
import ch.hearc.coursjava.meteofinal.meteo.exception.MeteoServiceException;


public class MeteoPortDetectionService implements MeteoPortDetectionService_I {

	private MeteoPortDetectionService() {
	}

	public static synchronized MeteoPortDetectionService_I getInstance() {
		if (INSTANCE == null) {
			INSTANCE = new MeteoPortDetectionService();
		}

		return INSTANCE;
	}

	@Override
	public List<String> findPortNameMeteo() {
		return findPortNameMeteo(null);
	}

	@Override
	public List<String> findPortNameMeteo(List<String> listPortExcluded) {
		List<String> listMeteoPorts = new ArrayList<String>();
		List<String> listPortsSerie = findPortSerie();
		
		if (listPortExcluded != null) {
			listPortsSerie.removeAll(listPortExcluded);
		}
		
		for (String port : listPortsSerie) {
			if (isStationMeteoAvailable(port)) {
				listMeteoPorts.add(port);
			}
		}
		return listMeteoPorts;
	}

	@Override
	public List<String> findPortSerie() {

		List<String> list = new ArrayList<String>();

		Enumeration portList = CommPortIdentifier.getPortIdentifiers();

		while (portList.hasMoreElements()) {
			
			CommPortIdentifier portId = (CommPortIdentifier) portList
					.nextElement();
			if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
				if (!portId.getName().contains("Bluetooth") && !portId.getName().contains("cu."))
				{
					list.add(portId.getName());
				}
				portMap.put(portId.getName(), false);
			}
		}

		list.add("test1");
		list.add("test2");
		list.add("test3");
		list.add("test4");
		return list;
	}

	@Override
	public boolean isStationMeteoAvailable(final String portName) {
		
		sendTrameToSerialPort(portName);
		return portMap.get(portName);
	}
	
	private void sendTrameToSerialPort(final String portName)
	{
		try {
			portId = CommPortIdentifier.getPortIdentifier(portName);
			serialPort = (SerialPort) portId.open("MS" + portName, 1000);
			
			comOption.applyTo(serialPort);
			serialPort.notifyOnDataAvailable(true);

			os = serialPort.getOutputStream();
			reader = new BufferedReader(new InputStreamReader(
					serialPort.getInputStream()));
			os.write(TrameEncoder.coder("010000"));
			
			serialPort.addEventListener(new SerialPortEventListener() {

				@Override
				public void serialEvent(SerialPortEvent event) {
					switch (event.getEventType()) {
					case SerialPortEvent.DATA_AVAILABLE:
						try {
							TrameDecoder.valeur(reader.readLine());
							System.out.println(portName + " is MS");
							portMap.put(portName, true);
						} catch (Exception e) {
							portMap.put(portName, false);
						}
						break;
					}
				}
			});
			System.out.println("Sleeping in send Trame with " + portName);
			Thread.sleep(300);

		} catch (Exception e) {
			System.err.println(portName + " is not SM! E : " + 
					e.getClass());
		}
		finally
		{
			if(serialPort != null) {
			serialPort.notifyOnDataAvailable(false);
			serialPort.removeEventListener();
			serialPort.close();
			}
		}
	}

	// Tools
	private static MeteoPortDetectionService_I INSTANCE = null;
	
	SerialPort serialPort = null;
	ComOption comOption = new ComOption();
	OutputStream os = null;
	BufferedReader reader = null;
	CommPortIdentifier portId = null;
	
	private static Map<String, Boolean> portMap = new HashMap<String, Boolean>(); // String = Portname, Boolean = is a Meteo Station

	//Inputs
	private List<String> listPortExcluded;
}
