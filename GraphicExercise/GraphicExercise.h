#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GraphicExercise.h"

class GraphicExercise : public QMainWindow
{
    Q_OBJECT

public:
    GraphicExercise(QWidget *parent = nullptr);
    ~GraphicExercise();

private:
    Ui::GraphicExerciseClass ui;
};
