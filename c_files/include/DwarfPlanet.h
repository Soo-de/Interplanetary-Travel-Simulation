/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/



#ifndef DWARFPLANET_H
#define DWARFPLANET_H

#include "Planet.h"

struct DWARFPLANET
{
	Planet	super;

	void	(*delete_DwarfPlanet)(struct DWARFPLANET*);
};

typedef struct DWARFPLANET* DwarfPlanet;

DwarfPlanet	new_DwarfPlanet(const char*,int ,int, int, int, int);
void		delete_DwarfPlanet(DwarfPlanet);


#endif