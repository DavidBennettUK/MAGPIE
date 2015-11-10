#include <QtGui>
#include "LawnViewWidget.h"
#include "../common.h"
#include "../glUtil.h"

LawnViewWidget::LawnViewWidget(QWidget *parent) : PlayerWidget(parent)
{
    statsFont = new QFont("Courier", 12, QFont::Bold);
    individual = NULL;
}

LawnViewWidget::~LawnViewWidget()
{
    safeDelete(statsFont);
}

void LawnViewWidget::setIndividual(Individual *individual)
{
    this->individual = dynamic_cast<Lawnmower *>(individual);

    Q_ASSERT(individual);
}

void LawnViewWidget::draw()
{
    update();
}

void LawnViewWidget::drawText()
{
    glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
    this->renderText(5, 15, QString("Moves:").leftJustified(8, ' ') +
                            QString::number(individual->getMoves()), *statsFont);
    this->renderText(5, 32, QString("Points: ").leftJustified(8, ' ') +
                            QString::number(individual->getPoints()), *statsFont);
}

void LawnViewWidget::drawLawn()
{
    Environment *environment = individual->getEnvironment();

    // Draw the grass
    for (int i = 0; i < environment->getWidth(); i++)
    {
        for (int j = 0; j < environment->getHeight(); j++)
        {
            glPushMatrix();
            {
                glTranslatef(i + 0.5f - environment->getWidth() / 2.0,
                             j + 0.5f - environment->getHeight() / 2.0, 0.0f);

                glBegin(GL_QUADS);
                {
                    if (environment->numMows(i,j) == 0)
                        glColor3f(0.0f, 0.7f, 0.0f);
                    else if (environment->numMows(i,j) == 1)
                        glColor3f(0.0f, 0.9f, 0.0f);
                    if (environment->numMows(i,j) == 2)
                        glColor3f(0.1f, 1.0f, 0.1f);
                    if (environment->numMows(i,j) >= 3)
                        glColor3f(0.3f, 1.0f, 0.15f);

                    glUtil::drawUnitSquare();
                }
                glEnd();
            }
            glPopMatrix();
        }
    }
}

void LawnViewWidget::drawLawnMower()
{
    Environment *environment = individual->getEnvironment();

    // Draw the lawnmower
    glPushMatrix();
    {
        glTranslatef(individual->getX() + 0.5f - environment->getWidth() / 2.0,
                     individual->getY() + 0.5f - environment->getHeight() / 2.0, 0.0f);
        glRotatef(individual->getFacing() * 90.0f, 0.0f, 0.0f, 1.0f);

        glBegin(GL_QUADS);
        {
            glColor3f(1.0f, 0.5f, 0.0f);
            glVertex2f(-0.25f, -0.5f);
            glVertex2f(0.25f, -0.5f);
            glVertex2f(0.5f, 0.5f);
            glVertex2f(-0.5f, 0.5f);
        }
        glEnd();
    }
    glPopMatrix();
}

void LawnViewWidget::drawGrid()
{
    Environment *environment = individual->getEnvironment();

    // Draw the grid
    for (int i = 0; i < environment->getWidth(); i++)
    {
        for (int j = 0; j < environment->getHeight(); j++)
        {
            glPushMatrix();
            {
                glTranslatef(i + 0.5f - environment->getWidth() / 2.0,
                             j + 0.5f - environment->getHeight() / 2.0, 0.0f);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glLineWidth(1.3f);

                glBegin(GL_QUADS);
                {
                    glColor3f(0.0f, 0.5f, 0.0f);

                    glUtil::drawUnitSquare();
                }
                glEnd();

                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            glPopMatrix();
        }
    }
}

void LawnViewWidget::initializeGL()
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
}

void LawnViewWidget::paintGL()
{
    Q_ASSERT(individual);

    glClear(GL_COLOR_BUFFER_BIT);

    drawLawn();
    drawGrid();
    drawLawnMower();
    drawText();
}

void LawnViewWidget::resizeGL(int width, int height)
{
    Q_ASSERT(individual);

    Environment *env = individual->getEnvironment();
    int gridWidth = env->getWidth();
    int gridHeight = env->getHeight();

    double ratio = (double) width / (double) height;
    double w = ratio > 1 ? gridWidth * ratio : gridWidth;
    double h = ratio < 1 ? gridHeight / ratio : gridHeight;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2.0, w / 2.0, h / 2.0, -h / 2.0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
