#ifndef CQS_MAIN_DIALOG_H
#define CQS_MAIN_DIALOG_H

#include <QDialog>

class QsForm_Settings; // just declaration
class QsThreadCore;
class QsRes;

namespace Ui { class QsForm_Main; }

class QsForm_Main : public QDialog
{
    Q_OBJECT

public:
    explicit QsForm_Main(QWidget* parent = 0);
    ~QsForm_Main();

private slots:
    void on_btStart_clicked();

    void on_cbByStep_stateChanged(int);

    void on_btBreak_clicked();

    void on_btSettings_clicked();

    void clear_tables();

    void output_res_auto();
    void output_res_step();

    void auto_start();
    void byStep_start();

    void on_btNext_clicked();

private:
    Ui::QsForm_Main* ui;
    QsThreadCore* core;
    QsRes* res;

public:

    QsForm_Settings* set_win;

};

#endif // CQS_MAIN_DIALOG_H
