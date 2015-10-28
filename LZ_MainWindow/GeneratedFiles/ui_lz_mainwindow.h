/********************************************************************************
** Form generated from reading UI file 'lz_mainwindow.ui'
**
** Created: Mon Oct 26 19:05:47 2015
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LZ_MAINWINDOW_H
#define UI_LZ_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LZ_MainWindowClass
{
public:
    QAction *actionAbout;
    QAction *actionExit;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *modeEdit;
    QLabel *hardwareEdit;
    QLabel *cameraLabel;
    QLabel *cameraStatusLabel;
    QPushButton *initCameraButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTextEdit *informationEdit;
    QFrame *line;
    QFrame *line_2;
    QGroupBox *groupBox_2;
    QPushButton *setInHoleButton;
    QLabel *inOutHoleLabel;
    QPushButton *setOutHoleButton;
    QLabel *label_5;
    QLabel *modeLabel;
    QGroupBox *imagesShowBox;
    QLabel *leftImgLabel;
    QLabel *rightImgLabel;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *rightDistanceEdit;
    QLineEdit *lefttDistanceEdit;
    QLabel *label_2;
    QLineEdit *leftTimeEdit;
    QMenuBar *menuBar;
    QMenu *menuMenu;

    void setupUi(QMainWindow *LZ_MainWindowClass)
    {
        if (LZ_MainWindowClass->objectName().isEmpty())
            LZ_MainWindowClass->setObjectName(QString::fromUtf8("LZ_MainWindowClass"));
        LZ_MainWindowClass->resize(982, 677);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resource/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        LZ_MainWindowClass->setWindowIcon(icon);
        LZ_MainWindowClass->setAutoFillBackground(true);
        LZ_MainWindowClass->setDocumentMode(false);
        actionAbout = new QAction(LZ_MainWindowClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resource/help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon1);
        actionExit = new QAction(LZ_MainWindowClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resource/cross.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon2);
        centralWidget = new QWidget(LZ_MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 570, 491, 51));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        modeEdit = new QLabel(centralWidget);
        modeEdit->setObjectName(QString::fromUtf8("modeEdit"));
        modeEdit->setGeometry(QRect(330, 30, 91, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        modeEdit->setFont(font);
        modeEdit->setMouseTracking(false);
        modeEdit->setIndent(0);
        hardwareEdit = new QLabel(centralWidget);
        hardwareEdit->setObjectName(QString::fromUtf8("hardwareEdit"));
        hardwareEdit->setGeometry(QRect(90, 0, 51, 51));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        hardwareEdit->setFont(font1);
        hardwareEdit->setPixmap(QPixmap(QString::fromUtf8(":/resource/cross.png")));
        hardwareEdit->setScaledContents(true);
        cameraLabel = new QLabel(centralWidget);
        cameraLabel->setObjectName(QString::fromUtf8("cameraLabel"));
        cameraLabel->setGeometry(QRect(380, -50, 81, 61));
        cameraStatusLabel = new QLabel(centralWidget);
        cameraStatusLabel->setObjectName(QString::fromUtf8("cameraStatusLabel"));
        cameraStatusLabel->setGeometry(QRect(180, 0, 50, 50));
        cameraStatusLabel->setFont(font1);
        cameraStatusLabel->setPixmap(QPixmap(QString::fromUtf8(":/resource/collectstatus1_2.png")));
        cameraStatusLabel->setScaledContents(true);
        initCameraButton = new QPushButton(centralWidget);
        initCameraButton->setObjectName(QString::fromUtf8("initCameraButton"));
        initCameraButton->setGeometry(QRect(160, 60, 101, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        initCameraButton->setFont(font2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resource/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        initCameraButton->setIcon(icon3);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 240, 521, 361));
        tabWidget->setFont(font2);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        informationEdit = new QTextEdit(tab);
        informationEdit->setObjectName(QString::fromUtf8("informationEdit"));
        informationEdit->setGeometry(QRect(10, 10, 501, 301));
        informationEdit->setAutoFillBackground(false);
        informationEdit->setTabChangesFocus(true);
        informationEdit->setReadOnly(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resource/info (2).png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab, icon4, QString());
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 90, 521, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 200, 521, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(70, 110, 411, 81));
        setInHoleButton = new QPushButton(groupBox_2);
        setInHoleButton->setObjectName(QString::fromUtf8("setInHoleButton"));
        setInHoleButton->setGeometry(QRect(64, 23, 71, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\215\216\346\226\207\347\273\206\351\273\221"));
        setInHoleButton->setFont(font3);
        setInHoleButton->setCursor(QCursor(Qt::ArrowCursor));
        setInHoleButton->setAutoFillBackground(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resource/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        setInHoleButton->setIcon(icon5);
        setInHoleButton->setAutoDefault(false);
        setInHoleButton->setDefault(true);
        setInHoleButton->setFlat(false);
        inOutHoleLabel = new QLabel(groupBox_2);
        inOutHoleLabel->setObjectName(QString::fromUtf8("inOutHoleLabel"));
        inOutHoleLabel->setGeometry(QRect(180, 20, 60, 60));
        QFont font4;
        font4.setItalic(false);
        inOutHoleLabel->setFont(font4);
        inOutHoleLabel->setPixmap(QPixmap(QString::fromUtf8(":/resource/lightouthole.png")));
        inOutHoleLabel->setScaledContents(true);
        setOutHoleButton = new QPushButton(groupBox_2);
        setOutHoleButton->setObjectName(QString::fromUtf8("setOutHoleButton"));
        setOutHoleButton->setGeometry(QRect(290, 23, 75, 31));
        setOutHoleButton->setFont(font3);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resource/minus.png"), QSize(), QIcon::Normal, QIcon::Off);
        setOutHoleButton->setIcon(icon6);
        setOutHoleButton->setDefault(true);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(80, 60, 71, 20));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font5.setPointSize(11);
        font5.setBold(false);
        font5.setWeight(50);
        label_5->setFont(font5);
        modeLabel = new QLabel(centralWidget);
        modeLabel->setObjectName(QString::fromUtf8("modeLabel"));
        modeLabel->setGeometry(QRect(10, 10, 71, 31));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font6.setPointSize(11);
        font6.setUnderline(false);
        modeLabel->setFont(font6);
        imagesShowBox = new QGroupBox(centralWidget);
        imagesShowBox->setObjectName(QString::fromUtf8("imagesShowBox"));
        imagesShowBox->setEnabled(true);
        imagesShowBox->setGeometry(QRect(570, 40, 391, 561));
        leftImgLabel = new QLabel(imagesShowBox);
        leftImgLabel->setObjectName(QString::fromUtf8("leftImgLabel"));
        leftImgLabel->setGeometry(QRect(40, 40, 311, 151));
        leftImgLabel->setPixmap(QPixmap(QString::fromUtf8(":/resource/pic.bmp")));
        leftImgLabel->setScaledContents(true);
        rightImgLabel = new QLabel(imagesShowBox);
        rightImgLabel->setObjectName(QString::fromUtf8("rightImgLabel"));
        rightImgLabel->setGeometry(QRect(40, 270, 321, 151));
        rightImgLabel->setPixmap(QPixmap(QString::fromUtf8(":/resource/pic.bmp")));
        rightImgLabel->setScaledContents(true);
        label_3 = new QLabel(imagesShowBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 440, 54, 12));
        label = new QLabel(imagesShowBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 210, 54, 12));
        rightDistanceEdit = new QLineEdit(imagesShowBox);
        rightDistanceEdit->setObjectName(QString::fromUtf8("rightDistanceEdit"));
        rightDistanceEdit->setGeometry(QRect(100, 440, 91, 21));
        rightDistanceEdit->setReadOnly(true);
        lefttDistanceEdit = new QLineEdit(imagesShowBox);
        lefttDistanceEdit->setObjectName(QString::fromUtf8("lefttDistanceEdit"));
        lefttDistanceEdit->setEnabled(true);
        lefttDistanceEdit->setGeometry(QRect(100, 210, 91, 21));
        lefttDistanceEdit->setMouseTracking(false);
        lefttDistanceEdit->setReadOnly(true);
        label_2 = new QLabel(imagesShowBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 480, 54, 12));
        leftTimeEdit = new QLineEdit(imagesShowBox);
        leftTimeEdit->setObjectName(QString::fromUtf8("leftTimeEdit"));
        leftTimeEdit->setGeometry(QRect(130, 480, 101, 21));
        leftTimeEdit->setReadOnly(true);
        LZ_MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LZ_MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 982, 23));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        LZ_MainWindowClass->setMenuBar(menuBar);
        QWidget::setTabOrder(setInHoleButton, setOutHoleButton);
        QWidget::setTabOrder(setOutHoleButton, initCameraButton);
        QWidget::setTabOrder(initCameraButton, informationEdit);
        QWidget::setTabOrder(informationEdit, tabWidget);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionAbout);
        menuMenu->addAction(actionExit);

        retranslateUi(LZ_MainWindowClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LZ_MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *LZ_MainWindowClass)
    {
        LZ_MainWindowClass->setWindowTitle(QApplication::translate("LZ_MainWindowClass", "\345\205\260\345\267\236\351\232\247\351\201\223\350\277\233\345\207\272\346\264\236\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("LZ_MainWindowClass", "\345\205\263\344\272\216(&A)", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("LZ_MainWindowClass", "\351\200\200\345\207\272(&E)", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        modeEdit->setText(QApplication::translate("LZ_MainWindowClass", "\346\211\213\345\212\250\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        hardwareEdit->setText(QString());
        cameraLabel->setText(QApplication::translate("LZ_MainWindowClass", "\347\233\270\346\234\272\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        cameraStatusLabel->setText(QString());
        initCameraButton->setText(QApplication::translate("LZ_MainWindowClass", "\345\210\235\345\247\213\345\214\226\347\233\270\346\234\272", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("LZ_MainWindowClass", "\347\212\266\346\200\201\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabToolTip(tabWidget->indexOf(tab), QApplication::translate("LZ_MainWindowClass", "<html><head/><body><p>\346\230\276\347\244\272\345\267\245\344\275\234\347\212\266\346\200\201\345\222\214\346\227\245\345\277\227</p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        setInHoleButton->setText(QApplication::translate("LZ_MainWindowClass", "\350\277\233\346\264\236", 0, QApplication::UnicodeUTF8));
        inOutHoleLabel->setText(QString());
        setOutHoleButton->setText(QApplication::translate("LZ_MainWindowClass", "\345\207\272\346\264\236", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("LZ_MainWindowClass", "USB \346\250\241\345\235\227", 0, QApplication::UnicodeUTF8));
        modeLabel->setText(QApplication::translate("LZ_MainWindowClass", "\345\267\245\344\275\234\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        imagesShowBox->setTitle(QApplication::translate("LZ_MainWindowClass", "\345\233\276\345\203\217\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        leftImgLabel->setText(QString());
        rightImgLabel->setText(QString());
        label_3->setText(QApplication::translate("LZ_MainWindowClass", "\350\267\235\347\246\273\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LZ_MainWindowClass", "\350\267\235\347\246\273\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("LZ_MainWindowClass", "\347\224\250\346\227\266\357\274\232", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("LZ_MainWindowClass", "\350\217\234\345\215\225(&M)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LZ_MainWindowClass: public Ui_LZ_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LZ_MAINWINDOW_H
