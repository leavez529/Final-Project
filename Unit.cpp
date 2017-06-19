#include"Unit.h"

Unit* Unit::create(const char *pszFileName)
{
	Unit *pobUnit = new Unit();
	if (pobUnit && pobUnit->initWithFile(pszFileName))
	{
		pobUnit->autorelease();
		return pobUnit;
	}
	CC_SAFE_DELETE(pobUnit);
	return NULL;
}

