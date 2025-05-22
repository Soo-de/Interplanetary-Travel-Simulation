/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "Person.h"

/* PRIVATE FUNSTIONS */
void	reduceHoursLeftToLive(Person this)
{
	/* CHECKING PARAMETERS AND VARIABLES THAT WE WILL USE IN THIS FUNCTION */
    if (this == NULL || 
        this->currentVehicle == NULL || 
        this->currentVehicle->state == NULL ||
        this->currentVehicle->currentPlanet == NULL ||
        this->currentVehicle->destPlanet == NULL ||
        this->hoursLeftToLive <= 0)
        return;
    
	/* REDUCE HOURS LEFT TO LIVE */
    if (this->hoursLeftToLive > 0)
    {
        if (strcmp(this->currentVehicle->state, "Bekliyor") == 0)
        {
            this->hoursLeftToLive -= this->currentVehicle->currentPlanet->getDecayRate(this->currentVehicle->currentPlanet);
        }
        else if (strcmp(this->currentVehicle->state, "Vardi") == 0)
        {
            this->hoursLeftToLive -= this->currentVehicle->destPlanet->getDecayRate(this->currentVehicle->destPlanet);
        }
        else
        {
            this->hoursLeftToLive -= 1; // when the state is "Yolda"
        }
    }

}
/* END OF PRIVATE FUNCTIONS */

Person	new_Person(const char* name, int age, double hoursLeftToLive, const char* currentVehicleName)
{
	/* CHECKING THE PARAMETERS */
	if (name == NULL || currentVehicleName == NULL)
	{
		printf("Memory allocation failed at new_Person\n");
		return (NULL);
	}

	/* MEMORY ALLOCATION FOR PERSON */
	Person this = (Person)malloc(sizeof(struct PERSON));
	if (this == NULL)
	{
		printf("Memory allocation failed at new_Person\n");
		return (NULL);
	}

	/* MEMORY ALLOCARION FOR ITIMELISTENER */
	this->listener = new_ITimeListener();
	if (this->listener == NULL)
	{
		printf("Memory allocation failed for listener!\n");
		free(this);
		return NULL;
	}

	/* SET INITAL VALUES */
	this->name = strdup(name);
	this->age = age;
	this->currentVehicleName = strdup(currentVehicleName);
	this->hoursLeftToLive = hoursLeftToLive;

	/* LINKS */
	this->setInitials_Person = &setInitials_Person;
	this->isAlive = &isAlive;
	this->delete_Person = &delete_Person;
	this->listener->onTimePass = &onTimePass_Person; // interface implementation method
    /* END OF LINKS */
	
	return (this);
}

void	setInitials_Person(const Person this, ArrayList spaceShipList)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL ||
		spaceShipList == NULL ||
		this->currentVehicleName == NULL)
	{
		printf("EROR: empty parameter at setInitials_Person!\n");
		return;
	}

	this->currentVehicle = NULL; // initial value for now
	for (size_t i = 0; i < spaceShipList->size ; i++)
	{
		SpaceShip spaceShip = (SpaceShip)(spaceShipList->getByIndex(spaceShipList, i));
		if (spaceShip != NULL && spaceShip->name != NULL)
		{
			/* IF SHIP EXISTS SET VALUE */
			if (equalsIgnoreCase(this->currentVehicleName, spaceShip->name))
			{
				this->currentVehicle = spaceShip;
				break;
			}
		}
	}
}

bool	isAlive(const Person this)
{
	/* CHECKING THE PARAMETERS */
    if (this == NULL)
    {
        printf("Eror: person is null at isAlive \n");
        return false;
    }

	/* ISALIVE */
    if (this->hoursLeftToLive <= 0.0)
    {
        return false;
    }else
        return true;
}

void	delete_Person(Person this)
{
    if (this == NULL)
        return;
    
    if (this->name != NULL)
        free(this->name);

    if (this->currentVehicleName != NULL)
        free(this->currentVehicleName);

    if (this->listener != NULL)
        free(this->listener);

    free(this);
}

/* OVERRIDE METHOD */
void	onTimePass_Person(const Person this)
{
    if (this == NULL)
    {
        printf("Error: onTimePass_Person 'this' NULL!\n");
        return;
    }
    reduceHoursLeftToLive(this);
}