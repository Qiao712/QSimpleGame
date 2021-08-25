#pragma once
#include <string>
#include "StringIdManager.h"

/*****************************************************************/
//生产getType成员,必须置于public后
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
		enum class DelayType{TIME, FRAME}; //延时类型，按时间/按帧
		
		//virtual void send(/*reciver, */ DelayType delay_type, uint64_t delay);
	private:
		//延时
		DelayType m_delay_type;				//延时类型，按时间/按帧
		uint64_t	  m_delay;					//延时时间/帧
		uint64_t  m_delay_rest;				//剩余延时时间/帧
	};

	//按剩余延时时间比较，x>y
	bool eventDelayCmp(const Event&,const Event&);
}

