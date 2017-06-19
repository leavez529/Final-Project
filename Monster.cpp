#include"Monster.h"

Monster* Monster::create(const char *pszFileName)
{
	Monster *pobMonster = new Monster();
	if (pobMonster && pobMonster->initWithFile(pszFileName))
	{
		pobMonster->autorelease();
		return pobMonster;
	}
	CC_SAFE_DELETE(pobMonster);
	return NULL;
}

