/*
list ��ģ��������
�÷�������ģ��ֱ�Ӱ�����ģ�飬Ȼ����Ϊ�����ķ���ֵ��
�ϲ�ͨ���������������жϺ�����ִ�������
*/ 
//--------------------------------------------------------------------------------------------


#include "common_list.h"





//1	��ʼ��������������
enum Error_code Common_list_init(Common_list * p_list)
{
	enum Error_code error_code = Succeed;

	if(p_list == NULL )
	{return Pointer_is_null;}

	p_list->length = 0;
	p_list->head = NULL;
	p_list->tail = NULL;


	return error_code;
}	


//1.2��������ʹ��ͬһ�����ݣ�����һ��ָ�����ȵ�����
enum Error_code Common_list_create(Common_list * p_list,  elemType * p_data, int data_size, int length)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;//p_index_node1��p_list��������
	Node *p_new_node2 = NULL;//p_new_node2���½���node
	int i = 0;
	int j = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(data_size <=0 || length < 0)
	{return Parameter_error;}

	p_list->length = length;
	p_list->head = NULL;
	p_list->tail = NULL;

	for(i =0; i<length; i++)
	{
		//		printf("test2  %d  %d  \r\n", i, length);	
		//����p_new_node2���������ڴ�
		p_new_node2 = (Node * )malloc(sizeof(Node));
		if(p_new_node2 == NULL) {return Pointer_malloc_fail;}

		p_new_node2->data_size = data_size;
		p_new_node2->next = NULL;

		p_new_node2->data = (elemType *)malloc(data_size * sizeof(elemType));
		if(p_new_node2->data == NULL) {free(p_new_node2);return Pointer_malloc_fail;}	
		for(j =0; j<data_size; j++)
		{
			p_new_node2->data[j] = p_data[j];
		}
		//		printf("test2  %d  %d  \r\n", i, length);

		//��������
		if(p_index_node1 == NULL)
		{

			p_new_node2->last = NULL;
			p_list->head =  p_index_node1 = p_new_node2;
			//			printf("1p_node: %p, last_pointer:%p, next_pointer:%p \r\n", p_index_node1, p_index_node1->last, p_index_node1->next);	
		}
		else
		{
			p_new_node2->last = p_index_node1;	
			p_index_node1->next = p_new_node2;
			//		printf("1p_node: %p, last_pointer:%p, next_pointer:%p \r\n", p_index_node1, p_index_node1->last, p_index_node1->next);	
			//			printf("2p_node: %p, last_pointer:%p, next_pointer:%p \r\n", p_new_node2, p_new_node2->last, p_new_node2->next);	
			p_index_node1 = p_new_node2;//��������
		}
	}
	p_list->tail =  p_index_node1;
	return error_code;
}



//2	����������p_list_old���Դ��ڵ��ڴ�ģ����ͷ�p_list_new��	Ȼ���p_list_new�����µĽڵ��ڴ棩
enum Error_code Common_list_copy(Common_list * p_list_old, Common_list * p_list_new)
{
	enum Error_code error_code = Succeed;
	int i  = 0;

	Node *p_index_node1 = NULL;					//p_index_node1��p_list_old��������
	Node *p_index_node2 = NULL;					//p_index_node2��p_list_new��������
	Node *p_new_node3 = NULL;					//p_new_node3���½���node

	if(p_list_old == NULL || p_list_new == NULL)
	{return Pointer_is_null;}


	if(p_list_new->length !=0)
	{
		Common_list_clear(p_list_new);
	}

	p_index_node1 = p_list_old->head;		//p_index_node1��p_list_old��������
	p_index_node2 = p_list_new->head;		//p_index_node2��p_list_new��������
	p_new_node3 = NULL;					//p_new_node3���½���node
	//	printf("list_length:%d,  list_head:%p, list_tail:%p, \r\n", p_list_new->length, p_list_new->head, p_list_new->tail);

