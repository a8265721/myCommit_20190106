
#include "can.h"

Common_list CAN_receive_message_list;//ȫ�ֱ�����������Ϣ����
Common_list CAN_receive_message_list_vms_shanghai; //ȫ�ֱ�����������Ϣ����
//u32 can_receive_number = 0;
//u32 can_send_number = 0;

/*
u8  temp_idr0 = 0;
u8  temp_idr1 = 0;               
u8  temp_idr2 = 0;
u8  temp_idr3 = 0;
 */
u32  test_huli_can0_receive = 0;
u32  test_huli_can1_receive = 0;
u32  test_huli_can2_receive = 0;


//��ʼ��can0
void INIT_CAN0(void)
{
	if(CAN0CTL0_INITRQ==0)      // ��ѯ�Ƿ�����ʼ��״̬   
		CAN0CTL0_INITRQ =1;        // �����ʼ��״̬

	while (CAN0CTL1_INITAK==0);  //�ȴ������ʼ��״̬

	CAN0BTR0_SJW = 0;            //����ͬ��
	//	CAN0BTR0_BRP = 7;            //���ò�����  
	CAN0BTR0_BRP = 15;       
	CAN0BTR1 = 0x1c;       //����ʱ��1��ʱ��2��Tq���� ,����Ƶ��Ϊ250kb/s
	//������ = ����ʱ�� / ��CAN0BTR0_BRP +1�� / ��CAN0BTR1_TSEG_10 + CAN0BTR1_TSEG_20 + 3��


	// �ر��˲���                                  
	CAN0IDMR0 = 0xFF;
	CAN0IDMR1 = 0xFF;
	CAN0IDMR2 = 0xFF;
	CAN0IDMR3 = 0xFF;
	CAN0IDMR4 = 0xFF;
	CAN0IDMR5 = 0xFF;
	CAN0IDMR6 = 0xFF;
	CAN0IDMR7 = 0xFF; 

	CAN0CTL1 = 0xC0;             //ʹ��MSCANģ��,����Ϊһ������ģʽ��ʹ������ʱ��Դ 

	CAN0CTL0 = 0x00;             //����һ��ģʽ����

	while(CAN0CTL1_INITAK);      //�ȴ��ص�һ������ģʽ

	while(CAN0CTL0_SYNCH==0);    //�ȴ�����ʱ��ͬ��

	CAN0RIER_RXFIE = 1;          //ʹ�ܽ����ж�

}

//can0����
enum Error_code MSCAN0_SendMsg(struct CAN_message *p_msg)
{
	unsigned char send_buf= 0;
	unsigned char sp = 0;
	enum Error_code error_code = Succeed;
	u16 num_temp = 0;

	if(p_msg == NULL )
	{return Pointer_is_null;}

	// ������ݳ���
	if(p_msg->can_len > 8)
	{
		return CAN_length_error;
	}

	// �������ʱ��
	if(CAN0CTL0_SYNCH==0)
	{
		return CAN_out_synchronization;
	}

	//���ͻ�������оƬ��3����ѡ�����п��еģ����û�У������޵ȴ���
	send_buf = 0;
	do
	{
		// Ѱ�ҿ��еĻ�����
		CAN0TBSEL=CAN0TFLG;
		send_buf=CAN0TBSEL;
		num_temp++;
		if(num_temp>100) 
		{
			return  Failed;
		} 
	}
	while(!send_buf);


	// д���ʶ��
	if(p_msg->can_ide == CAN_Id_Standard)
	{
		CAN0TXIDR0 = (u8)(p_msg->can_message_id >>3);
		CAN0TXIDR1 = (u8)(p_msg->can_message_id <<5);

		CAN0TXIDR1_IDE = 0;

		if(p_msg->can_rtr == CAN_RTR_Data)
		{
			CAN0TXIDR1 &= 0xef;
		}
		else
		{
			CAN0TXIDR1 |= 0x10;
		}
	}
	else
	{
		CAN0TXIDR0 = (u8)(p_msg->can_message_id >>21);
		CAN0TXIDR1 = ( (u8)(p_msg->can_message_id >>13) & 0xe0) 
			| ( (u8)(p_msg->can_message_id >>15) & 0x07) ;
		CAN0TXIDR2 = (u8)(p_msg->can_message_id >>7);
		CAN0TXIDR3 = (u8)(p_msg->can_message_id <<1);

		CAN0TXIDR1_SRR = 1;
		CAN0TXIDR1_IDE = 1;

		if(p_msg->can_rtr == CAN_RTR_Data)
		{
			CAN0TXIDR3_RTR = 0;
		}
		else
		{
			CAN0TXIDR3_RTR = 1;
		}
	}


