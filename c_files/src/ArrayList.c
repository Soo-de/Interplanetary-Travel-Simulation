/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 11.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "ArrayList.h"

#define INITIAL_CAPACITY 2

ArrayList	new_ArrayList()
{
	/* MEMORY ALLOCATION FOR ARRAYLIST */
	ArrayList this = (ArrayList)malloc(sizeof(struct ARRAYLIST));
	if (this == NULL)
	{
		printf("Memory allocation failed at new_ArrayList\n");
		return (NULL);
	}

	/* SET INITIALS VALUES*/
	this->size = 0;
	this->capacity = INITIAL_CAPACITY;

	/* MEMORY ALLOCATION FOR ARRAY */
	this->array = (void**)malloc(this->capacity * sizeof(void*));
	if (this->array == NULL)
	{
		printf("Memory allocation failed at new_ArrayList array\n");
		free(this);
		return (NULL);
	}

	/* LINKS */
	this->add = &add;
	this->getByIndex = &getByIndex;
	this->removeAt = &removeAt;
	this->detele_ArrayList = &detele_ArrayList;
	/* END OF LINKS */

	return (this);
}

void		add(ArrayList this, void* item)
{
	/* CHECKING THE PARAMETERS*/
	if (this == NULL || item == NULL)
	{
		printf("Couldn't add the item to ArrayList due to parameters \n");
		return;
	}

	/* IF THE CAPACITY IS NOT ENOUGH */
	/* 		  REALLOC MEMORY         */
	if (this->size >= this->capacity)
	{
		this->capacity *= 2;
		this->array = realloc(this->array, this->capacity * sizeof(void*));
		if (this->array == NULL)
		{
			printf("Memory allocation failed at add/ArrayList\n");
			return;
		}
	}

	/* ADD NEW ITEM TO THE LIST */
	this->array[this->size++] = item;
}

void*		getByIndex(ArrayList this, size_t index)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL)
		return (NULL);

	if (index < 0 || index >= this->size)
	{
		printf("Index out of bounds at get/ArrayList\n");
		return (NULL);
	}

	/* GET ITEM BY INDEX */
	return (this->array[index]);
}

void		removeAt(ArrayList this, size_t index)
{
	/* CHECKING THE PARAMETERS */
	if (this == NULL)
		return;
	if (index < 0 || index >= this->size)
	{
		printf("Index out of bounds at remove/ArrayList\n");
		return; 
	}

	/* FIND THE INDEX AND RELINK INDEXES */
    for (size_t i = index; i < this->size - 1; i++)
    {
        this->array[i] = this->array[i + 1];
    }
    this->size--;
}

void		detele_ArrayList(ArrayList this)
{
	if (this == NULL)
		return;

	if (this->array != NULL)
	{
		free(this->array);
	}

	free(this);
}