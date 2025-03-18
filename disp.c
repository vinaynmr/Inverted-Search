#include "main.h"

status display_hashtable(m_node *hash[])
{
	//traverse and print if data exists
	int count = 0;
	for(int i = 0; i < 27; i++)
	{
		//index has some nodes
		if(hash[i] != NULL)
		{
			m_node *main_temp = hash[i];
			//printing of main nodes in index
			while(main_temp != NULL)
			{
				printf("[%d] [%s] (%d) file/s     ",i,main_temp -> word,main_temp -> file_count);
				s_node *sub_temp = main_temp -> sub_link;
				//printing of sub nodes existing in main nodes
				while(sub_temp != NULL)
				{
					printf("FILE: %s (%d) time(s) ",sub_temp -> file_name,sub_temp -> word_count);
					sub_temp = sub_temp -> sub_link;
				}
				main_temp = main_temp -> main_link;
				printf("\n");
			}
			count++;
		}
	}
	//if table is empty
	if(count == 0)
	{
		printf("Hash Table is empty\n");
		return FAILURE;
	}
	return SUCCESS;
}