	if(p_msg->can_rtr == CAN_RTR_Data)
	{
		// д������  CAN0TXDSR0~7 ��8�����ݼĴ����������ģ����Կ���ȡָ��Ȼ��ƫ�ơ�
		for(sp = 0; sp < p_msg->can_len; sp++)
		{
			*((&CAN0TXDSR0)+sp) = p_msg->can_data[sp];   
		}

		// д�����ݳ���
		CAN0TXDLR = p_msg->can_len; 
	}
	else
	{
		// д������  CAN0TXDSR0~7 ��8�����ݼĴ����������ģ����Կ���ȡָ��Ȼ��ƫ�ơ�
		for(sp = 0; sp < p_msg->can_len; sp++)
		{
			*((&CAN0TXDSR0)+sp) = 0;   
		}

		// д�����ݳ���
		CAN0TXDLR = 0; 
	}


	// д�����ȼ�
	CAN0TXTBPR = p_msg->can_priorty;

	// �� TXx ��־ (������׼������)
	CAN0TFLG = send_buf;

	//	can_send_number++;

	return error_code;

}

//can0����
enum Error_code MSCAN0_ReceiveMsg(struct CAN_message *p_msg)
{
	unsigned char sp2 = 0;
	enum Error_code error_code = Succeed;
	u32 temp0 = 0;
	u32 temp1 = 0;
	u32 temp2 = 0;
	u32 temp3 = 0;


	if(p_msg == NULL )
	{return Pointer_is_null;}


	// �����ձ�־
	if(!(CAN0RFLG_RXF))
	{
		return CAN_receive_flag_error;
	}

	// ��� CANЭ�鱨��ģʽ ��һ��/��չ�� ��ʶ��
	if(CAN0RXIDR1_IDE == 0)
	{
		p_msg->can_ide = CAN_Id_Standard;

		// ����ʶ��
		p_msg->can_message_id = (u32)(CAN0RXIDR0<<3) | 
			(u32)(CAN0RXIDR1>>5);

		if(CAN0RXIDR1&0x10)
		{
			p_msg->can_rtr = CAN_RTR_Remote;
		}
		else
		{
			p_msg->can_rtr = CAN_RTR_Data;
		}
	}
	else
	{
		p_msg->can_ide = CAN_Id_Extended;
		temp0 =  CAN0RXIDR0;
		temp1 =  CAN0RXIDR1;
		temp2 =  CAN0RXIDR2;
		temp3 =  CAN0RXIDR3;

		// ����ʶ��
		p_msg->can_message_id = 
			(( temp0 << 21) & 0x1fe00000) | 
			(( temp1 << 13) & 0x001c0000) | 
			(( temp1 << 15) & 0x00038000) | 		
			(( temp2 << 7)  & 0x00007f80) | 
			(( temp3 >> 1)  & 0x0000007f) ; 
		//ע���ˣ�freescale�ļĴ����Ƚ����⣬����ֱ�Ӱ�8λ�ļĴ���ǿ��ת��Ϊu32��
		/*		// ����ʶ��
		p_msg->can_message_id = 
		(( (u32)(CAN0RXIDR0) << 21) & 0x1fe00000) | 
		(( (u32)(CAN0RXIDR1) << 13) & 0x001c0000) | 
		(( (u32)(CAN0RXIDR1) << 15) & 0x00038000) | 		
		(( (u32)(CAN0RXIDR2) << 7)  & 0x00007f80) | 
		(( (u32)(CAN0RXIDR3) >> 1)  & 0x0000007f) ;     
		*/		
		if(CAN0RXIDR3 & 0x01)
		{
			p_msg->can_rtr = CAN_RTR_Remote;
		}
		else
		{
			p_msg->can_rtr = CAN_RTR_Data;
		}
	}

