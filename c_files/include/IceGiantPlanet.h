/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#ifndef ICEGIANTPLANET_H
#define ICEGIANTPLANET_H

#include "Planet.h"

struct ICEGIANTPLANET
{
    Planet	super;

    void	(*delete_IceGiantPlanet)(struct ICEGIANTPLANET*);
};

typedef struct ICEGIANTPLANET* IceGiantPlanet;

IceGiantPlanet	new_IceGiantPlanet(const char*, int,int, int, int, int);
void			delete_IceGiantPlanet(IceGiantPlanet);

#endif