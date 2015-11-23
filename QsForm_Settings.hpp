#ifndef CQS_SETTINGS_DIALOG_H
#define CQS_SETTINGS_DIALOG_H

#include <QDialog>

namespace Ui { class QsForm_Settings; }

class QsForm_Settings : public QDialog
{
    Q_OBJECT

public:
    explicit QsForm_Settings(QWidget* parent = 0);
    ~QsForm_Settings();


signals:

    void settings_changed_signal();

private slots:
    void on_btApply_clicked();

    void on_btCancel_clicked();

    void on_btOk_clicked();



private:
    Ui::QsForm_Settings* ui;

};

#endif // CQS_SETTINGS_DIALOG_H
