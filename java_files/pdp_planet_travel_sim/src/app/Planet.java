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
/*END OF IMPORTS */

public class Planet implements ITimeListener
{
	private String			name;		// TO SET NAME THAT WE GET FROM THE FILE
	private int				hoursOfADay;// TO SET THE HOURS OF A DAY THAT WE GET FROM THE FILE
	private MyLocalTime		currentDate;// TO SET THE CURRENT DATE THAT WE GET FROM THE FILE
	private int				currentHour;// TO SET THE CURRENT HOUR THAT WE GET FROM THE FILE
	private int				population;	// TO SET THE POPULATION OF THE PLANET
	private List<SpaceShip>	ships;		// TO CALCULATE HOW MANY PEOPLE IS CURRENTLY LOCATED IN THE PLANET
	
	/* CONSTRUCTER */
	
	public Planet(String name, int hoursOfADay, MyLocalTime currentDate)
	{
		setName(name);
		setHoursOfADay(hoursOfADay);
		setCurrentDate(currentDate);
		setCurrentHour();
		setPopulation();
		Time.addListener(this);
	}
	
	/*END OF CONSTRUCTER*/
	
	/* SETTER METHODS */
	
	private void	setName(String name)
	{
		this.name = name;
	}
	private void	setHoursOfADay(int hour)
	{
		this.hoursOfADay = hour;
	}
	private void	setCurrentDate(MyLocalTime date)
	{
		this.currentDate = date;
	}
	private void	setCurrentHour()
	{
		this.currentHour = 0;
	}
	private void	setPopulation()
	{
		this.population = 0;
	}
	public void		setSpaceShipList(List<SpaceShip> ships)
	{
		this.ships = ships;
	}
	
	/* END OF SETTER METHODS */

	/* GETTER METHODS */
	
	public String		getName()
	{
		return (name);
	}
	public MyLocalTime	getCurrentDate()
	{
		return (currentDate);
		
	}
	public Integer 		getHoursOfADay()
	{
		return (hoursOfADay);
	}
	public int	 		getPopulation()
	{
		return (population);
	}
	
	
	/* END OF GETTER METHODS */
	
	/* METHODS */
	
	private void	updateCurrentHour()
	{
		// CALCULATE CURRENT HOUR
		this.currentHour = (int) (Time.getGlobalTime() % this.hoursOfADay);
		
		if (this.currentHour == 0)
		{
			// ADVANCE THE A DAY IF THE DAY IS ENDED
			this.currentDate.advanceDay();
		}
	}
	
	public void		updatePopulation()
	{	
		// START SHIP STREAM
		// IF CURRENT PLANET NAME AND THIS.NAME ARE MATCHED AND THE STATE OF THE SHIP IS "BEKLİYOR"
		// OR
		// IF DESTINATION PLANET NAME AND THIS.NAME ARE MATCHED AND THE STATE OF THE SHIP IS "VARDI"
		// CONVERT AN OBJECT STREAM TO AN INT STREAM 
		// SUM TO ADD THE POPULATION
		this.population = this.ships.stream()
						.filter(s -> (s.getCurrentPlanetName().equalsIgnoreCase(this.name) && s.getState().equals("Bekliyor"))
						|| (s.getDestPlanetName().equalsIgnoreCase(this.name) && s.getState().equals("Vardı")) )
						.mapToInt(SpaceShip :: getPassangersCount)
						.sum();
	}
	

	
	@Override
	public void		onTimePass() 
	{
		/* TRIGGER THE FUNCTIONS THAT RELATED TO THE TIME */
		updateCurrentHour();
		updatePopulation();

	}
}
