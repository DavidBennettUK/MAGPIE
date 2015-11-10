#include "LawnViewMultiWidget.h"
#include "../glUtil.h"

void LawnViewMultiWidget::drawText()
{
    LawnViewWidget::drawText();

    this->renderText(5, 49, QString("Hits: ").leftJustified(8, ' ') +
                            QString::number(((LawnmowerMulti *) individual)->getHits()), *statsFont);
}

void LawnViewMultiWidget::drawLawn()
{
    LawnViewWidget::drawLawn();

    EnvironmentMulti *environment = ((LawnmowerMulti *) individual)->getEnvironment();

    // Draw the obstacles
    for (int i = 0; i < environment->getWidth(); i++)
    {
        for (int j = 0; j < environment->getHeight(); j++)
        {
            if (environment->isObstacle(i,j))
            {
                glPushMatrix();
                {
                    glTranslatef(i + 0.5f - environment->getWidth() / 2.0,
                                 j + 0.5f - environment->getHeight() / 2.0, 0.0f);

                    glBegin(GL_QUADS);
                    {
                        glColor3f(1.0f, 0.0f, 0.0f);

                        glVertex2f(0.0f, -0.5f);
                        glVertex2f(0.5f, -0.0f);
                        glVertex2f(0.0f, 0.5f);
                        glVertex2f(-0.5f, 0.0f);
                    }
                    glEnd();
                }
                glPopMatrix();
            }
        }
    }
}
