#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H

#include <QDialog>
#include "constants.h"

namespace Ui {
class renameDialog;
}

class renameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit renameDialog(QWidget *parent = nullptr);
    ~renameDialog();

    void setPlaceholer(QString text, int item);
    void updateTheme(styles_data_t *style);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::renameDialog *ui;
    int m_itemToRename;

signals:
    void renamed(QString text, int item);

private slots:
    void rename();
};

#endif // RENAMEDIALOG_H
