#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "drawarea.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT    // macro autorisant slot et signal

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override; // On peut rajouter override, car le destructeur est virtuel dans la classe parente

public slots:
    void sayHello(bool clicked);

private:
    Ui::MainWindow *ui;
    // Ui::MainWindow : classe généré automatiquement à partir d’un fichier .ui décrivant le contenu de l’interface graphique
    QPushButton *start_button;
    QLabel *label;
    DrawArea *draw_area;
    int nb_milliseconds;
};
#endif // MAINWINDOW_H