	while(p_index_node1 != NULL)
	{

		p_new_node3 = (Node * )malloc(sizeof(Node));
		if(p_new_node3 == NULL) {return Pointer_malloc_fail;}

		p_new_node3->data_size = p_index_node1->data_size;
		p_new_node3->next = NULL;

		p_new_node3->data = (elemType *)malloc(p_new_node3->data_size * sizeof(elemType));
		if(p_new_node3->data == NULL) {free(p_new_node3);return Pointer_malloc_fail;}

		for(i=0 ; i<p_index_node1->data_size; i++)
		{
			p_new_node3->data[i] = p_index_node1->data[i] ;
		}

		if(p_index_node2 == NULL)
		{
			p_new_node3->last = NULL;
			p_list_new->head =  p_index_node2 = p_new_node3;
		}
		else
		{
			p_new_node3->last = p_index_node2;	
			p_index_node2->next = p_new_node3;
			p_index_node2 = p_new_node3;//��������
		}
		//		printf("1p_node: %p, last_pointer:%p, next_pointer:%p \r\n", p_index_node1, p_index_node1->last, p_index_node1->next);	

		p_index_node1 = p_index_node1->next;//��������

		(p_list_new->length)++;
	}

	p_list_new->tail =  p_index_node2;

	return error_code;
}



//3 ƴ������ֱ��ƴ�ӣ��������µ��ڴ棬��
//p_list1 = p_list1 + p_list2 ; p_list2 = NULL��    Ȼ�� p_list2����ӵ���ڴ�
enum Error_code Common_list_only_joint(Common_list * p_list1, Common_list * p_list2)
{
	enum Error_code error_code = Succeed;

	if(p_list1 == NULL || p_list2 == NULL)
	{return Pointer_is_null;}

	if(p_list1->head ==NULL )
	{
		p_list1->head = p_list2->head;
	}

	p_list1->tail->next = p_list2->head;
	p_list2->head->last = p_list1->tail;

	p_list1->tail = p_list2->tail;
	p_list1->length +=  p_list2->length;

	p_list2->length = 0;
	p_list2->head = NULL;
	p_list2->tail = NULL;

	return error_code;
}


//4 ƴ�������������µ��ڴ棬Ȼ�������ݲ�ƴ����list1�ĺ��档��
//p_list3 copy= p_list2��	p_list1 = p_list1 + p_list3 ;    	��ʱ p_list2����ӵ����ǰ���ڴ�
enum Error_code Common_list_copy_and_joint(Common_list * p_list1, Common_list * p_list2)
{
	enum Error_code error_code = Succeed;
	Common_list temp_list;

	if(p_list1 == NULL || p_list2 == NULL)
	{return Pointer_is_null;}

	Common_list_init(&temp_list);
	Common_list_copy(p_list2, &temp_list);
	Common_list_only_joint(p_list1, &temp_list);

	return error_code;
}


//5 ��ȡ������
enum Error_code Common_list_get_length(Common_list * p_list, int * p_length)
{
	enum Error_code error_code = Succeed;

	if(p_list == NULL || p_length == NULL)
	{return Pointer_is_null;}

	* p_length = p_list->length;                                                



	return error_code;
}	


//6 ����������������
enum Error_code Common_list_clear(Common_list * p_list)
{
	enum Error_code error_code = Succeed;

	Node *p_temp_node1 = NULL;
	Node *p_temp_node2 = NULL;

	if(p_list == NULL )
	{return Pointer_is_null;}

	p_temp_node1 = p_list->head;

	while(p_temp_node1 != NULL)
	{
		p_temp_node2 = p_temp_node1->next;
		if(p_temp_node1->data != NULL)
		{
			free(p_temp_node1->data);
			p_temp_node1->data = NULL;
		}
		free(p_temp_node1);
		p_temp_node1 = p_temp_node2;
		/*
		p_temp_node2->last = NULL;
		p_list->head = p_temp_node2;
		(p_list->length)--; 
		*/

	}

	p_list->length = 0;
	p_list->head = NULL;
	p_list->tail = NULL;




	return error_code;
}	


