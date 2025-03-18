#include "main.h"

status print_list(slist *head)
{
	//if list is empty
	if(head == NULL)
		return FAILURE;
	slist *temp = head;
	//if list is not empty
	printf("Head -> ");
	while(temp != NULL)
	{
		printf("%s -> ",temp -> f_name);
		temp = temp -> s_next;
	}
	printf("NULL\n");
	return SUCCESS;
}
