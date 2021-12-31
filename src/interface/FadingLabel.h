#ifndef FADINGLABEL_H
#define FADINGLABEL_H

#include <QLabel>

class QPropertyAnimation;
class QSequentialAnimationGroup;
class QGraphicsOpacityEffect;

class FadingLabel : public QLabel
{
    Q_OBJECT
public:
    FadingLabel(QWidget* parent = nullptr);

public slots:
    void setAnimatedText(const QString& msg, bool highPriority);
    void setAnimatedText(const QString& msg);

private:
    QGraphicsOpacityEffect* effect = nullptr;
    QPropertyAnimation* fadeIn = nullptr;
    QPropertyAnimation* fadeOut = nullptr;
    QSequentialAnimationGroup* fadeInOut = nullptr;
    bool lastAnimationHighPriority = false;
};

#endif // FADINGLABEL_H
