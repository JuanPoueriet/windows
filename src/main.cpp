#include <QApplication>
#include "WindowManager.h"
#include "AppWindow.h"
#include "TabHost.h"
#include "TabSession.h"
#include "TabView.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    WindowManager& wm = WindowManager::instance();
    AppWindow* win = wm.createWindow();

    for (int i = 1; i <= 3; ++i) {
        TabSession* session = new TabSession(QString("Tab %1").arg(i), win);
        TabView* view = new TabView();
        view->setContent(QString("This is the content of tab %1.\nYou can type here and it will be preserved when you move the tab between windows.").arg(i));
        session->setView(view);
        win->tabHost()->addTab(session);
    }

    return a.exec();
}
