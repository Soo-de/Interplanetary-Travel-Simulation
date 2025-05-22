/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 14.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "StartSim_Facade.h"

int main()
{
	StartSim_Facade sim = new_StartSim_Facade();
	if (sim == NULL)
	{
		printf("Memory allocation failed at main\n");
		return (1);
	}
	sim->runSim(sim);
	sim->delete_StartSim_Facade(sim);

	return (0);
}