	// ��ȡ���ݳ��� 
	p_msg->can_len = CAN0RXDLR_DLC;

	// ��ȡ����
	for(sp2 = 0; sp2 < p_msg->can_len; sp2++)
		p_msg->can_data[sp2] = *((&CAN0RXDSR0)+sp2);

	//��ȡʱ��
	p_msg->can_time = CAN0RXTSR;

	// �� RXF ��־λ (������׼������)
	CAN0RFLG = 0x01;

	return error_code;
}



//can0�����ж�
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt can0_interrupt_receive(void) 
{
	enum Error_code error_code = Succeed;
	struct CAN_message can_msg;

	error_code = MSCAN0_ReceiveMsg(&can_msg);
	if(error_code == Succeed)
	{
	   // test_huli_can0_receive++;
	    if(CAN_receive_message_list.length <20)    
	    {
	        error_code = Common_list_insert_data_from_tail(&CAN_receive_message_list, 0, (char*)(&can_msg), sizeof(CAN_message));
	        test_huli_can0_receive = error_code;
	    	if(error_code != Succeed)	{printf("can0_interrupt_receive failed, error_code:%d \r\n", error_code);} 
	    }
		
	}


}
#pragma CODE_SEG DEFAULT





    /*
#include "can.h"

struct CAN_message can_msg_send;
struct CAN_message can_msg_get;
   */

//��ʼ��CAN1
void INIT_CAN1(void)
{
	if(CAN1CTL0_INITRQ==0)      // ��ѯ�Ƿ�����ʼ��״̬   
		CAN1CTL0_INITRQ =1;        // �����ʼ��״̬

	while (CAN1CTL1_INITAK==0);  //�ȴ������ʼ��״̬

	CAN1BTR0_SJW = 0;            //����ͬ��
	//	CAN1BTR0_BRP = 7;            //���ò�����  
	CAN1BTR0_BRP = 15;      
	CAN1BTR1 = 0x1c;       //����ʱ��1��ʱ��2��Tq���� ,����Ƶ��Ϊ250kb/s
	//������ = ����ʱ�� / ��CAN1BTR0_BRP +1�� / ��CAN1BTR1_TSEG_10 + CAN1BTR1_TSEG_20 + 3��


	// �ر��˲���                                  
	CAN1IDMR0 = 0xFF;
	CAN1IDMR1 = 0xFF;
	CAN1IDMR2 = 0xFF;
	CAN1IDMR3 = 0xFF;
	CAN1IDMR4 = 0xFF;
	CAN1IDMR5 = 0xFF;
	CAN1IDMR6 = 0xFF;
	CAN1IDMR7 = 0xFF; 

	CAN1CTL1 = 0xC0;             //ʹ��MSCANģ��,����Ϊһ������ģʽ��ʹ������ʱ��Դ 

	CAN1CTL0 = 0x00;             //����һ��ģʽ����

	while(CAN1CTL1_INITAK);      //�ȴ��ص�һ������ģʽ

	while(CAN1CTL0_SYNCH==0);    //�ȴ�����ʱ��ͬ��

	CAN1RIER_RXFIE = 1;          //ʹ�ܽ����ж�

}

//CAN1����
enum Error_code MSCAN1_SendMsg(struct CAN_message *p_msg)
{
	unsigned char send_buf= 0;
	unsigned char sp = 0;
	enum Error_code error_code = Succeed;
	u16 num_temp = 0;

	if(p_msg == NULL )
	{return Pointer_is_null;}

	// ������ݳ���
	if(p_msg->can_len > 8)
	{
		return CAN_length_error;
	}

	// �������ʱ��
	if(CAN1CTL0_SYNCH==0)
	{
		return CAN_out_synchronization;
	}

