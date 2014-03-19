#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALLNODESIZE 1000100
#define ARRAY_SIZE 1024
#define INPUT_SIZE 8000
#define STR_LENGTH 15
typedef struct _node{
	int team;
	int self;
	struct _node* nextnode;
}node;

typedef struct _nodelist{
	struct _node* headnode;
	struct _node* tailnode;
	struct _nodelist* nextlist;
}nodelist;

typedef struct _listlist{

	struct _nodelist* headlist;
	struct _nodelist* taillist;
}listlist;

void print_all_queue(listlist* alllist)
{
	nodelist* tmplist9 = alllist->headlist;
	node* tmpnode9 = NULL;
	printf("***  alllist:%x alllist->headlist:%x alllist->taillist:%x\n", alllist, alllist->headlist, alllist->taillist);
	while(tmplist9 != NULL)
	{
		tmpnode9 = tmplist9->headnode;
		printf("***  list:%x ", tmplist9);
		while(tmpnode9 != NULL)
		{
			printf("%x add:%x ", tmpnode9->self, tmpnode9);
			tmpnode9 = tmpnode9->nextnode;
		}
		printf("\n");
		tmplist9 = tmplist9->nextlist;
	}
}

int main()
{

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
#endif

	int phase = 0, team_counts = 0, member_counts = 0;
	int cnt1 = 0, cnt2 = 0, operation_target = 0, Scenario = 1;
	unsigned int offset = 0;
	nodelist *list[ARRAY_SIZE];
	int teamsize[ARRAY_SIZE];
	node *allnode[ALLNODESIZE], *tempnode_enqueue;
	listlist* alllist = (listlist*) calloc(1, sizeof(listlist));
	char rawinput[INPUT_SIZE], operation[STR_LENGTH];
	char str_member_counts[STR_LENGTH], str_element[STR_LENGTH];
	memset( rawinput, 0 , sizeof(char)*INPUT_SIZE);
	while( fgets( rawinput, INPUT_SIZE, stdin) != NULL )
	{
		if( rawinput == NULL || rawinput[0] == '0')
		{
			break;
		}
		switch( phase )
		{
			default:
			break;
			case 0:
			sscanf( rawinput, "%x", &team_counts);
			phase++;
			cnt1 = 0;
			printf("Scenario #%x\n",Scenario);
			Scenario++;

			break;

			case 1:
			memset( str_element, 0 , sizeof(char)*STR_LENGTH);
			sscanf( rawinput, "%x", &member_counts);
			sprintf( str_member_counts, "%x", member_counts);
			teamsize[ team_counts] = member_counts;
			offset = 0;
			for( cnt2 = 0; cnt2 < member_counts;cnt2++)
			{
				sscanf( &rawinput[strlen(str_member_counts)+offset+1],"%x", &operation_target);
				memset( str_element, 0 , sizeof(char)*STR_LENGTH);
				sprintf( str_element, " %x", operation_target);
				offset += strlen(str_element);
				if(allnode[operation_target] == NULL)
				{
					printf("malloc for allnode operation_target:%x\n", operation_target);
					allnode[operation_target] = (node*) calloc( 1, sizeof(node));
				}
				allnode[operation_target]->team = cnt1;
				allnode[operation_target]->self = operation_target;
			}
			cnt1++;
			if( cnt1 >= team_counts)
				phase++;

			break;
			case 2:
			sscanf(rawinput,"%s", operation);
			if(strcmp( operation,"STOP") == 0)
			{
				/**
				 * clear alllist and list[] here...
				*/

				for( cnt1 = 0; cnt1 < team_counts ; cnt1++)
				{
					if(list[cnt1] != NULL)
					{
						printf("list[%x] == %x\n", cnt1, list[cnt1]);
						list[cnt1] = NULL;
					}
				}
				/*free( alllist);*/
				phase = 0;
				printf("\n");
				break;
			}
			else if(strcmp( operation, "ENQUEUE") == 0)
			{
				sscanf( rawinput, "%s %x", operation, &operation_target);
				printf("%s %x\n", operation, operation_target);
				print_all_queue(alllist);
				/**  ENQUEUE here */

				/** 1. enqueue this list to list of lists, if this list hasn't enter the list of lists
				 * */

				if( list[ allnode[operation_target]->team] == NULL )
				{
					/**  TODO: try realloc
					 * */
					printf("calloc a list\n");
					list[allnode[operation_target]->team] = (nodelist*)calloc( 1, sizeof(nodelist));
					list[allnode[operation_target]->team]->headnode = NULL;
					list[allnode[operation_target]->team]->tailnode = NULL;
					list[allnode[operation_target]->team]->nextlist = NULL;
				}

				if(list[ allnode[operation_target]->team]->headnode == NULL && list[ allnode[operation_target]->team]->tailnode == NULL)
				{
					if(alllist->taillist == NULL)
					{
						/*printf("alllist->taillist == NULL\n");*/
						alllist->headlist = list[ allnode[operation_target]->team];
					}
					else
					{
						/*printf("alllist->taillist != NULL\n");*/
						alllist->taillist->nextlist = list[ allnode[operation_target]->team];
					}
					alllist->taillist = list[ allnode[operation_target]->team];
					if(alllist->taillist->nextlist != NULL)
					{
						/*printf("alllist->taillist->nextlist %x\n", alllist->taillist->nextlist);*/
					}

					/*printf("list:%x\n", list[ allnode[operation_target]->team]);*/
				}
				else
				{

					printf("list %d headnode tailnode != NULL headnode:%x tailnode:%x \n", allnode[operation_target]->team,
						list[ allnode[operation_target]->team]->headnode, list[ allnode[operation_target]->team]->tailnode);

				}



				/** 2. enqueue this node to the team list
				 * */
				/*printf("malloc for tempnode_enqueue\n");*/
				tempnode_enqueue = (node*) calloc( 1, sizeof(node));
				tempnode_enqueue->team = cnt1;
				tempnode_enqueue->self = operation_target;
				if(list[ allnode[operation_target]->team]->tailnode == NULL)
				{
					list[ allnode[operation_target]->team]->headnode = tempnode_enqueue;

				}
				else
				{
					list[ allnode[operation_target]->team]->tailnode->nextnode = tempnode_enqueue;
				}
				list[ allnode[operation_target]->team]->tailnode = tempnode_enqueue;
				printf("alloc node %x\n",tempnode_enqueue);

			}
			else if(strcmp( operation, "DEQUEUE") == 0)
			{
				printf("\n\n%s\n", operation);
				if( alllist->headlist != NULL)
				{

					print_all_queue(alllist);
					for( cnt1 = 0; cnt1 < team_counts; cnt1++)
					{
						for( cnt2 = 0; cnt2 < teamsize[ team_counts]; cnt2++)
						{
							printf("cnt1:%d cnt2:%d list[ %d]->headnode:%x\n", cnt1, cnt2, cnt1, list[ cnt1]->headnode);
						}
					}

					/***/
					nodelist* tmplist = alllist->headlist;
					node* tmpnode = alllist->headlist->headnode;
					/**
					 * 1. dequeue a node
					*/
					printf("%d\n",alllist->headlist->headnode->self);
					/*printf("alllist->headlist->headnode:%x alllist->headlist->headnode->nextnode:%x\n", alllist->headlist->headnode, alllist->headlist->headnode->nextnode);*/
					alllist->headlist->headnode = alllist->headlist->headnode->nextnode;

					if(alllist->headlist->headnode == NULL)
					{
						alllist->headlist->tailnode = NULL;
					}

					free( tmpnode );
					tmpnode->nextnode = NULL;
					tmpnode = NULL;


					/**
					 * 2. check if the list is empty, if yes ,dequeue it.
					 */
					/*printf("alllist->headlist->headnode %x alllist->headlist->tailnode %x\n", alllist->headlist->headnode,alllist->headlist->tailnode);*/
					if(alllist->headlist->headnode == NULL && alllist->headlist->tailnode == NULL)
					{
						/*printf("dequeue list %x\n", alllist->headlist);*/
						alllist->headlist = alllist->headlist->nextlist;

						if(alllist->headlist == NULL)
						{
							alllist->taillist = NULL;

						}

						/*printf("free tmp list %x\n", tmplist);*/
						free( tmplist);
						/*printf("free tmp list done\n");*/
						tmplist->nextlist = NULL;
						tmplist = NULL;

					}

					print_all_queue(alllist);
				}
				else
				{
					/*printf("alllist->headlist == NULL\n");*/
				}
			}
			memset( operation, 0, STR_LENGTH*sizeof(char));

			break;
		}



	}

	free( alllist);
	return 0;
}
