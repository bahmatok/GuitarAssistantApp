#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    setenv("GSTREAMER_AUDIO_SINK", "autoaudiosink", 1);
    setenv("GSTREAMER_VIDEO_SINK", "autovideosink", 1);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    if (  (!QFile(":/MediaFiles/high.mp3").exists())
        ||(!QFile(":/MediaFiles/low.mp3").exists()))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Медиафайлы для метронома не найдены!");
        msgBox.exec();
        return 1;
    }
    return a.exec();
}
