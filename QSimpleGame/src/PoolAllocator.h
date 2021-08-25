#pragma once
#include "Singleton.h"

#include <cassert>
#include <cstring>
/*池分配器*/
namespace QSimpleGame {
	template<typename T>
	class PoolAllocator : public Singleton<PoolAllocator<T>>
	{
		friend class Singleton<PoolAllocator<T>>;
		union Element{
			Element() : next_pos(this + 1) { }	//相连接
			~Element() { };
			T		 obj;			//对象本身
			Element* next_pos;		//下个内存空间的位置
		};
	public:
		//构造
		template<typename ... Args>
		T* construct(Args ... args);

		//销毁
		void destory(T* ptr);

		//已申请对象的个数
		unsigned int getNum() { return m_num_used; }
	private:
		PoolAllocator(unsigned int n);
		~PoolAllocator();

		//最多可容纳的元素的数量
		unsigned int m_max_num;
		
		//已分配数量
		unsigned int m_num_used = 0;

		//内存块首地址
		Element* m_mem;

		//下一个可用空位置
		Element* m_empty_pos;

		//用于标记是否已经使用
		bool* m_marks;
	};

	template<typename T>
	template<typename ...Args>
	inline T* PoolAllocator<T>::construct(Args ... args)
	{
		assert(m_empty_pos != nullptr);
		m_num_used++;

		//标记已使用
		m_marks[m_empty_pos - m_mem] = true;

		T* curr_pos = reinterpret_cast<T*>(m_empty_pos);
		m_empty_pos = m_empty_pos->next_pos;

		::new(curr_pos) T(args...);

		return curr_pos;
	}

	template<typename T>
	inline PoolAllocator<T>::PoolAllocator(unsigned int n):
		m_max_num(n)
	{
		m_mem = new Element[n];
		m_empty_pos = m_mem;

		m_marks = new bool[n];
		memset(m_marks, 0, n * sizeof(bool));

		//以空指针作结尾
		m_mem[n - 1].next_pos = nullptr;
	}

	template<typename T>
	inline PoolAllocator<T>::~PoolAllocator()
	{
		for (int i = 0; i < m_max_num; i++) {
			if (m_marks[i]) {
				m_mem[i].obj.~T();
			}
		}

		delete [] m_marks;
		delete [] m_mem;
	}

	template<typename T>
	inline void PoolAllocator<T>::destory(T* ptr)
	{
		int pos = reinterpret_cast<Element*>(ptr) - m_mem;
		assert(pos >= 0 && pos < m_max_num && m_marks[pos]);
		m_num_used--;

		m_marks[pos] = false;

		ptr->~T();
		(reinterpret_cast<Element*>(ptr))->next_pos = m_empty_pos;
		m_empty_pos = reinterpret_cast<Element*>(ptr);
	}
}

