#include <QVector>
#include "RouletteWidget.h"
#include "../common.h"
#include "../glUtil.h"

RouletteWidget::RouletteWidget(Individual *winner, Generation *generation, QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    Q_ASSERT(winner);
    Q_ASSERT(generation);

    this->generation = generation;
    this->winner = winner;

    finalRotation = 360.0f;

    foreach (Individual *contestant, generation->getPopulation())
    {
        double slice = ((double) contestant->getFitness()->getValue() /
                        (double) generation->getTotalFitness()) * 360.0f;

        if (contestant != winner)
            finalRotation -= slice;
        else
        {
            finalRotation -= slice / 2.0f;
            break;
        }
    }

    fitnessFont = new QFont("Arial", 8, QFont::Bold);

    wheelRadius = 0.9f;
    labelRadius = 0.9f;
    numSpins = 2;

    connect(&spinTimer, SIGNAL(timeout()), this, SLOT(updateAnimation()));

    reset();
}

RouletteWidget::~RouletteWidget()
{
    safeDelete(fitnessFont);
}

void RouletteWidget::reset()
{
    wheelRotation = 0.0f;
    spinSpeed = 20.0f;

    // From SUVAT equation, does numSpins full spin(s) then lands on finalRotation
    spinAcceleration = -(spinSpeed * spinSpeed) / (2.0 * (finalRotation + numSpins * 360.0f));

    spinTimer.start(15);
}

void RouletteWidget::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void RouletteWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    double startAngle = 0, endAngle = 0;
    bool black = true;

    // Draw a slice for each individual
    foreach (Individual *individual, generation->getPopulation())
    {
        // Alternate between black and red
        if (black)
            glColor3f(0.0f, 0.0f, 0.0f);
        else
            glColor3f(1.0f, 0.0f, 0.0f);

        // Work out how big of a slice this individual has
        double slice = ((double) individual->getFitness()->getValue() /
                        (double) generation->getTotalFitness()) * 360.0f;

        // Only draw if individual has a chance
        if (slice > 0.0)
        {
            endAngle += slice;

            // Draw the slice
            glPushMatrix();
            {
                glScalef(wheelRadius, wheelRadius, 0.0f);
                glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

                glBegin(GL_TRIANGLE_FAN);
                {
                    // Centre point
                    glVertex2f(0.0f, 0.0f);

                    // Draw curve
                    double step = (endAngle - startAngle) / 360.0f;
                    for (double angle = startAngle; angle <= endAngle + 0.1; angle += step)
                        glVertex2f(cos(angle * PI_OVER_180), sin(angle * PI_OVER_180));
                }
                glEnd();

                glScalef(0.8f, 0.8f, 0.0f);
                glBegin(GL_TRIANGLE_FAN);
                {
                    glColor3f(0.7f, 0.7f, 0.7f);
                    glUtil::drawUnitCircle();
                }
                glEnd();
            }
            glPopMatrix();

            // Draw winner pointer
            glPushMatrix();
            {
                glTranslatef(wheelRadius, 0.0f, 0.0f);
                glScalef(0.1f, 0.1f, 0.0f);
                glRotatef(270.0f, 0.0f, 0.0f, 1.0f);

                glBegin(GL_TRIANGLE_FAN);
                {
                    glColor3f(0.0f, 1.0f, 0.0f);
                    glUtil::drawUnitTriangle();
                }
                glEnd();
            }
            glPopMatrix();

            // Calculate label coordinates, where x and y are the centre of the label
            double angle = wheelRotation + startAngle + ((endAngle - startAngle) / 2.0);
            QString label = QString::number(individual->getFitness()->getValue());
            QFontMetrics fm(*fitnessFont);
            float halfWidth = ((float) fm.width(label) / 2.0f) * (2.0f / (double) width());
            float halfHeight = (fitnessFont->pointSizeF() / 2.0f) * (2.0f / (double) height());
            float x = (cos(angle * PI_OVER_180) * wheelRadius * labelRadius) - halfWidth;
            float y = (sin(angle * PI_OVER_180) * wheelRadius * labelRadius) + halfHeight;

            // Draw the label
            glColor3f(1.0f, 1.0f, 1.0f);
            renderText(x, y, 0.0, label, *fitnessFont);

            // Prepare for next slice
            startAngle = endAngle;
            black = !black;
        }
    }
}

void RouletteWidget::resizeGL(int width, int height)
{
    double ratio = (double) width / (double) height;
    double w = ratio > 1.0 ? 2.0 * ratio : 2.0;
    double h = ratio < 1.0 ? 2.0 / ratio : 2.0;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2.0, w / 2.0, h / 2.0, -h / 2.0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void RouletteWidget::updateAnimation()
{
    // Stop the wheel if it has reached the winner, accounts for overshooting
    if (wheelRotation + spinSpeed >= finalRotation + numSpins * 360.0f)
    {
        wheelRotation = finalRotation;
        spinSpeed = 0.0f;
        spinTimer.stop();
        emit finished();
    }
    // Update wheel rotation
    else
    {
        wheelRotation += spinSpeed;
        spinSpeed += spinAcceleration;
    }

    update();
}
