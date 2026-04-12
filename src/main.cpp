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

    TabSession* session1 = new TabSession("Resumen ejecutivo", win);
    session1->setModuleType(TabSession::Dashboard);
    session1->setView(new TabView());
    win->tabHost()->addTab(session1);

    TabSession* session2 = new TabSession("Facturación", win);
    session2->setModuleType(TabSession::Invoicing);
    session2->setView(new TabView());
    win->tabHost()->addTab(session2);

    TabSession* session3 = new TabSession("Inventario", win);
    session3->setModuleType(TabSession::Inventory);
    session3->setView(new TabView());
    win->tabHost()->addTab(session3);

    return a.exec();
}
