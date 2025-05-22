/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 03.04.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/


package app;

/* IMPORTS */
import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
/* END OF IMPORTS */

public class MyLocalTime
{
	private LocalDate	currentDate;	// TO MANIPULATE THE OBJECT THE WAY WE WANT
	
	/* CONSTRUCTERS */
	
	public MyLocalTime (int day, int month, int year)
	{
		setCurrentDate(day, month, year);
	}
	public MyLocalTime (LocalDate localDate)
	{
		this.currentDate = localDate;
	}
	
	/* END OF CONSTRUCTERS */
	
	/* SETTER METHODS*/
	
	private void		setCurrentDate(int day, int month, int year)
	{
        this.currentDate = LocalDate.of(year, month, day);
    }
	
	/* END OF SETTER METHODS*/
	
	/* GETTER METHODS */
	
	public LocalDate	getCurrentDate()
	{
		return (currentDate);
	}
	
	/* END OF GETTER METHODS*/
	
	/* METHODS */
	
    public long		daysBetween(MyLocalTime other)
    {
    	// TO CALCULATE THE DAYS BETWEEN LEAVING DAY'S DATE AND CURRENT DATE
        return (ChronoUnit.DAYS.between(this.currentDate, other.getCurrentDate()));
    }
    
    public void		advanceDay()
    {
    	// TO ADVANCE DAY
    	this.currentDate = this.currentDate.plusDays(1);
    }
    
    public boolean isEqual(MyLocalTime other)
    {
    	// TO COMPARE DATES
        return (this.currentDate.equals(other.currentDate));
    }
	
	@Override
	public String	toString()
	{
		// TO WRITE THE DATE THE WAY WE WANT
		return String.format("%02d.%02d.%d",
							currentDate.getDayOfMonth(),
							currentDate.getMonthValue(),
							currentDate.getYear());
	}
	
}