	//���ͻ�������оƬ��3����ѡ�����п��еģ����û�У������޵ȴ���
	send_buf = 0;
	do
	{
		// Ѱ�ҿ��еĻ�����
		CAN1TBSEL=CAN1TFLG;
		send_buf=CAN1TBSEL;
		num_temp++;
		if(num_temp>100) 
		{
			return  Failed;
		}
	}
	while(!send_buf)   ;



	// д���ʶ��
	if(p_msg->can_ide == CAN_Id_Standard)
	{
		CAN1TXIDR0 = (u8)(p_msg->can_message_id >>3);
		CAN1TXIDR1 = (u8)(p_msg->can_message_id <<5);

		CAN1TXIDR1_IDE = 0;

		if(p_msg->can_rtr == CAN_RTR_Data)
		{
			CAN1TXIDR1 &= 0xef;
		}
		else
		{
			CAN1TXIDR1 |= 0x10;
		}
	}
	else
	{
		CAN1TXIDR0 = (u8)(p_msg->can_message_id >>21);
		CAN1TXIDR1 = ( (u8)(p_msg->can_message_id >>13) & 0xe0) 
			| ( (u8)(p_msg->can_message_id >>15) & 0x07) ;
		CAN1TXIDR2 = (u8)(p_msg->can_message_id >>7);
		CAN1TXIDR3 = (u8)(p_msg->can_message_id <<1);

		CAN1TXIDR1_SRR = 1;
		CAN1TXIDR1_IDE = 1;

		if(p_msg->can_rtr == CAN_RTR_Data)
		{
			CAN1TXIDR3_RTR = 0;
		}
		else
		{
			CAN1TXIDR3_RTR = 1;
		}
	}


	if(p_msg->can_rtr == CAN_RTR_Data)
	{
		// д������  CAN1TXDSR0~7 ��8�����ݼĴ����������ģ����Կ���ȡָ��Ȼ��ƫ�ơ�
		for(sp = 0; sp < p_msg->can_len; sp++)
		{
			*((&CAN1TXDSR0)+sp) = p_msg->can_data[sp];   
		}

		// д�����ݳ���
		CAN1TXDLR = p_msg->can_len; 
	}
	else
	{
		// д������  CAN1TXDSR0~7 ��8�����ݼĴ����������ģ����Կ���ȡָ��Ȼ��ƫ�ơ�
		for(sp = 0; sp < p_msg->can_len; sp++)
		{
			*((&CAN1TXDSR0)+sp) = 0;   
		}

		// д�����ݳ���
		CAN1TXDLR = 0; 
	}


	// д�����ȼ�
	CAN1TXTBPR = p_msg->can_priorty;

	// �� TXx ��־ (������׼������)
	CAN1TFLG = send_buf;

	return error_code;

}

//CAN1����
enum Error_code MSCAN1_ReceiveMsg(struct CAN_message *p_msg)
{
	unsigned char sp2 = 0;
	enum Error_code error_code = Succeed;
	u32 temp0 = 0;
	u32 temp1 = 0;
	u32 temp2 = 0;
	u32 temp3 = 0;	

	if(p_msg == NULL )
	{return Pointer_is_null;}


	// �����ձ�־
	if(!(CAN1RFLG_RXF))
	{
		return CAN_receive_flag_error;
	}

