/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#ifndef TERRESTRIALPLANET_H
#define TERRESTRIALPLANET_H

#include "Planet.h"


struct TERRESTRIALPLANET
{
	Planet	super;

	void	(*delete_TerrestrialPlanet)(struct TERRESTRIALPLANET*);
};

typedef struct TERRESTRIALPLANET* TerrestrialPlanet;

TerrestrialPlanet	new_TerrestrialPlanet(const char*,int ,int, int, int, int);
void				delete_TerrestrialPlanet(TerrestrialPlanet);

#endif