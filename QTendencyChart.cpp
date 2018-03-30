#include "QTendencyChart.h"
#include <QPainter>

#define DEFAULT_TIMES 12

static float angle(float x1, float y1, float x2, float y2)
{
    float angle_temp;
    float xx, yy;

    xx = x2 - x1;
    yy = y2 - y1;

    if (xx == 0.0)
        angle_temp = 3.1415926 / 2.0;
    else
        angle_temp = atan(fabs(yy / xx));

    if ((xx < 0.0) && (yy >= 0.0))
        angle_temp = 3.1415926 - angle_temp;
    else if ((xx < 0.0) && (yy < 0.0))
        angle_temp = 3.1415926 + angle_temp;
    else if ((xx >= 0.0) && (yy < 0.0))
        angle_temp = 3.1415926 * 2.0 - angle_temp;

    angle_temp = 180.0 * angle_temp/ 3.1415926;
    return (angle_temp);
}

QTendencyChart::QTendencyChart(QQuickItem *parent):
    QQuickPaintedItem(parent),
    m_MaxTime(DEFAULT_TIMES),
    m_bgColor(QColor(255,255,255)),
    m_sPColor(QColor(210,122,66,145)),
    m_dPColor(QColor(23,114,210,145)),
    m_aVColor(QColor(213,114,210,145)),
    m_RectStartY(0),
    mRectEndY(270),
    m_LeftRect(50),
    m_BtomRect(40),
    m_YLineCount(10)
{

    m_TextFont.setFamily("Microsoft YaHei");
    m_TextFont.setPointSize(10);

    //for test
    map<int, double> systolics;
    systolics[1] = 121;
    systolics[2] = 99;
    systolics[3] = 124;
    systolics[5] = 119;
    systolics[11] = 119;
    systolics[12] = 234;
    systolics[13] = 189;
    systolics[15] = 111;
    map<int, double> diastolics;
    diastolics[1] = 57;
    diastolics[2] = 99;
    diastolics[5] = 124;
    diastolics[6] = 119;
    diastolics[11] = 119;
    diastolics[12] = 234;
    diastolics[13] = 189;
    diastolics[18] = 111;
    map<int, double> avestolics;
    avestolics[1] = 100;
    avestolics[2] = 99;
    avestolics[17] = 124;
    avestolics[6] = 119;
    avestolics[10] = 23;
    avestolics[9] = 44;
    avestolics[13] = 123;
    avestolics[7] = 222;
    SetSampleTrend(systolics, diastolics, avestolics);
    //for test
}

void QTendencyChart::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);

    paintBcg(painter);
    paintGrid(painter);
    paitSystolicTrend(painter);
    paitDiastolicTrend(painter);
    paitavestolicTrend(painter);
}


void QTendencyChart::SetSampleTrend(map<int, double> &systolics,
                                    map<int, double> &diastolics,
                                    map<int, double> &avestolics)
{

    int iMaxSlen =  CalcMaxTime(systolics);
    int iMaxDlen =  CalcMaxTime(diastolics);
    int iMaxAlen =  CalcMaxTime(avestolics);
    m_MaxTime = max(iMaxAlen, max(iMaxSlen, iMaxDlen));
    if(m_MaxTime <= 0)
    {
        m_MaxTime = DEFAULT_TIMES;
    }
    m_systolics =   systolics;
    m_diastolics =  diastolics;
    m_avestolics =  avestolics;
    update();
}

void QTendencyChart::SetBgColor(QColor bgColor)
{
    m_bgColor = bgColor;
}

void QTendencyChart::SetRectRangeY(double Start, double End)
{
     m_RectStartY   = Start;
     mRectEndY      = End;

     if(m_RectStartY > mRectEndY)
     {
         double nTmp =  m_RectStartY;
         m_RectStartY = mRectEndY;
         mRectEndY = nTmp;
     }

     update();
}

int QTendencyChart::CalcMaxTime(const map<int, double> &datas)
{
    int iMaxTime = 0;
    map<int, double>::const_iterator it = datas.begin();
    for( ; it != datas.end(); ++it)
    {
        if(it->first > iMaxTime)
        {
            iMaxTime = it->first;
        }
    }
    return iMaxTime;
}

double QTendencyChart::CalcPosY(double value)
{
    double iStep = (double)(height() - m_BtomRect) / (double)(mRectEndY - m_RectStartY);
    double dDis =  iStep * (value - m_RectStartY);
    return height() - (dDis + m_BtomRect);
}

double QTendencyChart::CalcPosX(double value)
{
    int iStartX = m_LeftRect;
    int iWaveLen = width() - m_LeftRect;
    int iStepGrid = iWaveLen / (m_MaxTime + 1);
    return iStartX + iStepGrid * value;
}

