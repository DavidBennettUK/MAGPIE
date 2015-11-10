#include <QtGui>
#include "AntViewWidget.h"
#include "../common.h"
#include "../glUtil.h"

AntViewWidget::AntViewWidget(QWidget *parent) : PlayerWidget(parent)
{
    statsFont = new QFont("Courier", 12, QFont::Bold);
    ant = NULL;
}

AntViewWidget::~AntViewWidget()
{
    safeDelete(statsFont);
}

void AntViewWidget::setIndividual(Individual *individual)
{
    this->ant = dynamic_cast<Ant *>(individual);

    Q_ASSERT(individual);
}

void AntViewWidget::draw()
{
    update();
}

void AntViewWidget::drawText()
{
    glColor4f(0.95f, 0.95f, 0.95f, 0.7f);
    this->renderText(5, 15, QString("Moves:").leftJustified(8, ' ') +
                            QString::number(ant->getMoves()), *statsFont);
    this->renderText(5, 32, QString("Points: ").leftJustified(8, ' ') +
                            QString::number(ant->getPoints()), *statsFont);
}

void AntViewWidget::drawPellets()
{
    // Draw the pellets
    for (int i = 0; i < ant->getGridWidth(); i++)
    {
        for (int j = 0; j < ant->getGridHeight(); j++)
        {
            glPushMatrix();
            {
                glTranslatef(i + 0.5f - ant->getGridWidth() / 2.0,
                             j + 0.5f - ant->getGridHeight() / 2.0, 0.0f);

                glBegin(GL_QUADS);
                {
                    if (ant->isFoodAt(i,j))
                        glColor3f(0.6f, 0.3f, 0.1f);
                    else if (ant->hasVisited(i,j))
                        glColor3f(0.1f, 0.6f, 0.2f);
                    else
                        glColor3f(0.1f, 0.8f, 0.2f);

                    glUtil::drawUnitSquare();
                }
                glEnd();
            }
            glPopMatrix();
        }
    }
}

void AntViewWidget::drawAnt()
{
    // Draw the ant
    glPushMatrix();
    {
        glTranslatef(ant->getX() + 0.5f - ant->getGridWidth() / 2.0,
                     ant->getY() + 0.5f - ant->getGridHeight() / 2.0, 0.0f);
        glRotatef(ant->getFacing() * 90.0f, 0.0f, 0.0f, 1.0f);
        glScalef(0.25f, 0.25f, 1.0f);
        glColor3f(0.0f, 0.0f, 0.0f);

        glPushMatrix();
        {
            glTranslatef(0.0f, -1.0f, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
            {
                glUtil::drawUnitCircle();
            }
            glEnd();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(0.5f, -1.5f, 0.0f);
            glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
            glScalef(2.5f, 0.2f, 1.0f);
            glBegin(GL_QUADS);
            {
                glUtil::drawUnitSquare();
            }
            glEnd();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(-0.5f, -1.5f, 0.0f);
            glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
            glScalef(2.5f, 0.2f, 1.0f);
            glBegin(GL_QUADS);
            {
                glUtil::drawUnitSquare();
            }
            glEnd();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(0.0f, 1.0f, 0.0f);
            glScalef(1.0f, 2.0f, 1.0f);
            glBegin(GL_QUADS);
            {
                glUtil::drawUnitSquare();
            }
            glEnd();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(0.0f, 1.5f, 0.0f);
            glScalef(2.5f, 0.2f, 1.0f);
            glBegin(GL_QUADS);
            {
                glUtil::drawUnitSquare();
            }
            glEnd();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(0.0f, 0.8f, 0.0f);
            glScalef(2.5f, 0.2f, 1.0f);
            glBegin(GL_QUADS);
            {
                glUtil::drawUnitSquare();
            }
            glEnd();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(0.0f, 0.1f, 0.0f);
            glScalef(2.5f, 0.2f, 1.0f);
            glBegin(GL_QUADS);
            {
                glUtil::drawUnitSquare();
            }
            glEnd();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void AntViewWidget::drawGrid()
{
    // Draw the grid
    for (int i = 0; i < ant->getGridWidth(); i++)
    {
        for (int j = 0; j < ant->getGridHeight(); j++)
        {
            glPushMatrix();
            {
                glTranslatef(i + 0.5f - ant->getGridWidth() / 2.0,
                             j + 0.5f - ant->getGridHeight() / 2.0, 0.0f);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glLineWidth(1.0f);

                glBegin(GL_QUADS);
                {
                    glColor3f(0.2f, 0.6f, 0.2f);

                    glUtil::drawUnitSquare();
                }
                glEnd();

                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            glPopMatrix();
        }
    }
}

void AntViewWidget::initializeGL()
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
}

void AntViewWidget::paintGL()
{
    Q_ASSERT(ant);

    glClear(GL_COLOR_BUFFER_BIT);

    drawPellets();
    drawGrid();
    drawAnt();
    drawText();
}

void AntViewWidget::resizeGL(int width, int height)
{
    Q_ASSERT(ant);

    int gridWidth = ant->getGridWidth();
    int gridHeight = ant->getGridHeight();

    double ratio = (double) width / (double) height;
    double w = ratio > 1 ? gridWidth * ratio : gridWidth;
    double h = ratio < 1 ? gridHeight / ratio : gridHeight;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2.0, w / 2.0, h / 2.0, -h / 2.0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
