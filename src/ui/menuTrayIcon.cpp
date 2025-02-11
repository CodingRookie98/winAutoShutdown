/**
 ******************************************************************************
 * @file           : menuTrayIcon.cpp
 * @author         : hui
 * @brief          : None
 * @attention      : None
 * @date           : 2024/2/22
 ******************************************************************************
 */

#include "menuTrayIcon.h"

#include <qcoreevent.h>
MenuTrayIcon::MenuTrayIcon() :
    QMenu() {
    actExit       = new QAction(tr("退出"));
    actMainWindow = new QAction(tr("主界面"));

    init();
    signalsProcess();
}

MenuTrayIcon::~MenuTrayIcon() {
    delete actExit;
    delete actMainWindow;
}

bool MenuTrayIcon::event(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {

    }
    return QMenu::event(event);
}

void MenuTrayIcon::init() {
    this->addAction(actMainWindow);
    this->addAction(actExit);
}

void MenuTrayIcon::signalsProcess() {
    connect(actExit, &QAction::triggered, this, &MenuTrayIcon::sigExit);
    connect(actMainWindow, &QAction::triggered, this, &MenuTrayIcon::sigShowMainWindow);
}
