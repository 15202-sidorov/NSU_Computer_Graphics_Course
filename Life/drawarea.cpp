#include "drawarea.h"

#include <iostream>

DrawArea::DrawArea(QWidget *parent, FieldController * fieldCtl) :
    QWidget(parent),
    fieledCtl(fieldCtl),
    iterationTimer(this)
{
    resize(image.getImage()->size());

    setMouseTracking(true);
    drawPoligons();
    fillPoligons();
    iterationTimer.setSingleShot(false);
    iterationTimer.setInterval(timerInterval);
    connect(&iterationTimer, SIGNAL(timeout()), this, SLOT(invokeIteration()));
}

void DrawArea::refreshSize()
{
    centers.resize(0);
    image.setImage(new QImage(QSize( (int)(POLIGON_SIZE) * 2 * fieledCtl->getWidth() + 2 * POLIGON_SIZE,
                                     POLIGON_SIZE * 2 * fieledCtl->getHeight() + POLIGON_SIZE * 2),
                              QImage::Format_ARGB32));
    resize(image.getImage()->size());

    drawPoligons();
    std::cout << "Filling poligons.." << std::endl;
    fillPoligons();
    repaint();
    std::cout << "Refreshed successfully" << std::endl;
}

void DrawArea::drawLine(const QPoint &newPoint)
{
    QPoint prevPoint = currentPoint;
    currentPoint = newPoint;

    const int deltaX = abs(currentPoint.x() - prevPoint.x());
    const int deltaY = abs(currentPoint.y() - prevPoint.y());

    const int signX  = prevPoint.x() < currentPoint.x() ? 1 : -1;
    const int signY  = prevPoint.y() < currentPoint.y() ? 1 : -1;

    int error = deltaX - deltaY;
    image.setPixel(prevPoint.x(), prevPoint.y(), LINE_COLOR);
    while ( currentPoint.x() != prevPoint.x() || currentPoint.y() != prevPoint.y() )
    {
        image.setPixel(prevPoint.x(),       prevPoint.y() ,     LINE_COLOR);
        image.setPixel(prevPoint.x(),       prevPoint.y() + 1,  LINE_COLOR);
        image.setPixel(prevPoint.x(),       prevPoint.y() - 1,  LINE_COLOR);
        image.setPixel(prevPoint.x() + 1,   prevPoint.y(),      LINE_COLOR);
        image.setPixel(prevPoint.x() - 1,   prevPoint.y(),      LINE_COLOR);

        const int next_error = error * 2;
        if ( next_error > -deltaY )
        {
            error -= deltaY;
            prevPoint.setX(prevPoint.x() + signX);
        }

        if ( next_error < deltaX )
        {
            error += deltaX;
            prevPoint.setY(prevPoint.y() + signY);
        }
    }
}

void DrawArea::drawPoligon(int i, int j)
{
    float angle_deg = 0;
    float angle_rad = 0;
    for (int corner_num = 0; corner_num < ANGLE_COUNT; corner_num++)
    {
        angle_deg = 60 * corner_num + 30;
        angle_rad = M_PI / 180 * angle_deg;
        QPoint newPoint = QPoint(currentCenter.x() + (int)(POLIGON_SIZE * cos(angle_rad)),
                                 currentCenter.y() + (int)(POLIGON_SIZE * sin(angle_rad)));
        drawLine(newPoint);
    }
}

void DrawArea::countNextCenter( int i, int j )
{
    QPoint result;
    if (j % 2)
    {
        result = QPoint(START_POINT + (int)(POLIGON_SIZE  * cos(M_PI/6)), START_POINT);
    }
    else
    {
        result = QPoint(START_POINT, START_POINT);
    }

    result.setX(result.x() + i * (int)(POLIGON_SIZE  * cos(M_PI/6)) * 2);
    result.setY(result.y() + j * (POLIGON_SIZE + (int)(POLIGON_SIZE * sin(M_PI/6))));

    currentCenter = result;
    centers.push_back(result);
    return;
}

void DrawArea::drawPoligons()
{
    currentCenter = QPoint(START_POINT, START_POINT);
    currentPoint  = QPoint(currentCenter.x() + (int)(POLIGON_SIZE  * cos(M_PI/6)),
                           currentCenter.y() - (int)(POLIGON_SIZE  * sin(M_PI/6)));

    for (int j = 0; j < fieledCtl->getHeight(); j++)
    {
        for (int i = 0; i < fieledCtl->getWidth(); i++)
        {
            drawPoligon(i,j);
            countNextCenter(i, j);
            currentPoint.setX(currentCenter.x() + (int)(POLIGON_SIZE * cos(M_PI/6)));
            if ( i != fieledCtl->getWidth() - 1 )
            {
                currentPoint.setY(currentCenter.y() + (int)(POLIGON_SIZE  * sin(M_PI/6)));
            }
        }
    }
    drawPoligon(fieledCtl->getWidth() - 1, fieledCtl->getHeight() - 1);
}

