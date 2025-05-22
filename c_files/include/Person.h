/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/




#ifndef PERSON_H
#define PERSON_H

#include "ITimeListener.h"
#include "SpaceShip.h"
#include "ArrayList.h"
#include "StringUtils.h"

struct PERSON
{
    char*			name;
    char*			currentVehicleName;
    int				age;
    double			hoursLeftToLive;
    ITimeListener	listener;
    SpaceShip		currentVehicle;

    void	(*setInitials_Person)(struct PERSON*, ArrayList);
    bool	(*isAlive)(struct PERSON*);
    void	(*delete_Person)(struct PERSON*);
    void	(*onTimePass)(struct PERSON*); // interface implementation method
};

typedef struct PERSON* Person;

Person	new_Person(const char*, int, double, const char*);
void	setInitials_Person(const Person, ArrayList);
bool	isAlive(const Person);
void	delete_Person(Person);
void	onTimePass_Person(const Person);

#endif