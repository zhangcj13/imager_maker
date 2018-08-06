/********************************************************************************
** Form generated from reading UI file 'mslider2.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSLIDER2_H
#define UI_MSLIDER2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mSlider2
{
public:

    void setupUi(QWidget *mSlider2)
    {
        if (mSlider2->objectName().isEmpty())
            mSlider2->setObjectName(QStringLiteral("mSlider2"));
        mSlider2->resize(400, 300);

        retranslateUi(mSlider2);

        QMetaObject::connectSlotsByName(mSlider2);
    } // setupUi

    void retranslateUi(QWidget *mSlider2)
    {
        mSlider2->setWindowTitle(QApplication::translate("mSlider2", "mSlider2", 0));
    } // retranslateUi

};

namespace Ui {
    class mSlider2: public Ui_mSlider2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSLIDER2_H
