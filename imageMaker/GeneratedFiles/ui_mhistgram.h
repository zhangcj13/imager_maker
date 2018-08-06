/********************************************************************************
** Form generated from reading UI file 'mhistgram.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MHISTGRAM_H
#define UI_MHISTGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mHistGram
{
public:

    void setupUi(QWidget *mHistGram)
    {
        if (mHistGram->objectName().isEmpty())
            mHistGram->setObjectName(QStringLiteral("mHistGram"));
        mHistGram->resize(400, 300);

        retranslateUi(mHistGram);

        QMetaObject::connectSlotsByName(mHistGram);
    } // setupUi

    void retranslateUi(QWidget *mHistGram)
    {
        mHistGram->setWindowTitle(QApplication::translate("mHistGram", "mHistGram", 0));
    } // retranslateUi

};

namespace Ui {
    class mHistGram: public Ui_mHistGram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MHISTGRAM_H
