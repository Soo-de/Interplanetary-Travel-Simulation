/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 14.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/


#include "StartSim_Facade.h"
#include "PlanetLists.h"

#define COLUMN_WIDTH 15
#define NAME_WIDTH 20
#define STATUS_WIDTH 15
#define PLANET_WIDTH 12
#define DISTANCE_WIDTH 10
#define DATE_WIDTH 15


/* PRIVATE FUNCTIONS  */

void			refreshPage()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

bool			isSimFinished(const StartSim_Facade this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL)
	{
		printf("Error: at isSimFinished\n");
		return (false);
	}

	for (int i = 0; i < this->allShips->size; i++)
	{
		SpaceShip ship = (SpaceShip)this->allShips->getByIndex(this->allShips, i);
		// IF THERE ANY SHIP THAT THEIR STATE IS DIFFRENT FROM IMHA OR Vardi CONTINUE TO SIM
		if ( ship != NULL && (strcmp(ship->state, "IMHA") != 0 && strcmp(ship->state, "Vardi") != 0))
		{
			return (false);
		}
	}

	return (true);
}

void			setInitials(StartSim_Facade this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL || 
		this->allPersons == NULL || 
		this->allPlanets == NULL ||
		this->allShips == NULL)
	{
		printf("Error: at setInitials \n");
		throw;
	}

	int count = this->allShips->size; // extra variable for clean visibility
	for (int i = 0; i < count; i++)
	{

		SpaceShip ship = (SpaceShip)this->allShips->getByIndex(this->allShips, i);
		// CALL ALL SHIPS' SETINITIAL FUNCTION
		if (ship != NULL)
			ship->setInitials_Ship(ship, this->allPlanets, this->allPersons);
		
		// CHECK IF THERE ANY UNMATCHED VARIABLE
		if (ship->currentPlanet == NULL || ship->destPlanet == NULL)
		{
			// IF THERE ANY UNMATCHED VARIABLE DELETE THIS
			ship->delete_SpaceShip(ship);
			this->allShips->removeAt(this->allShips, i);
			count--;
			i--;
		}

		/* OTHER INITIAL VALUE SETTERS */
		ship->calculateArrivalDate(ship);
		ship->updatePassengers(ship);
	}

	count = this->allPersons->size;
	for (int i = 0; i < count; i++)
	{
		Person person = (Person)this->allPersons->getByIndex(this->allPersons, i);
		// CALL ALL PERSONS' SETINITIAL FUNCTION
		if (person != NULL)
			person->setInitials_Person(person, this->allShips);

		// CHECK IF THERE ANY UNMATCHED VARIABLE
		if (person->currentVehicle == NULL)
		{
			// IF THERE ANY UNMATCHED VARIABLE DELETE THIS
			person->delete_Person(person);
			this->allPersons->removeAt(this->allPersons, i);
			count--;
			i--;
		}
	}

	count = this->allPlanets->size;
	for (int i = 0; i < count; i++)
	{
		Planet planet = (Planet)this->allPlanets->getByIndex(this->allPlanets, i);
		// CALL ALL PLANETS' SETINITIAL FUNCTION
		if (planet != NULL)
			planet->setInitials_Planet(planet, this->allShips);
		
		/* OTHER INITIAL VALUE SETTERS */
		planet->updatePopulation(planet);
	}
}

void			planetsMenu(const StartSim_Facade this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL)
    {
		printf("Error: planetsMenu 'this' NULL!\n");
		return;
	}

	printf("Gezegenler:\n\n");

	printf("%-*s", COLUMN_WIDTH, " ");
	for (int i= 0; i < this->allPlanets->size; i++)
	{
		Planet planet = (Planet)this->allPlanets->getByIndex(this->allPlanets, i);
		printf("%-*s", COLUMN_WIDTH, planet->name);
	}
	printf("\n");

	printf("%-*s", COLUMN_WIDTH, "Tarih");
	for (int i = 0; i < this->allPlanets->size; i++)
	{
		Planet planet = (Planet)this->allPlanets->getByIndex(this->allPlanets, i);
		char* dateStr = planet->currentDate->toString(planet->currentDate);
		printf("%-*s", COLUMN_WIDTH, dateStr);
		free(dateStr);
	}
	printf("\n");

	printf("%-*s", COLUMN_WIDTH, "Nufus");
	for (int i = 0; i < this->allPlanets->size; i++)
	{
		Planet planet = (Planet)this->allPlanets->getByIndex(this->allPlanets, i);
		printf("%-*d", COLUMN_WIDTH, planet->population);
	}
	printf("\n\n");
}

