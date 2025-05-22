/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 17.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "PlanetLists.h"
#include "DwarfPlanet.h"
#include "TerrestrialPlanet.h"
#include "IceGiantPlanet.h"
#include "GasGiantPlanet.h"

void	freeGlobalPlanetLists()
{
	if (terrestrialList != NULL)
	{
		for (int i = 0; i < terrestrialList->size; i++)
		{
			TerrestrialPlanet tp = (TerrestrialPlanet)terrestrialList->getByIndex(terrestrialList, i);
			delete_TerrestrialPlanet(tp);
		}
		terrestrialList->detele_ArrayList(terrestrialList);
		terrestrialList = NULL;
	}

	if (gasGiantList != NULL)
	{
		for (int i = 0; i < gasGiantList->size; i++)
		{
			GasGiantPlanet gp = (GasGiantPlanet)gasGiantList->getByIndex(gasGiantList, i);
			delete_GasGiantPlanet(gp);
		}
		gasGiantList->detele_ArrayList(gasGiantList);
		gasGiantList = NULL;
	}

	if (iceGiantList != NULL)
	{
		for (int i = 0; i < iceGiantList->size; i++)
		{
			IceGiantPlanet ip = (IceGiantPlanet)iceGiantList->getByIndex(iceGiantList, i);
			delete_IceGiantPlanet(ip);
		}
		iceGiantList->detele_ArrayList(iceGiantList);
		iceGiantList = NULL;
	}

	if (dwarfList != NULL)
	{
		for (int i = 0; i < dwarfList->size; i++)
		{
			DwarfPlanet dp = (DwarfPlanet)dwarfList->getByIndex(dwarfList, i);
			delete_DwarfPlanet(dp);
		}
		dwarfList->detele_ArrayList(dwarfList);
		dwarfList = NULL;
	}
}