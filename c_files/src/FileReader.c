/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 11.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "FileReader.h"
#include "PlanetLists.h"


/* PRIVATE FUNCTIONS */
char*		read(const FileReader this)
{
	/* CHECKING THE VARIABLES THAT WE WILL USE */
	if (this == NULL || this->path == NULL) {
		return (NULL);
	}

	/* DEFINE LOCAL VARIABLES*/
	char*	content;
	int		length;
	FILE	*filePointer;
	/* END OF DEFINITION */

	/* SET INITIAL VALUES */
	content = NULL;
	length = 0;

	// Open the file in read mode, get file's content
	filePointer = fopen(this->path, "r");
	if (!filePointer) {
	    return (NULL);
	}

	fseek(filePointer, 0, SEEK_END);	// Move to the end of the file to determine its size
	length = ftell(filePointer);		// Get the size of the file
	rewind(filePointer);				// Go back to the beginning of the file

	// Memory allocation for content 
	content = (char*)malloc(sizeof(char) * length + 1);
	if (!content) {
		return (NULL);
	}

	// Read the file content into the allocated memory
	size_t fileLength = fread(content, 1, length, filePointer);

	content[fileLength] = '\0'; // to finish the string
	fclose(filePointer);		// close the file

	/* CHECKING IF THERE IS AN OLD CONTENT */
	if (this->content != NULL)
    	free(this->content);
	
	/* SET NEW CONTENT */
	this->content = content;

	return (content);
}

Planet		determinePlanetType(char* name, int planetType, int hoursOfADay, int day, int month, int year)
{
	/* CHECKING THE PARAMETERS */
	if (name == NULL || planetType < 0 || hoursOfADay <= 0 || day <= 0 || month <= 0 || year <= 0)
	{
		return (NULL); // for invalid values 
	}

	/* CREATE PLANET DUE TO PLANET TYPE */
	if (planetType == 0)
	{
		TerrestrialPlanet tp = new_TerrestrialPlanet(name, planetType, hoursOfADay, day, month, year);
		terrestrialList->add(terrestrialList, tp);
		return (tp->super);
	}
	else if (planetType == 1)
	{
		GasGiantPlanet gp = new_GasGiantPlanet(name, planetType, hoursOfADay, day, month, year);
		gasGiantList->add(gasGiantList, gp);
		return (gp->super);
	}
	else if (planetType == 2)
	{
		IceGiantPlanet ip = new_IceGiantPlanet(name, planetType, hoursOfADay, day, month, year);
		iceGiantList->add(iceGiantList, ip);
		return (ip->super);
	}
	else if (planetType == 3)
	{
		DwarfPlanet dp = new_DwarfPlanet(name, planetType, hoursOfADay, day, month, year);
		dwarfList->add(dwarfList, dp);
		return (dp->super);
	}

	return (NULL);  // Return NULL if the planet type is not recognized
}

/* END OF PRIVATE FUNCTIONS */

FileReader	new_FileReader(const char* pathofFile)
{
	/* CHECKING THE PARAMETERS */
	if (pathofFile == NULL)
		return (NULL);
	
	/* MEMORY ALLOCATION FOR FILE READER */
	FileReader this = (FileReader)malloc(sizeof(struct FILEREADER));
	if (this == NULL)
	{
		printf("Memory allocation failed at new_FileReader.\n");
		throw;
	}

	/* SET INITIAL VALUES*/
	this->path = strdup(pathofFile);
	this->content = NULL;

	/* LINKS */
	this->delete_FileReader = &delete_FileReader;
	this->readPersons = &readPersons;
	this->readVehicles = &readVehicles;
	this->readPlanets = &readPlanets;
	/* END OF LINKS */
	
	return (this);
}

ArrayList	readPersons(const FileReader this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL)
	{
		printf("Path is empty or couldn't find at readPersons \n");
		throw;
	}
	/* LOCAL VARIABLES */
	ArrayList persons;
	char* content;
	int lineCount;
	char** lines;

	/* SET INITIAL VALUES */
	content = read(this);
	persons = new_ArrayList();
	if (!content || !persons)
		throw;
	
	lineCount = 0;
	lines = split(content, '\n', &lineCount);  // Split the content into lines
    
    for (int i = 0; i < lineCount; i++)
	{
		/* VARIABLES FOR LINES' PARTS*/
		int partCount = 0;
		char** parts = split(lines[i], '#', &partCount);

		/* IF THERE IS ENOUGH PART CREATE NEW PERSON */
		if (partCount == 4)
		{
			const char* name = parts[0];
			int age = atoi(parts[1]);
			int hoursLeftToLive = (double)atoi(parts[2]);
			const char* currentVehicle = parts[3];

			Person person = new_Person(name, age, hoursLeftToLive, currentVehicle);
			persons->add(persons, person);  // Add person to the ArrayList
        }
		else 
			printf("Invalid line format: %s\n", lines[i]); // Handle invalid line format

		// FREE THE PARTS ARRAY AFTER EACH PROCESSS
		freeSplit(parts, partCount);
	}
	// FREE THE LINES ARRAY AFTER PROCESSING ALL LINES
	freeSplit(lines, lineCount);

	return (persons);
}

