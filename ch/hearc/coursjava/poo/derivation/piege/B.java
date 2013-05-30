
package ch.hearc.coursjava.poo.derivation.piege;

/**
 * Variations de code int�ressante :
 * - Mettre useM() en commentaire dans la classe B.
 * - Mettre m() en priv� dans la classe A et B.
 *
 * Question int�ressante : qu'affiche la classe useAB dans la variation ci-dessus ?
 */

public class B extends A
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public B()
		{
		// Rien.
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public void useM()
		{
		//super.useM();
		m();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void m()
		{
		System.out.println("B.m()");
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
	}