	// ��� CANЭ�鱨��ģʽ ��һ��/��չ�� ��ʶ��
	if(CAN1RXIDR1_IDE == 0)
	{
		p_msg->can_ide = CAN_Id_Standard;

		// ����ʶ��
		p_msg->can_message_id = (u32)(CAN1RXIDR0<<3) | 
			(u32)(CAN1RXIDR1>>5);

		if(CAN1RXIDR1&0x10)
		{
			p_msg->can_rtr = CAN_RTR_Remote;
		}
		else
		{
			p_msg->can_rtr = CAN_RTR_Data;
		}
	}
	else
	{
		p_msg->can_ide = CAN_Id_Extended;

		temp0 =  CAN1RXIDR0;
		temp1 =  CAN1RXIDR1;
		temp2 =  CAN1RXIDR2;
		temp3 =  CAN1RXIDR3;

		// ����ʶ��
		p_msg->can_message_id = 
			(( temp0 << 21) & 0x1fe00000) | 
			(( temp1 << 13) & 0x001c0000) | 
			(( temp1 << 15) & 0x00038000) | 		
			(( temp2 << 7)  & 0x00007f80) | 
			(( temp3 >> 1)  & 0x0000007f) ; 

		//ע���ˣ�freescale�ļĴ����Ƚ����⣬����ֱ�Ӱ�8λ�ļĴ���ǿ��ת��Ϊu32��		
		/*				// ����ʶ��
		p_msg->can_message_id = 
		(( (u32)(CAN1RXIDR0) << 21) & 0x1fe00000) | 
		(( (u32)(CAN1RXIDR1) << 13) & 0x001c0000) | 
		(( (u32)(CAN1RXIDR1) << 15) & 0x00038000) | 		
		(( (u32)(CAN1RXIDR2) << 7)  & 0x00007f80) | 
		(( (u32)(CAN1RXIDR3) >> 1)  & 0x0000007f) ;     
		*/	             

		if(CAN1RXIDR3 & 0x01)
		{
			p_msg->can_rtr = CAN_RTR_Remote;
		}
		else
		{
			p_msg->can_rtr = CAN_RTR_Data;
		}
	}

	// ��ȡ���ݳ��� 
	p_msg->can_len = CAN1RXDLR_DLC;

	// ��ȡ����
	for(sp2 = 0; sp2 < p_msg->can_len; sp2++)
		p_msg->can_data[sp2] = *((&CAN1RXDSR0)+sp2);

	//��ȡʱ��
	p_msg->can_time = CAN1RXTSR;

	// �� RXF ��־λ (������׼������)
	CAN1RFLG = 0x01;

	return error_code;
}

         

//CAN1�����ж�
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt can1_interrupt_receive(void) 
{
	enum Error_code error_code = Succeed;
	struct CAN_message can_msg;

	error_code = MSCAN1_ReceiveMsg(&can_msg);
                
	if(error_code == Succeed)
	{
	//    test_huli_can1_receive++;
	     if(CAN_receive_message_list.length <20)    
	    {
		error_code = Common_list_insert_data_from_tail(&CAN_receive_message_list, 0, (char*)(&can_msg), sizeof(CAN_message));
		test_huli_can1_receive = error_code ;
		if(error_code != Succeed)	{printf("can1_interrupt_receive failed, error_code:%d \r\n", error_code);}
	    }
	}

}
#pragma CODE_SEG DEFAULT




//��ʼ��CAN2
void INIT_CAN2(void)
{
	if(CAN2CTL0_INITRQ==0)      // ��ѯ�Ƿ�����ʼ��״̬   
		CAN2CTL0_INITRQ =1;        // �����ʼ��״̬

	while (CAN2CTL1_INITAK==0);  //�ȴ������ʼ��״̬

	CAN2BTR0_SJW = 0;            //����ͬ��
	//	CAN1BTR0_BRP = 7;            //���ò�����  
	CAN2BTR0_BRP = 15;      
	CAN2BTR1 = 0x1c;       //����ʱ��1��ʱ��2��Tq���� ,����Ƶ��Ϊ250kb/s
	//������ = ����ʱ�� / ��CAN1BTR0_BRP +1�� / ��CAN1BTR1_TSEG_10 + CAN1BTR1_TSEG_20 + 3��


	// �ر��˲���                                  
	CAN2IDMR0 = 0xFF;
	CAN2IDMR1 = 0xFF;
	CAN2IDMR2 = 0xFF;
	CAN2IDMR3 = 0xFF;
	CAN2IDMR4 = 0xFF;
	CAN2IDMR5 = 0xFF;
	CAN2IDMR6 = 0xFF;
	CAN2IDMR7 = 0xFF; 

	CAN2CTL1 = 0xC0;             //ʹ��MSCANģ��,����Ϊһ������ģʽ��ʹ������ʱ��Դ 

	CAN2CTL0 = 0x00;             //����һ��ģʽ����

	while(CAN2CTL1_INITAK);      //�ȴ��ص�һ������ģʽ

	while(CAN2CTL0_SYNCH==0);    //�ȴ�����ʱ��ͬ��

	CAN2RIER_RXFIE = 1;          //ʹ�ܽ����ж�

}

