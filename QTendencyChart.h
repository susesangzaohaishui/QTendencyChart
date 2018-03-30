#ifndef QTENDENCYCHART_H
#define QTENDENCYCHART_H


#include <QQuickPaintedItem>
#include <map>
using namespace std;

class QTendencyChart : public QQuickPaintedItem
{
    Q_OBJECT
public:

    QTendencyChart(QQuickItem *parent = 0);

    void  paint(QPainter *painter);

    //设置采样趋势
    void SetSampleTrend(map<int, double>&systolics,
                        map<int, double>&diastolics,
                        map<int, double>&avestolics);

    void SetBgColor(QColor bgColor);

    void SetRectRangeY(double Start, double End);

private:
    //绘制格子
    void    paintGrid(QPainter *painter);
    void    paintXLines(QPainter *painter);
    void    paintYLines(QPainter *painter);
    //绘制背景
    void    paintBcg(QPainter *painter);
    //绘制收缩压趋势图
    void    paitSystolicTrend(QPainter *painter);
    //绘制舒张压趋势图
    void    paitDiastolicTrend(QPainter *painter);
    //绘制平局压趋势图
    void    paitavestolicTrend(QPainter *painter);
    //计算次数中得最大值
    int     CalcMaxTime(const map<int, double>&datas);
    //输入一个值，输出这个值对应的Y值
    double  CalcPosY(double value);
    //计算第几次的X点位置
    double  CalcPosX(double value);
    void    DrawPresure(const QString& tips, const map<int, double> & datas, QColor color,QPainter *painter);

private:
    int m_MaxTime;//最大的次数
    map<int, double> m_systolics;
    map<int, double> m_diastolics;
    map<int, double> m_avestolics;

    QColor          m_bgColor;//背景颜色
    QColor          m_sPColor;//背景颜色
    QColor          m_dPColor;//背景颜色
    QColor          m_aVColor;//背景颜色

    double          m_RectStartY,mRectEndY;

    //左边宽度
    int             m_LeftRect;
    int             m_BtomRect;

    QFont           m_TextFont;
    int             m_YLineCount;//Y向线的个数
    double          m_YStep;



};

#endif // QTENDENCYCHART_H
