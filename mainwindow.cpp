#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QScrollArea>

MainWindow::MainWindow(int imageId, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      imageId(imageId)
{
    ui->setupUi(this);
    //QMainWindow::showFullScreen();
//    ui->penSizeButton->setDefaultAction(ui->actionPen_size);
    ui->finishButton->setDefaultAction(ui->actionFinish_2);
    ui->resetToAutoButton->setDefaultAction(ui->actionReset_to_the_Auto_Generated_Mask);
    ui->dilationButton->setDefaultAction(ui->actionDilation);
    ui->erosionButton->setDefaultAction(ui->actionErosion);
    ui->undoButton->setDefaultAction(ui->actionUndo_Ctrl_Z);

    this->setWindowTitle("Mask Generator - " + QString::number(imageId));

    ui->actionEraser->setShortcut(Qt::Key_S);
    ui->actionCircle->setShortcut(Qt::Key_D);
    ui->actionRectangle->setShortcut(Qt::Key_F);
    ui->actionTriangle->setShortcut(Qt::Key_G);
    ui->actionFill_with_coor->setShortcut(Qt::Key_H);
    ui->actionShow_Original_Image->setShortcut(Qt::Key_Space);
    ui->actionDilation->setShortcut(Qt::Key_W);
    ui->actionErosion->setShortcut(Qt::Key_E);
    ui->actionReset_to_the_Auto_Generated_Mask->setShortcut(Qt::Key_R);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ui->drawpanel;
}

void MainWindow::on_actionFinish_2_triggered(){
    QImage saveDrawing = ui->drawpanel->getImage();

    saveDrawing.save("/home/mehmet/Desktop/paint-qt/modified_masks/camera_"+QString::number(imageId)+"_102.png");

    this->close();
    if(imageId < 4){
        MainWindow* mainWin = new MainWindow(imageId+1);
        mainWin->show();
    }
}

void MainWindow::on_actionReset_to_the_Auto_Generated_Mask_triggered(){
    ui->showOriginalButton->setChecked(false);
    ui->actionShow_Original_Image->setChecked(false);
    ui->drawpanel->reset();
}

void MainWindow::on_actionDilation_triggered(){
    ui->drawpanel->dilation();

}
void MainWindow::on_actionErosion_triggered(){
    ui->drawpanel->erosion();

}

void MainWindow::on_actionUndo_Ctrl_Z_triggered(){
    ui->drawpanel->undo();
}


int MainWindow::openDialog()
{
    QMessageBox dialog(QMessageBox::Question, tr("Mask Generator"), tr("Do you want to save changes?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this);
    dialog.setButtonText(QMessageBox::Yes, tr("Yes"));
    dialog.setButtonText(QMessageBox::No, tr("No"));
    dialog.setButtonText(QMessageBox::Cancel, tr("Cancel"));
    dialog.setDefaultButton(QMessageBox::Yes);

    return dialog.exec();
}

void MainWindow::on_actionSave_triggered()
{
    QImage saveDrawing = ui->drawpanel->getImage();
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp)");
    saveDrawing.save(filePath);
}

void MainWindow::on_actionPen_size_triggered()
{
//    bool correct = false;

//    int size = QInputDialog::getInt(this, "Set pen size", "Pen size", 1, 1, 50, 1, &correct);

//    if (correct)
//    {
//        ui->drawpanel->setBrushWidth(size);
//    }

    ui->drawpanel->setBrushWidth(ui->penSizeButton_2->value());

}

void MainWindow::on_actionEraser_triggered()
{
    ui->eraserButton->setChecked(ui->actionEraser->isChecked());

    if(ui->actionEraser->isChecked() == true)
    {
        ui->drawpanel->setFillColor(Qt::white);

       ui->drawpanel->setPrevColor(ui->drawpanel->getColor());
       ui->drawpanel->setColor(Qt::white);
       ui->drawpanel->setIsLine(true);
       ui->drawpanel->setIsCircle(false);
       ui->drawpanel->setIsTriangle(false);
       ui->drawpanel->setIsRectangle(false);
       ui->rectangleButton->setChecked(false);
       ui->triangleButton->setChecked(false);
       ui->circleButton->setChecked(false);
       ui->actionRectangle->setChecked(false);
       ui->actionTriangle->setChecked(false);
       ui->actionCircle->setChecked(false);
    }
    if(ui->actionEraser->isChecked() == false)
    {
        ui->drawpanel->setFillColor(Qt::black);

        ui->drawpanel->setColor(ui->drawpanel->getPrevColor());
    }
}

void MainWindow::on_actionRectangle_triggered()
{
    ui->rectangleButton->setChecked(ui->actionRectangle->isChecked());

    if(ui->actionRectangle->isChecked() == true)
    {

        ui->circleButton->setChecked(false);
        ui->triangleButton->setChecked(false);
        ui->actionCircle->setChecked(false);
        ui->actionTriangle->setChecked(false);
        ui->drawpanel->setIsRectangle(true);
        ui->drawpanel->setIsCircle(false);
        ui->drawpanel->setIsTriangle(false);
        ui->drawpanel->setIsLine(false);
    }
    if(ui->actionRectangle->isChecked() == false)
    {

        ui->drawpanel->setIsRectangle(false);
        ui->drawpanel->setIsCircle(false);
        ui->drawpanel->setIsTriangle(false);
        ui->drawpanel->setIsLine(true);
    }
}


void MainWindow::on_actionShow_Original_Image_triggered()
{
    ui->drawpanel->showOriginal(ui->actionShow_Original_Image->isChecked());
    ui->showOriginalButton->setChecked(ui->actionShow_Original_Image->isChecked());
}

void MainWindow::on_actionCircle_triggered()
{
    ui->circleButton->setChecked(ui->actionCircle->isChecked() );

    if(ui->actionCircle->isChecked() == true)
    {

        ui->rectangleButton->setChecked(false);
        ui->triangleButton->setChecked(false);
        ui->actionRectangle->setChecked(false);
        ui->actionTriangle->setChecked(false);
        ui->drawpanel->setIsCircle(true);
        ui->drawpanel->setIsRectangle(false);
        ui->drawpanel->setIsTriangle(false);
        ui->drawpanel->setIsLine(false);
    }
    if(ui->actionCircle->isChecked() == false)
    {

        ui->drawpanel->setIsRectangle(false);
        ui->drawpanel->setIsCircle(false);
        ui->drawpanel->setIsTriangle(false);
        ui->drawpanel->setIsLine(true);
    }
}

void MainWindow::on_actionTriangle_triggered()
{
    ui->triangleButton->setChecked(ui->actionTriangle->isChecked());

    if(ui->actionTriangle->isChecked() == true)
    {

        ui->rectangleButton->setChecked(false);
        ui->circleButton->setChecked(false);
        ui->actionRectangle->setChecked(false);
        ui->actionCircle->setChecked(false);
        ui->drawpanel->setIsTriangle(true);
        ui->drawpanel->setIsCircle(false);
        ui->drawpanel->setIsRectangle(false);
        ui->drawpanel->setIsLine(false);
    }
    if(ui->actionTriangle->isChecked() == false)
    {

        ui->drawpanel->setIsRectangle(false);
        ui->drawpanel->setIsCircle(false);
        ui->drawpanel->setIsTriangle(false);
        ui->drawpanel->setIsLine(true);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    int dialog = openDialog();
    if(dialog == QMessageBox::Yes)
    {
       on_actionSave_triggered();
       ui->drawpanel->openImage();
    }
    else if(dialog == QMessageBox::No)
    {
        ui->drawpanel->openImage();
    }
    else if(dialog == QMessageBox::Cancel)
    {
        return;
    }
}

void MainWindow::on_actionNew_triggered()
{
    int dialog = openDialog();
    if(dialog == QMessageBox::Yes)
    {
       on_actionSave_triggered();
       ui->drawpanel->start();
       update();
    }
    else if(dialog == QMessageBox::No)
    {
        ui->drawpanel->start();
        update();
    }
    else if(dialog == QMessageBox::Cancel)
    {
        return;
    }
}

void MainWindow::on_actionClose_triggered()
{
    int dialog = openDialog();
    if(dialog == QMessageBox::Yes)
    {
       on_actionSave_triggered();
       QApplication::quit();
    }
    else if(dialog == QMessageBox::No)
    {
        QApplication::quit();
    }
    else if(dialog == QMessageBox::Cancel)
    {
        return;
    }
}

void MainWindow::on_actionFill_with_coor_triggered()
{
    ui->FillWithColorButton->setChecked(ui->actionFill_with_coor->isChecked());

    if(ui->actionFill_with_coor->isChecked() == true)
    {

        ui->drawpanel->setIsFilling(true);
    }
    else if(ui->actionFill_with_coor->isChecked() == false)
    {

        ui->drawpanel->setIsFilling(false);
    }
}

//void MainWindow::on_actionCut_triggered()
//{
//    ui->drawpanel->setCopyDrawing(ui->drawpanel->getImage());
//    ui->drawpanel->clear();
//    ui->actionPaste->setEnabled(true);
//}

//void MainWindow::on_actionPaste_triggered()
//{
//    ui->drawpanel->setImage(ui->drawpanel->getCopyDrawing());
//    QPainter painter;
//    painter.drawImage(0,0, ui->drawpanel->getImage());
//}

