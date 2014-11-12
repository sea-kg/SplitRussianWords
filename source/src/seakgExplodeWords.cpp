#include "seakgExplodeWords.h"
#include <iostream>
#include <QCoreApplication>
#include <QLocale>
//---------------------------------------------------------------------------

seakgExplodeWord::seakgExplodeWord() {
	m_strConsonant = "цкнгшщзхфвпрлджчсмтб";
	m_strVowel = "йуеыаоэяию";
	m_strChangesTheLastSound = "ьъ";

	/*
	 QString strСonsonant = "цкнгшщзхфвпрлджчсмтб";

	 for(int i = 1; i <= strСonsonant.Length(); i++)
	 vectСonsonant.push_back(QString(strСonsonant[i]));

	 QString strVowel = "йуеыаоэяию";
	 for(int i = 1; i <= strVowel.Length(); i++)
	 vectVowel.push_back(QString(strVowel[i]));

	 QString strChangesTheLastSound = "ьъ";
	 for(int i = 1; i <= strChangesTheLastSound.Length(); i++)
	 vectChangesTheLastSound.push_back(QString(strChangesTheLastSound[i]));
	 */
}
//---------------------------------------------------------------------------

QString seakgExplodeWord::Explode(QString strWord) {	
	/* первое разобьем слово на составляющие следующим образом:
	сгрупируем гласные
	сгрупируем согласные и мягкий знак или твердый знак
	отдельно будут идти согласные
	*/

	// QLocale locale(QLocale::Russian, QLocale::RussianFederation);
	// locale.toLower(strWord);
 	strWord = strWord.toLower();

	// std::cout << "strWord: Привет [" << strWord.toStdString() << "] \n";

	QVector<QString> vectWithGroup;
	{
		int nRes = makeGroupps(vectWithGroup, strWord);
		if( nRes < 0)
		{
			return strWord;
			// return "Errors " + QString::number(nRes);
		}
	}

	 /*
		далее сгруппированные символы будем разбивать на слоги следующим образом:
		будем искать переход:
		[согласная]->[гласные]
	 */

	 QVector<QString> vectSyllables;
	 vectSyllables.push_back("");
	 if( vectWithGroup.size() > 0 )
	 {
		 typeSimbol typePrepareSimbol = simbUnknown; //this->WhatIsSimbolType(vectWithGroup[0]);
		 QString strPrepareSimbol = "";
		 QString buf = "";
		 bool bFirstSyllable = true;
		 for(int i = 0; i < vectWithGroup.size(); i++)
		 {
			QString newSimbol(vectWithGroup[i]);
			typeSimbol typeNewSimbol = this->WhatIsSimbolType(newSimbol);

			//если встретили [согласная][гласная(гласные)]
			if( typePrepareSimbol == simbConsonant && typeNewSimbol == simbVowel)
			{
				//если это первый слог:
				if(bFirstSyllable)
				{

					bFirstSyllable = false;
					//если слог первый и он начинается с гласной
					if( this->WhatIsSimbolType(buf) == simbVowel)
					{
						//удаляем последнюю группу
						// buf = buf.SubString(1, buf.Length() - strPrepareSimbol.Length());
						buf = buf.mid(0,buf.length() - strPrepareSimbol.length());
						
						vectSyllables.push_back(buf);
						buf = "";
						buf = strPrepareSimbol + newSimbol;
					}
					else
					{
						//первый слог может содержать перед гласной много согласных
						buf += newSimbol;
					};
				}
				//если это не первый слог:
				else
				{

					//удаляем последнюю группу
					// buf = buf.SubString(1, buf.Length() - strPrepareSimbol.Length());
					buf = buf.mid(0,buf.length() - strPrepareSimbol.length());
					
					//добавляем в массив готовых слогов
					vectSyllables.push_back(buf);
					buf = "";
					//задаем значение нового буффера:
					buf = strPrepareSimbol + newSimbol;
				}
			}
			else
			{
				buf += newSimbol;
			};
			typePrepareSimbol = typeNewSimbol;
			strPrepareSimbol = newSimbol;
		 };
		 vectSyllables.push_back(buf);

		 //vectSyllables[vectSyllables.size()-1] = vectSyllables[vectSyllables.size()-1] + buf;
	 };


	 QString strResult;
	 for(int i = 0; i < vectSyllables.size(); i++ )
		if( vectSyllables[i].length() > 0 )
		  strResult += "[" + vectSyllables[i] + "]";
	 return strResult;
};
//---------------------------------------------------------------------------

typeSimbol seakgExplodeWord::WhatIsSimbolType(QString strSimbol) {
	if (strSimbol.length() >= 1) {
		QChar ch = strSimbol.at(0);
		if (m_strConsonant.contains(ch, Qt::CaseInsensitive))
			return simbConsonant;
		else if (m_strVowel.contains(ch, Qt::CaseInsensitive))
			return simbVowel;
		else if (m_strChangesTheLastSound.contains(ch, Qt::CaseInsensitive))
			return simbChangesTheLastSound;
		else
			return simbUnknown;
	}
	else
		return simbUnknown;
};
//---------------------------------------------------------------------------

int seakgExplodeWord::makeGroupps(QVector<QString> &vectWithGroup, QString strWord) {
	typeSimbol typePrepareSimbol = simbUnknown;
	for (int i = 0; i < strWord.count(); i++)
	{
		QString newSimbol(strWord.at(i));
		typeSimbol typeNewSimbol = this->WhatIsSimbolType(newSimbol);
		
		if( typeNewSimbol == simbConsonant )
			vectWithGroup.push_back(newSimbol);
		else if(typeNewSimbol == simbVowel )
		{
			if( typePrepareSimbol == simbVowel)
				vectWithGroup[vectWithGroup.size()-1] = vectWithGroup[vectWithGroup.size()-1] + newSimbol;
			else
				vectWithGroup.push_back(newSimbol);
		}
		else if( typeNewSimbol == simbChangesTheLastSound )
		{
			if( typePrepareSimbol == simbConsonant)
				vectWithGroup[vectWithGroup.size()-1] = vectWithGroup[vectWithGroup.size()-1] + newSimbol;
			else
				return -1;
		}
		else
			return -2;

		typePrepareSimbol = typeNewSimbol;
	};
	return 1;
};
