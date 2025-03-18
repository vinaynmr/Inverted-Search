#include "main.h"

m_node *create_main_node(char *word)
{
	//allocate memory for main node
	m_node *main_new = malloc(sizeof(m_node));
	if(main_new == NULL)
	{
		printf("New node creation has been failed!\n");
		return NULL;
	}
	//update node data
	strcpy(main_new -> word,word);
	main_new -> file_count = 1;
	main_new -> main_link = NULL;
	main_new -> sub_link = NULL;
	return main_new;
}

s_node* create_sub_node(char *file_name)
{
	//allocate memory for sub node
	s_node *sub_new = malloc(sizeof(s_node));
	if(sub_new == NULL)
	{
		printf("Subnode creation has been failed!\n"); 
		return NULL;
	}
	//update data
	strcpy(sub_new -> file_name,file_name);
   	sub_new -> word_count = 1;
	sub_new -> sub_link = NULL;
	sub_new -> sub_link = NULL;
	return sub_new;	
}
