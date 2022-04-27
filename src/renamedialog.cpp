#include "renamedialog.h"
#include "ui_renamedialog.h"

renameDialog::renameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::renameDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setModal(true);

    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->okButton, SIGNAL(clicked(bool)), this, SLOT(rename()));
}

renameDialog::~renameDialog()
{
    delete ui;
}

void renameDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        rename();
    else if (event->key() == Qt::Key_Escape)
        this->close();

    event->accept();
}

void renameDialog::setPlaceholer(QString text, int item)
{
    ui->renameLineEdit->clear();
    ui->renameLineEdit->setPlaceholderText(text);
    ui->renameLineEdit->setFocus();
    m_itemToRename = item;
}

void renameDialog::updateTheme(styles_data_t *style)
{
    ui->cancelButton->setStyleSheet(style->backcolor);
    ui->okButton->setStyleSheet(style->backcolor);
    ui->renameLineEdit->setStyleSheet(style->color);
}

void renameDialog::rename()
{
    if (ui->renameLineEdit->text().isEmpty())
        return;

#if DEBUG
    qDebug() << "Rename to" << ui->renameLineEdit->text();
#endif

    emit renamed(ui->renameLineEdit->text(), m_itemToRename);
    this->close();
}
