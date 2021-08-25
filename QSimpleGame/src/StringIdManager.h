#pragma once
#include "Singleton.h"

#include <vector>
#include <string>
#include <unordered_map>
using std::string;
using std::vector;
using std::unordered_map;

/*
* 总是有 ""对应Id 0
*/
namespace QSimpleGame {
	using StringId = unsigned int;
	
	class StringIdManager : public Singleton<StringIdManager>
	{
		friend class Singleton<StringIdManager>;
	public:
		//添加标识名称
		void		 addString(string string_name);
		//获取标识名称，没有则添加
		StringId   getStringId(string string_name);
		//获取标识名称的字符串
		string   getString(StringId name);
	private:
		StringIdManager();
		~StringIdManager() = default;
		
		//预先申请的个数
		const unsigned int RESERVE_SIZE = 1024*1024*4;
		vector<string> m_string;
		unordered_map<string, StringId> m_string_map;
	};
}