/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 02.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/



#ifndef ITIMELISTENER_H
#define ITIMELISTENER_H

#include <stdio.h>
#include <stdlib.h>

struct ITIMELISTENER
{
    void	(*onTimePass)(); // Like interface method
    void	(*runFunctions)(struct ITIMELISTENER*, void*);
};

typedef struct ITIMELISTENER* ITimeListener;

ITimeListener	new_ITimeListener();
void			runFunctions(ITimeListener, void*);

#endif