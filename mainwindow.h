#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <drawpanel.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int imageId, QWidget *parent = nullptr);
    ~MainWindow();

    int openDialog();


private:
    Ui::MainWindow *ui;
    DrawPanel *drawpanel;
    int currentZoom;

    int imageId;

private slots:
    void on_actionPen_color_triggered(){};
    void on_actionSave_triggered();
    void on_actionPen_size_triggered();
    void on_actionEraser_triggered();

    void on_actionRectangle_triggered();
    void on_actionCircle_triggered();
    void on_actionTriangle_triggered();
    void on_actionOpen_triggered();
    void on_actionNew_triggered();
    void on_actionClose_triggered();
    void on_actionShow_Original_Image_triggered();
    void on_actionResize_triggered(){};
    void on_actionFill_with_coor_triggered();
    void on_actionFill_color_triggered(){};
    void on_actionCut_triggered(){};
    void on_actionPaste_triggered(){};
    void on_actionAbout_PaintQT_triggered(){};
    void on_actionZoom_2_triggered(){};
    void on_actionFinish_2_triggered();
    void on_actionReset_to_the_Auto_Generated_Mask_triggered();
    void on_actionDilation_triggered();
    void on_actionErosion_triggered();
    void on_actionUndo_Ctrl_Z_triggered();

};
#endif // MAINWINDOW_H
