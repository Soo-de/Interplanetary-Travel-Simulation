/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 11.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h> // for size_t
#include <stdlib.h> // for malloc, free
#include <stdio.h>  // for printf
#include <string.h> // for memcpy


struct ARRAYLIST
{
	void**	array;
	int		size;
	int		capacity;

	void*	(*getByIndex)(struct ARRAYLIST*, size_t);
	void	(*add)(struct ARRAYLIST*, void*);
	void	(*removeAt)(struct ARRAYLIST*, size_t);
	void	(*detele_ArrayList)(struct ARRAYLIST*);

};

typedef struct ARRAYLIST* ArrayList;

ArrayList	new_ArrayList();
void*		getByIndex(ArrayList, size_t);
void		add(ArrayList, void*);
void		removeAt(ArrayList, size_t);
void		detele_ArrayList(ArrayList);

#endif