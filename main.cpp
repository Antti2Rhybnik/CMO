#include <QApplication>


#include "QsForm_Main.hpp"
#include "QsForm_Settings.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QsForm_Main mw;
    QsForm_Settings sw;

    mw.set_win = &sw;

    mw.show();
    sw.hide();

    return a.exec();
}
