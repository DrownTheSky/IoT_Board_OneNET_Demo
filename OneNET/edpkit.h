#ifndef _EDPKIT_H_
#define _EDPKIT_H_

#include "rtthread.h"
#include "stdbool.h"

#define edp_alloc_buffer(buffer_size) rt_malloc(buffer_size);
#define edp_free_buffer(buffer)\
{\
    if (buffer != NULL) {\
        rt_free(buffer);\
        buffer = NULL;\
    }\
}\

//=============================����==============================
#define MOSQ_MSB(A)         (uint8_t)((A & 0xFF00) >> 8)
#define MOSQ_LSB(A)         (uint8_t)(A & 0x00FF)


/*--------------------------------��Ϣ���--------------------------------*/
#define MSG_ID_HIGH			0x55
#define MSG_ID_LOW			0xAA


/*--------------------------------��Ϣ����--------------------------------*/
/* �������� */
#define CONNREQ             0x10
/* ������Ӧ */
#define CONNRESP            0x20
/* ���ӹر� */
#define DISCONNECT			0x40
/* ת��(͸��)���� */
#define PUSHDATA            0x30
/* �洢(ת��)���� */
#define SAVEDATA            0x80
/* �洢ȷ�� */
#define SAVEACK             0x90
/* �������� */
#define CMDREQ              0xA0
/* ������Ӧ */
#define CMDRESP             0xB0
/* �������� */
#define PINGREQ             0xC0
/* ������Ӧ */
#define PINGRESP            0xD0
/* �������� */
#define ENCRYPTREQ          0xE0
/* ������Ӧ */
#define ENCRYPTRESP         0xF0


#ifndef NULL
#define NULL (void*)0
#endif


/*--------------------------------SAVEDATA��Ϣ֧�ֵĸ�ʽ����--------------------------------*/
typedef enum
{
	
    kTypeFullJson = 0x01,
	
    kTypeBin = 0x02,
	
    kTypeSimpleJsonWithoutTime = 0x03,
	
    kTypeSimpleJsonWithTime = 0x04,
	
    kTypeString = 0x05
	
} SaveDataType;


/*--------------------------------�ڴ���䷽����־--------------------------------*/
#define MEM_FLAG_NULL		0
#define MEM_FLAG_ALLOC		1
#define MEM_FLAG_STATIC		2


typedef struct Buffer
{
	
	uint8_t	*_data;		//Э������
	
	uint32_t	_len;		//д������ݳ���
	
	uint32_t	_size;		//�����ܴ�С
	
	uint8_t	_memFlag;	//�ڴ�ʹ�õķ�����0-δ����	1-ʹ�õĶ�̬����		2-ʹ�õĹ̶��ڴ�
	
} EDP_PACKET_STRUCTURE;


/*--------------------------------ɾ��--------------------------------*/
void EDP_DeleteBuffer(EDP_PACKET_STRUCTURE *edpPacket);

/*--------------------------------���--------------------------------*/
uint8_t EDP_UnPacketRecv(uint8_t *dataPtr);

/*--------------------------------��¼��ʽ1���--------------------------------*/
bool EDP_PacketConnect1(const char *devid, const char *apikey, uint16_t cTime, EDP_PACKET_STRUCTURE *edpPacket);

/*--------------------------------��¼��ʽ2���--------------------------------*/
bool EDP_PacketConnect2(const char *proid, const char *auth_key, uint16_t cTime, EDP_PACKET_STRUCTURE *edpPacket);

/*--------------------------------���ӻظ����--------------------------------*/
uint8_t EDP_UnPacketConnectRsp(uint8_t *rev_data);

/*--------------------------------���ݵ��ϴ����--------------------------------*/
uint8_t EDP_PacketSaveData(const char *devid, int16_t send_len, char *type_bin_head, SaveDataType type, EDP_PACKET_STRUCTURE *edpPacket);

/*--------------------------------PushData���--------------------------------*/
uint8_t EDP_PacketPushData(const char *devid, const char *msg, uint32_t msg_len, EDP_PACKET_STRUCTURE *edpPacket);

/*--------------------------------PushData���--------------------------------*/
uint8_t EDP_UnPacketPushData(uint8_t *rev_data, char **src_devid, char **req, uint32_t *req_len);

/*--------------------------------�����·����--------------------------------*/
uint8_t EDP_UnPacketCmd(uint8_t *rev_data, char **cmdid, uint16_t *cmdid_len, char **req, uint32_t *req_len);

/*--------------------------------����ظ����--------------------------------*/
bool EDP_PacketCmdResp(const char *cmdid, uint16_t cmdid_len, const char *resp, uint32_t resp_len, EDP_PACKET_STRUCTURE *edpPacket);

/*--------------------------------�����������--------------------------------*/
bool EDP_PacketPing(EDP_PACKET_STRUCTURE *edpPacket);

#endif