void QTendencyChart::DrawPresure(const QString& tips, const map<int, double> &datas, QColor color, QPainter *painter)
{
    painter->save();
    QVector<QPoint>  vPoints;//
    for(int iIndex = 1; iIndex <= m_MaxTime; ++iIndex)
    {
        map<int, double>::const_iterator it = datas.find(iIndex);
        if(it != datas.end())
        {
            //绘制点
            double x = CalcPosX(iIndex);
            double y = CalcPosY(it->second);
            QPen Endpoint(color,10);
            painter->setPen(Endpoint);
            painter->drawEllipse(QRect(x - 3, y - 3, 6, 6));//-5

            QPoint point;
            point.setX(x);
            point.setY(y);
            vPoints.push_back(point);
        }
    }
     painter->restore();

    painter->save();
    //绘制线
    QPen Endpoint(color,8);
    painter->setPen(Endpoint);
    painter->drawPolyline(vPoints);

    //绘制对应的文字
    if(vPoints.size() > 0)
    {
        QPen Endpoint(QColor(0,0,0),12);
        painter->setPen(Endpoint);

        if(vPoints.size() > 1)
        {
            painter->translate(QPoint(vPoints[0].x(), vPoints[0].y() - 10));// 第1步：变换旋转中心到所绘制文字左下角
            painter->rotate(angle(vPoints[0].x(), vPoints[0].y(), vPoints[1].x(), vPoints[1].y()));                    // 第2步： 旋转一定角度
            painter->drawText(0,0, tips);      // 第3步： 绘制文字
            painter->resetMatrix();                  // 第4步： 恢复坐标旋转
        }
        else
        {
            painter->drawText(QPoint(vPoints[0].x(), vPoints[0].y() - 10), tips);
        }
    }
    painter->restore();
}

void QTendencyChart::paintGrid(QPainter *painter)
{
    painter->save();
    QPen pen;
    pen.setStyle(Qt::DotLine);
    painter->setFont(m_TextFont);
    painter->setPen(pen);
    paintXLines(painter);
    paintYLines(painter);
    painter->restore();

}

void QTendencyChart::paintXLines(QPainter *painter)
{
    //计算折线图区域长度
    for(int iIndex = 1; iIndex <= m_MaxTime; ++iIndex)
    {
        int iX = CalcPosX(iIndex);
        int iMinY = height() - m_BtomRect;
        int iMaxY = 0;
        painter->drawLine(QPoint(iX, iMinY), QPoint(iX, iMaxY));
        QString sTime = QString("%1th time").arg(iIndex);
        //绘制文字
        if(iIndex == 1)
        {
            sTime = QString("%1ST time").arg(iIndex);
        }
        else if(iIndex == 2)
        {
            sTime = QString("%1nd time").arg(iIndex);
        }
        else if(iIndex == 3)
        {
             sTime = QString("%1rd time").arg(iIndex);
        }

         QFontMetrics fm(m_TextFont);
         QRect rec = fm.boundingRect(sTime);
        painter->drawText(iX - rec.width() / 2.0, iMinY + rec.height() , sTime);
    }
}

void QTendencyChart::paintYLines(QPainter *painter)
{
    double dStep = (mRectEndY - m_RectStartY) / (m_YLineCount);

    //绘制最小点
    int y = CalcPosY(m_RectStartY);
    QString sValue = QString("%1").arg(m_RectStartY);
    QFontMetrics fm(sValue);
    QRect rec = fm.boundingRect(sValue);
    painter->drawText(QPoint(m_LeftRect - rec.width(), y + rec.height() /4.0 ), sValue);

    for(int iIndex = 1; iIndex <= m_YLineCount; ++iIndex)
    {
        double value = m_RectStartY + iIndex*dStep;
        int y = CalcPosY(value);
        painter->drawLine(QPoint(m_LeftRect, y), QPoint(width(), y));

        if(iIndex != m_YLineCount)
        {
            QString sValue = QString("%1").arg(value);
            QFontMetrics fm(sValue);
            QRect rec = fm.boundingRect(sValue);
            painter->drawText(QPoint(m_LeftRect - rec.width() - 3, y + rec.height() /4.0 ), sValue);
        }
    }
}

void QTendencyChart::paintBcg(QPainter *painter)
{
    painter->save();
    painter->setBrush(QBrush(m_bgColor));
    painter->drawRect(QRect(m_LeftRect,0,width() - m_LeftRect, height() - m_BtomRect));
    painter->restore();
}


void QTendencyChart::paitSystolicTrend(QPainter *painter)
{
    DrawPresure("SP (Systolic pressure)", m_systolics,m_sPColor,painter);
}

void QTendencyChart::paitDiastolicTrend(QPainter *painter)
{
    DrawPresure("DP (Diastolic pressure)", m_diastolics,m_dPColor,painter);
}

void QTendencyChart::paitavestolicTrend(QPainter *painter)
{
   DrawPresure("AP (Mean pressure)", m_avestolics,m_aVColor,painter);
}
