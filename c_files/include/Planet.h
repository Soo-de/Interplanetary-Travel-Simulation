/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 02.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#ifndef PLANET_H
#define PLANET_H

#include "MyLocalTime.h"
#include "ITimeListener.h"
#include "ArrayList.h"

struct PLANET
{
    char*			name;
    int				planetType;
    int				hoursOfADay;
    int				currentHour;
    int				population;
    MyLocalTime		currentDate;
    ITimeListener	listener;
    ArrayList		allShips;

    double	(*getDecayRate)(struct PLANET*);
    void	(*setInitials_Planet)(struct PLANET*, ArrayList);
    void	(*updatePopulation)(struct PLANET*);
    void	(*delete_Planet)(struct PLANET*);
};

typedef struct PLANET* Planet;

Planet	new_Planet(const char*,int,int ,int, int, int);
double	getDecayRate(const Planet);
void	updatePopulation(const Planet);
void	setInitials_Planet(const Planet, ArrayList);
void	delete_Planet(Planet);
void	onTimePass_Planet(const Planet);

#endif