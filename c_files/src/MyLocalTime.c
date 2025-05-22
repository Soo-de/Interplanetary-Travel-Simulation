/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 02.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "MyLocalTime.h"

MyLocalTime	new_MyLocalTime(int day, int month, int year)
{
    /* MEMORY ALLOCATION FOR MYLOCALTIME */
	MyLocalTime this = (MyLocalTime)malloc(sizeof(struct MYLOCALTIME));
	if (this == NULL)
	{
		printf("Memory allocation failed at MyLocalTime\n");
		return (NULL);
	}

	/* MEMORU ALLOCATION FOR DATETIME*/
	this->date = (DateTime)malloc(sizeof(struct tm));
	if (this->date == NULL)
	{
		printf("Memory allocation failed at MyLocalTime Date\n");
		free(this);
		return (NULL);
	}
	/* SET INITIAL VALUES */
    this->date->tm_year = year - 1900;  // tm_year is years since 1900
    this->date->tm_mon = month - 1;     // tm_mon is months since January
    this->date->tm_mday = day;          // tm_mday is the day of the month
    mktime(this->date);                 // Normalize the date structure

	/* LINKS */
    this->clone_MyLocalTime = &clone_MyLocalTime;
	this->toString = &toString;
	this->advanceDay = &advanceDay;
	this->isEqual = &isEqual;
	this->daysBetween = &daysBetween;
	this->delete_MyLocalTime = &delete_MyLocalTime;
	/* END OF LINKS */

	return (this);
}

MyLocalTime clone_MyLocalTime(const MyLocalTime this)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL || this->date == NULL)
	{
		printf("Cannot clone: original MyLocalTime is NULL.\n");
		return (NULL);
	}

	int day = this->date->tm_mday;
	int month = this->date->tm_mon + 1;
	int year = this->date->tm_year + 1900;

    // CREATE NEW MYLOCALTIME TO COPY TO
	MyLocalTime copy = new_MyLocalTime(day, month, year);

	return (copy);
}

char*       toString(const MyLocalTime this)
{
	/* CHECKING THE PARAMETERS */
    if (this == NULL || this->date == NULL)
    {
        printf("Cannot convert to string: MyLocalTime is NULL.\n");
        return NULL;
    }

	/* BUFFER TO WRITE DATE */
    char* buffer = (char*)malloc(20 * sizeof(char));
    if (buffer == NULL)
    {
        printf("Memory allocation failed at toString\n");
        return (NULL);
    }
    strftime(buffer, 20, "%d.%m.%Y", this->date);

    return (buffer);
}

void        advanceDay(const MyLocalTime this, int daysToAdd)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL || this->date == NULL)
	{
		printf("Cannot advance day: MyLocalTime is NULL.\n");
		return;
	}

	/* ADVANCE DAY */
	this->date->tm_mday += daysToAdd;
	mktime(this->date);
}

bool        isEqual(const MyLocalTime this, const MyLocalTime that)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL || that == NULL || this->date == NULL || that->date == NULL)
	{
		printf("Cannot compare: one of the MyLocalTime is NULL.\n");
		return false;
	}

	return ((this->date->tm_year == that->date->tm_year) &&
			(this->date->tm_mon == that->date->tm_mon) &&
			(this->date->tm_mday == that->date->tm_mday));
}

long        daysBetween(const MyLocalTime this, const MyLocalTime that)
{
	/* CHECKING THE PARAMETERS */
    if (this == NULL || that == NULL || this->date == NULL || that->date == NULL)
    {
        printf("Cannot calculate days between: one of the MyLocalTime is NULL.\n");
        return -1;
    }

	/* CALCULATE DAYS BETWEEN */
	time_t t1 = mktime(this->date);
	time_t t2 = mktime(that->date);
	double seconds = difftime(t1, t2);
	return ((long)(seconds / (60 * 60 * 24))); // Convert seconds to days
}

void        delete_MyLocalTime(MyLocalTime this)
{
	if (this != NULL)
	{
		if (this->date != NULL)
		{
			free(this->date);
		}
		free(this);
	}
}