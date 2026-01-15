#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include "drawarea.h"

#include <QMainWindow>
#include <qcheckbox.h>

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
    QPushButton *reset_button;
    QCheckBox *random_colors;
    QPushButton *random_color;
    QLabel *label;
    DrawArea *draw_area;
    int nb_milliseconds;
};
#endif // MAINWINDOW_H
