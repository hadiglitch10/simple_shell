#include "my_shell.h"

/**
 * get_node_index - Gets the index of a node in the linked list
 * @head: Pointer to the list head
 * @node: Pointer to the node that the index has to be found
 * Return: Index of the node or -1 if it failed or it equals to NULL
 */
ssize_t get_node_index(list_s *head, list_s *node)
{
	if (head == NULL)
	{
		perror("get_node_index - Invalid head pointer");
		return (-1);
	}

	size_t index = 0;
		/* check and move to the next node untill it equals NULL*/
	for (list_s *current = head; current; current = current->nxt, index++)
	{
		if (current == node)
			return (index);
	}

	/* If the node is not found, return -1*/
	return (-1);
}

/**
 * list_string - Converts the list->str elements into an array of strings
 * @head: Pointer to the first node of the linked list
 * Return: Array of strings or return NULL if head is NULL or the list is empty
 */
char **list_string(list_s *head)
{
	list_s *current_node = head;
	size_t num_elements = list_length(head), count;
	char **str_array;
	char *str_element;

	if (!head || num_elements == 0)
	{
		perror("list_string - Invalid head pointer or empty list");
		return (NULL);
	}

	str_array = malloc(sizeof(char *) * (num_elements + 1));
	if (!str_array)
	{
		perror("list_string - Memory allocation failed for array of strings");
		return (NULL);
	}

	for (count = 0; current_node; current_node = current_node->nxt, count++)
	{
		str_element = malloc(string_length(current_node->str) + 1);
		if (!str_element)
		{
			perror("list_string - Memory allocation failed for string element");
			for (size_t j = 0; j < count; j++)
				free(str_array[j]);
			free(str_array);
			return (NULL);
		}

		str_element = string_cpy(str_element, current_node->str);
		str_array[count] = str_element;
	}

	str_array[count] = NULL; /* Null-terminate the array of strings*/

	return (str_array);
}

/**
 * delete_node - Deletes a node at the given index
 * @head: Address of pointer to the first node
 * @index: Index of the node to be deleted
 * Return: 1 on success, 0 if failure or invalid input
 */
int delete_node(list_s **head, unsigned int index)
{
	if (head == NULL || *head == NULL)
	{
		perror("delete_node - Invalid head pointer or empty list");
		return (0);
	}

	if (index == 0)
	{
		list_s *node = *head;
		*head = (*head)->nxt;
		free(node->str);
		free(node);
		return (1);
	}

	list_s *node = *head;
	list_s *prev_node = NULL;
	unsigned int i = 0;

	while (node != NULL)
	{
		if (i == index)
		{
			prev_node->nxt = node->nxt;
			free(node->str);
			free(node);
			return (1);
		}

		i++;
		prev_node = node;
		node = node->nxt;
	}

	perror("delete_node_at_index - Invalid index");
	return (0);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * and optionally matches the next character.
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match (-1 to ignore)
 * Return: Pointer to the matching node or NULL if not found.
 */
list_s *node_starts_with(list_s *head, const char *prefix, char c)
{
	if (!head || !prefix)
	{
		/* Invalid arguments, return NULL*/
		return (NULL);
	}
	while (head)
	{
		size_t prefix_len = string_length(prefix);
		const char *str = head->str;

		/* Check if the node's string starts with the prefix*/
		int prefix_match = 1;

		for (size_t i = 0; i < prefix_len; i++)
		{
			if (tolower(str[i]) != tolower(prefix[i]))
			{
				prefix_match = 0;
				break;
			}
		}
		/* Check the next character if provided*/
		if (prefix_match && (c != -1))
		{
			char next_char = str[prefix_len];

			if (tolower(next_char) != tolower(c))
			{
				prefix_match = 0;
			}
		}
		if (prefix_match)
		{
			return (head); /* Return the matching node*/
		}
		head = head->nxt; /* Move to the next node*/
	}

	return (NULL); /* No match found*/
}
/**
 * free_link_list - frees all the list
 * @head_ptr: address of pointer to the head node
 * Return: nothing
 */

void free_link_list(list_s **head_ptr)
{
	if (!head_ptr || !*head_ptr)
		return;

	list_s *current_node = *head_ptr;
	list_s *next_node = NULL;

	for (; current_node; current_node = next_node)
	{
		next_node = current_node->nxt;
		free(current_node->str);
		free(current_node);
	}

	*head_ptr = NULL;
}
