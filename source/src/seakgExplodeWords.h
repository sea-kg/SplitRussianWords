/*
	Copyright (c) 2014
	Evgenii Sopov (mrseakg@gmail.com)
*/

#ifndef seakgExplodeWordsH
#define seakgExplodeWordsH

#include <QString>
#include <QVector>

enum typeSimbol {
	simbUnknown = 0,
	simbConsonant = 1,
	simbVowel = 2,
	simbChangesTheLastSound = 3
};

class seakgExplodeWord {
	public:
		seakgExplodeWord();
		QString Explode(QString strWord);

	private:
		// согласные
		QString m_strConsonant;
		
		// гласные
		QString m_strVowel;
		
		// изменяющие последний звук
		QString m_strChangesTheLastSound;

		typeSimbol WhatIsSimbolType(QString strSimbol);
		int makeGroupps(QVector<QString> &vectWithGroup, QString strWord);
};
#endif
