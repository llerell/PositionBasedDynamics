#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)       // passage en paramètre de la fenêtre parente (null pour la fenêtre racine)
    , ui(new Ui::MainWindow)    // création des widgets décrit dans fichier .ui
{
    ui->setupUi(this);          // initialisation des widgets

    draw_area = new DrawArea();

    reset_button = new QPushButton("Reset");
    random_colors = new QCheckBox("Random colors");
    active_collisions = new QCheckBox("Active health points");

    nb_milliseconds = 5;

    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget); // constructor’s parameter is the widget that will use the layout

    layout->addWidget(draw_area);
    layout->addWidget(reset_button);
    layout->addWidget(random_colors);
    layout->addWidget(active_collisions);

    QObject::connect(reset_button, &QPushButton::clicked, draw_area, &DrawArea::reset);
    QObject::connect(random_colors, &QCheckBox::checkStateChanged, draw_area, &DrawArea::randomColor);
    QObject::connect(active_collisions, &QCheckBox::checkStateChanged, draw_area, &DrawArea::activeCollisions);

    // Animate: Timer
    auto timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, draw_area, &DrawArea::animate);
    timer->start(nb_milliseconds);
}

MainWindow::~MainWindow()
{
    delete ui;  // nécessaire car par défaut Qt n’utilise pas de unique_ptr, il est donc possible de simplifier légèrement le code généré

}
