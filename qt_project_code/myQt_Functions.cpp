#include "myQt_Functions.h"

void centeredMessage(QMessageBox::Icon icon, QString title, QString text){
    //create qmessagebox
    QMessageBox *message = new QMessageBox(icon, title, text);
    //get the QSize of the message window
    QSize mSize = message->sizeHint();
    //get the dimensions of the primary screen (the screen that the app is running on)
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenRect = screen->availableGeometry();
    //move the message box on the QPoint which is calculated as shown (in order to point at the middle of the screen)
    message->move( QPoint( screenRect.width()/2 - mSize.width()/2,
                    screenRect.height()/2 - mSize.height()/2 ) );
    //run the message
    message->exec();
}
