/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "Planet.h"
#include "SpaceShip.h"
#include "StringUtils.h"
#include "MyTime.h"

/* PRIVATE FUNCTIONS */
void	updateCurrentHour(Planet this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL)
	{
		printf("Error: updateCurrentHour 'this' is NULL!\n");
		return;
	}

	/* TIME STRUCT FOR GLOBAL STATIC TIME */
	MyTime time = new_Time();
	if (time == NULL)
	{
		printf("Memory allocation failed at updateCurrentHour\n");
		return;
	}

	/* UPDATE CURRENT HOUR*/
	this->currentHour = (int)(time->getGlobalTime()% this->hoursOfADay);
	if (this->currentHour == 0)
	{
		this->currentDate->advanceDay(this->currentDate, 1);
	}

	/* DELETE TIME STRUCT */
	time->delete_Time(time);
}
/* END OF PRIVATE FUNCTIONS */

Planet	new_Planet(const char* name, int planetType, int hoursOfADay, int day, int month, int year)
{
	/* CHECKING THE PARAMETERS */
	if (name == NULL)
	{
		printf("Memory allocation failed at new_Planet\n");
		return (NULL);
	}

	/* MEMORY ALLOCATION FOR PLANET*/
	Planet this = (Planet)malloc(sizeof(struct PLANET));
	if (this == NULL)
	{
		printf("Memory allocation failed at new_Planet\n");
		return (NULL);
	}
	
	/* MEMORY ALLOCATION FOR TIMELISTENER */
	this->listener = new_ITimeListener();
	if (this->listener == NULL)
	{
		printf("Memory allocation failed for listener!\n");
		return (NULL);
	}

	/* MEMORY ALLOCATION FOR MYLOCALTIME*/
	this->currentDate = new_MyLocalTime(day, month, year);
	if (this->currentDate == NULL)
	{
		printf("Memory allocation failed at new_Planet MyLocalTime\n");
		free(this->listener);
		free(this);
		return (NULL);
	}

	/* SET INITIAL VALUES */
	this->name = strdup(name);
	this->planetType = planetType;
	this->hoursOfADay = hoursOfADay; 
	this->currentHour = 0;
	this->population = 0;

	/* LINKS */
	this->getDecayRate = &getDecayRate;
	this->setInitials_Planet = &setInitials_Planet;
	this->updatePopulation = &updatePopulation;
	this->delete_Planet = &delete_Planet;
	this->listener->onTimePass = &onTimePass_Planet; // interface implementation method
	/* END OF LINKS */

	return (this);
}

void	setInitials_Planet(const Planet this, ArrayList shipList)
{
	/* CHECKING THE PARAMETERS*/
    if (this == NULL || shipList == NULL) {
        printf("EROR: at setInitials_Planet\n");
        return;
    }
	/* SET */
    this->allShips = shipList;
}

double	getDecayRate(const Planet this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL)
	{
		printf("Error: at getDecayRate\n");
		return 0.0;
	}

	/* DETERMINE TYPE */
	switch (this->planetType)
	{
		case 0: // Terrestrial
			return 1.0;
		case 1: // Gas Giant
			return 0.1;
		case 2: // Ice Giant
			return 0.5;
		case 3: // Dwarf Planet
			return 0.01;
		default:
			return 1.0;
	}
}

void	updatePopulation(const Planet this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL || this->allShips == NULL)
	{
		printf("Hata: updatePopulation içinde 'this' NULL!\n");
		return;
	}

	/* CALCULATE POPULATION */
	int population = 0;
	for (size_t i = 0; i < this->allShips->size; i++)
	{
		SpaceShip ship = (SpaceShip)(this->allShips->getByIndex(this->allShips, i));
		/* CHECKING THE VARIABLES */
		if (ship != NULL || 
			ship->currentPlanetName != NULL ||
			ship->destPlanetName != NULL ||
			ship->state != NULL)
		{
			if (
				((equalsIgnoreCase(ship->currentPlanetName, this->name)) && (strcmp(ship->state, "Bekliyor") == 0)) ||
				((equalsIgnoreCase(ship->destPlanetName, this->name)) && (strcmp(ship->state, "Vardi") == 0))
			)
			{ // IF CONDITIONS ARE MET COUNT PASSANGER AS POPULATION
				population += ship->passengersCount;
			}
		}
	}
	/* SET VALUE */
	this->population = population;
}

void	delete_Planet(Planet this)
{
	if (this == NULL)
		return;
    
	if (this->name != NULL)
		free(this->name);

	if (this->listener != NULL)
		free(this->listener);

	if (this->currentDate != NULL)
		this->currentDate->delete_MyLocalTime(this->currentDate);

	free(this);
}

/* OVERRIDE METHOD */
void	onTimePass_Planet(const Planet this)
{
	if (this == NULL)
	{
		printf("Error: onTimePass_Planet !\n");
		return;
	}

	updateCurrentHour(this);
	updatePopulation(this);
}


