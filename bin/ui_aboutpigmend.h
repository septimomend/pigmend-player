/********************************************************************************
** Form generated from reading UI file 'aboutpigmend.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTPIGMEND_H
#define UI_ABOUTPIGMEND_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AboutPigmend
{
public:
    QLabel *player_name;
    QLabel *author_label;
    QPushButton *okButton;
    QLabel *pigmend_icon;
    QLabel *description;
    QLabel *version;

    void setupUi(QDialog *AboutPigmend)
    {
        if (AboutPigmend->objectName().isEmpty())
            AboutPigmend->setObjectName(QString::fromUtf8("AboutPigmend"));
        AboutPigmend->resize(441, 353);
        AboutPigmend->setFocusPolicy(Qt::StrongFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/pigmend.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AboutPigmend->setWindowIcon(icon);
        player_name = new QLabel(AboutPigmend);
        player_name->setObjectName(QString::fromUtf8("player_name"));
        player_name->setGeometry(QRect(140, 20, 281, 51));
        QFont font;
        font.setPointSize(30);
        player_name->setFont(font);
        author_label = new QLabel(AboutPigmend);
        author_label->setObjectName(QString::fromUtf8("author_label"));
        author_label->setGeometry(QRect(140, 80, 281, 21));
        okButton = new QPushButton(AboutPigmend);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(370, 310, 51, 29));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(okButton->sizePolicy().hasHeightForWidth());
        okButton->setSizePolicy(sizePolicy);
        okButton->setStyleSheet(QString::fromUtf8("color: rgb(243, 243, 243);"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/buttons/img/buttons/check-mark-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon1);
        okButton->setAutoDefault(false);
        okButton->setFlat(true);
        pigmend_icon = new QLabel(AboutPigmend);
        pigmend_icon->setObjectName(QString::fromUtf8("pigmend_icon"));
        pigmend_icon->setGeometry(QRect(20, 20, 101, 101));
        pigmend_icon->setPixmap(QPixmap(QString::fromUtf8(":/custom/img/custom/pigmendback.png")));
        pigmend_icon->setScaledContents(true);
        description = new QLabel(AboutPigmend);
        description->setObjectName(QString::fromUtf8("description"));
        description->setGeometry(QRect(30, 140, 381, 161));
        version = new QLabel(AboutPigmend);
        version->setObjectName(QString::fromUtf8("version"));
        version->setGeometry(QRect(140, 100, 281, 21));

        retranslateUi(AboutPigmend);

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(AboutPigmend);
    } // setupUi

    void retranslateUi(QDialog *AboutPigmend)
    {
        AboutPigmend->setWindowTitle(QApplication::translate("AboutPigmend", "About Pigmend Player", nullptr));
        player_name->setText(QString());
        author_label->setText(QString());
#ifndef QT_NO_TOOLTIP
        okButton->setToolTip(QApplication::translate("AboutPigmend", "Search data [Enter]", nullptr));
#endif // QT_NO_TOOLTIP
        okButton->setText(QApplication::translate("AboutPigmend", "Ok", nullptr));
        pigmend_icon->setText(QString());
        description->setText(QString());
        version->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AboutPigmend: public Ui_AboutPigmend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTPIGMEND_H
