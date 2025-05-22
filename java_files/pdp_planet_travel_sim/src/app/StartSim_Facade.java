/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 04.04.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/


package app;

/* IMPORTS */
import java.util.List;
import java.util.ArrayList;

/* END OF IMPORTS*/

public class StartSim_Facade
{
	List<Person>	persons;	// FOR PERSON OBJECTS
	List<SpaceShip>	ships;		// FOR SHIP OBJECTS
	List<Planet>	planets;	// FOR PLANET OBJECTS
	
	/* CONSTRUCTER */
	public StartSim_Facade()
	{
		/* GET FROM THE FILE */
		setPersons();
		setShips();
		setPlanets();
		
		/* CLEAN UP THE INVALID DATAS TO PREVENT FROM THE ERRORS */
		cleanUpInvalidData();
		
		/* SET FIELDS THAT RELATED TO OTHER OBJECTS */
		setShipInitials();
		setPlanetInitials();
	}
	/* END OF CONSTRUCTER */
	
	/* SETTER METHODS */
	
	private void	setPersons()
	{
		persons = FileReader.readPersons("Kisiler.txt");
	}
	private void	setShips()
	{
		ships = FileReader.readVehicles("Araclar.txt");

	}
	private void	setPlanets()
	{
		planets = FileReader.readPlanets("Gezegenler.txt");
	}
	private void	setShipInitials()
	{
		// SET THE OTHER FIELDS RELATED TO OTHER CLASSES' OBJECTS
		for (SpaceShip ship : ships)
		{

			ship.setPersonList(persons);
		}
		
		for (SpaceShip ship : ships)
		{
		        ship.setPlanetFromNames(planets);
		        ship.calculateArrivalDate();
		        ship.updatePassengers();
		}
	}


	private void	setPlanetInitials()
	{
		// SET THE OTHER FIELDS RELATED TO OTHER CLASSES' OBJECTS
		for (Planet planet : planets)
		{
			planet.setSpaceShipList(ships);
		}
		
		for (Planet planet : planets)
		{
			planet.updatePopulation();
		}
	}
	
	/*END OF SETTER METHODS */
	
	/* METHODS */

	private void	cleanUpInvalidData()
	{
	    List<Person> validPersons = new ArrayList<>();	// NEW LIST FOR THE UPDATE
	    List<SpaceShip> validShips = new ArrayList<>(); // NEW LIST FOR THE UPDATE
	    
	    for (Person person : persons)
	    {
	        if (person.isValid(ships))
	        { 
	            validPersons.add(person);
	        }
	    }
	    
	    for (SpaceShip ship : ships)
	    {
	        if (ship.isValid(planets))
	        {
	            validShips.add(ship); 
	        }
	    }
	    /* CLEAR THE LISTS */
	    persons.clear();
	    ships.clear();
	    
	    /* SET THE LISTS */
	    persons.addAll(validPersons);
	    ships.addAll(validShips);
	}

	
	private void	refreshPage()
	{
		try
		{
			String os = System.getProperty("os.name").toLowerCase();
	        if (os.contains("win"))
	        {
	        	// FOR WIN
	            new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
	        } 
	        else
	        {
	        	// FOR UNIX BASED SYSTEMS
	            System.out.print("\033[H\033[2J");
	            System.out.flush();
	        }
	     }
		 catch (Exception e)
		 {
			 e.printStackTrace();
	     }
	     
	}
	
	private boolean	isSimFinished()
	{
		for (SpaceShip ship : ships)
		{
			// IF ALL THE SHIPS' STATE IS "IMHA" OR "VARDI" RETURN TRUE TO FINISH THE SIM
			if (!((ship.getState().equals("İMHA")) || (ship.getState().equals("Vardı"))))
			{
				return (false);
			}
		}
		return (true);
	}
	
	private void	planetsMenu()
	{
		int kolonGenisligi = 15;

	    System.out.println("Gezegenler: ");
	        
	    System.out.printf("%-" + kolonGenisligi + "s", " ");
	    for (Planet p : planets)
	    {
	    	System.out.printf("%-" + kolonGenisligi + "s", "--- " + p.getName() + " ---");
	    }
	     
	    System.out.println();

	    System.out.printf("%-" + kolonGenisligi + "s", "Tarih");
	    for (Planet p : planets)
	    {
	    	System.out.printf("%-" + kolonGenisligi + "s", p.getCurrentDate().toString());
	    }
	    System.out.println();
	     
	    System.out.printf("%-" + kolonGenisligi + "s", "Nüfus");
	    for (Planet p : planets)
	    {
	    	System.out.printf("%-" + kolonGenisligi + "d", p.getPopulation());
	    }
	    System.out.println();
	    System.out.println();
	}

	private void	shipsMenu()
	{
		int nameWidth = 20;
	    int statusWidth = 15;
	    int planetWidth = 12;
	    int distanceWidth = 10;
	    int dateWidth = 15;
	    
	    System.out.println();
	    System.out.println("Uzay Araçları:");
 
	    System.out.printf("%-" + nameWidth + "s", "Araç Adı");
	    System.out.printf("%-" + statusWidth + "s", "Durum");
	    System.out.printf("%-" + planetWidth + "s", "Çıkış");
	    System.out.printf("%-" + planetWidth + "s", "Varış");
	    System.out.printf("%-" + distanceWidth + "s", "Mesafe");
	    System.out.printf("%-" + dateWidth + "s", "Varış Tarihi");
	    System.out.println();
		
	    for (SpaceShip ship : ships)
	    {
	        System.out.printf("%-" + nameWidth + "s", ship.getName());
	        System.out.printf("%-" + statusWidth + "s", ship.getState());
	        System.out.printf("%-" + planetWidth + "s", ship.getCurrentPlanetName());
	        System.out.printf("%-" + planetWidth + "s", ship.getDestPlanetName());
	        if (ship.getState().equals("İMHA"))
	        {
	        	System.out.printf("%-" + distanceWidth + "s", "--");
	        	System.out.printf("%-" + dateWidth + "s", "--.--.--");
	        }
	        else
	        {
	        	System.out.printf("%-" + distanceWidth + "d", ship.getDistanceLeft());
	        	System.out.printf("%-" + dateWidth + "s", ship.getArrivalDate().toString());
	        }
	        System.out.println();
	    }
	    System.out.println();
	}
	
	public void		runSim()
	{
		// SHOW THE INITIAL VALUES
		refreshPage();
		planetsMenu();
		shipsMenu();
		
		// START THE LOOP
		do
		{
			Time.advanceTime();
			refreshPage();
			planetsMenu();
			shipsMenu();
		}while(!isSimFinished());
	}
}
