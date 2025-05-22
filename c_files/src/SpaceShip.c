/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include    "SpaceShip.h"
#include	"Person.h"
#include	"StringUtils.h" 


/* PRIVATE FUNCTIONS */
void		setState(SpaceShip this, const char* newState)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL || newState == NULL)
	{
		printf("Error: setState 'this' or 'newState' is NULL!\n");
		return;
	}

	/* REALLOC STATE */
	if (this->state != NULL) 
	{
		free(this->state);
	}
	this->state = strdup(newState);
}

void		updateState(SpaceShip this)
{
	/* CHECKING THE PARAMETERS AND VARIABLES */
	if (this == NULL || this->currentPlanet == NULL || this->destPlanet == NULL || this->launchDate == NULL)
	{
		printf("Error: updateState 'this' or its members are NULL!\n");
		return;
	}
	if (this->currentPlanet->currentDate == NULL)
	{
		printf("Error: updateState 'this' is NULL!\n");
		return;
	}

	/* UPDATE STATE */
	if (this->passengersCount == 0)
	{
		setState(this, "IMHA");
	}
	else if (this->launchDate->isEqual(this->launchDate, this->currentPlanet->currentDate))
	{
		setState(this, "Yolda");
	}
	else if (strcmp(this->state , "Yolda") == 0 && this->distanceLeft == 0)
	{
		setState(this, "Vardi");
	}
}

void		reduceDistanceLeft(SpaceShip this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL || this->state == NULL)
	{
		printf("Error: reduceDistanceLeft 'this' or its state is NULL!\n");
		return;
	}

	/* REDUCE DISTANCE */
	if (strcmp(this->state, "Yolda") == 0 && this->distanceLeft > 0)
	{
		this->distanceLeft--;
	}
}
/* END OF PRIVATE FUNCTIONS */

SpaceShip	new_SpaceShip(const char* name, const char* currentPlanetName, const char* destPlanetName, int distanceLeft, int day, int month, int year)
{
	/* CHECKING THE PARAMETERS */
	if (name == NULL || currentPlanetName == NULL || destPlanetName == NULL)
	{
		printf("Memory allocation failed at new_SpaceShip\n");
		return (NULL);
	}

	/* MEMORY ALLOCATION FOR SPACESHIP*/
	SpaceShip this = (SpaceShip)malloc(sizeof(struct SPACESHIP));
	if (this == NULL)
	{
		printf("Memory allocation failed at new_SpaceShip\n");
		return (NULL);
	}

	/* MEMORY ALLOCATION FOR TIMELISTENER*/
	this->listener = new_ITimeListener();
	if (this->listener == NULL)
	{
		printf("Memory allocation failed for listener!\n");
		return NULL;
	}

	/* MEMORY ALLOCATION FOR MYLOCALTIME*/
	this->launchDate = new_MyLocalTime(day, month, year);
	if (this->launchDate == NULL)
	{
		printf("Memory allocation failed at new_SpaceShip MyLocalTime\n");
		free(this->listener);
		free(this);
		return (NULL);
	}

	/* SET INITIAL VALUES */
	this->name = strdup(name);
	this->currentPlanetName = strdup(currentPlanetName);
	this->destPlanetName = strdup(destPlanetName);
	this->state = strdup("Bekliyor");
	this->distanceLeft = distanceLeft;
	this->passengersCount = 0;

	/* LINKS */
	this->setInitials_Ship = &setInitials_Ship;
	this->calculateArrivalDate = &calculateArrivalDate;
	this->updatePassengers = &updatePassengers;
	this->delete_SpaceShip = &delete_SpaceShip;
	this->listener->onTimePass = &onTimePass_Ship; //interface implementation method
	/* END OF LINKS */

	return (this);
}

