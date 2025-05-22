/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/



#include "DwarfPlanet.h"

DwarfPlanet	new_DwarfPlanet(const char* name, int planetType, int hoursOfADay, int day, int month, int year)
{
	/* CHECKING THE PARAMETERS */
	if (name == NULL)
	{
		printf("Memory allocation failed at new_DwarfPlanet due to name \n");
		return (NULL);
	}

	/* MEMORY ALLOCATION FOR DWARF PLANET */
    DwarfPlanet this = (DwarfPlanet)malloc(sizeof(struct DWARFPLANET));
    if (this == NULL)
    {
        printf("Memory allocation failed at new_DwarfPlanet\n");
        return (NULL);
    }

    /* MEMORY ALLOCATION FOR PLANET */
	this->super = new_Planet(name, planetType, hoursOfADay, day, month, year);
	if (this->super == NULL)
	{
		printf("Memory allocation failed at new_DwarfPlanet Planet\n");
		free(this);
		return (NULL);
    }

	/* LINKS */
	this->delete_DwarfPlanet = &delete_DwarfPlanet;
	/* END OF LINKS */
    
	return (this);
}

void		delete_DwarfPlanet(DwarfPlanet this)
{
    if (this == NULL)
        return;

    if (this->super != NULL)
        this->super->delete_Planet(this->super);

    free(this);
}