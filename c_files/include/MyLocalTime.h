/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 02.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/


#ifndef MYLOCALTIME_H
#define MYLOCALTIME_H

#include <stdio.h>		//for printf
#include <stdlib.h>		//for memory allocation
#include <time.h>		//for time functions
#include <stdbool.h>	//for boolean type and comparisons
#include <string.h>		//for string functions

typedef struct tm* DateTime;

struct MYLOCALTIME
{
	DateTime	date;

	char*				(*toString)(struct MYLOCALTIME*);
	struct MYLOCALTIME*	(*clone_MyLocalTime)(struct MYLOCALTIME*);
	bool				(*isEqual)(struct MYLOCALTIME*, struct MYLOCALTIME*);
	long				(*daysBetween)(struct MYLOCALTIME*, struct MYLOCALTIME*);
	void				(*advanceDay)(struct MYLOCALTIME*, int);
	void				(*delete_MyLocalTime)(struct MYLOCALTIME*);
};

typedef struct MYLOCALTIME* MyLocalTime;

MyLocalTime	new_MyLocalTime(int, int, int);
MyLocalTime	clone_MyLocalTime(const MyLocalTime);
char*		toString(const MyLocalTime);
bool		isEqual(const MyLocalTime, const MyLocalTime);
long		daysBetween(const MyLocalTime, const MyLocalTime);
void		advanceDay(const MyLocalTime, int);
void		delete_MyLocalTime(MyLocalTime);

#endif