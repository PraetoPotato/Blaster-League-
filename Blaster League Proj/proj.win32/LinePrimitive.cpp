#include "LinePrimitive.h"
#include "2d/CCDrawNode.h"

OOP::PrimitiveLine::PrimitiveLine(const cocos2d::Vec2 & a_StartPosition, const cocos2d::Vec2 & a_EndPosition)
	: m_Node(cocos2d::DrawNode::create())
{
	m_Node->drawLine(a_StartPosition, a_EndPosition, cocos2d::Color4F(0.0f, 1.0f, 0.0f, 1.0f));
}