#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QQuickWidget>
#include <QQmlContext>

class TEstWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TEstWidget(QWidget *parent = nullptr);

signals:

public slots:
    void resizeEvent(QResizeEvent *event);

private:
    QQuickWidget* m_quickWidget;
};

#endif // TESTWIDGET_H
