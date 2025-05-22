/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 11.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#ifndef FILEREADER_H
#define FILEREADER_H

/* GLOBAL LIBRARIES */
#include <stdio.h>		// for printf
#include <stdlib.h>		// for memory allocations
/* END OF GLOBAL LIBRARIES */

/* LOCAL LIBRARIES */
#include "ArrayList.h"
#include "Person.h"
#include "SpaceShip.h"
#include "Planet.h"
#include "TerrestrialPlanet.h"
#include "GasGiantPlanet.h"
#include "IceGiantPlanet.h"
#include "DwarfPlanet.h"
#include "Exception.h"
#include "StringUtils.h"
/* END OF LOCAL LIBRARIES */

struct FILEREADER
{
	char*	path;
	char*	content;

	ArrayList	(*readPersons)(struct FILEREADER*);
	ArrayList	(*readVehicles)(struct FILEREADER*);
	ArrayList	(*readPlanets)(struct FILEREADER*);
	void		(*delete_FileReader)(struct FILEREADER*);
};

typedef struct FILEREADER* FileReader;

FileReader	new_FileReader(const char*);
ArrayList	readPersons(const FileReader);
ArrayList	readVehicles(const FileReader);
ArrayList	readPlanets(const FileReader);
void		freeGlobalPlanetLists();
void		delete_FileReader(FileReader);

#endif