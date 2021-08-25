#pragma once
#include <cassert>

namespace QSimpleGame {
	template<typename Class>
	class Singleton {
	public:
		template<typename ...Args>
		static void		init(Args ...args);
		static inline Class& instance();
		static void		destory();
	protected:
		Singleton() = default;
		virtual ~Singleton() = default;
	private:
		static Class* m_instance;
	};

	/*----------------------implement-------------------------------*/

	template<typename Class>
	Class* Singleton<Class>::m_instance = nullptr;
	
	template<typename Class>
	template<typename ...Args>
	inline void Singleton<Class>::init(Args ...args)
	{
		assert(m_instance == nullptr);
		m_instance = new Class(args...);
	}

	template<typename Class>
	inline Class& Singleton<Class>::instance()
	{
		assert(m_instance != nullptr);
		return *m_instance;
	}
	template<typename Class>
	void Singleton<Class>::destory()
	{
		assert(m_instance != nullptr);
		delete m_instance;
		m_instance = nullptr;
	}
}