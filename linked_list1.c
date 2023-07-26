#include "my_shell.h"

/**
 * print_link_list - prints all elements of the linked list
 * @h: pointer to first node of the list
 * Return: size of the linked list
 */
size_t print_link_list(const list_s *h)
{
	size_t i = 0; /* Declare and initialize the size counter */
	/* Traverse the linked list until reaching the end (h becomes NULL)*/
	while (h != NULL)
	{
		/* Print the numeric data of the node */
		print_str(convert_num(h->numf, 10, 0));
		put_char(':');
		put_char(' ');

		/* Print the string data of the node or print "(nil)" if it's NULL */
		print_str(h->str ? h->str : "(nil)");

		/* Print a newline character to move to the next line */
		print_str("\n");

		/* Move to the next node and increment the size counter */
		h = h->nxt;
		i++;
	}

	return (i); /* Return the size of the list (number of nodes printed) */
}


/**
 * print_str_list - Prints only the strings element of a list_s linked list
 * @head: Pointer to the first node of the list
 * Return: The size of the linked list
 */

size_t print_str_list(const list_s *head)
{
	size_t count = 0;

	/* Traverse the linked list until reaching the end */
	while (head != NULL)
	{
		/* Print the string data of the node or "(nil)" if it's NULL */
		print_str(head->str ? head->str : "(nil)");

		/* Print a newline character to move to the next line */
		print_str("\n");

		head = head->nxt;
		count++;
	}

	return (count); /* Return the size of the linked list*/
}

/**
 * list_length - calculate the length of the linked list
 * @h: pointer to first node
 * Return: lenght of the list
 */
size_t list_length(const list_s *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		h = h->nxt;
		count++;
	}
	return (count);
}

/**
 * Add_node_begin - Adds a new node at the beginning of a linked list
 * @head: Pointer to a pointer to the first node of the list (address)
 * @str: The string to be stored in the new node
 * @num: The number to be stored in the new node
 * Return: Pointer to the new node or NULL if failure
 */

list_s *Add_node_begin(list_s **head, const char *str, int num)
{
	list_s *new_node = malloc(sizeof(list_s));

	if (head == NULL)
	{
		perror("Add_node_begin:  Invalid head pointer");
		return (NULL);
	}

	if (new_node == NULL)
	{
		perror("Add_node_begin: Memory allocation failed");
		return (NULL);
	}

	memset(new_node, 0, sizeof(list_s));
	new_node->numf = num;

	if (str != NULL)
	{
		new_node->str = strdup(str);
		if (new_node->str == NULL)
		{
			perror("Add_node_begin: Memory allocation failed for string");
			free(new_node);
			return (NULL);
		}
	}

	new_node->nxt = *head;
	*head = new_node;

	return (new_node);
}

/**
 * Add_node_end - Adds a new node to the end of a linked list
 * @head: Address of a pointer to the head node
 * @str: The string to be stored in the new node
 * @num: The node index used by history
 * Return: Pointer to the new node or NULL if failure
 */
list_s *Add_node_end(list_s **head, const char *str, int num)
{
	list_s *new_node = malloc(sizeof(list_s));

	if (head == NULL)
	{
		perror("Add_node_end: Invalid head pointer");
		return (NULL);
	}

	if (new_node == NULL)
	{
		perror("Add_node_end: Memory allocation failed");
		return (NULL);
	}

	memset(new_node, 0, sizeof(list_s));
	new_node->numf = num;

	if (str)
	{
		new_node->str = string_dupli(str);
		if (new_node->str == NULL)
		{
			perror("Add_node_end: Memory allocation failed for string");
			free(new_node); /* Free the new_node to avoid memory leak */
			return (NULL);
		}
	}

	new_node->nxt = NULL;
	if (*head != NULL)
	{
		list_s *node = *head;

		while (node->nxt)
			node = node->nxt;
		node->nxt = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
