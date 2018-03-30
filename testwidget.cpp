#include "testwidget.h"
#include "QTendencyChart.h"

TEstWidget::TEstWidget(QWidget *parent) : QWidget(parent)
{
    //setWindowFlags(Qt::FramelessWindowHint| Qt::WindowMinimizeButtonHint|Qt::Tool);//不显示任务栏图标


    qmlRegisterType<QTendencyChart>("QTendencyChart", 1, 0, "QTendencyChart");

    m_quickWidget = new QQuickWidget(this);
    m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    //m_quickWidget->rootContext()->setContextProperty("QInitPage",this);
    QUrl source("qrc:/MainForm.qml");
    m_quickWidget->setSource(source);
    QObject *pRoot = (QObject*)m_quickWidget->rootObject();
    if(pRoot != nullptr)
    {
        //connect(pRoot,SIGNAL(imageClick(QString)),this,SLOT(onImageClick(QString)));
    }
    // m_quickWidget->show();

    //设置窗口透明色
    m_quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    m_quickWidget->setClearColor(QColor(Qt::transparent));
    m_quickWidget->setStyleSheet("background:transparent;");
    m_quickWidget->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background:transparent;");
    this->setAttribute(Qt::WA_TranslucentBackground);

}

void TEstWidget::resizeEvent(QResizeEvent *event)
{
    m_quickWidget->resize(this->size());
}
