/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "GasGiantPlanet.h"

GasGiantPlanet	new_GasGiantPlanet(const char* name, int planetType, int hoursOfADay, int day, int month, int year)
{
	/* CHECKING THE PARAMETERS */
    if (name == NULL)
    {
        printf("Memory allocation failed at new_GasGiantPlanet due to name \n");
        return (NULL);
    }

    /* MEMORY ALLOCATION FOR GAS GIANT PLANET */
    GasGiantPlanet this = (GasGiantPlanet)malloc(sizeof(struct GASGIANTPLANET));
    if (this == NULL)
    {
        printf("Memory allocation failed at new_GasGiantPlanet\n");
        return (NULL);
    }

    /* MEMORY ALLOCATION PLANET */
    this->super = new_Planet(name, planetType,hoursOfADay, day, month, year);
    if (this->super == NULL)
    {
        printf("Memory allocation failed at new_GasGiantPlanet Planet\n");
        free(this);
        return (NULL);
    }

	/* LINKS */
	this->delete_GasGiantPlanet = &delete_GasGiantPlanet;
	/* END OF LINKS */

	return (this);
}

void			delete_GasGiantPlanet(GasGiantPlanet this)
{
	if (this == NULL)
		return;

	if (this->super != NULL)
		this->super->delete_Planet(this->super);

	free(this);
}