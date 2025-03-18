#include "main.h"
status insert_at_last(slist **head,char *data)
{
	//allocate memory for new node
	slist *new = malloc(sizeof(slist));
	if(new == NULL)
		return FAILURE;
	//update new node
	new -> s_next = NULL;
	strcpy(new -> f_name,data);
	//if list is empty
	if(*head == NULL)
	{
		*head = new;
		return SUCCESS;
	}
	//if list is not empty
	slist *temp = *head;
	while(temp -> s_next != NULL)
		temp = temp -> s_next;
	temp -> s_next = new;
	return SUCCESS;
}
