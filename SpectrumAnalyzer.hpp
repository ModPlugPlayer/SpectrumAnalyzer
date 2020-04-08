#ifndef SPECTRUMANALYZER_HPP
#define SPECTRUMANALYZER_HPP

#include <QWidget>

struct Point {
    int x;
    int y;
};

class SpectrumAnalyzer : public QWidget
{
    Q_OBJECT
public:
    explicit SpectrumAnalyzer(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    Point startingPoint, endingPoint;

signals:

};

#endif // SPECTRUMANALYZER_HPP
