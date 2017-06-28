#include "player.h"

Player::Player()
{
}

void Player::endRaceDialog(QString lapTimeArray[])
{
	bool ok;
	mPlayerName = QInputDialog::getText(0,"FINISHED", "PLAYER NAME: ",\
										QLineEdit::Normal, "",&ok,Qt::Dialog);
	memcpy(mPlayerTimes,lapTimeArray,sizeof(mPlayerTimes));
}
