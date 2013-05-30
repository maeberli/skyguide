
package ch.hearc.coursjava.api.reseau.rmi.secret;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;




public class SecretSafe implements Serializable
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public SecretSafe(String secret)
		{
		this.secret = secret;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public String toString()
		{
		StringBuilder builder = new StringBuilder();
		builder.append("SecretSafe [secret=");
		builder.append(this.secret);
		builder.append("]");
		return builder.toString();
		}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	public String getSecret()
		{
		return this.secret;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void writeObject(ObjectOutputStream oos) throws IOException
		{
		System.out.println("SecretSafe:SerialisationCustom");
		oos.writeObject(crypter(this.secret));
		}

	private void readObject(ObjectInputStream ois) throws Exception
		{
		System.out.println("SecretSafe:DéserialisationCustom");
		this.secret = decrypter((String) ois.readObject());
		}

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	private static String crypter(String secret)
		{
		// TODO: Faire du vrai cryptage
		return secret + "xxx";
		}

	private static String decrypter(String secretCrypte)
		{
		// TODO: Faire du vrai décryptage
		return secretCrypte.substring(0, secretCrypte.length() - 3);
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input / Output
	private String secret;

	}