//CAN2����
enum Error_code MSCAN2_SendMsg(struct CAN_message *p_msg)
{
	unsigned char send_buf= 0;
	unsigned char sp = 0;
	enum Error_code error_code = Succeed;
	u16 num_temp = 0;

	if(p_msg == NULL )
	{return Pointer_is_null;}

	// ������ݳ���
	if(p_msg->can_len > 8)
	{
		return CAN_length_error;
	}

	// �������ʱ��
	if(CAN2CTL0_SYNCH==0)
	{
		return CAN_out_synchronization;
	}

	//���ͻ�������оƬ��3����ѡ�����п��еģ����û�У������޵ȴ���
	send_buf = 0;
	do
	{
		// Ѱ�ҿ��еĻ�����
		CAN2TBSEL=CAN2TFLG;
		send_buf=CAN2TBSEL;
		num_temp++;
		if(num_temp>100) 
		{
			return  Failed;
		}
	}
	while(!send_buf)   ;



	// д���ʶ��
	if(p_msg->can_ide == CAN_Id_Standard)
	{
		CAN2TXIDR0 = (u8)(p_msg->can_message_id >>3);
		CAN2TXIDR1 = (u8)(p_msg->can_message_id <<5);

		CAN2TXIDR1_IDE = 0;

		if(p_msg->can_rtr == CAN_RTR_Data)
		{
			CAN2TXIDR1 &= 0xef;
		}
		else
		{
			CAN2TXIDR1 |= 0x10;
		}
	}
	else
	{
		CAN2TXIDR0 = (u8)(p_msg->can_message_id >>21);
		CAN2TXIDR1 = ( (u8)(p_msg->can_message_id >>13) & 0xe0) 
			| ( (u8)(p_msg->can_message_id >>15) & 0x07) ;
		CAN2TXIDR2 = (u8)(p_msg->can_message_id >>7);
		CAN2TXIDR3 = (u8)(p_msg->can_message_id <<1);

		CAN2TXIDR1_SRR = 1;
		CAN2TXIDR1_IDE = 1;

		if(p_msg->can_rtr == CAN_RTR_Data)
		{
			CAN2TXIDR3_RTR = 0;
		}
		else
		{
			CAN2TXIDR3_RTR = 1;
		}
	}


	if(p_msg->can_rtr == CAN_RTR_Data)
	{
		// д������  CAN1TXDSR0~7 ��8�����ݼĴ����������ģ����Կ���ȡָ��Ȼ��ƫ�ơ�
		for(sp = 0; sp < p_msg->can_len; sp++)
		{
			*((&CAN2TXDSR0)+sp) = p_msg->can_data[sp];   
		}

		// д�����ݳ���
		CAN2TXDLR = p_msg->can_len; 
	}
	else
	{
		// д������  CAN1TXDSR0~7 ��8�����ݼĴ����������ģ����Կ���ȡָ��Ȼ��ƫ�ơ�
		for(sp = 0; sp < p_msg->can_len; sp++)
		{
			*((&CAN2TXDSR0)+sp) = 0;   
		}

		// д�����ݳ���
		CAN2TXDLR = 0; 
	}


	// д�����ȼ�
	CAN2TXTBPR = p_msg->can_priorty;

	// �� TXx ��־ (������׼������)
	CAN2TFLG = send_buf;

	return error_code;

}

//CAN2����    
enum Error_code MSCAN2_ReceiveMsg(struct CAN_message *p_msg)
{
	unsigned char sp2 = 0;
	enum Error_code error_code = Succeed;
	u32 temp0 = 0;
	u32 temp1 = 0;
	u32 temp2 = 0;
	u32 temp3 = 0;	

	if(p_msg == NULL )
	{return Pointer_is_null;}


	// �����ձ�־
	if(!(CAN2RFLG_RXF))
	{
		return CAN_receive_flag_error;
	}

