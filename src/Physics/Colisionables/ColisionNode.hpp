#pragma once

#include "../../Graphics/Nodes/BaseNode.hpp"

namespace bas {

	class ColisionNode : public BaseNode
	{
	public:
		ColisionNode();
		virtual char getType();
	};

}