//6.2 ��������ڵ���ڴ�
enum Error_code Node_clear(Node ** pp_node)
{
	enum Error_code error_code = Succeed;

	if(pp_node == NULL)
	{return Pointer_is_null;}
	else if(* pp_node == NULL)
	{return Pointer_is_null;}

	if( (*pp_node)->data != NULL)
	{
		free((*pp_node)->data);
		(*pp_node)->data = NULL;
	}
	free(*pp_node);
	*pp_node = NULL;

	return error_code;
}	

//6.3 ���������ڵ���ڴ�(����node��data���ڴ�)
enum Error_code Node_create(Node ** pp_node, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	int i = 0;

	if(pp_node == NULL || p_data == NULL)
	{return Pointer_is_null;}
	else if((* pp_node) != NULL)
	{return Parameter_error;}

	if(data_size <=0)
	{return Parameter_error;}                                   

	//����node���������ڴ�
	(* pp_node) = (Node * )malloc(sizeof(Node));
	if((* pp_node) == NULL) {return Pointer_malloc_fail;}

	(* pp_node)->data_size = data_size;
	(* pp_node)->data = (elemType *)malloc(data_size * sizeof(elemType));
	if((* pp_node)->data == NULL) {free(* pp_node);return Pointer_malloc_fail;}	
	for(i =0; i<data_size; i++)
	{
		(* pp_node)->data[i] = p_data[i];
	}


	return error_code;
}	

//7 �޸Ľڵ�����ݣ����ݺͽڵ㶼�Դ��ڴ棬ʹ��֮ǰp_node�����ֶ������ڴ棩
enum Error_code Common_list_data_to_node(elemType * p_data, int data_size, Node * p_node)
{
	enum Error_code error_code = Succeed;
	int i =0;

	if(p_data == NULL || p_node == NULL  )
	{return Pointer_is_null;}

	if(data_size <=0)
	{return Parameter_error;}

	p_node->next = NULL;
	p_node->last = NULL;

	if(p_node->data == NULL)
	{return Parameter_error;}

	if(p_node->data_size != data_size )
	{
		free(p_node->data);
		p_node->data_size = data_size;
		p_node->data = (elemType *)malloc(data_size * sizeof(elemType));
		if(p_node->data == NULL) {return Pointer_malloc_fail;}
	}

	for(i=0 ; i<data_size; i++)
	{
		p_node->data[i] = p_data[i] ;
	}



	return error_code;
}

