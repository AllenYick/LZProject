#include "InOutStatus.h"

InOutTunnelStatus* InOutTunnelStatus::inouttunnel_instance_ = NULL;

InOutTunnelStatus::InOutTunnelStatus()
{
	for(int i = 0; i < NUM_STATUS; i++)
		m_vSt_[i] = STATUS_OUT;   // initial with LZ_OUT
	is_prein_ = false;
	is_in_ = false;
	last_state_ = OUT_TUNNEL;
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
	// ȷ����ǰ"Ƭ��״̬"
	Status current_status;   // ��һʱ��״̬
	if( num_camreas == 2 )
	{
		if(dis[0] <= -0.5 || dis[1] <= -0.5)
			current_status = STATUS_OUT; 
		else if (dis[0] < INOUTHOLE_THRESH && dis[1] < INOUTHOLE_THRESH)    // or leftd + rightd < 20
			current_status = STATUS_IN;
		else
			current_status = STATUS_OUT;
	}
	else // num_camaras == 1
	{
		if( dis[0] >= 0.0 && dis[0] < INOUTHOLE_THRESH )
			current_status = STATUS_IN;
		else 
			current_status = STATUS_OUT;
	}
	// ����״̬����
	for(int i = 0; i < NUM_STATUS-1; i++)   
		m_vSt_[i] = m_vSt_[i+1];
	m_vSt_[NUM_STATUS-1] = current_status;

	// ״̬ת��
	switch(last_state_)
	{
	case OUT_TUNNEL:  //
		if(current_status == STATUS_IN)
		{  
			is_prein_ = true;
			is_in_ = false;
			last_state_ = PREIN_TUNNEL;  // ת�Ƶ�Ԥ����
		}
		break;
	case PREIN_TUNNEL:
		if(current_status == STATUS_OUT)
		{
			is_prein_ = false;       // ����
			is_in_ = false;
			last_state_ = OUT_TUNNEL;
		}
		else  // ���������ϸ�
		{
			int i = 0;
			// �������� NUM_STATUS ��Ԥ�����������
			while(i < NUM_STATUS && m_vSt_[i] == STATUS_IN) 
				i++;
			if(i == NUM_STATUS) 
			{
				is_in_ = true;	   // ����
				is_prein_ = true;
				last_state_ = IN_TUNNEL;
			}
		}
		break;
	case IN_TUNNEL:
		if(current_status == STATUS_OUT)
		{
			int i = 0;
			// �������� NUM_STATUS ��Ԥ����������������
			while(i < NUM_STATUS && m_vSt_[i] == STATUS_OUT)
				i++;
			if(i == NUM_STATUS)
			{
				is_prein_ = false;       // ����
				is_in_ = false;
				last_state_ = OUT_TUNNEL;
			}
		}
		break;
	}
	return last_state_;
}