void		setInitials_Ship(const SpaceShip this, ArrayList planetList, ArrayList personList)
{
	/* CHECK THE PARAMETERS */
	if (this == NULL || this->currentPlanetName == NULL || this->destPlanetName == NULL)
	{
		printf("EROR: at setInitials_Ship \n");
		return;
	}

	/* SET INITIAL VALUES */
	this->currentPlanet = NULL;
	this->destPlanet = NULL;

	/* SET EXACT VALUES IF EXIST */
	if (planetList != NULL)
	{
		for (size_t i = 0; i < planetList->size; i++)
		{
			Planet planet = (Planet)(planetList->getByIndex(planetList, i));
			if (planet != NULL && planet->name != NULL)
			{
				if (equalsIgnoreCase(this->currentPlanetName, planet->name))
				{
					this->currentPlanet = planet;
				}
				if (equalsIgnoreCase(this->destPlanetName, planet->name))
				{
					this->destPlanet = planet;
				}

				/* IF THE VALUES THAT WE WANT FOUND BREAK THE LOOP*/
				if (this->currentPlanet != NULL && this->destPlanet != NULL)
				{
					break;
				}
			}
		}
	}else{
		printf("PlanetList is empty at setInitials_Ship\n");
	}

	/* SET THE PERSONLIST */
	if (personList != NULL)
	{
		this->allPersons = personList;
	}else{
    	printf("PersonList is empty at setInitials_Ship\n");
	}
}

void		calculateArrivalDate(const SpaceShip this)
{
	/* CHECKING THE PARAMETERS AND VARIABLES*/
	if (this == NULL || 
		this->currentPlanet == NULL || 
		this->destPlanet == NULL || 
		this->launchDate == NULL ||
		this->currentPlanet->currentDate == NULL ||
		this->destPlanet->currentDate == NULL)
	{
		printf("Error: calculateArrivalDate 'this' or its members are NULL!\n");
		return;
	}

	/* LOCAL VARIABLES */
	long daysBetween;
	long totalHours;
	long daysToAdd;
	this->arrivalDate = NULL;

	if ((this->currentPlanet != NULL) && (this->destPlanet != NULL))
	{
		// date copy to not effect the real date
		MyLocalTime destDateCopy;
		destDateCopy = this->destPlanet->currentDate->clone_MyLocalTime(this->destPlanet->currentDate);

		// get days between now and launch date
		daysBetween = this->currentPlanet->currentDate
							->daysBetween(this->launchDate,
											this->currentPlanet->currentDate);
		
		// calculate total hours to arrive to the destination
		totalHours = daysBetween * this->currentPlanet->hoursOfADay;
		totalHours += this->distanceLeft;

		// add days to destination planet's copy date to find arrival date
		daysToAdd = totalHours / this->destPlanet->hoursOfADay;
		destDateCopy->advanceDay(destDateCopy, daysToAdd);

		//set arrival date
		this->arrivalDate = destDateCopy;
	}

}

void		updatePassengers(const SpaceShip this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL || this->allPersons == NULL)
	{
		printf("Error: updatePassengers 'this' is NULL!\n");
		return;
	}

	/* CALCULATE PASSANGERS COUNT*/
	int count = 0;
	for (int i = 0; i < this->allPersons->size; i++)
	{
		Person person = (Person)(this->allPersons->getByIndex(this->allPersons, i));
		if (person != NULL)
		{
			if (equalsIgnoreCase(person->currentVehicleName, this->name) && (person->isAlive(person)))
			{
				count++;
			}
		}else {
			printf("EROR: at updatePassangers person is null\n", i);
		}
	}
	
	/* SET PASSANGER COUNT */
	this->passengersCount = count;
}

void		delete_SpaceShip(SpaceShip this)
{
    if (this == NULL)
        return;
    
    if (this->name != NULL)
        free(this->name);

    if (this->currentPlanetName != NULL)
        free(this->currentPlanetName);
    
    if (this->destPlanetName != NULL)
        free(this->destPlanetName);
    
    if (this->state != NULL)
        free(this->state);
    
    if (this->listener != NULL)
        free(this->listener);

    if (this->launchDate != NULL)
        this->launchDate->delete_MyLocalTime(this->launchDate);
    
    if (this->arrivalDate != NULL)
        this->arrivalDate->delete_MyLocalTime(this->arrivalDate);
    
    free(this);
}

/* OVERRIDE METHOD */
void		onTimePass_Ship(const SpaceShip this)
{
	if (this == NULL)
	{
		printf("Error: onTimePass_Ship 'this' is NULL!\n");
		return;
	}

    updatePassengers(this);
    reduceDistanceLeft(this);
    updateState(this);
}