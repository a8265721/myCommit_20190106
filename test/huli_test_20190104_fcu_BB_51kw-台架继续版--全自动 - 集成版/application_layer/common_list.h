/*
list ��ģ��������
�÷�������ģ��ֱ�Ӱ�����ģ�飬Ȼ����Ϊ�����ķ���ֵ��
�ϲ�ͨ���������������жϺ�����ִ�������
*/ 
//--------------------------------------------------------------------------------------------

#ifndef __COMMON_LIST_H
#define __COMMON_LIST_H	


#include "error_system.h"
#include "sci.h"

/*
ע�⣺
common_list���Զ������ڴ�ġ�
node�����ֶ�����ġ�
����˵����

*/

typedef char  elemType ;

//ͨ������Ľṹ�壬ֱ�Ӵ������ɣ��ڴ��Զ�����
//���밴�չ���ʹ��  init--������ɾ�Ĳ�--����clear
typedef struct common_list{   
	int length;
	struct node *head;
	struct node *tail;
}Common_list;

//ͨ������ڵ�Ľṹ��
//ֻ�����ֶ�������ͷ��ڴ�
typedef struct node{    
	elemType * data;
	int data_size;

	struct node *last;
	struct node *next;
}Node;



//1	��ʼ��������������
enum Error_code Common_list_init(Common_list * p_list);

//1.2��������ʹ��ͬһ�����ݣ�����һ��ָ�����ȵ�����
enum Error_code Common_list_create(Common_list * p_list,  elemType * p_data, int data_size, int length);

//2	����������p_list_old���Դ��ڵ��ڴ�ģ����ͷ�p_list_new��	Ȼ���p_list_new�����µĽڵ��ڴ棩
enum Error_code Common_list_copy(Common_list * p_list_old, Common_list * p_list_new);

//3 ƴ������ֱ��ƴ�ӣ��������µ��ڴ棬��
//p_list1 = p_list1 + p_list2 ; p_list2 = NULL��    		Ȼ�� p_list2����ӵ����ǰ�Ľڵ��ڴ�
enum Error_code Common_list_only_joint(Common_list * p_list1, Common_list * p_list2);

//4 ƴ�������������µ��ڴ棬Ȼ�������ݲ�ƴ����list1�ĺ��档��
//p_list3 copy= p_list2��	p_list1 = p_list1 + p_list3 ;    	��ʱ p_list2����ӵ����ǰ���ڴ�
enum Error_code Common_list_copy_and_joint(Common_list * p_list1, Common_list * p_list2);

//5 ��ȡ������
enum Error_code Common_list_get_length(Common_list * p_list, int * p_length);

//6 ����������������(�ͷ�node��data���ڴ�)
enum Error_code Common_list_clear(Common_list * p_list);

//6.2 ��������ڵ���ڴ�(�ͷ�node��data���ڴ�)
enum Error_code Node_clear(Node ** pp_node);

//6.3 ���������ڵ���ڴ�(����node��data���ڴ�)
enum Error_code Node_create(Node ** pp_node, elemType * p_data, int data_size);



//7 �޸Ľڵ�����ݣ����ݺͽڵ㶼�Դ��ڴ棬ʹ��֮ǰp_node�����ֶ������ڴ棩
enum Error_code Common_list_data_to_node(elemType * p_data, int data_size, Node * p_node);

//8 �ڵ�ת��Ϊ���ݣ����ݺͽڵ㶼�Դ��ڴ棬p_node���ڴ����ֶ�����ģ� ֮������Ƿ��p_node���д���
enum Error_code Common_list_node_to_data(Node * p_node, elemType * p_data, int data_size);


//9 ��ѯ�����pos���ڵ㣨��ͷ��(pp_node��Ϊ�գ�*pp_nodeΪ�գ���ѯ���֮��*pp_nodeָ���Ӧ�Ľڵ�)(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_find_node_from_head(Common_list * p_list, int pos, Node ** pp_node);
//10��ѯ�����pos���ڵ㣨��β��(pp_node��Ϊ�գ�*pp_nodeΪ�գ���ѯ���֮��*pp_nodeָ���Ӧ�Ľڵ�)(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_find_node_from_tail(Common_list * p_list, int pos, Node ** pp_node);


//11��ѯ�����pos�����ݣ���ͷ����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽���ѯ�������ݸ��Ƹ�p_data��(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_find_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size);
//12��ѯ�����pos�����ݣ���β����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽���ѯ�������ݸ��Ƹ�p_data��(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_find_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size);

//13�޸������pos�����ݣ���ͷ����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽�p_data�����ݸ��Ƶ�ָ���Ľڵ㣩(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_updata_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size);
//14�޸������pos�����ݣ���β����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽�p_data�����ݸ��Ƶ�ָ���Ľڵ㣩(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_updata_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size);


//15�������ݵ������pos���ڵ����ߣ���ͷ����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽�p_data�������������ݵ������pos���ڵ����ߣ�(pos��ȡֵ��Χ��0 ~ length-1)
//15�������ݵ������pos���ڵ����ߡ��޷���ĩβ��ӡ�
//ע�⣺��ɾ�Ĳ�֮�У�ֻ�������ܶԿ��������������3�������ܶԿ����������
enum Error_code Common_list_insert_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size);
//16�������ݵ������pos���ڵ���ұߣ���β����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽�p_data�������������ݵ������pos���ڵ���ұߣ�(pos��ȡֵ��Χ��0 ~ length-1)
//16�������ݵ������pos���ڵ���ұߡ��޷��ڿ�ͷ��ӡ�
//ע�⣺��ɾ�Ĳ�֮�У�ֻ�������ܶԿ��������������3�������ܶԿ����������
enum Error_code Common_list_insert_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size);


//17ɾ�������pos�����ݣ���ͷ��(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_delete_data_from_head(Common_list * p_list, int pos);
//18ɾ�������pos�����ݣ���β��(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_delete_data_from_tail(Common_list * p_list, int pos);


//19��ѯ��ɾ�������pos�����ݣ���ͷ����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽���ѯ�������ݸ��Ƹ�p_data����ɾ���ڵ㣩(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_moveout_data_from_head(Common_list * p_list, int pos, elemType * p_data, int data_size);
//20��ѯ��ɾ�������pos�����ݣ���β����p_data���Դ��ڴ�ģ���ѯ���֮�󣬽���ѯ�������ݸ��Ƹ�p_data����ɾ���ڵ㣩(pos��ȡֵ��Χ��0 ~ length-1)
enum Error_code Common_list_moveout_data_from_tail(Common_list * p_list, int pos, elemType * p_data, int data_size);


//**ͨ�õ����ַ��������ʽ��ӡ���ݣ�uchar������
//ע��data�������ǿ���ʹ������������ǿת�ģ��������ݵĴ�����Ҫ�����ض��ĳ���������
enum Error_code Common_list_printf_total_uchar_data(Common_list * p_list);








#endif




















