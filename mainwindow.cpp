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

    start_button = new QPushButton("Start");
    label = new QLabel("Currently stopped...");
    draw_area = new DrawArea();

    nb_milliseconds = 50;

    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget); // constructor’s parameter is the widget that will use the layout

    layout->addWidget(start_button); // ownership of ptr is transferred
    layout->addWidget(label);  // ownership of ptr is transferred
    layout->addWidget(draw_area);


    QObject::connect(this->start_button, &QPushButton::clicked, this, &MainWindow::sayHello);

    // Calls the paintEvent method in drawarea -> Draws an ellipse
    //draw_area->update();
    // How to stop the ellipse to be drawn when launching the project?

    // Animate: Timer
    auto timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, draw_area, &DrawArea::animate);
    timer->start(nb_milliseconds);
}

MainWindow::~MainWindow()
{
    delete ui;  // nécessaire car par défaut Qt n’utilise pas de unique_ptr, il est donc possible de simplifier légèrement le code généré

}


void MainWindow::sayHello(bool clicked)
{
    this->label->setText("Hello World!");
}
