/*
list 本模块是链表
用法：其他模块直接包含本模块，然后作为函数的返回值。
上层通过分析错误码来判断函数的执行情况。
*/ 
//--------------------------------------------------------------------------------------------

#ifndef __COMMON_LIST_H
#define __COMMON_LIST_H	


#include "error_system.h"
#include "sci.h"

/*
注意：
common_list是自动分配内存的。
node则是手动分配的。
操作说明：

*/

typedef char  elemType ;

//通用链表的结构体，直接创建即可，内存自动管理。
//必须按照规则使用  init--》》增删改查--》》clear
typedef struct common_list{   
	int length;
	struct node *head;
	struct node *tail;
}Common_list;

//通用链表节点的结构体
//只允许手动分配和释放内存
typedef struct node{    
	elemType * data;
	int data_size;

	struct node *last;
	struct node *next;
}Node;



//1	初始化链表，（空链表）
enum Error_code Common_list_init(Common_list * p_list);

//1.2创建链表（使用同一个数据，创建一个指定长度的链表）
enum Error_code Common_list_create(Common_list * p_list,  elemType * p_data, int data_size, int length);

//2	复制链表，（p_list_old是自带节点内存的，先释放p_list_new，	然后给p_list_new申请新的节点内存）
enum Error_code Common_list_copy(Common_list * p_list_old, Common_list * p_list_new);

//3 拼接链表（直接拼接，不申请新的内存，）
//p_list1 = p_list1 + p_list2 ; p_list2 = NULL；    		然后 p_list2不再拥有以前的节点内存
enum Error_code Common_list_only_joint(Common_list * p_list1, Common_list * p_list2);

//4 拼接链表（先申请新的内存，然后复制数据并拼接在list1的后面。）
//p_list3 copy= p_list2；	p_list1 = p_list1 + p_list3 ;    	此时 p_list2还是拥有以前的内存
enum Error_code Common_list_copy_and_joint(Common_list * p_list1, Common_list * p_list2);

//5 获取链表长度
enum Error_code Common_list_get_length(Common_list * p_list, int * p_length);

//6 清除链表的所有数据(释放node和data的内存)
enum Error_code Common_list_clear(Common_list * p_list);

//6.2 清除单个节点的内存(释放node和data的内存)
enum Error_code Node_clear(Node ** pp_node);

//6.3 创建单个节点的内存(申请node和data的内存)
enum Error_code Node_create(Node ** pp_node, elemType * p_data, int data_size);



//7 修改节点的数据（数据和节点都自带内存，使用之前p_node必须手动分配内存）
enum Error_code Common_list_data_to_node(elemType * p_data, int data_size, Node * p_node);

//8 节点转化为数据（数据和节点都自带内存，p_node的内存是手动分配的， 之后看情况是否对p_node进行处理）
enum Error_code Common_list_node_to_data(Node * p_node, elemType * p_data, int data_size);


//9 查询链表第pos个节点（从头）(pp_node不为空，*pp_node为空，查询完成之后，*pp_node指向对应的节点)(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_find_node_from_head(Common_list * p_list, int pos, Node ** pp_node);
//10查询链表第pos个节点（从尾）(pp_node不为空，*pp_node为空，查询完成之后，*pp_node指向对应的节点)(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_find_node_from_tail(Common_list * p_list, int pos, Node ** pp_node);


//11查询链表第pos个数据（从头）（p_data是自带内存的，查询完成之后，将查询到的数据复制给p_data）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_find_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size);
//12查询链表第pos个数据（从尾）（p_data是自带内存的，查询完成之后，将查询到的数据复制给p_data）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_find_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size);

//13修改链表第pos个数据（从头）（p_data是自带内存的，查询完成之后，将p_data的数据复制到指定的节点）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_updata_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size);
//14修改链表第pos个数据（从尾）（p_data是自带内存的，查询完成之后，将p_data的数据复制到指定的节点）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_updata_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size);


//15增加数据到链表第pos个节点的左边（从头）（p_data是自带内存的，查询完成之后，将p_data的数据增加数据到链表第pos个节点的左边）(pos的取值范围：0 ~ length-1)
//15增加数据到链表第pos个节点的左边《无法在末尾添加》
//注意：增删改查之中，只有增加能对空链表操作，其他3个都不能对空链表操作。
enum Error_code Common_list_insert_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size);
//16增加数据到链表第pos个节点的右边（从尾）（p_data是自带内存的，查询完成之后，将p_data的数据增加数据到链表第pos个节点的右边）(pos的取值范围：0 ~ length-1)
//16增加数据到链表第pos个节点的右边《无法在开头添加》
//注意：增删改查之中，只有增加能对空链表操作，其他3个都不能对空链表操作。
enum Error_code Common_list_insert_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size);


//17删除链表第pos个数据（从头）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_delete_data_from_head(Common_list * p_list, int pos);
//18删除链表第pos个数据（从尾）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_delete_data_from_tail(Common_list * p_list, int pos);


//19查询并删除链表第pos个数据（从头）（p_data是自带内存的，查询完成之后，将查询到的数据复制给p_data，并删除节点）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_moveout_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size);
//20查询并删除链表第pos个数据（从尾）（p_data是自带内存的，查询完成之后，将查询到的数据复制给p_data，并删除节点）(pos的取值范围：0 ~ length-1)
enum Error_code Common_list_moveout_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size);


//**通用的以字符数组的形式打印数据，uchar【】，
//注：data的内容是可以使用其他类型来强转的，所以数据的处理需要根据特定的场景来处理
enum Error_code Common_list_printf_total_uchar_data(Common_list * p_list);








#endif




















