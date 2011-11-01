/********************************************************************************
** Form generated from reading UI file 'GuettaCapture.ui'
**
** Created: Mon Oct 31 00:33:49 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUETTACAPTURE_H
#define UI_GUETTACAPTURE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GuettaCapture
{
public:
    QGroupBox *groupBoxCaptureSettings;
    QSpinBox *spinBoxCaptureNumber;
    QPushButton *pushButtonCapture;
    QCheckBox *checkBoxOverwriteFiles;
    QLineEdit *lineEditSceneName;
    QProgressBar *progressBar;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *checkBoxAutoincrementNumber;
    QLineEdit *lineEditCaptureName;
    QLabel *label_3;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget_2;
    QGridLayout *capturedViewer;
    QGroupBox *groupBox_2;
    QWidget *gridLayoutWidget;
    QGridLayout *realTimeViewer;
    QLabel *labelNoInputDeviceConnected;
    QPushButton *pushButtonConnectInputDevice;

    void setupUi(QWidget *GuettaCapture)
    {
        if (GuettaCapture->objectName().isEmpty())
            GuettaCapture->setObjectName(QString::fromUtf8("GuettaCapture"));
        GuettaCapture->resize(1183, 579);
        groupBoxCaptureSettings = new QGroupBox(GuettaCapture);
        groupBoxCaptureSettings->setObjectName(QString::fromUtf8("groupBoxCaptureSettings"));
        groupBoxCaptureSettings->setGeometry(QRect(10, 10, 311, 271));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxCaptureSettings->sizePolicy().hasHeightForWidth());
        groupBoxCaptureSettings->setSizePolicy(sizePolicy);
        groupBoxCaptureSettings->setBaseSize(QSize(0, 0));
        groupBoxCaptureSettings->setContextMenuPolicy(Qt::DefaultContextMenu);
        groupBoxCaptureSettings->setLayoutDirection(Qt::LeftToRight);
        groupBoxCaptureSettings->setAutoFillBackground(true);
        groupBoxCaptureSettings->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBoxCaptureSettings->setFlat(false);
        spinBoxCaptureNumber = new QSpinBox(groupBoxCaptureSettings);
        spinBoxCaptureNumber->setObjectName(QString::fromUtf8("spinBoxCaptureNumber"));
        spinBoxCaptureNumber->setGeometry(QRect(130, 80, 59, 27));
        pushButtonCapture = new QPushButton(groupBoxCaptureSettings);
        pushButtonCapture->setObjectName(QString::fromUtf8("pushButtonCapture"));
        pushButtonCapture->setGeometry(QRect(10, 200, 97, 27));
        checkBoxOverwriteFiles = new QCheckBox(groupBoxCaptureSettings);
        checkBoxOverwriteFiles->setObjectName(QString::fromUtf8("checkBoxOverwriteFiles"));
        checkBoxOverwriteFiles->setGeometry(QRect(10, 160, 181, 22));
        lineEditSceneName = new QLineEdit(groupBoxCaptureSettings);
        lineEditSceneName->setObjectName(QString::fromUtf8("lineEditSceneName"));
        lineEditSceneName->setGeometry(QRect(130, 40, 113, 27));
        progressBar = new QProgressBar(groupBoxCaptureSettings);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(140, 200, 118, 23));
        progressBar->setValue(24);
        label = new QLabel(groupBoxCaptureSettings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 111, 27));
        label_2 = new QLabel(groupBoxCaptureSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 111, 27));
        checkBoxAutoincrementNumber = new QCheckBox(groupBoxCaptureSettings);
        checkBoxAutoincrementNumber->setObjectName(QString::fromUtf8("checkBoxAutoincrementNumber"));
        checkBoxAutoincrementNumber->setGeometry(QRect(210, 80, 61, 27));
        checkBoxAutoincrementNumber->setChecked(true);
        lineEditCaptureName = new QLineEdit(groupBoxCaptureSettings);
        lineEditCaptureName->setObjectName(QString::fromUtf8("lineEditCaptureName"));
        lineEditCaptureName->setGeometry(QRect(130, 120, 171, 27));
        label_3 = new QLabel(groupBoxCaptureSettings);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 120, 101, 27));
        groupBox = new QGroupBox(GuettaCapture);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(750, 10, 410, 380));
        gridLayoutWidget_2 = new QWidget(groupBox);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 30, 391, 341));
        capturedViewer = new QGridLayout(gridLayoutWidget_2);
        capturedViewer->setObjectName(QString::fromUtf8("capturedViewer"));
        capturedViewer->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(GuettaCapture);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(330, 10, 410, 380));
        gridLayoutWidget = new QWidget(groupBox_2);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 391, 341));
        realTimeViewer = new QGridLayout(gridLayoutWidget);
        realTimeViewer->setObjectName(QString::fromUtf8("realTimeViewer"));
        realTimeViewer->setContentsMargins(0, 0, 0, 0);
        labelNoInputDeviceConnected = new QLabel(GuettaCapture);
        labelNoInputDeviceConnected->setObjectName(QString::fromUtf8("labelNoInputDeviceConnected"));
        labelNoInputDeviceConnected->setEnabled(true);
        labelNoInputDeviceConnected->setGeometry(QRect(340, 390, 201, 21));
        labelNoInputDeviceConnected->setAutoFillBackground(false);
        pushButtonConnectInputDevice = new QPushButton(GuettaCapture);
        pushButtonConnectInputDevice->setObjectName(QString::fromUtf8("pushButtonConnectInputDevice"));
        pushButtonConnectInputDevice->setGeometry(QRect(576, 390, 151, 27));
        pushButtonConnectInputDevice->setLayoutDirection(Qt::RightToLeft);

        retranslateUi(GuettaCapture);

        QMetaObject::connectSlotsByName(GuettaCapture);
    } // setupUi

    void retranslateUi(QWidget *GuettaCapture)
    {
        GuettaCapture->setWindowTitle(QApplication::translate("GuettaCapture", "Form", 0, QApplication::UnicodeUTF8));
        groupBoxCaptureSettings->setTitle(QApplication::translate("GuettaCapture", "Capture settings", 0, QApplication::UnicodeUTF8));
        pushButtonCapture->setText(QApplication::translate("GuettaCapture", "Capture", 0, QApplication::UnicodeUTF8));
        checkBoxOverwriteFiles->setText(QApplication::translate("GuettaCapture", "Overwrite files", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GuettaCapture", "Scence name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GuettaCapture", "Capture number:", 0, QApplication::UnicodeUTF8));
        checkBoxAutoincrementNumber->setText(QApplication::translate("GuettaCapture", "Auto", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GuettaCapture", "Capture name:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("GuettaCapture", "Captured cloud", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("GuettaCapture", "Real time cloud", 0, QApplication::UnicodeUTF8));
        labelNoInputDeviceConnected->setText(QApplication::translate("GuettaCapture", "No input device connected.", 0, QApplication::UnicodeUTF8));
        pushButtonConnectInputDevice->setText(QApplication::translate("GuettaCapture", "Connect input device", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GuettaCapture: public Ui_GuettaCapture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUETTACAPTURE_H
