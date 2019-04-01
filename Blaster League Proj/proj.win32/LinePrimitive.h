#pragma once
//forward declareing

namespace cocos2d
{
	class Vec2;
	class DrawNode;
}

namespace OOP
{

	class PrimitiveLine
	{
	public:
		PrimitiveLine(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_EndPosition);
		~PrimitiveLine();
		cocos2d::DrawNode *getPrimitive();
	private:
		cocos2d::DrawNode *m_Node;
	};
}