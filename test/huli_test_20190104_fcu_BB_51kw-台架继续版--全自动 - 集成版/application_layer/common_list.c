/*
list 本模块是链表
用法：其他模块直接包含本模块，然后作为函数的返回值。
上层通过分析错误码来判断函数的执行情况。
*/ 
//--------------------------------------------------------------------------------------------


#include "common_list.h"





//1	初始化链表，（空链表）
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


//1.2创建链表（使用同一个数据，创建一个指定长度的链表）
enum Error_code Common_list_create(Common_list * p_list,  elemType * p_data, int data_size, int length)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;//p_index_node1是p_list的索引，
	Node *p_new_node2 = NULL;//p_new_node2是新建的node
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
		//创建p_new_node2，并分配内存
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

		//建立连接
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
			p_index_node1 = p_new_node2;//索引后移
		}
	}
	p_list->tail =  p_index_node1;
	return error_code;
}



//2	复制链表，（p_list_old是自带节点内存的，先释放p_list_new，	然后给p_list_new申请新的节点内存）
enum Error_code Common_list_copy(Common_list * p_list_old, Common_list * p_list_new)
{
	enum Error_code error_code = Succeed;
	int i  = 0;

	Node *p_index_node1 = NULL;					//p_index_node1是p_list_old的索引，
	Node *p_index_node2 = NULL;					//p_index_node2是p_list_new的索引，
	Node *p_new_node3 = NULL;					//p_new_node3是新建的node

	if(p_list_old == NULL || p_list_new == NULL)
	{return Pointer_is_null;}


	if(p_list_new->length !=0)
	{
		Common_list_clear(p_list_new);
	}

	p_index_node1 = p_list_old->head;		//p_index_node1是p_list_old的索引，
	p_index_node2 = p_list_new->head;		//p_index_node2是p_list_new的索引，
	p_new_node3 = NULL;					//p_new_node3是新建的node
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
			p_index_node2 = p_new_node3;//索引后移
		}
		//		printf("1p_node: %p, last_pointer:%p, next_pointer:%p \r\n", p_index_node1, p_index_node1->last, p_index_node1->next);	

		p_index_node1 = p_index_node1->next;//索引后移

		(p_list_new->length)++;
	}

	p_list_new->tail =  p_index_node2;

	return error_code;
}



//3 拼接链表（直接拼接，不申请新的内存，）
//p_list1 = p_list1 + p_list2 ; p_list2 = NULL；    然后 p_list2不再拥有内存
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


//4 拼接链表（先申请新的内存，然后复制数据并拼接在list1的后面。）
//p_list3 copy= p_list2；	p_list1 = p_list1 + p_list3 ;    	此时 p_list2还是拥有以前的内存
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


//5 获取链表长度
enum Error_code Common_list_get_length(Common_list * p_list, int * p_length)
{
	enum Error_code error_code = Succeed;

	if(p_list == NULL || p_length == NULL)
	{return Pointer_is_null;}

	* p_length = p_list->length;                                                



	return error_code;
}	


//6 清除链表的所有数据
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


//6.2 清除单个节点的内存
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

//6.3 创建单个节点的内存(申请node和data的内存)
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

	//创建node，并分配内存
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

//7 修改节点的数据（数据和节点都自带内存，使用之前p_node必须手动分配内存）
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

//8 节点转化为数据（数据和节点都自带内存，）
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


//9 查询链表第pos个节点（从头）(pp_node不为空，*pp_node为空，查询完成之后，*pp_node指向对应的节点)(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_find_node_from_head(Common_list * p_list, int pos, Node ** pp_node)
{
	enum Error_code error_code = Succeed;
	int i =0;


	if(p_list == NULL || pp_node == NULL)
	{return Pointer_is_null;}

	if((*pp_node) !=NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length )//注：这里不用判断p_list的长度是否为0，因为如果长度为0，那么pos一定会出错
	{return Parameter_error;}

	(*pp_node) = p_list->head;
	for(i =0; i<pos; i++)
	{
		(*pp_node) = (*pp_node)->next;
	}

	return error_code;
}	
//10查询链表第pos个节点（从尾）(pp_node不为空，*pp_node为空，查询完成之后，*pp_node指向对应的节点)(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_find_node_from_tail(Common_list * p_list, int pos, Node ** pp_node)
{
	enum Error_code error_code = Succeed;
	int i =0;


	if(p_list == NULL || pp_node == NULL)
	{return Pointer_is_null;}

	if((*pp_node) !=NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length )//注：这里不用判断p_list的长度是否为0，因为如果长度为0，那么pos一定会出错
	{return Parameter_error;}

	(*pp_node) = p_list->tail;
	for(i =0; i<pos; i++)
	{
		(*pp_node) = (*pp_node)->last;
	}

	return error_code;
}		


