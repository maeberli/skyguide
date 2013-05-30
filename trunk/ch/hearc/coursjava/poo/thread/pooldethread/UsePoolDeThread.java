
package ch.hearc.coursjava.poo.thread.pooldethread;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;



public class UsePoolDeThread
	{
	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args)
		{
		main();
		}

	public static void main()
		{
		hello();
		hello2();
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/



	private static void hello2()
		{
		Callable<Long> callable = new Callable<Long>()
			{
				@Override
				public Long call() throws Exception
					{
					Long out = System.currentTimeMillis();
					System.out.println(Thread.currentThread().getName());
					return out;
					}
			};

		Future<Long> future = executorService.submit(callable);

		try
			{
			Long result = future.get();//Equivalent join du thread, bloquant
			System.out.println(result);
			}
		catch (Exception e)
			{
			e.printStackTrace();
			}

		}

	private static void hello()
		{
		executorService.submit(new Callable<Void>()
			{

				@Override
				public Void call() throws Exception
					{
					System.out.println("Hello " + Thread.currentThread().getName());
					return null;
					}
			});
		}

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	public static final ExecutorService executorService = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());

	}

