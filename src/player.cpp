#include "player.h"
#include "game.h"

Player::Player()
{
	mInputDialog.setHidden(true);

	mInputDialog.setFont(QFont("GillSansMT",20,60));
	mInputDialog.setFixedSize(500,300);

	mInputDialog.setWindowTitle("FINISH!");
	mInputDialog.setLabelText("PLEASE GIVE IN YOUR\nPLAYER NAME: ");
	mInputDialog.setOkButtonText("Save");
	mInputDialog.setCancelButtonText(QString("Don't save"));

	mInputDialog.setTextEchoMode(QLineEdit::Normal);
	mInputDialog.setModal(Qt::WindowModal);

	connect(&mInputDialog,SIGNAL(textValueSelected(QString)),this,SLOT(savePlayerName(QString)));

	mPlayerName = "";
}

void Player::updateFile()
{

	QTime time;
	QTime time2;
	QString filename;
	int lineOfInsertion = 0;

	time.setHMS(0,0,0);
	time = QTime::fromString(mTotalTime,"mm:ss.zzz"); // convert player time for file comparison

	switch(mCircuit)
	{
	case Monza:
		filename = "highscores/Monza.score";
		break;
	case Hockenheimring:
		filename = "highscores/Hockenheimring.score";
		break;
	case YasMarina:
		filename = "highscores/YasMarina.score";
		break;
    case Bahrain:
        filename = "highscores/Bahrain.score";
        break;
	}

	QFile file(filename);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
		QStringList list,tmpList;
		QString line;
		QTextStream in(&file);

		while(!in.atEnd()){
			line = in.readLine();
			list << line;
		}
		in.reset();
		in.flush();
		if(in.seek(0)){
			while (!in.atEnd())
			{
				line = in.readLine();
				tmpList = line.split(QRegExp("\\,"));

				time2.setHMS(0,0,0);
				time2 = QTime::fromString(tmpList.at(1),"mm:ss.zzz");

				if(time < time2) break;
				if(tmpList.at(1) == "-") break;

				lineOfInsertion++;
			}
		}
		list.insert(lineOfInsertion,QString(mPlayerName + "," + mTotalTime));
		list.removeLast();
		file.close();

		if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text )){
			for(int i = 0; i < 10; i++)	in << list.at(i) << "\n";
		}
		file.close();
	}
}

void Player::endRaceDialog(QString lapTimeArray[], QString totalTime)
{
	mInputDialog.showNormal();
	memcpy(mPlayerTimes,lapTimeArray,sizeof(mPlayerTimes));
	mTotalTime = totalTime;
}

void Player::SetCircuit(Circuit circuit){
	mCircuit = circuit;
}

void Player::savePlayerName(QString name){
	if(name == ""){
		mInputDialog.showNormal();
	} else{
		mPlayerName = name;
		updateFile();
		emit playerInputFinished();
	}
}
