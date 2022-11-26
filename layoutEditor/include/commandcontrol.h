#ifndef CommandControl_H
#define CommandControl_H
#include <QStack>
#include <QObject>
class Command;
class CommandControl: public QObject
{
    Q_OBJECT
public:
    static CommandControl* getInstance();
    void pushCommand(Command *pCommand);
public slots:
    void execute(Command *pCommand);
private:
    CommandControl();
    ~CommandControl();
    static CommandControl mSingle;
    QStack<Command*> mUndoStack;
    QStack<Command*> mRedoStack;
};

#endif // CommandControl_H