ArrayList	readVehicles(const FileReader this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL)
	{
		printf("Path is empty or couldn't find at readVehicles \n");
		throw;
	}	
	/* LOCAL VARIABLES */
	ArrayList vehicles;
	char* content;
	int lineCount;
	char** lines;

	/* SET INITIAL VALUES */
	vehicles = new_ArrayList();
	content = read(this);
	if (!content || !vehicles)
		throw;

	lineCount = 0;
	lines = split(content, '\n', &lineCount);  // Split the content into lines

	for (int i = 0; i < lineCount; i++)
	{
		/* VARIABLES FOR LINES' PARTS*/
		int partCount = 0;
		char** parts = split(lines[i], '#', &partCount);

		/* IF THERE IS ENOUGH PART CREATE NEW SPACESHIP */
		if (partCount == 5)
		{
			char* name = parts[0];
			char* currentPlanet = parts[1];
			char* destPlanet = parts[2];
			int distance = atoi(parts[4]);

            /* SPLIT THE DATE STRING */
            char** dateParts = NULL;
            int dateCount = 0;
            dateParts = split(parts[3], '.', &dateCount);
			
			if (dateCount == 3)
			{
				int day = atoi(dateParts[0]);
				int month = atoi(dateParts[1]);
				int year = atoi(dateParts[2]);

				SpaceShip ship = new_SpaceShip(name, currentPlanet, destPlanet, distance, day, month, year);    
				vehicles->add(vehicles, ship);
			}
			else
				printf("Invalid date line format: %s\n", lines[i]); //handle invalid format

			// FREE THE DATE PARTS AFTER EACH PROCESS
			freeSplit(dateParts, dateCount);
		}
		else 
			printf("Invalid line format: %s\n", lines[i]); //handle invalid format
		// FREE THE LINE PARTS AFTER EACH PROCESS
		freeSplit(parts, partCount);
	}
	//FREE THE LINES AFTER PROCESSING ALL LINES
	freeSplit(lines, lineCount);

	return (vehicles);
}

ArrayList	readPlanets(const FileReader this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL)
	{
		printf("Path is empty or couldn't find at readPlanets \n");
		throw;
	}
	dwarfList = new_ArrayList();
	gasGiantList = new_ArrayList();
	iceGiantList = new_ArrayList();
	terrestrialList = new_ArrayList();

	/* LOCAL VARIABLES */
	ArrayList planets;
	char* content;
	int lineCount;
	char** lines;

	/* SET INITIAL VALUES */
	content = read(this);
	planets = new_ArrayList();
	if (!content || !planets)
		throw;
	
	lineCount = 0;
	lines = split(content, '\n', &lineCount);
	
	for (int i = 0; i < lineCount; i++)
	{
		/* VARIABLES FOR LINES' PARTS*/
		int partCount = 0;
		char** parts = split(lines[i], '#', &partCount);
		
		/* IF THERE IS ENOUGH PART CREATE NEW PLANET */
		if (partCount == 4)
		{
			char* name = parts[0];
			int planetType = atoi(parts[1]);
			int hoursOfADay = atoi(parts[2]);
			
			char** dateParts = NULL;
            int dateCount = 0;
            dateParts = split(parts[3], '.', &dateCount);
			if (dateCount == 3)
			{
				int day = atoi(dateParts[0]);
				int month = atoi(dateParts[1]);
				int year = atoi(dateParts[2]);

				Planet planet = determinePlanetType(name, planetType,hoursOfADay, day, month, year);
				planets->add(planets, planet);
			}else
			{
				printf("Invalid date line format: %s\n", lines[i]); //handle invalid format
			}
			// FREE THE DATE PARTS AFTER EACH PROCESS
			freeSplit(dateParts, dateCount);
		}
		else 
			printf("Invalid line format: %s\n", lines[i]); //handle invalid format
		
		// FREE THE LINE PARTS AFTER EACH PROCESS
		freeSplit(parts, partCount);
	}
	//FREE THE LINES AFTER PROCESSING ALL LINES
	freeSplit(lines, lineCount);

	return (planets);
}


void		delete_FileReader(FileReader this)
{
	if(this == NULL)
    	return;

    if (this->path != NULL)
    	free(this->path);

    if (this->content != NULL)
    	free(this->content);

    free(this);
}