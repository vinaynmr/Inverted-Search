#include "main.h"
status search_hashtable(m_node *hash[],char *word)
{
	//check each index
	int count = 0,i = 0;
	if(word[0] >= 65 && word[0] <= 90)
		i = (word[0] + 32) - 97;
	else if(word[0] >= 97 && word[0] <= 122)
		i = word[0] - 97;
	else
		i = 26;
	printf("%d -> %d\n",i,word[0]);
	if(hash[i] != NULL)
	{
		count++;
		m_node *main_temp = hash[i];
		//check all main nodes in index
		while(main_temp != NULL)
		{
			//check for word in all main nodes of particular index
			if(!strcmp(main_temp -> word,word))
			{
				//print data of main node if found
				printf("Word => [%s] present in %d files:\n",main_temp -> word,main_temp -> file_count);
				s_node *sub_temp = main_temp -> sub_link;
				//print all sub nodes of main node if found
				while(sub_temp != NULL)
				{
					printf("In File: %s present %d time(s)\n",sub_temp -> file_name,sub_temp -> word_count);
					sub_temp = sub_temp -> sub_link;
				}
				return SUCCESS;
			}
			main_temp = main_temp -> main_link;
		}
		//data doesn't exist
		return DATA_NOT_FOUND;
	}else //index is empty
		return HASHTABLE_IS_EMPTY;
}
