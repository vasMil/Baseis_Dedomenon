#ifndef MYQT_FUNCTIONS_H
#define MYQT_FUNCTIONS_H

#include "DBConnect.h"

//will also include some notes

//if you rename a class then ui interface will most likely not work
//in order to fix that you will need:
//  instead of renaming the class, create a new one
//  copy width, height of the ui window and the whole layout
//  paste these in the new ui layout.
//  do the same with the cpp file and the .h file -> watch out for the names!
//  As well as the libraries that you have included in the original file
//  IMPORTANT: Do not forget to remove oldfile.h, oldfile.cpp, oldfile.ui from the .pro (or .pri) file!

//In order to create a .pri file you will need to follow these steps
//  1) create a new folder inside the project folder and add a new file named as: name.pri
//  2) in the .pro file add the line: include( ./folder/name.pri )
//  3) run the program and expect to load the .pri file in qt.
//  4) open the .pri file and add these 2 lines: INCLUDEPATH += manager
//                                               DEPENDPATH += manager
//  5) you may now create new qt form classes in the name folder (name.pri sub-project)

//If you need to add a new image in resources, during run time
//you will also need to re compile the resources, using rcc?
//really don't recommend looking into it

//Signal and Slots - errors, what to look for
//  how to connect s&s, without arguments:    connect(this, SIGNAL( decr_child_count() ), this->p, SLOT( decr_child_count() ) );
//  how to connect s&s, WITH ARGUMENTS:    connect(this, SIGNAL( update_child(QWidget*) ), this->p, SLOT( update_child(QWidget*) ) );
//The code above is the old style of connect, there is a new one -> check documentation
//slots are private attributes
//signals are public? (check if they may be protected as well)
//If you have an error you don't really understand check if you have connected the signal to the slot
//in the constructor of the sender (the one with the signal obv)
//Signals CAN NEVER HAVE A RETURN TYPE (always void) -> documentation says so
//For slots it is not clear if they can have a return type, although in forums it is said that they should not
//even though if you implement them, it is not garanted that it will work and if it does it is said to be an abnormal behaviour
//If you want a slot to have a return type (most probably because you need to use it as a function aswell
//it is advised to create a function with whatever return type and call that function inside the slot

//For comboboxes, if you need to set the default choice (knowing there is one already assigned)
//do ui->comboBox_name->setCurrentText("choice");

//creates a message box with icon: icon, title: title, message: text and display's it at the middle of the primary screen
void centeredMessage(QMessageBox::Icon icon, QString title, QString text);
#endif // MYQT_FUNCTIONS_H