//8 �ڵ�ת��Ϊ���ݣ����ݺͽڵ㶼�Դ��ڴ棬��
enum Error_code Common_list_node_to_data(Node * p_node, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	int i =0;

	if(p_node == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(p_node->data_size !=  data_size || data_size <=0)
	{return Parameter_error;}

	for(i=0 ; i<data_size; i++)
	{
		p_data[i] = p_node->data[i]  ;
	}

	return error_code;
}


//9 ��ѯ�����pos���ڵ㣨��ͷ��(pp_node��Ϊ�գ�*pp_nodeΪ�գ���ѯ���֮��*pp_nodeָ���Ӧ�Ľڵ�)(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_find_node_from_head(Common_list * p_list, int pos, Node ** pp_node)
{
	enum Error_code error_code = Succeed;
	int i =0;


	if(p_list == NULL || pp_node == NULL)
	{return Pointer_is_null;}

	if((*pp_node) !=NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length )//ע�����ﲻ���ж�p_list�ĳ����Ƿ�Ϊ0����Ϊ�������Ϊ0����ôposһ�������
	{return Parameter_error;}

	(*pp_node) = p_list->head;
	for(i =0; i<pos; i++)
	{
		(*pp_node) = (*pp_node)->next;
	}

	return error_code;
}	
//10��ѯ�����pos���ڵ㣨��β��(pp_node��Ϊ�գ�*pp_nodeΪ�գ���ѯ���֮��*pp_nodeָ���Ӧ�Ľڵ�)(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_find_node_from_tail(Common_list * p_list, int pos, Node ** pp_node)
{
	enum Error_code error_code = Succeed;
	int i =0;


	if(p_list == NULL || pp_node == NULL)
	{return Pointer_is_null;}

	if((*pp_node) !=NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length )//ע�����ﲻ���ж�p_list�ĳ����Ƿ�Ϊ0����Ϊ�������Ϊ0����ôposһ�������
	{return Parameter_error;}

	(*pp_node) = p_list->tail;
	for(i =0; i<pos; i++)
	{
		(*pp_node) = (*pp_node)->last;
	}

	return error_code;
}		


//11��ѯ�����pos�����ݣ���ͷ����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽���ѯ�������ݸ��Ƹ�p_data��(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_find_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//ע�����ﲻ���ж�p_list�ĳ����Ƿ�Ϊ0����Ϊ�������Ϊ0����ôposһ�������
	{return Parameter_error;}

	p_index_node1 = p_list->head;
	for(i =0; i<pos; i++)
	{
		p_index_node1 = p_index_node1->next;
	}

	if(p_index_node1->data_size != data_size )
	{return Parameter_error;}

	for(i =0; i<data_size; i++)
	{
		p_data[i] = p_index_node1->data[i];
	}

	return error_code;
}
//12��ѯ�����pos�����ݣ���β����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽���ѯ�������ݸ��Ƹ�p_data��(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_find_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//ע�����ﲻ���ж�p_list�ĳ����Ƿ�Ϊ0����Ϊ�������Ϊ0����ôposһ�������
	{return Parameter_error;}

	p_index_node1 = p_list->tail;
	for(i =0; i<pos; i++)
	{
		p_index_node1 = p_index_node1->last;
	}

	if(p_index_node1->data_size != data_size )
	{return Parameter_error;}

	for(i =0; i<data_size; i++)
	{
		p_data[i] = p_index_node1->data[i];
	}

	return error_code;
}



//13�޸������pos�����ݣ���ͷ����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽�p_data�����ݸ��Ƶ�ָ���Ľڵ㣩(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_updata_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//ע�����ﲻ���ж�p_list�ĳ����Ƿ�Ϊ0����Ϊ�������Ϊ0����ôposһ�������
	{return Parameter_error;}

	p_index_node1 = p_list->head;
	for(i =0; i<pos; i++)
	{
		p_index_node1 = p_index_node1->next;
	}

	if(p_index_node1->data_size != data_size )
	{
		free(p_index_node1->data);
		p_index_node1->data_size = data_size;
		p_index_node1->data = (elemType *)malloc(data_size * sizeof(elemType));
		if(p_index_node1->data == NULL) {return Pointer_malloc_fail;}
	}

	for(i =0; i<data_size; i++)
	{
		p_index_node1->data[i] = p_data[i];
	}

	return error_code;
}	
//14�޸������pos�����ݣ���β����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽�p_data�����ݸ��Ƶ�ָ���Ľڵ㣩(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_updata_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//ע�����ﲻ���ж�p_list�ĳ����Ƿ�Ϊ0����Ϊ�������Ϊ0����ôposһ�������
	{return Parameter_error;}

	p_index_node1 = p_list->tail;
	for(i =0; i<pos; i++)
	{
		p_index_node1 = p_index_node1->last;
	}

	if(p_index_node1->data_size != data_size )
	{
		free(p_index_node1->data);
		p_index_node1->data_size = data_size;
		p_index_node1->data = (elemType *)malloc(data_size * sizeof(elemType));
		if(p_index_node1->data == NULL) {return Pointer_malloc_fail;}
	}

	for(i =0; i<data_size; i++)
	{
		p_index_node1->data[i] = p_data[i];
	}

	return error_code;
}		




