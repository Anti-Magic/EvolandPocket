#include "OperatorBase.h"

bool OperatorBase::init()
{
	if (!Layer::init()) {
		return false;
	}
	_dir = Tools::Direction::NONE;
	_isTrigger = false;
	return true;
}

bool OperatorBase::isTrigger()
{
	return _isTrigger;
}

Tools::Direction OperatorBase::getDirection()
{
	return _dir;
}

void OperatorBase::reset()
{
	_dir = Tools::Direction::NONE;
	_isTrigger = false;
}

std::string OperatorBase::getOpName()
{
	return _opName;
}