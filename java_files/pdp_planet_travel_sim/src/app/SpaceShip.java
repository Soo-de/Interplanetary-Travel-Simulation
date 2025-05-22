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

public class SpaceShip implements ITimeListener
{
	private String			name;				// TO SET NAME THAT WE GET FROM THE FILE
	private String			currentPlanetName;	// TO SET CURRENT PLANET THAT WE GET FROM THE FILE
	private String			destPlanetName;		// TO SET DESTINATION PLANET THAT WE GET FROM THE FILE
	private String			state;				// TO DETERMINE THE STATE
	private MyLocalTime		leavingDate;		// TO SET THE LEAVING DATE THAT WE GET FROM THE FILE
	private MyLocalTime		arrivalDate;		// TO SET THE ARRIVAL DATE THAT WE WILL CALCULATE
	private int 			distanceLeft;		// TO SET THE LEAVINF DATE THAT WE GET FROM THE FILE
	private int 			passengersCount;	// TO SET THE POPULATION OF THE SHIP
	private Planet			currentPlanet;		// TO MANIPULATE PLANET OBJECTS
	private Planet			destPlanet;			// TO MANIPULATE PLANET OBJECTS 
	private List<Person>	allPersons;			// TO CALCULATE HOW MANY PEOPLE CURRENTLY LOCATED IN THIS SHIP
	
	/* CONSTRUCTERS */
	
	public	SpaceShip(String name, String planetName, String destPlanetName, MyLocalTime leavingDate, int distance)
	{
		this.setName(name);
		this.setCurrentPlanet(planetName);
		this.setDestPlanet(destPlanetName);
		this.setLeavingDate(leavingDate);
		this.setDistanceLeft(distance);
		this.setArrivalDate(null);
		this.setState();
		this.setPassangersCount();
		Time.addListener(this);

	}
	
	/* END OF CONSTRUCTERS */
	
	
	/* SETTER METHODS */
	
	private void	setName(String name)
	{
		this.name = name;
	}
	private void	setCurrentPlanet(String planetName)
	{
		this.currentPlanetName = planetName;
	}
	
	private void	setDestPlanet(String planetName)
	{
		this.destPlanetName = planetName;
	}
	private void	setState()
	{
		this.state = "Bekliyor";
	}
	private void	setLeavingDate(MyLocalTime date)
	{
		this.leavingDate = date;
	}
	private void	setArrivalDate(MyLocalTime date)
	{
		if (date == null)
			this.arrivalDate = new MyLocalTime(1,1,1);
		else
			this.arrivalDate = date;
	}
	private void	setDistanceLeft(int hours)
	{
		this.distanceLeft = hours;
	}
	private void	setPassangersCount()
	{
		this.passengersCount = 0;
	}
	public void		setPlanetFromNames(List<Planet> planets)
	{
		// FIND THE PLANET OBJECT FROM THE PLANET NAME
		for (Planet planet : planets)
		{
			if (planet.getName().equalsIgnoreCase(currentPlanetName))
			{
				this.currentPlanet = planet;
			}
			if (planet.getName().equalsIgnoreCase(destPlanetName))
			{
				this.destPlanet = planet;
			}
		}
	}
	public void		setPersonList(List<Person> allPersons)
	{
		this.allPersons = allPersons;
	}
	
	/* END OF SETTER METHODS */
	
	/* GETTER METHODS */
	
	public String		getName()
	{
		return (name);
	}
	public String		getState()
	{
		return (state);
	}
	public String		getCurrentPlanetName()
	{
		return (currentPlanetName);
	}
	public String		getDestPlanetName()
	{
		return (destPlanetName);
	}
	public int			getDistanceLeft()
	{
		return (distanceLeft);
	}
	public int			getPassangersCount()
	{
		return (passengersCount);
	}
	public MyLocalTime	getLeavingDate()
	{
		return (leavingDate);
	}
	public MyLocalTime	getArrivalDate()
	{
		return (arrivalDate);
	}
	public Planet		getCurrentPlanet()
	{
		return (currentPlanet);
	}
	public Planet		getDestPlanet()
	{
		return (destPlanet);
	}
	
	/* END OF GETTER METHODS */

	/* METHODS */
	
	private void	updateState() {
		if (passengersCount == 0)
		{
			state = "İMHA";
			// IF THE SHIP IS NOT EXIST ANYMORE NO NEED TO BE RELATED TO THE TIME
			Time.removeListener(this);
		}
		else if (leavingDate.isEqual(currentPlanet.getCurrentDate()))
		{
			state = "Yolda";
		}
		else if (state.equals("Yolda") && distanceLeft == 0)
		{
			state = "Vardı";
		}
	}
	
	private void	reduceDistanceLeft()
	{
		if (state.equals("Yolda") && distanceLeft > 0)
		{
			distanceLeft--;
		}
	}
	
	public void		updatePassengers()
	{
		if (allPersons != null)
		{
			// IF THE PERSON IS ALIVE
			// AND
			// IF THE PERSON IS CURRENTLY IN THIS SHIP
			// COUNT TO CALCULATE POPULATION OF THE SHIP
			this.passengersCount = (int) allPersons.stream()
		            .filter(p -> p.isAlive() && p.getCurrentVehicle().equals(this.name))
		            .count();
		}
	}
	
	public void		calculateArrivalDate()
	{
		long daysBetween;	// DAYS BETWEEN CURRENT DATE AND LEAVING DATE
		long totalHours;	// CONVERT DAYS TO HOURS
		long daysToAdd;		// TO CALCULATE ARRIVAL DATE WHICH IS RELATED TO DESTINATION PLANET
		
		if (currentPlanet != null && destPlanet != null)
		{
			daysBetween = currentPlanet.getCurrentDate().daysBetween(leavingDate);
			totalHours = daysBetween * currentPlanet.getHoursOfADay();
			totalHours += distanceLeft;
		
			daysToAdd = totalHours / destPlanet.getHoursOfADay(); // CONVERT TOTAL HOURS TO DAYS
			setArrivalDate(new MyLocalTime(destPlanet.getCurrentDate().getCurrentDate().plusDays(daysToAdd)));
		}
	}
	
    public boolean	isValid(List<Planet> planets) // TO FIND THE PLANET THE SHIP CURRENTLY IS IN
    {
    	
    	boolean currentPlanetExists = planets.stream()
    	        .anyMatch(planet -> planet.getName().equalsIgnoreCase(this.currentPlanetName));
    	    
    	boolean destPlanetExists = planets.stream()
    	        .anyMatch(planet -> planet.getName().equalsIgnoreCase(this.destPlanetName));
    	
    	/* IF CURRENT PLANET AND DESTINATION PLANET ARE EXIST AT THE SAME TIME
    	 *  RETURN TRUE TO ADD THE SHIP TO THE UPDATED LIST */
    	return (currentPlanetExists && destPlanetExists);
    }
	
	@Override 
	public void		onTimePass()
	{
		// TRIGGER THE FUNCTIONS THAT RELATED TO THE TIME
		updatePassengers();
		reduceDistanceLeft();
		updateState();
	}
}


