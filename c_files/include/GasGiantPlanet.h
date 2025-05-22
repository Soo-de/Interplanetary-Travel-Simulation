/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#ifndef GASGIANTPLANET_H
#define GASGIANTPLANET_H

#include "Planet.h"

struct GASGIANTPLANET
{
    Planet	super;

    void	(*delete_GasGiantPlanet)(struct GASGIANTPLANET*);
};

typedef struct GASGIANTPLANET* GasGiantPlanet;

GasGiantPlanet	new_GasGiantPlanet(const char*, int,int, int, int, int);
void			delete_GasGiantPlanet(GasGiantPlanet);

#endif