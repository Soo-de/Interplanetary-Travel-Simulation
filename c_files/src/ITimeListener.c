/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 02.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "ITimeListener.h"

ITimeListener	new_ITimeListener()
{
	/* MEMORY ALLOCATION FOR TIMELISTENER */
	ITimeListener this = (ITimeListener)malloc(sizeof(struct ITIMELISTENER));
	if ( this == NULL)
	{
		printf("memory allocation failed at ITimeListener");
		return (NULL);
	}

	/* LINKS */
	this->runFunctions = &runFunctions;
	/* END OF LINKS */

    return (this);
}

void			runFunctions(ITimeListener this, void* pointer)
{
	/* CHECKING THE PARAMETERS BEFORE FUNCTION CALL */
	if ((this != NULL) && (pointer != NULL) && (this->onTimePass != NULL))
	{
		this->onTimePass(pointer);
	}
}
