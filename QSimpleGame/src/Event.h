#pragma once
#include <string>
#include "StringIdManager.h"

/*****************************************************************/
//����getType��Ա,��������public��
#define EVENT_TYPE(TYPE_NAME) \
	virtual StringId getType() {	  \
		static StringId type_name_id = StringIdManager::instance().getStringId(TYPE_NAME);	\
		return type_name_id;	 \
	}
/*****************************************************************/

namespace QSimpleGame {
	class Event
	{
		friend bool eventDelayCmp(const Event&, const Event&);
	public:
		EVENT_TYPE("BASE_EVENT")
		enum class DelayType{TIME, FRAME}; //��ʱ���ͣ���ʱ��/��֡
		
		//virtual void send(/*reciver, */ DelayType delay_type, uint64_t delay);
	private:
		//��ʱ
		DelayType m_delay_type;				//��ʱ���ͣ���ʱ��/��֡
		uint64_t	  m_delay;					//��ʱʱ��/֡
		uint64_t  m_delay_rest;				//ʣ����ʱʱ��/֡
	};

	//��ʣ����ʱʱ��Ƚϣ�x>y
	bool eventDelayCmp(const Event&,const Event&);
}

