#include "common.h"
#include "widget.h"

int main()
{
    Window *widget = new Window();
    widget->init();
    widget->show();
    widget->destroy();

    return 0;
}