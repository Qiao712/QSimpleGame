#pragma once
#include "Singleton.h"

#include <vector>
#include <string>
#include <unordered_map>
using std::string;
using std::vector;
using std::unordered_map;

/*
* ������ ""��ӦId 0
*/
namespace QSimpleGame {
	using StringId = unsigned int;
	
	class StringIdManager : public Singleton<StringIdManager>
	{
		friend class Singleton<StringIdManager>;
	public:
		//��ӱ�ʶ����
		void		 addString(string string_name);
		//��ȡ��ʶ���ƣ�û�������
		StringId   getStringId(string string_name);
		//��ȡ��ʶ���Ƶ��ַ���
		string   getString(StringId name);
	private:
		StringIdManager();
		~StringIdManager() = default;
		
		//Ԥ������ĸ���
		const unsigned int RESERVE_SIZE = 1024*1024*4;
		vector<string> m_string;
		unordered_map<string, StringId> m_string_map;
	};
}