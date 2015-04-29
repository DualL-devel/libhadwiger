#ifndef YaGraphProgram_H
#define YaGraphProgram_H

#include <QtCore/QObject>

class YaGraphProgram : public QObject
{
    Q_OBJECT

public:
    YaGraphProgram();
    virtual ~YaGraphProgram();

private slots:
    void output();
};

#endif // YaGraphProgram_H
