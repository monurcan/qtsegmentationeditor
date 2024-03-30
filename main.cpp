#include "mainwindow.h"
#include "wait.h"

#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include <QDir>
#include <QMutex>

class MaskThread : public QThread
{
protected:
void run(void)
{
    QDir mask_path("/home/mehmet/Desktop/paint-qt/masks");
    bool areAllMasksExist = true;

    if (!mask_path.exists()){
        mask_path.mkpath(".");
        areAllMasksExist = false;
    }else {
        for(int i = 1; i < 5; i++){
            if(!mask_path.exists("camera_"+QString::number(i)+"_102.png")){
                areAllMasksExist = false;
                break;
            }
        }
    }

    if(areAllMasksExist) return;

    // mask inference system()...runx..
    // python -m runx.runx scripts/onurcan.yml -i
    // sftp://192.168.1.100/mnt/trains/users/onurcan/treebushsegmentation. scriptte result_dir değişecek
    QThread::msleep(3000); //for testing

}

};

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QPixmap pixmap("/home/mehmet/Desktop/paint-qt/splash.png");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.setEnabled(false); //Prevent user from closing the splash
    splash.showMessage("Bekleyin, maske tahmini oluşturuluyor...",Qt::AlignCenter, QColor(255,255,255));
    splash.show();

    app.processEvents(); //Make sure splash screen gets drawn ASAP

    QEventLoop loop;

    MaskThread *thread = new MaskThread();
    QObject::connect(thread, SIGNAL(finished()), &loop, SLOT(quit()));
    thread->start();

    loop.exec(); //Do event processing until the thread has finished!
    splash.hide();

    MainWindow mainWin(1);
    mainWin.show();

    return app.exec();
}

