/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 04.04.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/


package app;

public class Simulation {

	public static void main(String[] args)
	{
		/* MAKE AN OBJECT FROM FACADE */
		StartSim_Facade start;
		start = new StartSim_Facade();
		
		/* START THE SIM */
		start.runSim();
	}

}