void			shipsMenu(const StartSim_Facade this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL)
	{
		printf("Hata: shipsMenu içinde 'this' NULL!\n");
		return;
	}

	printf("Uzay Gemileri:\n\n");

	printf("%-*s", NAME_WIDTH, "Arac Adi");
	printf("%-*s", STATUS_WIDTH, "Durum");
	printf("%-*s", PLANET_WIDTH, "Cikis");
	printf("%-*s", PLANET_WIDTH, "Varis");
	printf("%-*s", DISTANCE_WIDTH, "Mesafe");
	printf("%-*s", DATE_WIDTH, "Varis Tarihi");
	printf("\n");

	for (int i = 0; i < this->allShips->size; i++)
	{
		SpaceShip ship = (SpaceShip)this->allShips->getByIndex(this->allShips, i);
		printf("%-*s", NAME_WIDTH, ship->name);
		printf("%-*s", STATUS_WIDTH, ship->state);
		printf("%-*s", PLANET_WIDTH, ship->currentPlanetName);
		printf("%-*s", PLANET_WIDTH, ship->destPlanetName);

		if (strcmp(ship->state, "IMHA") == 0) {
			printf("%-*s", DISTANCE_WIDTH, "--");
			printf("%-*s", DATE_WIDTH, "--.--.--");
		} else {
			printf("%-*d", DISTANCE_WIDTH, ship->distanceLeft);
			char* dateStr = ship->arrivalDate->toString(ship->arrivalDate);
			printf("%-*s", DATE_WIDTH, dateStr);
			free(dateStr);
		}
		printf("\n");
	}
	printf("\n");
}

/* END OF PRIVATE FUNCTIONS*/

StartSim_Facade	new_StartSim_Facade()
{
    /* MEMORY ALLOCATION FOR START SIM FACADE*/
	StartSim_Facade this = (StartSim_Facade)malloc(sizeof(struct STARTSIM_FACADE));
	if (this == NULL)
	{
		printf("Memory allocation failed at new_StartSim_Facade\n");
		return (NULL);
	}

	/* SET ARRAY LISTS */
	try{
		FileReader fileReader = new_FileReader("Araclar.txt");
		if (fileReader != NULL)
		{
			this->allShips = readVehicles(fileReader);
			fileReader->delete_FileReader(fileReader); 
		}

		fileReader = new_FileReader("Gezegenler.txt");
		if (fileReader != NULL)
		{
			this->allPlanets = readPlanets(fileReader);
			fileReader->delete_FileReader(fileReader);
		}	

		fileReader = new_FileReader("Kisiler.txt");
		if (fileReader != NULL)
		{
			this->allPersons = readPersons(fileReader);
			fileReader->delete_FileReader(fileReader);
		}
	}
	catch{
		printf("Error reading files at new_StartSim_Facade.\n");
		delete_StartSim_Facade(this);
		return NULL;
	}
	tryEnd;

	/* SET INITIAL VALUES */
	try{
		setInitials(this);
	}
	catch{
		printf("Error setting initials at new_StartSim_Facade.\n");
		delete_StartSim_Facade(this);
		return NULL;
	}
	tryEnd;

	/* LINKS */
	this->runSim = &runSim;
	this->delete_StartSim_Facade = &delete_StartSim_Facade;
	/* END OF LINKS*/

	return (this);
}

void			runSim(const StartSim_Facade this)
{
	/* CHECK THE PARAMETERS */
	if (this == NULL)
		return;

	MyTime time = new_Time();	// time struct to advance time
	refreshPage();				// initial values at time = 0
	planetsMenu(this);			// initial values at time = 0
	shipsMenu(this);			// initial values at time = 0
    
	/* MAIN LOOP */
	while (isSimFinished(this) == false)
	{
		time->advanceTime(this->allShips, this->allPlanets, this->allPersons);
		refreshPage();
		planetsMenu(this);
		shipsMenu(this);
	}

	time->delete_Time(time); // delete time struct 
}

void			delete_StartSim_Facade(StartSim_Facade this)
{

    if (this == NULL)
        return;

    if (this->allPlanets != NULL)
    {
		freeGlobalPlanetLists();
        this->allPlanets->detele_ArrayList(this->allPlanets);
    }

    if (this->allShips != NULL)
    {
        for (size_t i = 0; i < this->allShips->size; i++)
        {
            SpaceShip s = (SpaceShip)this->allShips->getByIndex(this->allShips,i);
            if (s != NULL)
                s->delete_SpaceShip(s);
        }
        this->allShips->detele_ArrayList(this->allShips);
    }

    if (this->allPersons != NULL)
    {
        for (size_t i = 0; i < this->allPersons->size; i++)
        {
            Person per = (Person)this->allPersons->getByIndex(this->allPersons,i);
            
            if (per != NULL)
                per->delete_Person(per);
        }
        this->allPersons->detele_ArrayList(this->allPersons);
    }

    free(this);
}
