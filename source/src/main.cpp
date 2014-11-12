#include <QCoreApplication>
#include <QMap>
#include <QTextCodec> // подключение класса кодека текста
#include <iostream>
#include "seakgExplodeWords.h"

int main(int argc, char *argv[])
{
	// для корректной работы с русскими символами
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    
    QCoreApplication a(argc, argv);
	
	// init class 
	seakgExplodeWord exp;
	
	// some tests
	QMap<QString,QString> mapTests;
	mapTests.insert(QString("телефон"), QString("[те][ле][фон]"));
	mapTests["компьютер"] = "[ком][пью][тер]";
	mapTests["звук"] = "[звук]";
	mapTests["словарь"] = "[сло][варь]";
	mapTests["текст"] = "[текст]";
	mapTests["фонетика"] = "[фо][не][ти][ка]";
	mapTests["абрикос"] = "[аб][ри][кос]";
	mapTests["калькулятор"] = "[каль][ку][ля][тор]";
	mapTests["дуб"] = "[дуб]";
	mapTests["вышка"] = "[выш][ка]";
	mapTests["телевизор"] = "[те][ле][ви][зор]";
	mapTests["сайт"] = "[сайт]";
	mapTests["человек"] = "[че][ло][век]";
	mapTests["лодка"] = "[лод][ка]";
	mapTests["корабль"] = "[ко][рабль]";
	mapTests["геракл"] = "[ге][ракл]";
	mapTests["дизайнер"] = "[ди][зай][нер]";
	mapTests["согласование"] = "[сог][ла][со][ва][ние]";
	mapTests["программирование"] = "[прог][рам][ми][ро][ва][ние]";

	QMap<QString, QString>::const_iterator i = mapTests.constBegin();
	int nFailedTests = 0;
	while (i != mapTests.constEnd()) {
		QString tmpRes = exp.Explode(i.key());
		if ( tmpRes != i.value()) {
			std::cout << "Failed test:\n"
				<< " When try split word '" << i.key().toStdString() << "'"
				<< " expected '" << i.value().toStdString() << "'"
				<< " but got '" << tmpRes.toStdString() << "'"
				<< std::endl;
			nFailedTests++;
		}
		++i;
	}
	
	if (nFailedTests > 0) {
		return -1;
	}

	if (argc == 1)
	{
		std::cout << "Usage: " << argv[0] << " слово и еще одно слово\n\n";
		return -1;
	}
	
	for (int i = 1; i < argc; i++)
	{
		QString sWord = QString(argv[i]);
		QString res = exp.Explode(sWord);
		std::cout << res.toStdString() << " ";
	}
	// std::cout << "Result: " << res.toStdString() << "\n\n";
	std::cout << "\n";
    return 0;
}
