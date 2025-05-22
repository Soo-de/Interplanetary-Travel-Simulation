/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 02.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "MyTime.h"

static long globalTime = 0;

/* PRIVATE FUNCTIONS */

void	advanceTimeForShips(ArrayList ships)
{
	for (size_t i = 0; i < ships->size; i++)
	{
		SpaceShip ship = (SpaceShip)(ships->getByIndex(ships, i));
		ship->listener->runFunctions(ship->listener, ship);
	}
}

void	advanceTimeForPlanets(ArrayList planets)
{
	for (size_t i = 0; i < planets->size; i++)
	{
		Planet planet = (Planet)(planets->getByIndex(planets, i));
		planet->listener->runFunctions(planet->listener, planet);
	}
}

void	advanceTimeForPersons(ArrayList persons)
{
	for (size_t i = 0; i < persons->size; i++)
	{
		Person person = (Person)(persons->getByIndex(persons, i));
		person->listener->runFunctions(person->listener, person);
	}
}

/* END OF PRIVATE FUNCTIONS */

MyTime	new_Time()
{
    /* MEMORY ALLOCATION FOR TIME */
	MyTime this = (MyTime)malloc(sizeof(struct MYTIME));
	if (this == NULL)
	{
		printf("Memory allocation failed at new_Time\n");
		return (NULL);
	}

	/* LINKS */
	this->getGlobalTime = &getGlobalTime;
	this->advanceTime = &advanceTime;
	this->delete_Time = &delete_Time;
	/* END OF LINKS */

	return (this);
}

long	getGlobalTime()
{
	return (globalTime);
}

void	advanceTime(ArrayList ships, ArrayList planets, ArrayList persons)
{
	/* CHECKING THE PARAMETERS*/
	if (!ships || !planets || !persons)
	{
		printf("Empty ArrayList at advanceTime \n");
		return;
	}

	globalTime++;
    advanceTimeForPersons(persons);
    advanceTimeForShips(ships);
    advanceTimeForPlanets(planets);
}

void	delete_Time(MyTime this)
{
	if (this == NULL)
		return;

	free(this);
}