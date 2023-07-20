#include "my_shell.h"

/**
 * reallocate - Reallocates a block of memory
 * @ptr: Pointer to the previous malloc'ed block
 * @old_size: Byte size of the previous block
 * @new_size: Byte size of the new block
 * Return: Pointer to the reallocated memory block, or NULL if failure
 */
void *reallocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	/* Check if ptr is NULL  equivalent to malloc(new_size) */
	if (ptr == NULL)
		return (malloc(new_size));

	/* Check if new_size is 0; equivalent to free(ptr) and return NULL */
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	/* Check if new_size is the same as old_size, return the original ptr */
	if (new_size == old_size)
		return (ptr);

	/* Allocate memory for the new block. */
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		perror("Error in _realloc: Memory allocation failed");
		return (NULL);
	}

	/* Copy data from the old block to the new block. */
	if (new_size > old_size)    /* check */
		memcpy(new_ptr, ptr, old_size);
	else                        /* check */
		memcpy(new_ptr, ptr, new_size);

	/* Free the old block. */
	free(ptr);

	return (new_ptr);
}


/**
 * memofill - Fills memory with a constant byte
 * @s: Pointer to the memory area
 * @b: The byte that th s will be filled with
 * @n: The number of bytes to be filled
 * Return: Pointer to the memory area @s.
 */
char *memofill(char *s, char b, unsigned int n)
{
	if (s == NULL)
	{
		perror("Error in _memset: Provided pointer is NULL");
		return (NULL);
	}

	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}

	return (s);
}

/**
 * funfree - Frees a string of strings.
 * @pp: Pointer to the string of strings.
 */
void funfree(char **pp)
{
	if (pp == NULL)
	{
		perror("Error in ffree: Invalid input pointer");
		return;
	}

	char **temp_ptr = pp;

	/* Free each individual string in the array. */
	for (; *pp != NULL; pp++)
	{
		free(*pp);
	}

	/* Free the array of pointers itself. */
	free(temp_ptr);
}

/**
 * freememo - Frees the dynamic allocated memory
 * @ptr: the Address of the pointer to be free
 * Return: 1 if the pointer is freed else return 0
 */
int freememo(void **ptr)
{
	if (ptr == NULL)
	{
		perror("Error in bfree: Invalid input pointer");
		return (0);
	}

	if (*ptr == NULL)
	{
		perror("Error in freememo: Nothing to free or the pointer is already NULL");
		return (0);
	}

	free(*ptr);
	*ptr = NULL;

	return (1);
}
