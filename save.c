#include "main.h"

status save_validation(m_node *hash[])
{
	//check if table is empty or not
	int count = 0;
	for(int i = 0; i < 27; i++)
	{
		if(hash[i] != NULL)
			count++;
	}
	if(count == 0)
		return HASHTABLE_IS_EMPTY;
	return SUCCESS;
}


status save_hashtable(m_node *hash[],FILE *fp)
{
	char file[100];
label:
	//file name to save
	printf("Enter the file name u want to save: ");
	scanf("%s",file);
	//file should be csv file
	if(!strstr(file,".csv"))
	{
		printf("\nERROR: enter the proper extension file!\n\n");
		printf("\nDo you want to continue [YES -> 1] / [NO -> 0]: ");
		int cont;
		scanf("%d",&cont);
		if(cont == 1)
			goto label;
		else
			return FAILURE;
	}
	//open file to write data
	fp = fopen(file,"w");
	if(fp == NULL)
		return FAILURE;
	//check each node and write data
	for(int i = 0; i < 27; i++)
	{
		if(hash[i] != NULL)
		{
			m_node *main_temp = hash[i];
			while(main_temp != NULL)
			{
				//main node data writing 
				fprintf(fp,"#%d,%s,%d,",i,main_temp -> word,main_temp -> file_count);
				s_node *sub_temp = main_temp -> sub_link;
				//sub node data writing
				for(int j = 0; j < (main_temp -> file_count); j++)
				{
					fprintf(fp,"%s,%d,",sub_temp -> file_name,sub_temp -> word_count);
					sub_temp = sub_temp -> sub_link;
				}
				fprintf(fp,"#\n");
				main_temp = main_temp -> main_link;
			}
		}
	}
	return SUCCESS;
}