void DrawArea::fillPoligonInDirection(QPoint brushPosition,
                                      const SpanDirection &direction,
                                      const QRgb &color)
{
    int currentX = brushPosition.x();
    int currentY = brushPosition.y();

    int pixelsRight = 0;
    int pixelsLeft = 0;

    if ( LINE_COLOR != image.getPixel(currentX,currentY) )
    {
        image.setPixel(currentX,currentY, color);
    }

    currentX++;
    while ( LINE_COLOR != image.getPixel(currentX, currentY) )
    {
        image.setPixel(currentX, currentY, color);
        currentX++;
        pixelsRight++;
    }

    currentX = brushPosition.x();
    currentX--;
    while ( LINE_COLOR != image.getPixel(currentX, currentY) )
    {
        image.setPixel(currentX, currentY, color);
        currentX--;
        pixelsLeft++;
    }

    // Means no pixels found in any direction, end of algorithm.
    if ( 0 == pixelsRight && 0 == pixelsLeft )
    {
        return;
    }

    if ( 0 == pixelsRight )
    {
        brushPosition.setX(brushPosition.x() - pixelsLeft/2);
    }
    else if ( 0 == pixelsLeft )
    {
        brushPosition.setX(brushPosition.x() + pixelsRight/2);
    }

    if ( UPWARDS == direction )
    {
        fillPoligonInDirection(QPoint(brushPosition.x(), brushPosition.y() - 1), direction, color);
    }
    else
    {
        fillPoligonInDirection(QPoint(brushPosition.x(), brushPosition.y() + 1), direction, color);
    }

    return;
}

void DrawArea::drawImpacts( QPainter &painter )
{
    FieldController::OffsetCoordinate coordinate(0,0);
    QPoint center;
    float impact = 0;
    for (int j = 0; j < fieledCtl->getHeight(); j++)
    {
        for (int i = 0; i < fieledCtl->getWidth(); i++)
        {
            coordinate.column = i;
            coordinate.row = j;
            center = getCenter(coordinate);
            center.setX(center.x() - 10);
            fieledCtl->countImpact(fieledCtl->getCell(coordinate));
            impact = fieledCtl->getCell(coordinate).getNextImpact();

            std::stringstream stream;
            stream << std::fixed << std::setprecision(1) << impact;
            QString s = QString::fromStdString(stream.str());
            painter.drawText(center, s);
        }
    }
}


void DrawArea::fillPoligon( QPoint mousePosition, const QRgb &color )
{
    fillPoligonInDirection(mousePosition, UPWARDS, color);
    fillPoligonInDirection(mousePosition, DOWNWARDS, color);
}

void DrawArea::fillPoligons()
{
    for (int j = 0; j < fieledCtl->getHeight(); j++)
    {
        for (int i = 0; i < fieledCtl->getWidth(); i++)
        {
            if ( fieledCtl->getCell(i,j).isAlive() )
            {
                fillPoligon(getCenter(i,j), ALIVE_CELL_COLOR);
            }
            else
            {
                fillPoligon(getCenter(i,j), DEAD_CELL_COLOR);
            }
        }
    }
}

void DrawArea::mousePressEvent(QMouseEvent * event)
{
    QRgb currentPixel = image.getPixel(event->pos().x(), event->pos().y());
    if ( LINE_COLOR == currentPixel )
    {
        return;
    }

    FieldController::OffsetCoordinate coordinate = getPoligonCoordinateFromMousePoint(event->pos());
    prevCoordinate = coordinate;
    if ( DEAD_CELL_COLOR == currentPixel )
    {
        fieledCtl->getCell(coordinate).setAlive(true);
        fillPoligon(event->pos(), ALIVE_CELL_COLOR);
    }
    else if ( ALIVE_CELL_COLOR == currentPixel )
    {
        if ( XOR == currentRegime )
        {
            fieledCtl->getCell(coordinate).setAlive(false);
            fillPoligon(event->pos(), DEAD_CELL_COLOR);

        }
    }
    if (impactMode)
    {
        fieledCtl->countImpact();
    }

    repaint();
}

void DrawArea::mouseMoveEvent( QMouseEvent *event )
{
    QRgb currentPixel = image.getPixel(event->pos().x(), event->pos().y());
    if ( LINE_COLOR == currentPixel )
    {
        return;
    }

    FieldController::OffsetCoordinate coordinate = getPoligonCoordinateFromMousePoint(event->pos());
    if ( coordinate == prevCoordinate )
    {
        return;
    }
    else
    {
        prevCoordinate = coordinate;
    }

    if ((Qt::LeftButton == event->buttons()) &&
        (DEAD_CELL_COLOR == currentPixel))
    {
        fieledCtl->getCell(coordinate).setAlive(true);
        if ( impactMode )  fieledCtl->countImpact();
        fillPoligon(event->pos(), ALIVE_CELL_COLOR);
    }
    else if ((Qt::LeftButton == event->buttons()) &&
             (ALIVE_CELL_COLOR == currentPixel) &&
             (XOR == currentRegime))
    {

        fieledCtl->getCell(coordinate).setAlive(false);
        if ( impactMode ) fieledCtl->countImpact();
        fillPoligon(event->pos(), DEAD_CELL_COLOR);
    }
    repaint();
}

