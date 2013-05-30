
package ch.hearc.coursjava.poo.derivation.animal;

public class Chat extends Mamifere
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public Chat(String nom)
		{
		super(nom, TEMPERATURE_SANG);
		}

	public Chat(Chat source)
		{
		super(source);

		// Rien d'autre � cloner car pas d'attributs sp�cifiques � la classe chat.
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public String manger()
		{
		return "Souris";
		}

	@Override
	public String nomClasse()
		{
		return super.nomClasse() + " " + Chat.class.getSimpleName();
		}

	@Override
	public Chat cloneOf()
		{
		return new Chat(this);
		}

	/*------------------------------*\
	|*				Is				*|
	\*------------------------------*/

	public boolean isEgal(Chat chat2)
		{
		return equals(chat2);
		}

	@Override
	public boolean equals(Object objet)
		{
		if (objet instanceof Chat)
			{
			return super.equals(objet);
			}
		else
			{
			return false;
			}
		}

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	/**
	 * Tous les chats instanci�s apr�s l'appel de cette m�thode auront la nouvelle temp�rature.
	 * Les chats instanci�s avant l'appel de cette m�thode auront l'ancienne temp�rature.
	 */
	public static void setTemperatureSang(int temperature)
		{
		Chat.TEMPERATURE_SANG = temperature;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	private static int TEMPERATURE_SANG = 36;

	}
