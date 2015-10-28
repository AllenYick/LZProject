/****************************************************************
*	CameraConfiguration.h
* @brief 
*   处理进出洞状态
* @params
*   distance 
* @author   Yike    
*          2015.06.10
*****************************************************************/
#ifndef INOUTSTATUS_H
#define INOUTSTATUS_H

#include <vector>
#include "LzCommon.h"

#define  NUM_STATUS   5           // 连续状态序列长度
/*
 * @brief  
 *  片刻状态（moment status）：火车在某一时刻的状态，由距离决定
 */
enum Status
{
	STATUS_IN  = 4, 
	STATUS_OUT = 5
};  
/*
 * @brief  
 * 连续状态（continue status）: 由连续状态序列最后n个以及当前时刻的片刻状态决定  
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
	// 状态序列
	Status m_vSt_[NUM_STATUS]; 
	State  last_state_;    // 前一个状态
	bool   is_prein_;   // s1->P
	bool   is_in_;      // s0->I
	// PI 00: 出洞  10: 预进洞  11:进洞
};

#endif