#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab1314.h"

class lab1314 : public QMainWindow
{
    Q_OBJECT

public:
    lab1314(QWidget *parent = nullptr);
    ~lab1314();

private:
    Ui::lab1314Class ui;
};