//11查询链表第pos个数据（从头）（p_data是自带内存的，查询完成之后，将查询到的数据复制给p_data）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_find_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//注：这里不用判断p_list的长度是否为0，因为如果长度为0，那么pos一定会出错
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
//12查询链表第pos个数据（从尾）（p_data是自带内存的，查询完成之后，将查询到的数据复制给p_data）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_find_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//注：这里不用判断p_list的长度是否为0，因为如果长度为0，那么pos一定会出错
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



//13修改链表第pos个数据（从头）（p_data是自带内存的，查询完成之后，将p_data的数据复制到指定的节点）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_updata_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//注：这里不用判断p_list的长度是否为0，因为如果长度为0，那么pos一定会出错
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
//14修改链表第pos个数据（从尾）（p_data是自带内存的，查询完成之后，将p_data的数据复制到指定的节点）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_updata_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_index_node1 = NULL;
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//注：这里不用判断p_list的长度是否为0，因为如果长度为0，那么pos一定会出错
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




//15增加数据到链表第pos个节点的左边（从头）（p_data是自带内存的，查询完成之后，将p_data的数据增加数据到链表第pos个节点的左边）(pos的取值范围：0 ~ length-1)
//15增加数据到链表第pos个节点的左边《无法在末尾添加》
//注意：增删改查之中，只有增加能对空链表操作，其他3个都不能对空链表操作。
enum Error_code Common_list_insert_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//第pos个
	Node *p_temp_node2 = NULL;//第pos的左边一个
	Node *p_temp_node3 = NULL;//新增的节点
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)
	{
		if(pos == 0 && p_list->length == 0 )//注：增加可以对空链表操作
		{;}
		else
		{return Parameter_error;}		
	}

	//创建p_temp_node3，并分配内存
	p_temp_node3 = (Node * )malloc(sizeof(Node));
	if(p_temp_node3 == NULL) {return Pointer_malloc_fail;}

	p_temp_node3->data_size = data_size;
	p_temp_node3->data = (elemType *)malloc(data_size * sizeof(elemType));
	if(p_temp_node3->data == NULL) { free(p_temp_node3);return Pointer_malloc_fail;}	
	for(i =0; i<data_size; i++)
	{
		p_temp_node3->data[i] = p_data[i];
	}

	if(pos == 0 && p_list->length == 0 )//注：增加可以对空链表操作
	{
		p_temp_node3->last = NULL;
		p_temp_node3->next = NULL;	
		p_list->head = p_temp_node3;
		p_list->tail = p_temp_node3;
	}
	else
	{
		//找到p_temp_node1和p_temp_node2，（p_temp_node1一定存在，当p_temp_node1为head时，p_temp_node2可能会为NULL）
		p_temp_node1 = p_list->head;
		for(i =0; i<pos; i++)
		{
			p_temp_node1 = p_temp_node1->next;
		}
		p_temp_node2 = p_temp_node1->last;



		//建立连接
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


//16增加数据到链表第pos个节点的右边（从尾）（p_data是自带内存的，查询完成之后，将p_data的数据增加数据到链表第pos个节点的右边）(pos的取值范围：0 ~ length-1)
//16增加数据到链表第pos个节点的右边《无法在开头添加》
//注意：增删改查之中，只有增加能对空链表操作，其他3个都不能对空链表操作。
enum Error_code Common_list_insert_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//第pos个
	Node *p_temp_node2 = NULL;//第pos的右边一个
	Node *p_temp_node3 = NULL;//新增的节点
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)
	{
		if(pos == 0 && p_list->length == 0 )//注：增加可以对空链表操作
		{;}
		else
		{return Parameter_error;}		
	}

	//创建p_temp_node3，并分配内存
	p_temp_node3 = (Node * )malloc(sizeof(Node));
	if(p_temp_node3 == NULL) {return Pointer_malloc_fail;}

	p_temp_node3->data_size = data_size;
	p_temp_node3->data = (elemType *)malloc(data_size * sizeof(elemType));
	if(p_temp_node3->data == NULL) {free(p_temp_node3);return Pointer_malloc_fail;}	
	for(i =0; i<data_size; i++)
	{
		p_temp_node3->data[i] = p_data[i];
	}


	if(pos == 0 && p_list->length == 0 )//注：增加可以对空链表操作
	{
		p_temp_node3->last = NULL;
		p_temp_node3->next = NULL;	
		p_list->head = p_temp_node3;
		p_list->tail = p_temp_node3;
	}
	else
	{	
		//找到p_temp_node1和p_temp_node2，（p_temp_node1一定存在，当p_temp_node1为tail时，p_temp_node2可能会为NULL）
		p_temp_node1 = p_list->tail;
		for(i =0; i<pos; i++)
		{
			p_temp_node1 = p_temp_node1->last;
		}
		p_temp_node2 = p_temp_node1->next;

		//建立连接
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


//17删除链表第pos个数据（从头）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_delete_data_from_head(Common_list * p_list, int pos)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//第pos个（需要删除的）
	Node *p_temp_node2 = NULL;//第pos-1个
	Node *p_temp_node3 = NULL;//第pos+1个
	int i = 0;

	if(p_list == NULL )
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length )//注：这里不用判断p_list的长度是否为0，因为如果长度为0，那么pos一定会出错
	{return Parameter_error;}

	p_temp_node1 = p_list->head;
	for(i =0; i<pos; i++)
	{
		p_temp_node1 = p_temp_node1->next;
	}
	p_temp_node2 = p_temp_node1->last;//第pos-1个
	p_temp_node3 = p_temp_node1->next;//第pos+1个


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
//18删除链表第pos个数据（从尾）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_delete_data_from_tail(Common_list * p_list, int pos)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//第pos个（需要删除的）
	Node *p_temp_node2 = NULL;//第pos-1个
	Node *p_temp_node3 = NULL;//第pos+1个
	int i = 0;

	if(p_list == NULL )
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length )//注：这里不用判断p_list的长度是否为0，因为如果长度为0，那么pos一定会出错
	{return Parameter_error;}

	p_temp_node1 = p_list->tail;
	for(i =0; i<pos; i++)
	{
		p_temp_node1 = p_temp_node1->last;
	}
	p_temp_node2 = p_temp_node1->last;//第pos-1个
	p_temp_node3 = p_temp_node1->next;//第pos+1个


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




