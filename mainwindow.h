#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "drawarea.h"

#include <QMainWindow>
#include <qcheckbox.h>
#include <qspinbox.h>

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


private:
    Ui::MainWindow *ui; // Classe générée automatiquement à partir d’un fichier .ui décrivant le contenu de l’interface graphique

    /// scene
    DrawArea *draw_area;
    /// button to reset the scene
    QPushButton *reset_button;
    /// check box to activate or desactivate random colors for the particles
    QCheckBox *random_colors;
    /// check box to activate or desactivate health points of the particles
    QCheckBox *active_collisions;
    /// choose how many health points the particles have
    QLabel *label;
    QSpinBox *health_number;

    /// time between two frames
    const int nb_milliseconds = 10;
};
#endif // MAINWINDOW_H
