#include "StringIdManager.h"
#include <cassert>

namespace QSimpleGame {
	StringIdManager::StringIdManager()
	{
		m_string_map.reserve(RESERVE_SIZE);
		m_string.reserve(RESERVE_SIZE);

		//默认的0标识空字符串
		m_string.push_back(string(""));
		m_string_map[string("")] = 0;
	}

	void StringIdManager::addString(string str)
	{
		m_string.push_back(str);
		StringId name = m_string.size() - 1;
		m_string_map[str] = name;
	}

	StringId StringIdManager::getStringId(string str)
	{
		auto it = m_string_map.find(str);
		if (it == m_string_map.end()) {
			//add new string_id
			m_string.push_back(str);
			StringId name = m_string.size() - 1;
			m_string_map[str] = name;
			return name;
		}

		return it->second;
	}
	string StringIdManager::getString(StringId string_id)
	{
		assert(string_id < m_string.size());
		return m_string[string_id];
	}
}
