#ifndef SHORTCUTPLAINEDITTEXT_H
#define SHORTCUTPLAINEDITTEXT_H

#include <qplaintextedit.h>
#include <qmainwindow.h>

#include <unordered_map>

class Key {
public:
    Key();
    Key(bool p, int c, std::string t);

    bool isPressed();
    int getCode();
    std::string getText();

    void setPressed(bool b);

private:
    bool pressed;
    int code;
    std::string text;
};

class ShortcutPlainTextEdit :  public QPlainTextEdit {
public:
    ShortcutPlainTextEdit(QWidget*& widget);
protected:
    virtual void keyPressEvent( QKeyEvent * );
    virtual void keyReleaseEvent(QKeyEvent *);

private:
    std::unordered_map<int, Key> keyMapping;
    int numberKeyPressed;
    Key keys[10];
};

#endif // SHORTCUTPLAINEDITTEXT_H
