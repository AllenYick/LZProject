#include "InOutStatus.h"
#include "DataModel.h"

InOutTunnelStatus* InOutTunnelStatus::inouttunnel_instance_ = NULL;

InOutTunnelStatus::InOutTunnelStatus()
{
	for(int i = 0; i < NUM_STATUS; i++)
		m_vSt_[i] = STATUS_OUT;   // initial with LZ_OUT
	is_prein_ = false;
	is_in_ = false;
	last_state_ = OUT_TUNNEL;
	DataModel *m = DataModel::getInstance();
	thresh = m->inOutTunnelThresh;
	m = NULL;
}

InOutTunnelStatus* InOutTunnelStatus::getInstance()
{
	if(inouttunnel_instance_ == NULL)
		inouttunnel_instance_ = new InOutTunnelStatus;
	return inouttunnel_instance_;
}

State InOutTunnelStatus::getState()
{
	return last_state_;
}

State InOutTunnelStatus::process(double dis[], int num_camreas)
{
	// 确定当前"片刻状态"
	Status current_status;   // 这一时刻状态
	if( num_camreas == 2 )
	{
		if(dis[0] <= -0.5 || dis[1] <= -0.5)
			current_status = STATUS_OUT; 
		else if ( (dis[0] < thresh && dis[1] < thresh) || (dis[0] + dis[1] < 2*thresh))    // or leftd + rightd < 20
			current_status = STATUS_IN;
		else
			current_status = STATUS_OUT;
	}
	else // num_camaras == 1
	{
		if( dis[0] >= 0.0 && dis[0] < thresh )
			current_status = STATUS_IN;
		else 
			current_status = STATUS_OUT;
	}
	// 更新状态序列
	for(int i = 0; i < NUM_STATUS-1; i++)   
		m_vSt_[i] = m_vSt_[i+1];
	m_vSt_[NUM_STATUS-1] = current_status;

	// 状态转移
	switch(last_state_)
	{
	case OUT_TUNNEL:  //
		if(current_status == STATUS_IN)
		{  
			is_prein_ = true;
			is_in_ = false;
			last_state_ = PREIN_TUNNEL;  // 转移到预进洞
		}
		break;
	case PREIN_TUNNEL:
		if(current_status == STATUS_OUT)
		{
			is_prein_ = false;       // 出洞
			is_in_ = false;
			last_state_ = OUT_TUNNEL;
		}
		else  // 进洞条件严格
		{
			int i = 0;
			// 连续出现 NUM_STATUS 次预进洞才算进洞
			while(i < NUM_STATUS && m_vSt_[i] == STATUS_IN) 
				i++;
			if(i == NUM_STATUS) 
			{
				is_in_ = true;	   // 进洞
				is_prein_ = true;
				last_state_ = IN_TUNNEL;
			}
		}
		break;
	case IN_TUNNEL:
		if(current_status == STATUS_OUT)
		{
			int i = 0;
			// 连续出现 NUM_STATUS 次预出洞才算真正出洞
			while(i < NUM_STATUS && m_vSt_[i] == STATUS_OUT)
				i++;
			if(i == NUM_STATUS)
			{
				is_prein_ = false;       // 出洞
				is_in_ = false;
				last_state_ = OUT_TUNNEL;
			}
		}
		break;
	}
	return last_state_;
}

