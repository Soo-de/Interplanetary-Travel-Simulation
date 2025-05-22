/**
*
*@author Sude Andurman	sude.andurman@ogr.sakarya.edu.tr
*@since 11.05.2025
*<p>
*	Bilgisayar Mühendisliği 2. Sınıf 
*	Programlama Dilleri Prensipleri 1/C şubesi 
*</p>
*/

#include "StringUtils.h"

/* PRIVATE FUNCTIONS */
char**	checkCapacity(char** tokens, int* capacity, int size)
{
    /* IF THE CAPACITY IS NOT ENOUGH DOUBLE IT */
	if (size >= *capacity)
	{
		*capacity *= 2;
		tokens = realloc(tokens, sizeof(char*) * (*capacity));
		if (!tokens)
			return (NULL);  // IF REALLOC FAILS RETURN NULL
    }
    return (tokens);
}
/* END OF PRIVATE FUNCTIONS */

bool	equalsIgnoreCase(const char* string1, const char* string2)
{
	/* CHECKING THE PARAMETERS */
	if (string1 == NULL || string2 == NULL) 
		return false;

	while (*string1 && *string2)
	{
		if (tolower((unsigned char)*string1) != tolower((unsigned char)*string2)) {
			return false;
		}
		string1++;
		string2++;
	}

	/* IF BOTH STRINGS AT THE FINISHER CHAR RETURN TRUE */
	return (*string1 == '\0' && *string2 == '\0');
}

char**	split(const char* str, char delimiter, int* count)
{
	/* CHECKING THE PARAMETERS */    
	if (!str || !count)
		return (NULL);

	int capacity = 5;	// INTIAL CAPACITY
	int size = 0;		// TOKEN COUNT

	char** tokens = (char**)malloc(sizeof(char*) * capacity);
	if (!tokens) return (NULL);

	const char* start = str;	// STRING'S START INDEX
	const char* ptr = str;		// POINTER TO READ STRING TILL THE END

	while (*ptr)
	{
		// IF CHAR EQUAL TO DELIMITER CHAR THEN WE HAVE THE FIRST TOKEN
		if (*ptr == delimiter) 
		{
			int len = ptr - start;					// FIRST TOKEN LENGTH
			char* token = (char*)malloc(len + 1);	// MALLOC FOR TOKEN
			if (!token) continue;

			strncpy(token, start, len);				// COPY FIRST STRING TO TOKEN LIST
			token[len] = '\0';

			// CHECK CAPACITY
			tokens = checkCapacity(tokens, &capacity, size);
			if (!tokens) return (NULL);

			tokens[size++] = token;					// ADD TOKEN TO THE LIST
			start = ptr + 1;						// SECOND TOKEN START POINT
		}
		ptr++; // MOVE TO THE NEXT CHAR ON STRING
	}

	// FOR THE LAST TOKEN
	if (ptr != start)
	{
		int len = ptr - start;
		char* token = (char*)malloc(len + 1);
		strncpy(token, start, len);
		token[len] = '\0';

		tokens = checkCapacity(tokens, &capacity, size);
		if (!tokens) return NULL;
		tokens[size++] = token;
	}

	*count = size;	// TOKEN COUNT 
	return (tokens);
}

void	freeSplit(char** tokens, int count)
{
	/* CHECKING THE PARAMETERS */
	if (!tokens) return;

	/* FREE THE TOKENS */
	for (int i = 0; i < count; i++)
	{
		free(tokens[i]);
	}
	
	free(tokens);
}