//19查询并删除链表第pos个数据（从头）（p_data是自带内存的，查询完成之后，将查询到的数据复制给p_data，并删除节点）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_moveout_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//第pos个（需要删除的）
	Node *p_temp_node2 = NULL;//第pos-1个
	Node *p_temp_node3 = NULL;//第pos+1个
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//注：这里不用判断p_list的长度是否为0，因为如果长度为0，那么pos一定会出错
	{return Parameter_error;}

	p_temp_node1 = p_list->head;
	for(i =0; i<pos; i++)
	{
		p_temp_node1 = p_temp_node1->next;
	}
	p_temp_node2 = p_temp_node1->last;//第pos-1个
	p_temp_node3 = p_temp_node1->next;//第pos+1个
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
//20查询并删除链表第pos个数据（从尾）（p_data是自带内存的，查询完成之后，将查询到的数据复制给p_data，并删除节点）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_moveout_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size)
{
	enum Error_code error_code = Succeed;
	Node *p_temp_node1 = NULL;//第pos个（需要删除的）
	Node *p_temp_node2 = NULL;//第pos-1个
	Node *p_temp_node3 = NULL;//第pos+1个
	int i = 0;

	if(p_list == NULL || p_data == NULL)
	{return Pointer_is_null;}

	if(pos<0 || pos >= p_list->length  || data_size <=0)//注：这里不用判断p_list的长度是否为0，因为如果长度为0，那么pos一定会出错
	{return Parameter_error;}

	p_temp_node1 = p_list->tail;
	for(i =0; i<pos; i++)
	{
		p_temp_node1 = p_temp_node1->last;
	}
	p_temp_node2 = p_temp_node1->last;//第pos-1个
	p_temp_node3 = p_temp_node1->next;//第pos+1个
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


//**通用的以字符数组的形式打印数据，uchar【】，
//注：data的内容是可以使用其他类型来强转的，所以数据的处理需要根据特定的场景来处理
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