FieldController::OffsetCoordinate
DrawArea::getPoligonCoordinateFromMousePoint( const QPoint &mouseLocation )
{
    int q = (mouseLocation.x() * sqrt(3)/3 - mouseLocation.y()/3) / POLIGON_SIZE;
    int r = (mouseLocation.y() * 2/3) / POLIGON_SIZE;
    FieldController::CubeCoordinate cube = FieldController::CubeCoordinate(q, -q-r, r);
    FieldController::OffsetCoordinate offset = FieldController::cubeToOffset(cube);
    int minDistance = 0;
    int distance = 0;
    std::vector<QPoint> centers;
    std::vector<FieldController::OffsetCoordinate> coordinates;

    FieldController::OffsetCoordinate result = offset;
    minDistance = countDistance(getCenter(offset), mouseLocation);

    for (int i = 0; i < 2; i++)
    {
        if ( i % 2 )
        {
            if (offset.column >= 1)
            {
                coordinates.push_back(FieldController::OffsetCoordinate(offset.column - 1, offset.row));
                centers.push_back(getCenter(coordinates.back()));
            }

            if (offset.row >= 1)
            {
                coordinates.push_back(FieldController::OffsetCoordinate(offset.column, offset.row - 1));
                centers.push_back(getCenter(coordinates.back()));
            }

            if ((offset.column < fieledCtl->getWidth() - 1) && (offset.row  >= 1))
            {
                coordinates.push_back(FieldController::OffsetCoordinate(offset.column + 1, offset.row - 1));
                centers.push_back(getCenter(coordinates.back()));
            }
        }
        else
        {
            if (offset.column < fieledCtl->getWidth() - 1)
            {
                coordinates.push_back(FieldController::OffsetCoordinate(offset.column + 1, offset.row));
                centers.push_back(getCenter(coordinates.back()));
            }

            if (offset.row > fieledCtl->getHeight() - 1)
            {
                coordinates.push_back(FieldController::OffsetCoordinate(offset.column, offset.row + 1));
                centers.push_back(getCenter(coordinates.back()));
            }

            if ((offset.column < fieledCtl->getWidth() - 1) && (offset.row  < fieledCtl->getHeight() - 1))
            {
                coordinates.push_back(FieldController::OffsetCoordinate(offset.column + 1, offset.row + 1));
                centers.push_back(getCenter(coordinates.back()));
            }
        }

        for (int i = 0; i < centers.size(); i++)
        {
            distance = countDistance(centers[i], mouseLocation);
            if ( distance < minDistance )
            {
                minDistance = distance;
                result = coordinates[i];
            }
        }
    }

    return result;
}

QPoint
DrawArea::getMouseLocationFromCoordinate(const FieldController::OffsetCoordinate &coordinate )
{
    int x = POLIGON_SIZE * sqrt(3) * coordinate.column + 0.5 * (coordinate.row&1);
    int y = POLIGON_SIZE * (3/2) * coordinate.row;
    return QPoint(x,y);
}

QPoint& DrawArea::getCenter(int i, int j)
{
    return centers[j * fieledCtl->getWidth() + i];
}

QPoint& DrawArea::getCenter(const FieldController::OffsetCoordinate &coordinate )
{
    return centers[coordinate.row * fieledCtl->getWidth() + coordinate.column];
}

void DrawArea::invokeIteration()
{
    fieledCtl->nextItaration();
    fillPoligons();
    repaint();
}

void DrawArea::newPoligonSize( int size )
{
    setPoligonSize(size);
}

void DrawArea::startGame()
{
    iterationTimer.stop();
}

void DrawArea::stopGame()
{
    iterationTimer.start();
}

void DrawArea::switchRun(bool b)
{
    if ( !b )
    {
        startGame();
    }
    else
    {
        stopGame();
    }
}

void DrawArea::setTimerInterval( int interval )
{
    timerInterval = interval;
}

void DrawArea::setXOR(bool b)
{
    if (b) { currentRegime = XOR; }
    else { currentRegime = NORMAL; }
}

void DrawArea::setReset(bool b)
{
    if (b) { currentRegime = NORMAL; }
}

void DrawArea::setImpactMode(bool b)
{
    impactMode = b;
    repaint();
}

void DrawArea::clear()
{
    fieledCtl->clear();
    fillPoligons();
    repaint();
}

void DrawArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0,0,*image.getImage());
    if ( impactMode )
    {
        drawImpacts(painter);
    }

    currentCenter = QPoint(START_POINT, START_POINT);
    currentPoint  = QPoint(currentCenter.x() + (int)(POLIGON_SIZE * cos(M_PI/6)),
                           currentCenter.y() - (int)(POLIGON_SIZE * sin(M_PI/6)));
}


