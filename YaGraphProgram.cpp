#include "YaGraphProgram.h"

#include <QTimer>
#include <iostream>

YaGraphProgram::YaGraphProgram()
{
    QTimer* timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), SLOT(output()) );
    timer->start( 1000 );
}

YaGraphProgram::~YaGraphProgram()
{}

void YaGraphProgram::output()
{
    std::cout << "Hello World!" << std::endl;
}

#include "YaGraphProgram.moc"
