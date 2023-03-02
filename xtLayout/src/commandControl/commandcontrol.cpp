#include "commandcontrol.h"
#include "command.h"
#include <QStack>
CommandControl CommandControl::mSingle;
CommandControl::CommandControl()
{

}

CommandControl::~CommandControl()
{

}

CommandControl* CommandControl::getInstance()
{
    return &mSingle;
}

void CommandControl::pushCommand(Command *pCommand)
{
    mUndoStack.push(pCommand);
}

void CommandControl::execute(Command *pCommand)
{
    pCommand->execute();
}
