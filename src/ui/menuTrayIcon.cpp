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
MenuTrayIcon::MenuTrayIcon() :
    QMenu(){
    actExit = new QAction("退出");
    actMainWindow = new QAction("主界面");
    
    init();
    signalsProcess();
}
MenuTrayIcon::~MenuTrayIcon() {
    delete actExit;
    delete actMainWindow;
}
void MenuTrayIcon::init() {
    this->addAction(actMainWindow);
    this->addAction(actExit);
}
void MenuTrayIcon::signalsProcess() {
    connect(actExit, &QAction::triggered, this, &MenuTrayIcon::sigExit);
    connect(actMainWindow, &QAction::triggered, this, &MenuTrayIcon::sigShowMainWindow);
}
