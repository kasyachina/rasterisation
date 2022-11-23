#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QPlainTextEdit>

class LogWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit LogWidget(QWidget *parent = nullptr);
    void AppendMessage(const QString& message);
    void AppendSeparator();
};

#endif // LOGWIDGET_H