	// ��� CANЭ�鱨��ģʽ ��һ��/��չ�� ��ʶ��
	if(CAN2RXIDR1_IDE == 0)
	{
		p_msg->can_ide = CAN_Id_Standard;

		// ����ʶ��
		p_msg->can_message_id = (u32)(CAN2RXIDR0<<3) | 
			(u32)(CAN2RXIDR1>>5);

		if(CAN2RXIDR1&0x10)
		{
			p_msg->can_rtr = CAN_RTR_Remote;
		}
		else
		{
			p_msg->can_rtr = CAN_RTR_Data;
		}
	}
	else
	{
		p_msg->can_ide = CAN_Id_Extended;

		temp0 =  CAN2RXIDR0;
		temp1 =  CAN2RXIDR1;
		temp2 =  CAN2RXIDR2;
		temp3 =  CAN2RXIDR3;

		// ����ʶ��
		p_msg->can_message_id = 
			(( temp0 << 21) & 0x1fe00000) | 
			(( temp1 << 13) & 0x001c0000) | 
			(( temp1 << 15) & 0x00038000) | 		
			(( temp2 << 7)  & 0x00007f80) | 
			(( temp3 >> 1)  & 0x0000007f) ; 

		//ע���ˣ�freescale�ļĴ����Ƚ����⣬����ֱ�Ӱ�8λ�ļĴ���ǿ��ת��Ϊu32��		
		/*				// ����ʶ��
		p_msg->can_message_id = 
		(( (u32)(CAN1RXIDR0) << 21) & 0x1fe00000) | 
		(( (u32)(CAN1RXIDR1) << 13) & 0x001c0000) | 
		(( (u32)(CAN1RXIDR1) << 15) & 0x00038000) | 		
		(( (u32)(CAN1RXIDR2) << 7)  & 0x00007f80) | 
		(( (u32)(CAN1RXIDR3) >> 1)  & 0x0000007f) ;     
		*/	             

		if(CAN2RXIDR3 & 0x01)
		{
			p_msg->can_rtr = CAN_RTR_Remote;
		}
		else
		{
			p_msg->can_rtr = CAN_RTR_Data;
		}
	}

	// ��ȡ���ݳ��� 
	p_msg->can_len = CAN2RXDLR_DLC;

	// ��ȡ����
	for(sp2 = 0; sp2 < p_msg->can_len; sp2++)
		p_msg->can_data[sp2] = *((&CAN2RXDSR0)+sp2);

	//��ȡʱ��
	p_msg->can_time = CAN2RXTSR;

	// �� RXF ��־λ (������׼������)
	CAN2RFLG = 0x01;

	return error_code;
}



//CAN2�����ж�
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt can2_interrupt_receive(void) 
{
	enum Error_code error_code = Succeed;
	struct CAN_message can_msg;

	error_code = MSCAN2_ReceiveMsg(&can_msg);

	if(error_code == Succeed)
	{
	 //   test_huli_can2_receive++;
	     if(CAN_receive_message_list_vms_shanghai.length <20)    
	    {
		error_code = Common_list_insert_data_from_tail(&CAN_receive_message_list_vms_shanghai, 0, (char*)(&can_msg), sizeof(CAN_message));
		test_huli_can2_receive   =  error_code;
		if(error_code != Succeed)	{printf("can1_interrupt_receive failed, error_code:%d \r\n", error_code);}
	    }
	}

}
#pragma CODE_SEG DEFAULT







//��ʱ����can���ݣ�Ĭ��can0��
enum Error_code Control_Policy_ontime_can_send_data(enum Can_Channels CANx, CAN_message * p_can_msg)
{
	enum Error_code error_code = Succeed;

	if(p_can_msg == NULL)
	{return Pointer_is_null;}

	switch(CANx)
	{
	case CAN0:
		error_code = MSCAN0_SendMsg(p_can_msg);
		break;
	case CAN1:
		error_code = MSCAN1_SendMsg(p_can_msg);
		break;
	case CAN2:
  	error_code = MSCAN2_SendMsg(p_can_msg);
		break;
  	default:
  	break;
	//	need 
	
	}

	return error_code;
}





