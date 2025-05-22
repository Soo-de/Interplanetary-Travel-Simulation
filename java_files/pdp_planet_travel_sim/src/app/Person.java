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
/* END OF IMPORTS */

public class Person implements ITimeListener
{
	private String		name;			// TO SET THE NAME THAT WE GET FROM THE FILE
	private String		currentVehicle;	// TO SET THE CURRENT VEHICLE THAT WE GET FROM THE FILE
	private int			age;			// TO SET THE AGE THAT WE GET FROM THE FILE
	private int			hoursLeftToLive;// TO SET THE LIFETIME THAT WE GET FROM THE FILE

	/* CONSTRUCTERS */
	
	public Person(String name, int age, int hoursLeftToLive ,String currentVehicle)
	{
		this.setName(name);
		this.setAge(age);
		this.setHoursLeftToLive(hoursLeftToLive);
		this.setCurrentVehicle(currentVehicle);
		Time.addListener(this);
	}
	
	/* END OF CONSTRUCTERS */
	
	/* SETTER METHODS */
	
	private void	setName(String name)
	{
		this.name = name;
	}
	private void	setCurrentVehicle(String currentVehicle)
	{
		this.currentVehicle = currentVehicle;
	}
	private void	setAge (int age)
	{
		this.age = age;
	}
	private void	setHoursLeftToLive(int hours)
	{
		if (hours < 0) // TO PREVENT FROM ERORS SET THE LIFETIME "0"
		{
			hoursLeftToLive = 0;
		}
		else
		{
			this.hoursLeftToLive = hours;
		}	
	}
	
	/* END OF SETTER METHODS */
	
	/* GETTER METHODS */
	
	public String	getCurrentVehicle()
	{
		return (currentVehicle);
	}
	public int		getHoursLeftToLive()
	{
		return (hoursLeftToLive);
	}
	public String	getName()
	{
		return (name);
	}
	public int		getAge()
	{
		return (age);
	}
	/* END OF GETTER METHODS */
	
	/* METHODS */
	
	private void	reduceHoursLeftToLive()
	{
		if (isAlive())
		{
			hoursLeftToLive--;
		}
	}
	
	public boolean	isAlive()
	{
		if (hoursLeftToLive == 0)
		{
			// IF THE PERSON IS NOT ALIVE NO NEED TO BE RELATED WITH THE TIME ANYMORE
			Time.removeListener(this);
			return (false);
		}
		else
			return (true);
	}
	
	public boolean	isValid(List<SpaceShip> ships)// TO FIND THE SHIP THAT PERSON CURRENTLY IS IN
	{
		// IF THERE ANY MATCHED PLANET NAME RETURN TRUE TO ADD THE PERSON UPDATED LIST
		return (ships.stream()
	           .anyMatch(ship -> ship.getName().equalsIgnoreCase(this.currentVehicle)));
		
	}
	
	@Override
	public void		onTimePass()
	{
		// TRIGGER THE FUNCTIONS THAT RELATED TO THE TIME
		reduceHoursLeftToLive();

	}
}
