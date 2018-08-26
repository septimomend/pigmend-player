/********************************************************************************
** Form generated from reading UI file 'searchdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDIALOG_H
#define UI_SEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SearchDialog
{
public:
    QLineEdit *searchLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QFrame *frame;
    QLabel *noMatchesLabel;

    void setupUi(QDialog *SearchDialog)
    {
        if (SearchDialog->objectName().isEmpty())
            SearchDialog->setObjectName(QStringLiteral("SearchDialog"));
        SearchDialog->setWindowModality(Qt::NonModal);
        SearchDialog->resize(461, 121);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SearchDialog->sizePolicy().hasHeightForWidth());
        SearchDialog->setSizePolicy(sizePolicy);
        SearchDialog->setStyleSheet(QStringLiteral("background-color: rgb(53, 53, 53);"));
        SearchDialog->setModal(false);
        searchLineEdit = new QLineEdit(SearchDialog);
        searchLineEdit->setObjectName(QStringLiteral("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(20, 30, 421, 22));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        searchLineEdit->setFont(font);
        searchLineEdit->setStyleSheet(QStringLiteral(""));
        searchLineEdit->setInputMethodHints(Qt::ImhHiddenText);
        searchLineEdit->setFrame(true);
        searchLineEdit->setEchoMode(QLineEdit::Normal);
        okButton = new QPushButton(SearchDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(350, 70, 33, 29));
        sizePolicy.setHeightForWidth(okButton->sizePolicy().hasHeightForWidth());
        okButton->setSizePolicy(sizePolicy);
        okButton->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/img/buttons/check-mark-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon);
        okButton->setAutoDefault(false);
        okButton->setFlat(true);
        cancelButton = new QPushButton(SearchDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(400, 70, 33, 29));
        sizePolicy.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy);
        cancelButton->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/img/buttons/x-mark-16.ico"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon1);
        cancelButton->setAutoDefault(false);
        cancelButton->setFlat(true);
        frame = new QFrame(SearchDialog);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setEnabled(false);
        frame->setGeometry(QRect(0, 0, 461, 121));
        frame->setStyleSheet(QStringLiteral(""));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        noMatchesLabel = new QLabel(frame);
        noMatchesLabel->setObjectName(QStringLiteral("noMatchesLabel"));
        noMatchesLabel->setEnabled(false);
        noMatchesLabel->setGeometry(QRect(20, 70, 311, 16));
        QFont font1;
        font1.setPointSize(10);
        noMatchesLabel->setFont(font1);
        noMatchesLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        noMatchesLabel->setTextFormat(Qt::AutoText);
        frame->raise();
        searchLineEdit->raise();
        okButton->raise();
        cancelButton->raise();

        retranslateUi(SearchDialog);

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(SearchDialog);
    } // setupUi

    void retranslateUi(QDialog *SearchDialog)
    {
        SearchDialog->setWindowTitle(QApplication::translate("SearchDialog", "Searching...", nullptr));
        searchLineEdit->setInputMask(QString());
        searchLineEdit->setText(QString());
#ifndef QT_NO_TOOLTIP
        okButton->setToolTip(QApplication::translate("SearchDialog", "Search data [Enter]", nullptr));
#endif // QT_NO_TOOLTIP
        okButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        cancelButton->setToolTip(QApplication::translate("SearchDialog", "Cancel [Esc]", nullptr));
#endif // QT_NO_TOOLTIP
        cancelButton->setText(QString());
        noMatchesLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SearchDialog: public Ui_SearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDIALOG_H
