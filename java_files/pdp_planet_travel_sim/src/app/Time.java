/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.04.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/


package app;

/* IMPORTS */
import java.util.List;
import java.util.ArrayList;
/* END OF IMPORTS */

public class Time
{
	private static Long 				globalTime = 0L;				// GLOBAL TIME
	private static List<ITimeListener>	listeners = new ArrayList<>();	// OBJECTS THAT RELATED TO TIME 
	
	
	/* GETTER METHODS */
	
	public static Long					getGlobalTime()
	{
		return (globalTime);
	}
	
	public static List<ITimeListener>	getListenersList()
	{
		return (listeners);
	}
	
	/* END OF GETTER METHODS */
	
	/* METHODS */
	
	public synchronized static void	advanceTime()
	{
		 // TO PREVENT FROM ConcurrentModificationException
		List<ITimeListener> listenersCopy = new ArrayList<>(listeners);
		
		globalTime += 1L;
		if (listeners != null)
		{
			for (ITimeListener listener : listenersCopy)
			{
				listener.onTimePass(); // TRIGGER ALL THE FUNCTIONS FOR LISTENER
			}
		}
	}
	
	public static void				addListener(ITimeListener listenerObject)
	{
		listeners.add(listenerObject);
	}
	
	public static void				removeListener(ITimeListener listenerObject)
	{
		listeners.remove(listenerObject);
	}
}
