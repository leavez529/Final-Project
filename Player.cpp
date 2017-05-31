#include"Player.h"
Player* Player::create(const char *pszFileName)
{
	Player *pobPlayer = new Player();
	if (pobPlayer && pobPlayer->initWithFile(pszFileName))
	{
		pobPlayer->autorelease();
		return pobPlayer;
	}
	CC_SAFE_DELETE(pobPlayer);
	return NULL;
}
