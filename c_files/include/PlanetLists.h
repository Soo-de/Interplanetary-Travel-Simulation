/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 17.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#ifndef PLANETLISTS_H
#define PLANETLISTS_H

#include "ArrayList.h"

static ArrayList	dwarfList = NULL;
static ArrayList	gasGiantList = NULL;
static ArrayList	iceGiantList = NULL;
static ArrayList	terrestrialList = NULL;

void	freeGlobalPlanetLists();

#endif