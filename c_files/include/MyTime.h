/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 02.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#ifndef MYTIME_H
#define MYTIME_H

/* GLOBAL LIBRARIES */
#include <stdlib.h>			//for memory allocation
#include <stdio.h>			//for printf
/* END OF GLOBAL LIBRARIES */

/* LOCAL LIBRARIES */
#include "ArrayList.h"
#include "SpaceShip.h"
#include "Planet.h"
#include "Person.h"
/* END OF LOCAL LIBRARIES */

struct MYTIME
{
    long	(*getGlobalTime)();
    void	(*advanceTime)(ArrayList, ArrayList, ArrayList);
    void	(*delete_Time)(struct MYTIME*);
};

typedef struct MYTIME* MyTime;

MyTime	new_Time();
long	getGlobalTime();
void	advanceTime(ArrayList, ArrayList, ArrayList);
void	delete_Time(MyTime);

#endif


