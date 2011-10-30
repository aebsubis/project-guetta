/********************************************************************************
** Form generated from reading UI file 'Guetta.ui'
**
** Created: Sun Oct 30 19:09:35 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUETTA_H
#define UI_GUETTA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Guetta
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QLabel *label_7;
    QLineEdit *lineEdit_maxKeyPoints;
    QLineEdit *lineEdit__maxKeyPointsAlineamiento;
    QLabel *label_8;
    QLineEdit *lineEdit_maxDistancia;
    QLabel *label_9;
    QPushButton *pushButton_cambiar;
    QWidget *tab_4;
    QLabel *label;
    QRadioButton *radioButton_narf;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_acumular;
    QGroupBox *groupBox;
    QLabel *label_6;
    QLabel *label_5;
    QLineEdit *lineEdit_distanceDescriptor;
    QLineEdit *lineEdit_keyPoint1;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *lineEdit_distanceXYZ;
    QLineEdit *lineEdit_keyPoint2;
    QRadioButton *radioButton_surf;
    QRadioButton *radioButton_sift;
    QComboBox *comboBox2;
    QLabel *label_2;
    QComboBox *comboBox1;
    QWidget *tab_2;
    QLabel *label_10;
    QLineEdit *lineEdit_directorio;
    QPushButton *pushButton_seleccionarDirectorio;
    QTableView *tableView;
    QPushButton *pushButton_procesar;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;

    void setupUi(QDialog *Guetta)
    {
        if (Guetta->objectName().isEmpty())
            Guetta->setObjectName(QString::fromUtf8("Guetta"));
        Guetta->resize(1435, 824);
        tabWidget = new QTabWidget(Guetta);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 10, 1421, 811));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget_2 = new QTabWidget(tab);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(1150, 130, 261, 301));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 20, 211, 17));
        lineEdit_maxKeyPoints = new QLineEdit(tab_3);
        lineEdit_maxKeyPoints->setObjectName(QString::fromUtf8("lineEdit_maxKeyPoints"));
        lineEdit_maxKeyPoints->setGeometry(QRect(90, 50, 81, 27));
        lineEdit__maxKeyPointsAlineamiento = new QLineEdit(tab_3);
        lineEdit__maxKeyPointsAlineamiento->setObjectName(QString::fromUtf8("lineEdit__maxKeyPointsAlineamiento"));
        lineEdit__maxKeyPointsAlineamiento->setGeometry(QRect(90, 120, 81, 27));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 90, 281, 20));
        lineEdit_maxDistancia = new QLineEdit(tab_3);
        lineEdit_maxDistancia->setObjectName(QString::fromUtf8("lineEdit_maxDistancia"));
        lineEdit_maxDistancia->setGeometry(QRect(90, 200, 81, 27));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 170, 211, 17));
        pushButton_cambiar = new QPushButton(tab_3);
        pushButton_cambiar->setObjectName(QString::fromUtf8("pushButton_cambiar"));
        pushButton_cambiar->setGeometry(QRect(80, 240, 97, 27));
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget_2->addTab(tab_4, QString());
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1150, 20, 67, 17));
        radioButton_narf = new QRadioButton(tab);
        radioButton_narf->setObjectName(QString::fromUtf8("radioButton_narf"));
        radioButton_narf->setGeometry(QRect(1150, 90, 116, 22));
        radioButton_narf->setChecked(false);
        gridLayoutWidget = new QWidget(tab);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 1141, 791));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_acumular = new QCheckBox(tab);
        checkBox_acumular->setObjectName(QString::fromUtf8("checkBox_acumular"));
        checkBox_acumular->setGeometry(QRect(1190, 760, 97, 22));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(1150, 450, 231, 281));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 220, 141, 17));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 160, 101, 17));
        lineEdit_distanceDescriptor = new QLineEdit(groupBox);
        lineEdit_distanceDescriptor->setObjectName(QString::fromUtf8("lineEdit_distanceDescriptor"));
        lineEdit_distanceDescriptor->setGeometry(QRect(10, 240, 201, 27));
        lineEdit_keyPoint1 = new QLineEdit(groupBox);
        lineEdit_keyPoint1->setObjectName(QString::fromUtf8("lineEdit_keyPoint1"));
        lineEdit_keyPoint1->setGeometry(QRect(10, 60, 201, 27));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 100, 67, 17));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 67, 17));
        lineEdit_distanceXYZ = new QLineEdit(groupBox);
        lineEdit_distanceXYZ->setObjectName(QString::fromUtf8("lineEdit_distanceXYZ"));
        lineEdit_distanceXYZ->setGeometry(QRect(10, 180, 201, 27));
        lineEdit_keyPoint2 = new QLineEdit(groupBox);
        lineEdit_keyPoint2->setObjectName(QString::fromUtf8("lineEdit_keyPoint2"));
        lineEdit_keyPoint2->setGeometry(QRect(10, 120, 201, 27));
        radioButton_surf = new QRadioButton(tab);
        radioButton_surf->setObjectName(QString::fromUtf8("radioButton_surf"));
        radioButton_surf->setGeometry(QRect(1280, 90, 71, 22));
        radioButton_sift = new QRadioButton(tab);
        radioButton_sift->setObjectName(QString::fromUtf8("radioButton_sift"));
        radioButton_sift->setGeometry(QRect(1220, 90, 61, 22));
        radioButton_sift->setChecked(true);
        comboBox2 = new QComboBox(tab);
        comboBox2->setObjectName(QString::fromUtf8("comboBox2"));
        comboBox2->setGeometry(QRect(1220, 40, 171, 27));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1150, 50, 67, 17));
        comboBox1 = new QComboBox(tab);
        comboBox1->setObjectName(QString::fromUtf8("comboBox1"));
        comboBox1->setGeometry(QRect(1220, 10, 171, 27));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 40, 91, 17));
        lineEdit_directorio = new QLineEdit(tab_2);
        lineEdit_directorio->setObjectName(QString::fromUtf8("lineEdit_directorio"));
        lineEdit_directorio->setGeometry(QRect(110, 30, 113, 27));
        pushButton_seleccionarDirectorio = new QPushButton(tab_2);
        pushButton_seleccionarDirectorio->setObjectName(QString::fromUtf8("pushButton_seleccionarDirectorio"));
        pushButton_seleccionarDirectorio->setGeometry(QRect(240, 30, 97, 27));
        tableView = new QTableView(tab_2);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(730, 20, 111, 521));
        pushButton_procesar = new QPushButton(tab_2);
        pushButton_procesar->setObjectName(QString::fromUtf8("pushButton_procesar"));
        pushButton_procesar->setGeometry(QRect(350, 30, 97, 27));
        gridLayoutWidget_2 = new QWidget(tab_2);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 90, 661, 491));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget->addTab(tab_2, QString());

        retranslateUi(Guetta);

        tabWidget->setCurrentIndex(1);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Guetta);
    } // setupUi

    void retranslateUi(QDialog *Guetta)
    {
        Guetta->setWindowTitle(QApplication::translate("Guetta", "Guetta", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Guetta", "M\303\241ximo n\302\272 keypoints", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Guetta", "M\303\241ximo n\302\272 keypoints alienamiento", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Guetta", "M\303\241x distancia emparejamiento", 0, QApplication::UnicodeUTF8));
        pushButton_cambiar->setText(QApplication::translate("Guetta", "Cambiar", 0, QApplication::UnicodeUTF8));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("Guetta", "Tab 1", 0, QApplication::UnicodeUTF8));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("Guetta", "Tab 2", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Guetta", "Cloud1: ", 0, QApplication::UnicodeUTF8));
        radioButton_narf->setText(QApplication::translate("Guetta", "NARF", 0, QApplication::UnicodeUTF8));
        checkBox_acumular->setText(QApplication::translate("Guetta", "Acumular", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Guetta", "Selecci\303\263n", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Guetta", "Distancia descriptor:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Guetta", "Distancia xyz:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Guetta", "KeyPoint2", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Guetta", "KeyPoint1", 0, QApplication::UnicodeUTF8));
        radioButton_surf->setText(QApplication::translate("Guetta", "SURF", 0, QApplication::UnicodeUTF8));
        radioButton_sift->setText(QApplication::translate("Guetta", "SIFT", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Guetta", "Cloud2:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Guetta", "Tab 1", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Guetta", "Directorio:", 0, QApplication::UnicodeUTF8));
        lineEdit_directorio->setText(QApplication::translate("Guetta", "prueba1", 0, QApplication::UnicodeUTF8));
        pushButton_seleccionarDirectorio->setText(QApplication::translate("Guetta", "Seleccionar", 0, QApplication::UnicodeUTF8));
        pushButton_procesar->setText(QApplication::translate("Guetta", "Procesar", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Guetta", "Tab 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Guetta: public Ui_Guetta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUETTA_H
