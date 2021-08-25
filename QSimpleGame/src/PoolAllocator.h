#pragma once
#include "Singleton.h"

#include <cassert>
#include <cstring>
/*�ط�����*/
namespace QSimpleGame {
	template<typename T>
	class PoolAllocator : public Singleton<PoolAllocator<T>>
	{
		friend class Singleton<PoolAllocator<T>>;
		union Element{
			Element() : next_pos(this + 1) { }	//������
			~Element() { };
			T		 obj;			//������
			Element* next_pos;		//�¸��ڴ�ռ��λ��
		};
	public:
		//����
		template<typename ... Args>
		T* construct(Args ... args);

		//����
		void destory(T* ptr);

		//���������ĸ���
		unsigned int getNum() { return m_num_used; }
	private:
		PoolAllocator(unsigned int n);
		~PoolAllocator();

		//�������ɵ�Ԫ�ص�����
		unsigned int m_max_num;
		
		//�ѷ�������
		unsigned int m_num_used = 0;

		//�ڴ���׵�ַ
		Element* m_mem;

		//��һ�����ÿ�λ��
		Element* m_empty_pos;

		//���ڱ���Ƿ��Ѿ�ʹ��
		bool* m_marks;
	};

	template<typename T>
	template<typename ...Args>
	inline T* PoolAllocator<T>::construct(Args ... args)
	{
		assert(m_empty_pos != nullptr);
		m_num_used++;

		//�����ʹ��
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

		//�Կ�ָ������β
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

