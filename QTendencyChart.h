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

    //���ò�������
    void SetSampleTrend(map<int, double>&systolics,
                        map<int, double>&diastolics,
                        map<int, double>&avestolics);

    void SetBgColor(QColor bgColor);

    void SetRectRangeY(double Start, double End);

private:
    //���Ƹ���
    void    paintGrid(QPainter *painter);
    void    paintXLines(QPainter *painter);
    void    paintYLines(QPainter *painter);
    //���Ʊ���
    void    paintBcg(QPainter *painter);
    //��������ѹ����ͼ
    void    paitSystolicTrend(QPainter *painter);
    //��������ѹ����ͼ
    void    paitDiastolicTrend(QPainter *painter);
    //����ƽ��ѹ����ͼ
    void    paitavestolicTrend(QPainter *painter);
    //��������е����ֵ
    int     CalcMaxTime(const map<int, double>&datas);
    //����һ��ֵ��������ֵ��Ӧ��Yֵ
    double  CalcPosY(double value);
    //����ڼ��ε�X��λ��
    double  CalcPosX(double value);
    void    DrawPresure(const QString& tips, const map<int, double> & datas, QColor color,QPainter *painter);

private:
    int m_MaxTime;//���Ĵ���
    map<int, double> m_systolics;
    map<int, double> m_diastolics;
    map<int, double> m_avestolics;

    QColor          m_bgColor;//������ɫ
    QColor          m_sPColor;//������ɫ
    QColor          m_dPColor;//������ɫ
    QColor          m_aVColor;//������ɫ

    double          m_RectStartY,mRectEndY;

    //��߿��
    int             m_LeftRect;
    int             m_BtomRect;

    QFont           m_TextFont;
    int             m_YLineCount;//Y���ߵĸ���
    double          m_YStep;



};

#endif // QTENDENCYCHART_H
