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

/* IMPORST */
import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.*;
import java.util.*;
/* END OF IMPORTS*/

public class FileReader
{
	
	/* FUNCTION THAT GETS PERSONS FROM THE FILE */
	public static List<Person>		readPersons(String filePath)
	{
		String			name; 			// TO GET NAME
		String			currentVehicle; // TO GET VEHICLE THAT PERSON IS IN
		int				age; 			// TO GET PERSON'S AGE
		int				hoursLeftToLive;// TO GET PERSON'S LIFETIME
		Person			person;			// TO MAKE AN OBJECT FROM PERSON CLASS
		String[]		parts;			// TO HOLD THE SUBSTRINGS OF EACH LINE
		List<Person>	persons;		// TO KEEP ALL PERSON OBJECTS TOGETHER
		List<String>	lines;			// TO GET LINES FROM THE FILE
		
		persons = new ArrayList<>(); // CREATE PERSON OBJECT LIST
		try
		{
			lines = Files.readAllLines(Paths.get(filePath)); // GET LINES
			for (String line : lines)
			{
				parts = line.split("#"); // SPLIT THE LINE
				
				/* SET VALUES */
				name = parts[0];
				age = Integer.parseInt(parts[1]);
				hoursLeftToLive = Integer.parseInt(parts[2]);
				currentVehicle = parts[3];
				/* END OF SETTING */
				
				/* CREATE OBJECT AND ADD IT TO THE LIST */
				person = new Person(name, age, hoursLeftToLive, currentVehicle);
				persons.add(person);
			}
		}
		catch(IOException e) // FOR EXCEPTIONS 
		{
			System.out.println("Hata : " + e.getMessage());
		}
		
		return (persons); // RETURN OBJECTS' LIST
	}
	/* END OF PERSONS' FUNCTION */
	
	/* FUNCTION THAT GETS VEHICLES FROM THE FILE */
	public static List<SpaceShip>	readVehicles(String filePath)
	{
		String			name;		  	// TO GET NAME
		String			currentPlanet;	// TO GET CURRENT PLANET THAT VEHICLE CURRENTLY IS IN
		String			destPlanet;		// TO GET DESTINATION PLANET
		int				distance;		// TO GET DISTANCE LEFT TO THE DESTINATION PLANET
		int				day;			// TO GET DAY OF THE LEAVING DATE
		int				month;			// TO GET MONTH OF THE LEAVING DATE
		int				year;			// TO GET YEAR OF THE LEAVING DATE
		MyLocalTime		date;			// TO MAKE A DATE OBJECT
		SpaceShip		ship;			// TO MAKE AN OBJECT FROM SPACESHIP CLASS
		String[]		parts;			// TO HOLD THE SUBSTRINGS OF EACH LINE
		String[]		dateParts;		// TO HOLD THE DATE SUBSTRINGS OF EACH LINE
		List<SpaceShip>	ships;			// TO KEEP ALL SPACESHIP OBJECTS TOGETHER
		List<String>	lines;			// TO GET LINES FROM THE FILE
		
		ships = new ArrayList<>(); // CREATE SPACESHIP OBJECT LIST 
		try
		{
			lines = Files.readAllLines(Paths.get(filePath)); // GET LINES
			for (String line : lines)
			{
				parts = line.split("#"); // SPLIT THE LINE
				dateParts = parts[3].split("\\."); // SPLIT THE DATE
				
				/* SET THE VALUES */
				name = parts[0];
				currentPlanet = parts[1];
				destPlanet = parts[2];
				distance = Integer.parseInt(parts[4]);
				day = Integer.parseInt(dateParts[0]);
				month = Integer.parseInt(dateParts[1]);
				year = Integer.parseInt(dateParts[2]);
				
				/* CREATE OBJECTS AND ADD TO THE LIST */
				date = new MyLocalTime(day,month,year);
				ship = new SpaceShip(name, currentPlanet, destPlanet, date, distance);
				ships.add(ship);
			}
		}
		catch(IOException e) // FOR EXCEPTIONS 
		{
			System.out.println("Hata : " + e.getMessage());
		}
		
		return (ships); // RETURN OBJECTS' LIST
	}
	/* END OF VEHICLES' FUNCTION */
	
	/* FUNCTION THAT GETS PLANETS FROM THE FILE */
	public static List<Planet>		readPlanets(String filePath)
	{
		String			name;		// TO GET NAME
		int				hoursOfADay;// TO GET HOURS OF A DAY AT THE PLANET
		int				day;		// TO GET CURRENT DATE'S DAY
		int				month;		// TO GET CURRENT DATE'S MONTH
		int				year;		// TO GET CURRENT DATE'S YEAR
		MyLocalTime		date;		// TO MAKE A DATE OBJECT
		Planet			planet;		// TO MAKE AN OBJECT FROM PLANET CLASS
		String[]		parts;		// TO HOLD THE SUBSTRINGS OF EACH LINE
		String[]		dateParts;	// TO HOLD THE DATE SUBSTRINGS OF EACH LINE
		List<Planet>	planets ;	// TO KEEP ALL PLANET OBJECTS TOGETHER
		List<String>	lines;		// TO GET LINES FROM THE FILE
		
		planets = new ArrayList<>(); // CREATE PLANET OBJECT LIST
		try
		{
			lines = Files.readAllLines(Paths.get(filePath)); // GET LINES
			for (String line : lines)
			{
				parts = line.split("#"); // SPLIT THE LINE
				dateParts = parts[2].split("\\."); // SPLIT THE DATE
				
				/* SET THE VALUES */
				name = parts[0];
				hoursOfADay = Integer.parseInt(parts[1]);
				day = Integer.parseInt(dateParts[0]);
				month = Integer.parseInt(dateParts[1]);
				year = Integer.parseInt(dateParts[2]);
				
				/* CREATE OBJECTS AND TO THE LIST*/
				date = new MyLocalTime(day, month, year);
				planet = new Planet(name, hoursOfADay, date);
				planets.add(planet);
			}
		}
		catch (IOException e) // FOR EXCEPTIONS
		{
			System.out.println("Hata: " + e.getMessage());
		}
		return (planets);
	}
	/* END OF PLANETS' FUNCTION */
}
