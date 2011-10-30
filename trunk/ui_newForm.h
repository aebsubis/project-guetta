/********************************************************************************
** Form generated from reading UI file 'newForm.ui'
**
** Created: Tue Oct 11 18:22:58 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFORM_H
#define UI_NEWFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newForm
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox_keyPoints;
    QLabel *label;
    QLineEdit *lineEdit_keyPoint1;
    QLineEdit *lineEdit_keyPoint2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_distanceXYZ;
    QLineEdit *lineEdit_distanceDescriptor;

    void setupUi(QDialog *newForm)
    {
        if (newForm->objectName().isEmpty())
            newForm->setObjectName(QString::fromUtf8("newForm"));
        newForm->resize(660, 388);
        verticalLayoutWidget = new QWidget(newForm);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 10, 631, 261));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_keyPoints = new QCheckBox(newForm);
        checkBox_keyPoints->setObjectName(QString::fromUtf8("checkBox_keyPoints"));
        checkBox_keyPoints->setGeometry(QRect(20, 280, 97, 22));
        label = new QLabel(newForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 320, 91, 17));
        lineEdit_keyPoint1 = new QLineEdit(newForm);
        lineEdit_keyPoint1->setObjectName(QString::fromUtf8("lineEdit_keyPoint1"));
        lineEdit_keyPoint1->setGeometry(QRect(90, 310, 221, 27));
        lineEdit_keyPoint2 = new QLineEdit(newForm);
        lineEdit_keyPoint2->setObjectName(QString::fromUtf8("lineEdit_keyPoint2"));
        lineEdit_keyPoint2->setGeometry(QRect(400, 310, 221, 27));
        label_4 = new QLabel(newForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(320, 320, 91, 17));
        label_5 = new QLabel(newForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 350, 101, 17));
        label_6 = new QLabel(newForm);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(280, 360, 141, 17));
        lineEdit_distanceXYZ = new QLineEdit(newForm);
        lineEdit_distanceXYZ->setObjectName(QString::fromUtf8("lineEdit_distanceXYZ"));
        lineEdit_distanceXYZ->setGeometry(QRect(130, 350, 113, 27));
        lineEdit_distanceDescriptor = new QLineEdit(newForm);
        lineEdit_distanceDescriptor->setObjectName(QString::fromUtf8("lineEdit_distanceDescriptor"));
        lineEdit_distanceDescriptor->setGeometry(QRect(430, 350, 113, 27));

        retranslateUi(newForm);

        QMetaObject::connectSlotsByName(newForm);
    } // setupUi

    void retranslateUi(QDialog *newForm)
    {
        newForm->setWindowTitle(QApplication::translate("newForm", "newForm", 0, QApplication::UnicodeUTF8));
        checkBox_keyPoints->setText(QApplication::translate("newForm", "KeyPoints", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("newForm", "KeyPoint:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("newForm", "KeyPoint:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("newForm", "Distance xyz:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("newForm", "Distance descriptor:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class newForm: public Ui_newForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFORM_H
