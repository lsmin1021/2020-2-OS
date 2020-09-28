#include "main.h"


struct list **list_Arr;
struct bitmap **bm_Arr;
struct hash **hash_Arr;

int main(void){
	char input[50];
	list_Arr = (struct list**)malloc(sizeof(struct list*)*10);
	bm_Arr = (struct bitmap**)malloc(sizeof(struct bitmap*)*10);
	hash_Arr = (struct hash**)malloc(sizeof(struct hash*)*10);

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
		
		/* less instruction start */
		list_less_func *less;
		void *aux = NULL;

		int temp_idx, temp_idx2;

		//create list <LIST>
		if(!strcmp(inArr[0], "create") && !strcmp(inArr[1], "list") && in_cnt == 3){
			temp_idx = inArr[2][strlen(inArr[2])-1] - '0';
			list_Arr[temp_idx] = (struct list*)malloc(sizeof(struct list));
			list_init(list_Arr[temp_idx]);
		}

		//dumpdata <LIST> TODO 조건
		if(!strcmp(inArr[0],"dumpdata") && inArr[1][0] == 'l' && in_cnt == 2){
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
		
		//list_swap <BM> index1 index2
		if(!strcmp(inArr[0], "list_swap") && in_cnt == 4){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index1 = atoi(inArr[2]);
			int index2 = atoi(inArr[3]);
			struct list_elem *e1 = list_find_nth(list_Arr[temp_idx], index1);
			struct list_elem *e2 = list_find_nth(list_Arr[temp_idx], index2);
			list_swap(e1,e2);
		}

		//list_shuffle <BM>
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
		if(!strcmp(inArr[0], "delete") && inArr[1][0] == 'l' && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			delete_list(list_Arr[temp_idx]);		
		}
		/* list instruction end */



		/* bitmap instruction start */

		//create bitmap <BM> bit_cnt
		if(!strcmp(inArr[0], "create") && !strcmp(inArr[1], "bitmap") && in_cnt == 4){
			temp_idx = inArr[2][strlen(inArr[2])-1] - '0';
			size_t bit_cnt = atoi(inArr[3]);
			bm_Arr[temp_idx] = bitmap_create(bit_cnt);
		}

		//dumpdata <BM>
		if(!strcmp(inArr[0], "dumpdata") && inArr[1][0] == 'b' && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			dump_bitmap(bm_Arr[temp_idx]);
		}
	
		//bitmap_mark <BM> index
		if(!strcmp(inArr[0], "bitmap_mark") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			size_t idx = atoi(inArr[2]);
			bitmap_mark(bm_Arr[temp_idx], idx);
		}

		//bitmap_all <BM> start cnt 
		if(!strcmp(inArr[0], "bitmap_all") && in_cnt == 4){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int start = atoi(inArr[2]), cnt = atoi(inArr[3]);
			if(bitmap_all(bm_Arr[temp_idx], start, cnt))
				printf("true\n");
			else
				printf("false\n");
		}

		//bitmap_any <BM> start cnt 
		if(!strcmp(inArr[0], "bitmap_any") && in_cnt == 4){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int start = atoi(inArr[2]), cnt = atoi(inArr[3]);
			if(bitmap_any(bm_Arr[temp_idx], start, cnt))
				printf("true\n");
			else
				printf("false\n");
		}
		
		//bitmap_none <BM> start cnt 
		if(!strcmp(inArr[0], "bitmap_none") && in_cnt == 4){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int start = atoi(inArr[2]), cnt = atoi(inArr[3]);
			if(bitmap_none(bm_Arr[temp_idx], start, cnt))
				printf("true\n");
			else
				printf("false\n");
		}
		
		//bitmap_contains <BM> start cnt value
		if(!strcmp(inArr[0], "bitmap_contains") && in_cnt == 5){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int start = atoi(inArr[2]), cnt = atoi(inArr[3]);
			bool value = false;
			if(inArr[4][0] == 't') value = true;	
			if(bitmap_contains(bm_Arr[temp_idx], start, cnt, value))
				printf("true\n");
			else
				printf("false\n");
		}

		//bitmap_count <BM> start cnt value
		if(!strcmp(inArr[0], "bitmap_count") && in_cnt == 5){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int start = atoi(inArr[2]), cnt = atoi(inArr[3]);
			bool value = false;
			if(inArr[4][0] == 't') value = true;
			printf("%zu\n",bitmap_count(bm_Arr[temp_idx], start, cnt, value));
		}

		//bitmap_expand <BM> cnt
		if(!strcmp(inArr[0], "bitmap_expand") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int cnt = atoi(inArr[2]);
			bm_Arr[temp_idx] = bitmap_expand(bm_Arr[temp_idx], cnt);
		}

		//bitmap_set <BM> index value
		if(!strcmp(inArr[0], "bitmap_set") && in_cnt == 4){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index = atoi(inArr[2]);
			bool value = false;
			if(inArr[3][0] == 't') value = true;
			bitmap_set(bm_Arr[temp_idx], index, value);
		}

		//bitmap_set_all <BM> value
		if(!strcmp(inArr[0], "bitmap_set_all") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			bool value = false;
			if(inArr[2][0] == 't') value = true;
			bitmap_set_all(bm_Arr[temp_idx], value);
		}

		//bitmap_set_multiple <BM> start cnt value
		if(!strcmp(inArr[0], "bitmap_set_multiple") && in_cnt == 5){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int start = atoi(inArr[2]), cnt = atoi(inArr[3]);
			bool value = false;
			if(inArr[4][0] == 't') value = true;
			bitmap_set_multiple(bm_Arr[temp_idx], start, cnt, value);
		}

		//bitmap_flip <BM> idx
		if(!strcmp(inArr[0], "bitmap_flip") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index = atoi(inArr[2]);
			bitmap_flip(bm_Arr[temp_idx], index);
		}

		
		//bitmap_reset <BM> idx
		if(!strcmp(inArr[0], "bitmap_reset") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index = atoi(inArr[2]);
			bitmap_reset(bm_Arr[temp_idx], index);
		}

		//bitmap_scan <BM> start cnt value
		if(!strcmp(inArr[0], "bitmap_scan") && in_cnt == 5){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int start = atoi(inArr[2]), cnt = atoi(inArr[3]);
			bool value = false;
			if(inArr[4][0] == 't') value = true;
			printf("%zu\n",bitmap_scan(bm_Arr[temp_idx], start, cnt, value));
		}		

		//bitmap_scan_and_flip <BM> start cnt value
		if(!strcmp(inArr[0], "bitmap_scan_and_flip") && in_cnt == 5){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int start = atoi(inArr[2]), cnt = atoi(inArr[3]);
			bool value = false;
			if(inArr[4][0] == 't') value = true;
			printf("%zu\n",bitmap_scan_and_flip(bm_Arr[temp_idx], start, cnt, value));
		}

		//bitmap_size <BM>
		if(!strcmp(inArr[0], "bitmap_size") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			printf("%zu\n",bitmap_size(bm_Arr[temp_idx]));
		}

		//bitmap_test <BM> idx
		if(!strcmp(inArr[0], "bitmap_test") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			int index = atoi(inArr[2]);
			if(bitmap_test(bm_Arr[temp_idx], index))
				printf("true\n");
			else
				printf("false\n");
		}

		//bitmap_dump <BM>
		if(!strcmp(inArr[0], "bitmap_dump") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			bitmap_dump(bm_Arr[temp_idx]);
		}

		//dumpdata <BM>
		if(!strcmp(inArr[0],"delete") && inArr[1][0] == 'b' && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			bitmap_destroy(bm_Arr[temp_idx]);
		}
		/* bitmap instruction end */


		/* hash instruction start */
		hash_less_func *hash_less_f = hash_less;
		hash_hash_func *hash_func = hash_int_func;
		hash_action_func *action_func;
		void *hash_aux = NULL;

		//create hashtable <HASH>
		if(!strcmp(inArr[0], "create") && !strcmp(inArr[1], "hashtable") && in_cnt == 3){
			temp_idx = inArr[2][strlen(inArr[2])-1] - '0';
			hash_Arr[temp_idx] = (struct hash*)malloc(sizeof(struct hash));
			hash_init(hash_Arr[temp_idx],hash_func,hash_less_f,hash_aux);
		}

		//dumpdata <HASH> 
		if(!strcmp(inArr[0],"dumpdata") && inArr[1][0] == 'h' && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			hash_dump(hash_Arr[temp_idx]);
		}

		//hash_insert <HASH> value
		if(!strcmp(inArr[0], "hash_insert") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			struct hash_elem *new_elem = malloc(sizeof(struct hash_elem));
			struct hash_item *new_item = hash_entry(new_elem, struct hash_item, elem);
			new_item->data = atoi(inArr[2]);
			hash_insert(hash_Arr[temp_idx],new_elem);
		}

		//hash_delete <HASH> delete 
		if(!strcmp(inArr[0], "hash_delete") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			struct hash_elem *new_elem = malloc(sizeof(struct hash_elem));
			struct hash_item *hash_item = hash_entry(new_elem, struct hash_item, elem);
			hash_item->data = atoi(inArr[2]);
			hash_delete(hash_Arr[temp_idx], new_elem);
			free(new_elem);
		}

		//hash_apply <HASH> action_func 
		if(!strcmp(inArr[0], "hash_apply") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			if(!strcmp(inArr[2], "square"))
				action_func = square_func;
			else if(!strcmp(inArr[2], "triple"))
				action_func = triple_func;

			hash_apply(hash_Arr[temp_idx],action_func);
		}

		//hash_empty <HASH>
		if(!strcmp(inArr[0], "hash_empty") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			if(hash_empty(hash_Arr[temp_idx]))
				printf("true\n");
			else
				printf("false\n");
		}

		//hash_size <HASH>
		if(!strcmp(inArr[0], "hash_size") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			printf("%zu\n",hash_size(hash_Arr[temp_idx]));
		}

		//hash_clear <HASH>
		if(!strcmp(inArr[0], "hash_clear") && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			action_func = destructor_func;
			hash_clear(hash_Arr[temp_idx],action_func);
		}

		//hash_find <HASH> value
		if(!strcmp(inArr[0], "hash_find") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			struct hash_elem *new_elem = malloc(sizeof(struct hash_elem));
			struct hash_item *hash_item = hash_entry(new_elem, struct hash_item, elem);
			hash_item->data = atoi(inArr[2]);
			struct hash_elem *temp_elem = hash_find(hash_Arr[temp_idx], new_elem);
			if(temp_elem != NULL){
				hash_item = hash_entry(new_elem, struct hash_item, elem);
				printf("%d\n",hash_item->data);
			}
			free(new_elem);
		}

		//hash_replace <HASH> value
		if(!strcmp(inArr[0], "hash_replace") && in_cnt == 3){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			struct hash_elem *new_elem = malloc(sizeof(struct hash_elem));
			struct hash_item *new_item = hash_entry(new_elem, struct hash_item, elem);
			new_item->data = atoi(inArr[2]);
			hash_replace(hash_Arr[temp_idx],new_elem);
		}

		//delete <HASH>
		if(!strcmp(inArr[0], "delete") && inArr[1][0] == 'h' && in_cnt == 2){
			temp_idx = inArr[1][strlen(inArr[1])-1] - '0';
			action_func = destructor_func;
			hash_destroy(hash_Arr[temp_idx],action_func);
			free(hash_Arr[temp_idx]);
		}

		/* hash instruction end */
	}


	return 0;
}
