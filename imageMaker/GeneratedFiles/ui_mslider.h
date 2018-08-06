/********************************************************************************
** Form generated from reading UI file 'mslider.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSLIDER_H
#define UI_MSLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mSlider
{
public:

    void setupUi(QWidget *mSlider)
    {
        if (mSlider->objectName().isEmpty())
            mSlider->setObjectName(QStringLiteral("mSlider"));
        mSlider->resize(400, 300);

        retranslateUi(mSlider);

        QMetaObject::connectSlotsByName(mSlider);
    } // setupUi

    void retranslateUi(QWidget *mSlider)
    {
        mSlider->setWindowTitle(QApplication::translate("mSlider", "mSlider", 0));
    } // retranslateUi

};

namespace Ui {
    class mSlider: public Ui_mSlider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSLIDER_H
