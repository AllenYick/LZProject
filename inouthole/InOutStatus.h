/****************************************************************
*	CameraConfiguration.h
* @brief 
*   ���������״̬
* @params
*   distance 
* @author   Yike    
*          2015.06.10
*****************************************************************/
#ifndef INOUTSTATUS_H
#define INOUTSTATUS_H

#include <vector>
#include "LzCommon.h"

#define  NUM_STATUS   5           // ����״̬���г���
/*
 * @brief  
 *  Ƭ��״̬��moment status��������ĳһʱ�̵�״̬���ɾ������
 */
enum Status
{
	STATUS_IN  = 4, 
	STATUS_OUT = 5
};  
/*
 * @brief  
 * ����״̬��continue status��: ������״̬�������n���Լ���ǰʱ�̵�Ƭ��״̬����  
 */
enum State
{
	IN_TUNNEL    = 3, 
	OUT_TUNNEL   = 0, 
	PREIN_TUNNEL = 2
};

class InOutTunnelStatus
{
public:
	static InOutTunnelStatus* getInstance(); 
	State process(double[], int);
	State getState();

private:
	InOutTunnelStatus();
	static InOutTunnelStatus *inouttunnel_instance_;
	// ״̬����
	Status m_vSt_[NUM_STATUS]; 
	State  last_state_;    // ǰһ��״̬
	bool   is_prein_;   // s1->P
	bool   is_in_;      // s0->I
	// PI 00: ����  10: Ԥ����  11:����
};

#endif