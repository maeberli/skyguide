
package ch.hearc.coursjava.api.io.serialization.demo;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Equipe implements Iterable<Homme> ,Serializable
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public Equipe(int n)
		{
		listeHommes = new ArrayList<Homme>(n);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public String toString()
		{
		StringBuilder builder = new StringBuilder();
		builder.append("Equipe [listeHommes=");
		builder.append(this.listeHommes);
		builder.append("]");
		return builder.toString();
		}

	public void add(Homme homme)
		{
		listeHommes.add(homme);
		}

	@Override
	public Iterator<Homme> iterator()
		{
		return this.listeHommes.iterator();
		}

	/*------------------------------*\
	|*				Is				*|
	\*------------------------------*/

	public boolean isEgal(Equipe equipe2)
		{
		if (this.listeHommes.size() != equipe2.listeHommes.size())
			{
			return false;
			}
		else
			{
			Iterator<Homme> it = this.iterator();

			for(Homme homme2:equipe2)
				{
				Homme homme1 = it.next();
				if (!homme1.isEgal(homme2)) { return false; }
				}
			return true;
			}
		}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	//Tools
	private List<Homme> listeHommes;
	}