//15�������ݵ������pos���ڵ����ߣ���ͷ����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽�p_data�������������ݵ������pos���ڵ����ߣ�(pos��ȡֵ��Χ��0 ~ length-1)
//15�������ݵ������pos���ڵ����ߡ��޷���ĩβ��ӡ�
//ע�⣺��ɾ�Ĳ�֮�У�ֻ�������ܶԿ��������������3�������ܶԿ����������
enum Error_code Common_list_insert_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//��pos��
	Node *p_temp_node2 = NULL;//��pos�����һ��
	Node *p_temp_node3 = NULL;//�����Ľڵ�
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)
	{
		if(pos == 0 && p_list->length == 0 )//ע�����ӿ��ԶԿ��������
		{;}
		else
		{return Parameter_error;}		
	}

	//����p_temp_node3���������ڴ�
	p_temp_node3 = (Node * )malloc(sizeof(Node));
	if(p_temp_node3 == NULL) {return Pointer_malloc_fail;}

	p_temp_node3->data_size = data_size;
	p_temp_node3->data = (elemType *)malloc(data_size * sizeof(elemType));
	if(p_temp_node3->data == NULL) { free(p_temp_node3);return Pointer_malloc_fail;}	
	for(i =0; i<data_size; i++)
	{
		p_temp_node3->data[i] = p_data[i];
	}

	if(pos == 0 && p_list->length == 0 )//ע�����ӿ��ԶԿ��������
	{
		p_temp_node3->last = NULL;
		p_temp_node3->next = NULL;	
		p_list->head = p_temp_node3;
		p_list->tail = p_temp_node3;
	}
	else
	{
		//�ҵ�p_temp_node1��p_temp_node2����p_temp_node1һ�����ڣ���p_temp_node1Ϊheadʱ��p_temp_node2���ܻ�ΪNULL��
		p_temp_node1 = p_list->head;
		for(i =0; i<pos; i++)
		{
			p_temp_node1 = p_temp_node1->next;
		}
		p_temp_node2 = p_temp_node1->last;



		//��������
		p_temp_node3->last = p_temp_node2;
		p_temp_node3->next = p_temp_node1;		
		p_temp_node1->last = p_temp_node3;
		if(p_temp_node2 == NULL)
		{
			p_list->head = p_temp_node3;
		}
		else
		{
			p_temp_node2->next = p_temp_node3;
		}
	}


	(p_list->length)++;

	return error_code;
}


//16�������ݵ������pos���ڵ���ұߣ���β����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽�p_data�������������ݵ������pos���ڵ���ұߣ�(pos��ȡֵ��Χ��0 ~ length-1)
//16�������ݵ������pos���ڵ���ұߡ��޷��ڿ�ͷ��ӡ�
//ע�⣺��ɾ�Ĳ�֮�У�ֻ�������ܶԿ��������������3�������ܶԿ����������
enum Error_code Common_list_insert_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//��pos��
	Node *p_temp_node2 = NULL;//��pos���ұ�һ��
	Node *p_temp_node3 = NULL;//�����Ľڵ�
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)
	{
		if(pos == 0 && p_list->length == 0 )//ע�����ӿ��ԶԿ��������
		{;}
		else
		{return Parameter_error;}		
	}

	//����p_temp_node3���������ڴ�
	p_temp_node3 = (Node * )malloc(sizeof(Node));
	if(p_temp_node3 == NULL) {return Pointer_malloc_fail;}

	p_temp_node3->data_size = data_size;
	p_temp_node3->data = (elemType *)malloc(data_size * sizeof(elemType));
	if(p_temp_node3->data == NULL) {free(p_temp_node3);return Pointer_malloc_fail;}	
	for(i =0; i<data_size; i++)
	{
		p_temp_node3->data[i] = p_data[i];
	}


	if(pos == 0 && p_list->length == 0 )//ע�����ӿ��ԶԿ��������
	{
		p_temp_node3->last = NULL;
		p_temp_node3->next = NULL;	
		p_list->head = p_temp_node3;
		p_list->tail = p_temp_node3;
	}
	else
	{	
		//�ҵ�p_temp_node1��p_temp_node2����p_temp_node1һ�����ڣ���p_temp_node1Ϊtailʱ��p_temp_node2���ܻ�ΪNULL��
		p_temp_node1 = p_list->tail;
		for(i =0; i<pos; i++)
		{
			p_temp_node1 = p_temp_node1->last;
		}
		p_temp_node2 = p_temp_node1->next;

		//��������
		p_temp_node3->last = p_temp_node1;
		p_temp_node3->next = p_temp_node2;		
		p_temp_node1->next = p_temp_node3;
		if(p_temp_node2 == NULL)
		{
			p_list->tail = p_temp_node3;
		}
		else
		{
			p_temp_node2->last = p_temp_node3;
		}
	}
	(p_list->length)++;

	return error_code;
}	


