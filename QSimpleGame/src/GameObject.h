#pragma once
#include "StringIdManager.h"

#include <string>
using std::string;

namespace QSimpleGame{
	class GameObject
	{
	public:
		GameObject() = default;
		GameObject(string name);
	protected:
		string m_name;
		StringId m_name_id;
	private:

	};
}

