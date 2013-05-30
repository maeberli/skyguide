
package ch.hearc.coursjava.api.reseau.rmi.secret;

import java.rmi.Remote;
import java.rmi.RemoteException;



public interface Secret_I extends Remote
	{
	public SecretSafe getSecretSafe() throws RemoteException;
	}

