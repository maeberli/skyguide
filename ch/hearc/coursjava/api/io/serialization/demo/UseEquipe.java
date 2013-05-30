
package ch.hearc.coursjava.api.io.serialization.demo;

import java.io.IOException;

import ch.hearc.coursjava.api.io.serialization.SerializerTools;

public class UseEquipe
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args) throws ClassNotFoundException, IOException
		{
		main();
		}

	public static void main() throws ClassNotFoundException, IOException
		{
		int n = 11;
		Equipe equipeSrc = new Equipe(n);
		for(int i = 1; i <= n; i++)
			{
			equipeSrc.add(new Homme("Name" + i, i * 10));
			}

		serializationFileBin(equipeSrc);
		serializationMemory(equipeSrc);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private static void serializationMemory(Equipe equipeSrc) throws IOException, ClassNotFoundException
		{
		byte[] tabByte = SerializerTools.saveMemory(equipeSrc);
		Equipe equipeClone = (Equipe)SerializerTools.loadMemory(tabByte);
		System.out.println(equipeClone.isEgal(equipeSrc));
		}

	private static void serializationFileBin(Equipe equipeSrc) throws ClassNotFoundException, IOException
		{
		String filename = Equipe.class.getSimpleName() + ".bin";
		SerializerTools.saveBin(filename, equipeSrc);
		Equipe equipeClone = (Equipe)SerializerTools.loadBin(filename);
		System.out.println(equipeClone.isEgal(equipeSrc));
		System.out.println(equipeSrc);
		System.out.println(equipeClone);
		}

	}
