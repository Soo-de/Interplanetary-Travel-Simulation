/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 12.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#ifndef STARTSIM_FACADE_H
#define STARTSIM_FACADE_H

/* GLOBAL LIBRARIES */
#include <stdlib.h>     // printf
#include <stdbool.h>    // boolean
/* END OF GLOBAL LIBRARIES*/

/* LOCAL LIBRARIES */
#include "ArrayList.h"
#include "FileReader.h"
#include "Person.h"
#include "Planet.h"
#include "MyTime.h"
#include "SpaceShip.h"
#include "Exception.h"
/* END OF LIBRARIES */

struct STARTSIM_FACADE
{
	ArrayList	allPlanets;
	ArrayList	allShips;
	ArrayList	allPersons;

	void	(*runSim)(struct STARTSIM_FACADE*);
	void	(*delete_StartSim_Facade)(struct STARTSIM_FACADE*);
};

typedef struct STARTSIM_FACADE* StartSim_Facade;

StartSim_Facade	new_StartSim_Facade();
void			runSim(const StartSim_Facade);
void			delete_StartSim_Facade(StartSim_Facade);

#endif


