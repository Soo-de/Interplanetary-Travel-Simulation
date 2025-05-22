/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 11.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <ctype.h>   	// tolower
#include <string.h>  	// strlen
#include <stdbool.h> 	// bool, true, false
#include <stdlib.h>  	// malloc, realloc, free

bool	equalsIgnoreCase(const char* , const char* );
char**	split(const char* , char , int* );
void	freeSplit(char** , int );

#endif 
