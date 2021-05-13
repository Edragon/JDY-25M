#include <reg51.h>
#include <intrins.h>
#include <string.h>



#define INT8 	  		char
#define INT16 			int
#define UINT8 	unsigned  	char
#define UINT16 	unsigned 	int


UINT8 ReceivedString[20];
UINT8 ReceivedStringPosition;


//��ʱ����,us,���255 us-------------------------------------------------------
void Delay_us(UINT8 n)
{
	for(;n>0;n--)
		_nop_();
}


//��ʱ����,ms------------------------------------------------------------------
void Delay_ms(UINT16 n)
{
    UINT16 i;
    for(i=0; i<n; i++)
    {
	 	Delay_us(250);
		Delay_us(250);
		Delay_us(250);
		Delay_us(250);
    }
}
			
				

	   
//���ڳ�ʼ��
void UART_Init(void)
{ 
	SCON = 0x40;                	//���ڷ�ʽ1
	PCON = 0;                   	//SMOD=0
	REN = 1;                     	//�������
	
	TMOD = 0x20;               		//��ʱ��1��ʱ��ʽ2

	//TH1 = 0xe6;                		//12MHz 1200������
	//TL1 = 0xe6;			   	   
	//TH1 = 0xF3;                		//12MHz 2400������
	//TL1 = 0xF3;			   	   
	//TH1 = 0xFE;                		//12MHz 19200������
	//TL1 = 0xFE;			   	   
	TH1 = 0xFD;                		//12MHz 9600������
	TL1 = 0xFD;			   	   
	//TH1 = 0xE8;					//11.0592MHz,1200������
	//TL1 = 0xE8;

	TR1 = 1;                  		//������ʱ��

	ES = 1;							//UART�ж�
	EA = 1;							//�ж�ʹ��

}

//����һ��Char
void UART_Send_Char(INT8 aChar)
{
 	SBUF = aChar;
 	while(TI == 0);//�ȴ���ֱ�����ͳɹ�
	TI = 0;
}


void UART_Send_String(INT8 *aString, UINT16 StringLength)
{
	UINT8 i;
	for ( i = 0; i< StringLength; i++ )
	{
		UART_Send_Char( aString[i] );
	}

}


char code Sdata[] = "lxr";
INT8 Receive[1] = "*";
INT16 index =0;
//������-----------------------------------------------------------------------

#define STAT_pinn P00

uchar *name = "AT+NANE123\r\n";
uchar *NETID = "AT+NETID123456789ABC\r\n";
uchar all_io_H[7]={0xAA,0xfc,0xff,0xff,0xe7,0xff,0xff};//��ָ���Ϊ������OUT��������Ϊ�ߵ�ƽ
uchar all_io_L[7]={0xAA,0xfc,0xff,0xff,0xe7,0xf0,0x00};//��ָ���Ϊ������OUT��������Ϊ�͵�ƽ
uchar MESH_UART_data[7]={0xAA,0xFB,0xFF,0xFF,0x31,0x32,0x33};//��ָ�ϱ�ʾ������ģ�鴮�ڹ㲥123���ݣ����Ӵ����������
uchar MESH_UART_02_data[7]={0xAA,0xFB,0x00,0x03,0x37,0x38,0x39};//��ָ�ϱ�ʾֻ��̵�ַΪ0X03��ģ�鷢��0X373839���ݣ����Ӵ������



void main(void)//�˴���ֻ��˼·�ο���δʵ�����в��Թ�����Ҫ����֧����ϵQQ��3411947569
{
	UART_Init();  //��ʼ��UART
	Delay_ms(1000);//500MS
	UART_Send_String( name,strlen(name) );//���������㲥��Ϊ112233
	Delay_ms(500);
	UART_Send_String( NETID,strlen(NETID) );//������������ID��   һ�������˹㲥��������ID�ź�����ģ�飬ģ�齫���Զ�����
	Delay_ms(500);
	UART_Send_String( all_io_H,7 );//��ָ���Ϊ������OUT��������Ϊ�ߵ�ƽ
	Delay_ms(500);
	UART_Send_String( all_io_L,7 );//��ָ���Ϊ������OUT��������Ϊ�͵�ƽ
	Delay_ms(500);
	UART_Send_String( MESH_UART_data,7 );//��ָ�ϱ�ʾ������ģ�鴮�ڹ㲥123���ݣ����Ӵ����������
	Delay_ms(1000);
	UART_Send_String( MESH_UART_02_data7 );//��ָ�ϱ�ʾֻ��̵�ַΪ0X03��ģ�鷢��0X373839���ݣ����Ӵ������
	Delay_ms(1000);
	
	while (1)
	{

		
	}
}

//UART�жϷ������-------------------------------------------------------------
void UART_Receive_Int() interrupt 4
{	
	if( RI == 1)
	{
		RI	= 0;		
		if( index < 1 )
		{
			Receive[index] = SBUF;
			index++;
		}else{
			index = 0;
		}		
	}	
}
