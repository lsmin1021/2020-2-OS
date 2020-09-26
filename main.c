#include "main.h"


struct list **list_Arr;

int main(void){
	char input[50];
//	printf("ddd\n");
	list_Arr = (struct list**)malloc(sizeof(struct list*)*10);
//	printf("여긴 됬아ㅣ아");

	int i=0;
	while(1){

		if(fgets(input,50,stdin) == NULL)
			break;
		if(strlen(input) == 1 || input[0] == ' ' ) // TODO 첫 문자가 띄어쓰기면?
			continue;
		input[strlen(input)-1]= 0;
		i++;
		
		//printf("%s\n",input);
		if(!strcmp(input, "quit")) break;

		//LIST instruction start
		//인자 여러 개인 경우 처리
		
		char *inArr[20] = {NULL, };
		int in_cnt = 0;
		char *ptr = strtok(input, " ");
		while(ptr != NULL){
			inArr[in_cnt] = ptr;
			in_cnt++;
			ptr = strtok(NULL, " ");
		}
		
		int temp_idx;
		if(!strcmp(inArr[0], "create") && !strcmp(inArr[1], "list") && in_cnt == 3){
//			printf("%s %s %s %d --\n",inArr[0], inArr[1], inArr[2], in_index);
			char list_name[10];
			strcpy(list_name, inArr[2]);
			temp_idx = list_name[strlen(list_name)-1] - '0';
		//	printf("%d<<<\n",temp_idx);
			list_Arr[temp_idx] = (struct list*)malloc(sizeof(struct list));
			list_init(list_Arr[temp_idx]);
		}
		if(!strcmp(inArr[0], "dumpdata") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			dump_list(list_Arr[temp_idx]);
		}
		
	/*	if(!strcmp(inArr[0], "list_insert") && in_cnt == 4){
			int temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index, value;
			index = atoi(inArr[2]);
			value = atoi(inArr[3]);
			list_insert(

		}*/
		if(!strcmp(inArr[0], "list_pop_front") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			struct list_elem *e;

			e = list_pop_front(list_Arr[temp_idx]);
			printf("%d\n", list_entry(e, struct list_item, elem)->data);
		}
		if(!strcmp(inArr[0], "list_pop_back") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			struct list_elem *e;

			e = list_pop_back(list_Arr[temp_idx]);
			printf("%d\n", list_entry(e, struct list_item, elem)->data);
		}
		if(!strcmp(inArr[0], "list_push_back") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			
			struct list_elem *new_elem = malloc(sizeof(new_elem));
			struct list_item *new_item = malloc(sizeof(new_item));
			new_elem->prev = NULL;
			new_elem->next = NULL;
			
			new_item = list_entry(new_elem, struct list_item, elem);
			new_item->data = atoi(inArr[2]);

			list_push_back(list_Arr[temp_idx], new_elem);
		}
		if(!strcmp(inArr[0], "list_push_front") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			
			struct list_elem *new_elem = malloc(sizeof(new_elem));
			struct list_item *new_item = malloc(sizeof(new_item));
			new_elem->prev = NULL;
			new_elem->next = NULL;
			
			new_item = list_entry(new_elem, struct list_item, elem);
			new_item->data = atoi(inArr[2]);

			list_push_front(list_Arr[temp_idx], new_elem);
		}
		if(!strcmp(inArr[0], "list_front") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			

			//TODO list_begin으로 바꿔야할까?
			struct list_elem *temp_elem = list_front(list_Arr[temp_idx]);
			struct list_item *temp_item = list_entry(temp_elem, struct list_item, elem);
			printf("%d\n", temp_item -> data);

		}
		if(!strcmp(inArr[0], "list_back") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			//TODO list_rbegin으로 바꿔야할까?
			struct list_elem *temp_elem = list_back(list_Arr[temp_idx]);
			struct list_item *temp_item = list_entry(temp_elem, struct list_item, elem);
			printf("%d\n", temp_item -> data);
		}
		if(!strcmp(inArr[0], "list_remove") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index = atoi(inArr[2]);

			struct list_elem *temp_elem = list_find_nth(list_Arr[temp_idx], index);
			list_remove(temp_elem);
		}
		if(!strcmp(inArr[0], "list_reverse") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			list_reverse(list_Arr[temp_idx]);
		}
	/*	if(!strcmp(inArr[0], "list_sort") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			list_less_func *less;
			void *aux;
			list_sort(list_Arr[temp_idx], less, aux);
		}*/
		if(!strcmp(inArr[0], "list_splice") && in_cnt == 6){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index = atoi(inArr[2]);
			int temp_idx2 = inArr[3][strlen(inArr[3])-1] - '0';
			int start = atoi(inArr[4]), end = atoi(inArr[5]);
			struct list_elem *e1 = list_find_nth(list_Arr[temp_idx], index);
			struct list_elem *e2 = list_find_nth(list_Arr[temp_idx2], start);
			struct list_elem *e3 = list_find_nth(list_Arr[temp_idx2], end);

			list_splice(e1, e2, e3);

		}
//		if(!strcmp(inArr[0], "list_unique"), && in_cnt == 3){
//			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
//			int temp_idx2 = inArr[3][strlen(inArr[3])-1] - '0';

				

//		}
		if(!strcmp(inArr[0], "list_empty") && in_cnt ==2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			if(list_empty(list_Arr[temp_idx]))
				printf("true\n");
			else
				printf("false\n");
		}
		if(!strcmp(inArr[0], "list_size") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			size_t size = list_size(list_Arr[temp_idx]);
			printf("%zu\n",size);
		}
		if(!strcmp(inArr[0], "delete") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			delete_list(list_Arr[temp_idx]);		
		}
		

	}


	return 0;
}
