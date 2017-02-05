#include <iostream>
#include "ShortcutPlainTextEdit.h"
#include "ui_MainWindow.h"
#include "MainWindow.h"

using namespace std;

Key::Key() : Key(false, -1, "") {
}

Key::Key(bool p, int c, std::string t) {
    pressed = p;
    code = c;
    text = t;
}


bool Key::isPressed() {
    return pressed;
}

int Key::getCode() {
    return code;
}

std::string Key::getText() {
    return text;
}

void Key::setPressed(bool b) {
    pressed = b;
}


ShortcutPlainTextEdit::ShortcutPlainTextEdit(QWidget*& widget) : QPlainTextEdit(widget) {
    numberKeyPressed = 0;
}

void ShortcutPlainTextEdit::keyPressEvent( QKeyEvent * event ) {

    numberKeyPressed++;
    keyMapping[event->key()] = Key(true, event->nativeVirtualKey(), QKeySequence(event->key() | event->modifiers()).toString().toStdString());
    if(keyMapping.size() == 2) {

        if(this->window() != NULL) {

            int tmpCount = 0;
            for(std::pair<const int, Key> &elems : keyMapping) {
                if(elems.second.isPressed()) {
                    keys[tmpCount] = Key(elems.second.isPressed(), elems.second.getCode(), elems.second.getText());
                    tmpCount++;
                }
                if(tmpCount >= 10) {
                    break;
                }
            }

            ((MainWindow*)this->window())->setShortcut(keys[1].getCode(), keys[0].getCode() );
            string s =  keys[1].getText() + " + " + keys[0].getText();
            QString qs(s.c_str());
            cout << qs.toStdString() << endl;
            setPlainText(qs);
        }
    }
}


void ShortcutPlainTextEdit::keyReleaseEvent( QKeyEvent * event ) {
    numberKeyPressed--;
    if(keyMapping.size() > 2) {
        cout << "Erreur : trop de touches appuyees simultanement : " << keyMapping.size() << " Maximum de touches appuyees simultanement : 2" << endl;
        //On clear par sécurité en cas de "blocage" des touches (ex: perte de focus de la fenêtre)
        keyMapping.clear();
    }

    keyMapping[event->key()].setPressed(false);

    unordered_map<int,Key>::const_iterator keyPos = keyMapping.find(event->key());
    if(keyPos != keyMapping.end()) {
        keyMapping.erase(keyPos);
    }

}
