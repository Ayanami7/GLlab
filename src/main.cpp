#include "common.h"
#include "widget.h"

int main()
{
    MainWindow *widget = new MainWindow();
    widget->init();
    widget->show();
    widget->destroy();


    return 0;
}