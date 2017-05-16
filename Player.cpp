#include"Player.h"
bool Player::initWithFile(const char *pszFilename)
{
	CCAssert(pszFilename != NULL, "Invalid filename for Player");

	//作些自己的初始化
	bool bRet = CCSprite::initWithFile(pszFilename);
	velocity = ccp(0.f, 0.f); //速度初始化
	return bRet;
}
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

void Player::update(float dt)
{//2
	CCPoint gravity = ccp(0.f, -450.f);
	//3
	CCPoint gravityStep = ccpMult(gravity, dt);
	//4
	this->velocity = ccpAdd(this->velocity, gravityStep);
	//5
	this->setPosition(ccpAdd(this->getPosition(), velocity*dt));
}
