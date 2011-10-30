/********************************************************************************
** Form generated from reading UI file 'GuettaViewer.ui'
**
** Created: Sun Oct 30 19:09:34 2011
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

class Ui_GuettaViewer
{
public:
    QPushButton *pushButton;
    QToolButton *toolButton;

    void setupUi(QWidget *GuettaViewer)
    {
        if (GuettaViewer->objectName().isEmpty())
            GuettaViewer->setObjectName(QString::fromUtf8("GuettaViewer"));
        GuettaViewer->resize(341, 216);
        pushButton = new QPushButton(GuettaViewer);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 20, 97, 27));
        toolButton = new QToolButton(GuettaViewer);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(50, 90, 24, 25));

        retranslateUi(GuettaViewer);

        QMetaObject::connectSlotsByName(GuettaViewer);
    } // setupUi

    void retranslateUi(QWidget *GuettaViewer)
    {
        GuettaViewer->setWindowTitle(QApplication::translate("GuettaViewer", "GuettaViewer", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("GuettaViewer", "PushButton", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("GuettaViewer", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GuettaViewer: public Ui_GuettaViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUETTAVIEWER_H
