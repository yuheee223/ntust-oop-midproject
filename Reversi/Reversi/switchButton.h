#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QColor>

class SwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget* parent = nullptr);

signals:
    void statusChanged(bool checked);

public slots:

private slots:
    void UpdateValue();

private:
    void drawBackGround(QPainter* painter);
    void drawSlider(QPainter* painter);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    //和邊界距離
    int m_space;
    int m_radius;
    //開關
    bool m_checked;
    bool m_showText;
    bool m_showCircle;
    bool m_animation;

    //打開十背景顏色
    QColor m_bgColorOn;
    //關閉十背景顏色
    QColor m_bgColorOff;
    //打開十划塊顏色
    QColor m_sliderColorOn;
    //關閉十划塊顏色
    QColor m_sliderColorOff;
    //文字颜色
    QColor m_textColor;

    QString m_textOn;
    QString m_textOff;

    QTimer* m_timer;
    //動畫步長
    int m_step;
    int m_startX;
    int m_endX;

public:
    int space()                 const;
    int radius()                const;
    bool checked()              const;
    bool showText()             const;
    bool showCircle()           const;
    bool animation()            const;

    QColor bgColorOn()          const;
    QColor bgColorOff()         const;
    QColor sliderColorOn()      const;
    QColor sliderColorOff()     const;
    QColor textColor()          const;

    QString textOn()            const;
    QString textOff()           const;

    int step()                  const;
    int startX()                const;
    int endX()                  const;

public Q_SLOTS:
    void setSpace(int space);
    void setRadius(int radius);
    void setChecked(bool checked);
    void setShowText(bool show);
    void setShowCircle(bool show);
    void setAnimation(bool ok);

    void setBgColorOn(const QColor& color);
    void setBgColorOff(const QColor& color);
    void setSliderColorOn(const QColor& color);
    void setSliderColorOff(const QColor& color);
    void setTextColor(const QColor& color);

    void setTextOn(const QString& text);
    void setTextOff(const QString& text);

    //    void setStep(int step);
    //    void setStartX(int startX);
    //    void setEndX(int endX);
};

#endif // SWITCHBUTTON_H