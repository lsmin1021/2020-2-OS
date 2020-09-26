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
		
		//less func이용 시 사용하는 변수
		list_less_func *less;
		void *aux;


		int temp_idx, temp_idx2;

		//create list <LIST>
		if(!strcmp(inArr[0], "create") && !strcmp(inArr[1], "list") && in_cnt == 3){
			char list_name[10];
			strcpy(list_name, inArr[2]);
			temp_idx = list_name[strlen(list_name)-1] - '0';
			list_Arr[temp_idx] = (struct list*)malloc(sizeof(struct list));
			list_init(list_Arr[temp_idx]);
		}

		//dumpdata <LIST>
		if(!strcmp(inArr[0],"dumpdata") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			dump_list(list_Arr[temp_idx]);
		}
		
		//list_insert <LIST> index value
		if(!strcmp(inArr[0], "list_insert") && in_cnt == 4){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index, value;
			index = atoi(inArr[2]);
			value = atoi(inArr[3]);

			struct list_elem *before = list_find_nth(list_Arr[temp_idx], index);
			//새 elem 생성
			struct list_elem *new_elem = malloc(sizeof(new_elem));
			struct list_item *new_item = malloc(sizeof(new_item));
			new_elem->prev = NULL;
			new_elem->next = NULL;
			new_item = list_entry(new_elem, struct list_item, elem);
			new_item->data = value;

			list_insert(before, new_elem);

		}
		
		//list_insert_ordered <LIST> value
		if(!strcmp(inArr[0], "list_insert_ordered") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int value = atoi(inArr[2]);
			
			//새 elem 생성
			struct list_elem *new_elem = malloc(sizeof(new_elem));
			struct list_item *new_item = malloc(sizeof(new_item));
			new_elem->prev = NULL;
			new_elem->next = NULL;
			new_item = list_entry(new_elem, struct list_item, elem);
			new_item->data = value;
			less = less_func;
			list_insert_ordered(list_Arr[temp_idx], new_elem, less, aux);

		}

		//list_pop_front <LIST>
		if(!strcmp(inArr[0], "list_pop_front") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			list_pop_front(list_Arr[temp_idx]);
		}

		//list_pop_back <LIST>
		if(!strcmp(inArr[0], "list_pop_back") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';

			list_pop_back(list_Arr[temp_idx]);
		}

		//list_push_back <LIST> value
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

		//list_push_front <LIST> value
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

		//list_front <LIST>
		if(!strcmp(inArr[0], "list_front") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			

			//TODO list_begin으로 바꿔야할까?
			struct list_elem *temp_elem = list_front(list_Arr[temp_idx]);
			struct list_item *temp_item = list_entry(temp_elem, struct list_item, elem);
			printf("%d\n", temp_item -> data);

		}

		//list_back <LIST>
		if(!strcmp(inArr[0], "list_back") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			//TODO list_rbegin으로 바꿔야할까?
			struct list_elem *temp_elem = list_back(list_Arr[temp_idx]);
			struct list_item *temp_item = list_entry(temp_elem, struct list_item, elem);
			printf("%d\n", temp_item -> data);
		}

		//list_remove <LIST> index
		if(!strcmp(inArr[0], "list_remove") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index = atoi(inArr[2]);

			struct list_elem *temp_elem = list_find_nth(list_Arr[temp_idx], index);
			list_remove(temp_elem);
		}

		//list_reverse <LIST>
		if(!strcmp(inArr[0], "list_reverse") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			list_reverse(list_Arr[temp_idx]);
		}

		//list_sort <LIST>
		if(!strcmp(inArr[0], "list_sort") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
		
			less = less_func;
			list_sort(list_Arr[temp_idx], less, aux);
		}
		
		//list_splice <LIST1> index <LIST2> start end
		if(!strcmp(inArr[0], "list_splice") && in_cnt == 6){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index = atoi(inArr[2]);
			temp_idx2 = inArr[3][strlen(inArr[3])-1] - '0';
			int start = atoi(inArr[4]), end = atoi(inArr[5]);
			struct list_elem *e1 = list_find_nth(list_Arr[temp_idx], index);
			struct list_elem *e2 = list_find_nth(list_Arr[temp_idx2], start);
			struct list_elem *e3 = list_find_nth(list_Arr[temp_idx2], end);

			list_splice(e1, e2, e3);

		}

		//list_unique <LIST1> <LIST2>
		if(!strcmp(inArr[0], "list_unique") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			temp_idx2 = inArr[2][strlen(inArr[2])-1] - '0';
			less = less_func;
			list_unique(list_Arr[temp_idx], list_Arr[temp_idx2],less, aux);

		}
		//list_unique <LIST>
		if(!strcmp(inArr[0], "list_unique") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			struct list *temp_list = malloc(sizeof(struct list));
			list_init(temp_list);
			less = less_func;
			list_unique(list_Arr[temp_idx], temp_list, less, aux);

			delete_list(temp_list);

		}

		if(!strcmp(inArr[0], "list_swap") && in_cnt == 4){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index1 = atoi(inArr[2]);
			int index2 = atoi(inArr[3]);
			struct list_elem *e1 = list_find_nth(list_Arr[temp_idx], index1);
			struct list_elem *e2 = list_find_nth(list_Arr[temp_idx], index2);
			list_swap(e1,e2);
		}

		if(!strcmp(inArr[0], "list_shuffle") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			list_shuffle(list_Arr[temp_idx]);
		}
		//list_empty <LIST>
		if(!strcmp(inArr[0], "list_empty") && in_cnt ==2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			if(list_empty(list_Arr[temp_idx]))
				printf("true\n");
			else
				printf("false\n");
		}

		//list_size <LIST>
		if(!strcmp(inArr[0], "list_size") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			size_t size = list_size(list_Arr[temp_idx]);
			printf("%zu\n",size);
		}

		//list_max <LIST>
		if(!strcmp(inArr[0], "list_max") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			less = less_func;
			struct list_elem *e = list_max(list_Arr[temp_idx], less, aux);
			struct list_item *temp_item = list_entry(e, struct list_item, elem);
			printf("%d\n", temp_item -> data);
		}

		//list_min <LIST>
		if(!strcmp(inArr[0], "list_min") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			less = less_func;
			struct list_elem *e = list_min(list_Arr[temp_idx], less, aux);
			struct list_item *temp_item = list_entry(e, struct list_item, elem);
			printf("%d\n", temp_item -> data);
		}
		//delete <LIST>
		if(!strcmp(inArr[0], "delete") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			delete_list(list_Arr[temp_idx]);		
		}
		

	}


	return 0;
}
