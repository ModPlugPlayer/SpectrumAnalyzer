#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <QPointF>
#include <QSizeF>
#include <QPainter>

class Drawable
{
public:
    Drawable();

    virtual void draw(QPainter &painter) = 0;

    inline QPointF getCoordinates() const;
    inline void setCoordinates(const QPointF &value);

    inline QSizeF getSizes() const;
    inline void setSizes(const QSizeF &value);

private:
    QPointF coordinates;
    QSizeF sizes;
};

inline QPointF Drawable::getCoordinates() const
{
    return coordinates;
}

inline void Drawable::setCoordinates(const QPointF &value)
{
    coordinates = value;
}

inline QSizeF Drawable::getSizes() const
{
    return sizes;
}

inline void Drawable::setSizes(const QSizeF &value)
{
    sizes = value;
}

#endif // DRAWABLE_HPP