//17ɾ�������pos�����ݣ���ͷ��(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_delete_data_from_head(Common_list * p_list, int pos)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//��pos������Ҫɾ���ģ�
	Node *p_temp_node2 = NULL;//��pos-1��
	Node *p_temp_node3 = NULL;//��pos+1��
	int i = 0;

	if(p_list == NULL )
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length )//ע�����ﲻ���ж�p_list�ĳ����Ƿ�Ϊ0����Ϊ�������Ϊ0����ôposһ�������
	{return Parameter_error;}

	p_temp_node1 = p_list->head;
	for(i =0; i<pos; i++)
	{
		p_temp_node1 = p_temp_node1->next;
	}
	p_temp_node2 = p_temp_node1->last;//��pos-1��
	p_temp_node3 = p_temp_node1->next;//��pos+1��


	if(p_temp_node2 == NULL && p_temp_node3 == NULL)
	{
		p_list->head = NULL;
		p_list->tail = NULL;
	}
	else if(p_temp_node2 == NULL)
	{
		p_list->head = p_temp_node3;
		p_temp_node3->last = NULL;
	}
	else if(p_temp_node3 == NULL)
	{
		p_list->tail = p_temp_node2;
		p_temp_node2->next = NULL;
	}
	else
	{
		p_temp_node2->next = p_temp_node3;
		p_temp_node3->last = p_temp_node2;
	}

	free(p_temp_node1->data);
	free(p_temp_node1);
	(p_list->length)--;

	return error_code;
}	
//18ɾ�������pos�����ݣ���β��(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_delete_data_from_tail(Common_list * p_list, int pos)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//��pos������Ҫɾ���ģ�
	Node *p_temp_node2 = NULL;//��pos-1��
	Node *p_temp_node3 = NULL;//��pos+1��
	int i = 0;

	if(p_list == NULL )
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length )//ע�����ﲻ���ж�p_list�ĳ����Ƿ�Ϊ0����Ϊ�������Ϊ0����ôposһ�������
	{return Parameter_error;}

	p_temp_node1 = p_list->tail;
	for(i =0; i<pos; i++)
	{
		p_temp_node1 = p_temp_node1->last;
	}
	p_temp_node2 = p_temp_node1->last;//��pos-1��
	p_temp_node3 = p_temp_node1->next;//��pos+1��


	if(p_temp_node2 == NULL && p_temp_node3 == NULL)
	{
		p_list->head = NULL;
		p_list->tail = NULL;
	}
	else if(p_temp_node2 == NULL)
	{
		p_list->head = p_temp_node3;
		p_temp_node3->last = NULL;
	}
	else if(p_temp_node3 == NULL)
	{
		p_list->tail = p_temp_node2;
		p_temp_node2->next = NULL;
	}
	else
	{
		p_temp_node2->next = p_temp_node3;
		p_temp_node3->last = p_temp_node2;
	}

	free(p_temp_node1->data);
	free(p_temp_node1);
	(p_list->length)--;

	return error_code;
}		




