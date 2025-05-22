/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/


#ifndef SPACESHIP_H
#define SPACESHIP_H

/* GLOBAL LIBRARIES */
#include <string.h> 	//strcmp
/* END OF GLOBAL LIBRARIES*/

/* LOCAL LIBRARIES */
#include "ITimeListener.h"
#include "MyLocalTime.h"
#include "Planet.h"
#include "ArrayList.h"
/* END OF LOCAL LIBRARIES*/


struct SPACESHIP
{
	char*			name;
	char*			currentPlanetName;
	char*			destPlanetName;
	char*			state;
	MyLocalTime		launchDate;
	MyLocalTime		arrivalDate;
	int				distanceLeft;
	int				passengersCount;
	ITimeListener	listener;
	Planet			currentPlanet;
	Planet			destPlanet;
	ArrayList		allPersons;

	void	(*setInitials_Ship)(struct SPACESHIP*, ArrayList, ArrayList);
	void	(*calculateArrivalDate)(struct SPACESHIP*);
	void	(*updatePassengers)(struct SPACESHIP*);
	void	(*delete_SpaceShip)(struct SPACESHIP*);
};

typedef struct SPACESHIP* SpaceShip;

SpaceShip	new_SpaceShip(const char*, const char*, const char*, int, int, int, int);
void		setInitials_Ship(const SpaceShip, ArrayList, ArrayList);
void		calculateArrivalDate(const SpaceShip);
void		updatePassengers(const SpaceShip);
void		delete_SpaceShip(SpaceShip);
void		onTimePass_Ship(const SpaceShip);

#endif


