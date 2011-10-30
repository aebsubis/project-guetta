/********************************************************************************
** Form generated from reading UI file 'GuettaViewer.ui'
**
** Created: Sun Oct 30 19:30:17 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUETTAVIEWER_H
#define UI_GUETTAVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuettaCapture
{
public:
    QPushButton *pushButton;
    QToolButton *toolButton;

    void setupUi(QWidget *GuettaCapture)
    {
        if (GuettaCapture->objectName().isEmpty())
            GuettaCapture->setObjectName(QString::fromUtf8("GuettaCapture"));
        GuettaCapture->resize(341, 216);
        pushButton = new QPushButton(GuettaCapture);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 20, 97, 27));
        toolButton = new QToolButton(GuettaCapture);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(50, 90, 24, 25));

        retranslateUi(GuettaCapture);

        QMetaObject::connectSlotsByName(GuettaCapture);
    } // setupUi

    void retranslateUi(QWidget *GuettaCapture)
    {
        GuettaCapture->setWindowTitle(QApplication::translate("GuettaCapture", "GuettaViewer", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("GuettaCapture", "PushButton", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("GuettaCapture", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GuettaCapture: public Ui_GuettaCapture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUETTAVIEWER_H
