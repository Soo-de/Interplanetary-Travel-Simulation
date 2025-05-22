/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "TerrestrialPlanet.h"

TerrestrialPlanet	new_TerrestrialPlanet(const char* name, int planetType,int hoursOfADay, int day, int month, int year)
{
	/* CHECKING THE PARAMETERS */
	if (name == NULL)
	{
		printf("Memory allocation failed at new_TerrestrialPlanet due to name \n");
		return (NULL);
	}

	/* MEMORY ALLOCATION FOR TERRESTRIAL PLANET */
	TerrestrialPlanet this = (TerrestrialPlanet)malloc(sizeof(struct TERRESTRIALPLANET));
	if (this == NULL)
	{
		printf("Memory allocation failed at new_TerrestrialPlanet\n");
		return (NULL);
	}

	/* MEMORY ALLOCATION FOR PLANET */
	this->super = new_Planet(name, planetType,hoursOfADay, day, month, year);
	if (this->super == NULL)
	{
		printf("Memory allocation failed at new_TerrestrialPlanet Planet\n");
		free(this);
		return (NULL);
	}

	/* LINKS */
	this->delete_TerrestrialPlanet = &delete_TerrestrialPlanet;
	/* END OF LINKS */

	return (this);
}

void				delete_TerrestrialPlanet(TerrestrialPlanet this)
{
	if (this == NULL)
		return;

	if (this->super != NULL)
		this->super->delete_Planet(this->super);

	free(this);
}