//19��ѯ��ɾ�������pos�����ݣ���ͷ����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽���ѯ�������ݸ��Ƹ�p_data����ɾ���ڵ㣩(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_moveout_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//��pos������Ҫɾ���ģ�
	Node *p_temp_node2 = NULL;//��pos-1��
	Node *p_temp_node3 = NULL;//��pos+1��
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//ע�����ﲻ���ж�p_list�ĳ����Ƿ�Ϊ0����Ϊ�������Ϊ0����ôposһ�������
	{return Parameter_error;}

	p_temp_node1 = p_list->head;
	for(i =0; i<pos; i++)
	{
		p_temp_node1 = p_temp_node1->next;
	}
	p_temp_node2 = p_temp_node1->last;//��pos-1��
	p_temp_node3 = p_temp_node1->next;//��pos+1��
	if(p_temp_node1->data_size != data_size )
	{return Failed;}

	for(i =0; i<data_size; i++)
	{
		p_data[i] = p_temp_node1->data[i];
	}

	if(p_temp_node2 == NULL && p_temp_node3 == NULL)
	{
		p_list->head = NULL;
		p_list->tail = NULL;
	}
	else if(p_temp_node2 == NULL)
	{
		p_list->head = p_temp_node3;
		p_temp_node3->last = NULL;
	}
	else if(p_temp_node3 == NULL)
	{
		p_list->tail = p_temp_node2;
		p_temp_node2->next = NULL;
	}
	else
	{
		p_temp_node2->next = p_temp_node3;
		p_temp_node3->last = p_temp_node2;
	}

	free(p_temp_node1->data);
	free(p_temp_node1);
	(p_list->length)--;

	return error_code;
}	
//20��ѯ��ɾ�������pos�����ݣ���β����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽���ѯ�������ݸ��Ƹ�p_data����ɾ���ڵ㣩(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_moveout_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//��pos������Ҫɾ���ģ�
	Node *p_temp_node2 = NULL;//��pos-1��
	Node *p_temp_node3 = NULL;//��pos+1��
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//ע�����ﲻ���ж�p_list�ĳ����Ƿ�Ϊ0����Ϊ�������Ϊ0����ôposһ�������
	{return Parameter_error;}

	p_temp_node1 = p_list->tail;
	for(i =0; i<pos; i++)
	{
		p_temp_node1 = p_temp_node1->last;
	}
	p_temp_node2 = p_temp_node1->last;//��pos-1��
	p_temp_node3 = p_temp_node1->next;//��pos+1��
	if(p_temp_node1->data_size != data_size )
	{return Parameter_error;}

	for(i =0; i<data_size; i++)
	{
		p_data[i] = p_temp_node1->data[i];
	}

	if(p_temp_node2 == NULL && p_temp_node3 == NULL)
	{
		p_list->head = NULL;
		p_list->tail = NULL;
	}
	else if(p_temp_node2 == NULL)
	{
		p_list->head = p_temp_node3;
		p_temp_node3->last = NULL;
	}
	else if(p_temp_node3 == NULL)
	{
		p_list->tail = p_temp_node2;
		p_temp_node2->next = NULL;
	}
	else
	{
		p_temp_node2->next = p_temp_node3;
		p_temp_node3->last = p_temp_node2;
	}

	free(p_temp_node1->data);
	free(p_temp_node1);
	(p_list->length)--;

	return error_code;
}		


//**ͨ�õ����ַ��������ʽ��ӡ���ݣ�uchar������
//ע��data�������ǿ���ʹ������������ǿת�ģ��������ݵĴ�����Ҫ�����ض��ĳ���������
enum Error_code Common_list_printf_total_uchar_data(Common_list * p_list)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;
	int i = 0;
	int pos = 0;

	if(p_list == NULL )
	{return Pointer_is_null;}

	p_index_node1 = p_list->head;
	printf("list_length:%d,  list_head:%p, list_tail:%p, \r\n", p_list->length, p_list->head, p_list->tail);	

	while(p_index_node1 != NULL)
	{
		if(p_index_node1->data != NULL && p_index_node1->data_size >0)
		{
			printf("node num : %05d, data_size: %05d, data: ", pos, p_index_node1->data_size);	
			for(i=0; i<p_index_node1->data_size; i++)
			{
				printf("%c", p_index_node1->data[i]);
			}
			printf(", node_pointer:%p, last_pointer:%p, next_pointer:%p, \r\n", p_index_node1, p_index_node1->last, p_index_node1->next);	
		}
		else
		{
			printf("test1    \r\n");	
		}

		p_index_node1 = p_index_node1->next;
		pos++;
	}


	return error_code;
}


