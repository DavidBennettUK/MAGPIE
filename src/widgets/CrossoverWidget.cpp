#include <QQueue>
#include "CrossoverWidget.h"
#include "../glUtil.h"
#include "../common.h"

using std::min;
using std::max;

CrossoverWidget::CrossoverWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    parent1 = NULL;
    parent2 = NULL;
    child1 = NULL;
    child2 = NULL;
    drawParent1 = NULL;
    drawParent2 = NULL;
    drawChild1 = NULL;
    drawChild2 = NULL;
    crossover1 = NULL;
    crossover2= NULL;
    drawCrossover1 = NULL;
    drawCrossover2 = NULL;
    showChildren = false;
    memset(&crossoverResult, 0, sizeof(CrossoverResult));

    LINE_THICKNESS = 1.0f;
    NODE_WIDTH = 40.0f;
    NODE_HEIGHT = 20.0f;
    LABEL_SIZE = 10.0f;
    MAX_WIDTH = 300.0f;
    MAX_HEIGHT = 150.0f;
    CROSSOVER_SPEED = 3.0f;

    nodeFont = new QFont("Arial", LABEL_SIZE, QFont::Bold);

    drawTreeBuilder = new DrawTreeBuilder(NODE_WIDTH * 1.7f, NODE_HEIGHT * 1.7f);

    setMinimumSize(MAX_WIDTH * 2, MAX_HEIGHT * 2);

    startTimer.setInterval(800);
    endTimer.setInterval(1000);
    connect(&startTimer, SIGNAL(timeout()), this, SLOT(startAnimation()));
    connect(&animationTimer1, SIGNAL(timeout()), this, SLOT(crossoverAnimation1()));
    connect(&animationTimer2, SIGNAL(timeout()), this, SLOT(crossoverAnimation2()));
    connect(&endTimer, SIGNAL(timeout()), this, SIGNAL(finished()));
}

CrossoverWidget::~CrossoverWidget()
{
    safeDelete(drawParent1);
    safeDelete(drawParent2);
    safeDelete(drawChild1);
    safeDelete(drawChild2);
    safeDelete(drawCrossover1);
    safeDelete(drawCrossover2);
    safeDelete(crossover1);
    safeDelete(crossover2);
    safeDelete(nodeFont);
    safeDelete(drawTreeBuilder);
}

void CrossoverWidget::setTrees(Node *parent1, Node *parent2, Node *child1, Node *child2, CrossoverResult crossoverResult)
{
    // Make sure no animations are running
    startTimer.stop();;
    endTimer.stop();
    animationTimer1.stop();
    animationTimer2.stop();

    // Store trees
    this->parent1 = parent1;
    this->parent2 = parent2;
    this->child1 = child1;
    this->child2 = child2;
    this->crossoverResult = crossoverResult;
    showChildren = false;

    // Build draw trees
    drawParent1 = drawTreeBuilder->build(parent1);
    drawParent2 = drawTreeBuilder->build(parent2);
    drawChild1 = drawTreeBuilder->build(child1);
    drawChild2 = drawTreeBuilder->build(child2);

    // Calculate the required zooms for both trees to fit in window
    float zoom1 = calculateZoom(drawParent1);
    float zoom2 = calculateZoom(drawParent2);
    float zoom3 = calculateZoom(drawChild1);
    float zoom4 = calculateZoom(drawChild1);

    // Choose the smallest zoom so both trees fit and are the same size
    zoom = min(min(zoom1, zoom2), min(zoom3, zoom4));

    // Get the crossover points
    crossover1 = parent1->getNode(crossoverResult.point1)->clone();
    crossover2 = parent2->getNode(crossoverResult.point2)->clone();

    // Build crossover draw trees that will be animated
    drawCrossover1 = drawTreeBuilder->build(crossover1);
    drawCrossover2 = drawTreeBuilder->build(crossover2);

    // Calculate begin and end points of crossover animation (left parent to right child)
    DrawNode *s1 = drawParent1->getNode(crossoverResult.point1);
    DrawNode *e1 = drawChild2->getNode(crossoverResult.point2);
    float sx1 = ((s1->getX() - (drawParent1->getBoundsH().x() + (drawParent1->getWidth() / 2.0f))) * zoom) - (MAX_WIDTH / 2.0f);
    float sy1 = ((s1->getY() - (drawParent1->getBoundsV().x() + (drawParent1->getHeight() / 2.0f))) * zoom) - (MAX_HEIGHT / 2.0f);
    float ex1 = ((e1->getX() - (drawChild2->getBoundsH().x() + (drawChild2->getWidth() / 2.0f))) * zoom) + (MAX_WIDTH / 2.0f);
    float ey1 = ((e1->getY() - (drawChild2->getBoundsV().x() + (drawChild2->getHeight() / 2.0f))) * zoom) + (MAX_HEIGHT / 2.0f);
    startPoint1 = QPointF(sx1, sy1);
    currentPosition1 = startPoint1;
    endPoint1 = QPointF(ex1, ey1);

    // Calculate begin and end points of crossover animation (right parent to left child)
    DrawNode *s2 = drawParent2->getNode(crossoverResult.point2);
    DrawNode *e2 = drawChild1->getNode(crossoverResult.point1);
    float sx2 = ((s2->getX() - (drawParent2->getBoundsH().x() + (drawParent2->getWidth() / 2.0f))) * zoom) + (MAX_WIDTH / 2.0f);
    float sy2 = ((s2->getY() - (drawParent2->getBoundsV().x() + (drawParent2->getHeight() / 2.0f))) * zoom) - (MAX_HEIGHT / 2.0f);
    float ex2 = ((e2->getX() - (drawChild1->getBoundsH().x() + (drawChild1->getWidth() / 2.0f))) * zoom) - (MAX_WIDTH / 2.0f);
    float ey2 = ((e2->getY() - (drawChild1->getBoundsV().x() + (drawChild1->getHeight() / 2.0f))) * zoom) + (MAX_HEIGHT / 2.0f);
    startPoint2 = QPointF(sx2, sy2);
    currentPosition2 = startPoint2;
    endPoint2 = QPointF(ex2, ey2);

    // Start animation
    startTimer.start();
}

void CrossoverWidget::initializeGL()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}

void CrossoverWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Crossover lines
    glBegin(GL_QUADS);
    {
        glColor3f(0.7f, 0.0f, 0.0f);
        glUtil::drawLine(startPoint1.x(), startPoint1.y(), currentPosition1.x(), currentPosition1.y(), LINE_THICKNESS);
        glUtil::drawLine(startPoint2.x(), startPoint2.y(), currentPosition2.x(), currentPosition2.y(), LINE_THICKNESS);
    }
    glEnd();

    // Parent 1
    glPushMatrix();
    {
        glTranslatef(-MAX_WIDTH / 2.0f, -MAX_HEIGHT / 2.0f, 0.0f);
        glScalef(zoom, zoom, 1.0f);
        glTranslatef(-(drawParent1->getBoundsH().x() + (drawParent1->getWidth() / 2.0f)),
                     -(drawParent1->getBoundsV().x() + (drawParent1->getHeight() / 2.0f)), 0.0f);

        drawLine(drawParent1, 0);
        drawNode(drawParent1, 0);
        drawLabel(drawParent1, 0);
    }
    glPopMatrix();

    // Parent 2
    glPushMatrix();
    {
        glTranslatef(MAX_WIDTH / 2.0f, -MAX_HEIGHT / 2.0f, 0.0f);
        glScalef(zoom, zoom, 1.0f);
        glTranslatef(-(drawParent2->getBoundsH().x() + (drawParent2->getWidth() / 2.0f)),
                     -(drawParent2->getBoundsV().x() + (drawParent2->getHeight() / 2.0f)), 0.0f);

        drawLine(drawParent2, 0);
        drawNode(drawParent2, 0);
        drawLabel(drawParent2, 0);
    }
    glPopMatrix();

    // Child 1
    if (showChildren)
    {
        glPushMatrix();
        {
            glTranslatef(-MAX_WIDTH / 2.0f, MAX_HEIGHT / 2.0f, 0.0f);
            glScalef(zoom, zoom, 1.0f);
            glTranslatef(-(drawChild1->getBoundsH().x() + (drawChild1->getWidth() / 2.0f)),
                         -(drawChild1->getBoundsV().x() + (drawChild1->getHeight() / 2.0f)), 0.0f);

            drawLine(drawChild1, 0);
            drawNode(drawChild1, 0);
            drawLabel(drawChild1, 0);
        }
        glPopMatrix();

        // Child 2
        glPushMatrix();
        {
            glTranslatef(MAX_WIDTH / 2.0f, MAX_HEIGHT / 2.0f, 0.0f);
            glScalef(zoom, zoom, 1.0f);
            glTranslatef(-(drawChild2->getBoundsH().x() + (drawChild2->getWidth() / 2.0f)),
                         -(drawChild2->getBoundsV().x() + (drawChild2->getHeight() / 2.0f)), 0.0f);

            drawLine(drawChild2, 0);
            drawNode(drawChild2, 0);
            drawLabel(drawChild2, 0);
        }
        glPopMatrix();
    }

    // Crossover 1
    glPushMatrix();
    {
        glTranslatef(currentPosition1.x(), currentPosition1.y(), 0.0f);
        glScalef(zoom, zoom, 1.0f);
        glTranslatef(-drawCrossover1->getX(), 0.0f, 0.0f);

        drawLine(drawCrossover1, 0, true);
        drawNode(drawCrossover1, 0, true);
        drawLabel(drawCrossover1, 0);

        glColor3f(1.0f, 0.0f, 0.0f);

    }
    glPopMatrix();

    // Crossover 2
    glPushMatrix();
    {
        glTranslatef(currentPosition2.x(), currentPosition2.y(), 0.0f);
        glScalef(zoom, zoom, 1.0f);
        glTranslatef(-drawCrossover2->getX(), 0.0f, 0.0f);

        drawLine(drawCrossover2, 0, true);
        drawNode(drawCrossover2, 0, true);
        drawLabel(drawCrossover2, 0);
    }
    glPopMatrix();

    // Headings
    nodeFont->setPointSizeF(16);
    glColor3f(0.0f, 0.0f, 0.0f);
    renderText(5.0, 20.0, "Parents", *nodeFont);
    if (showChildren)
        renderText(5.0, MAX_HEIGHT + 20.0, "Children", *nodeFont);
}

void CrossoverWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2.0f, width / 2.0f, height / 2.0f, -height / 2.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void CrossoverWidget::drawLine(DrawNode *node, int depth, bool highlight)
{
    foreach (DrawNode *child, node->getChildren())
    {
        glBegin(GL_QUADS);
        {
            if (highlight)
                glColor3f(1.0f, 0.0f, 0.0f);
            else
                glColor3f(0.0f, 0.0f, 0.0f);

            glUtil::drawLine(node->getX(), node->getY(), child->getX(), child->getY(), LINE_THICKNESS);
        }
        glEnd();

        drawLine(child, depth + 1, highlight);
    }
}

void CrossoverWidget::drawNode(DrawNode *node, int depth, bool highlight)
{
    glPushMatrix();
    {
        glTranslatef(node->getX(), node->getY(), 0.0f);
        glScalef(NODE_WIDTH, NODE_HEIGHT, 0.0f);

        glBegin(GL_QUADS);
        {
            if (highlight)
                glColor3f(1.0f, 0.0f, 0.0f);
            else if (node->getNode()->getArity() != 0)
                glColor3f(1.0f, 1.0f, 0.0f);
            else
                glColor3f(1.0f, 1.0f, 1.0f);

            glUtil::drawUnitSquare();
        }
        glEnd();
    }
    glPopMatrix();

    foreach (DrawNode *child, node->getChildren())
        drawNode(child, depth + 1, highlight);
}

void CrossoverWidget::drawLabel(DrawNode *node, int depth)
{
    // Calculate the width of the label
    nodeFont->setPointSizeF(LABEL_SIZE);
    QFontMetrics fm(*nodeFont);
    float strWidth = fm.width(node->getNode()->getName());
    float strHeight = LABEL_SIZE;

    // Check if the label is too wide for the node
    // Allow 10% padding either side
    float factor = 1.0f;
    if (strWidth > NODE_WIDTH * 0.8f)
    {
        factor = (NODE_WIDTH * 0.8f) / strWidth;
        strWidth *= factor;
        strHeight *= factor;
    }

    // Render the text using the calculated size
    // renderText crashes when using a font size less than 6, so limit it
    nodeFont->setPointSizeF(max(6.0f, (LABEL_SIZE * factor) * zoom));
    glColor3f(0.0f, 0.0f, 0.0f);
    renderText(node->getX() - strWidth * 0.5f, node->getY() + strHeight * 0.5f,
               0.0f, node->getNode()->getName(), *nodeFont);

    // Draw children labels
    foreach (DrawNode *child, node->getChildren())
        drawLabel(child, depth + 1);
}

float CrossoverWidget::calculateZoom(DrawNode *tree)
{
    float zoom = 1.0f;

    if (tree->getWidth() + NODE_WIDTH * 2.0f > MAX_WIDTH)
        zoom = MAX_WIDTH / (tree->getWidth() + NODE_WIDTH * 2.0f);

    if (zoom * tree->getHeight() > MAX_HEIGHT)
        zoom = zoom * (MAX_HEIGHT / (tree->getHeight() * zoom));

    return zoom;
}

void CrossoverWidget::startAnimation()
{
    animationTimer1.start(15);
    animationTimer2.start(15);
    showChildren = true;
}

void CrossoverWidget::crossoverAnimation1()
{
    float x = endPoint1.x() - startPoint1.x();
    float y = endPoint1.y() - startPoint1.y();
    float length = sqrt(x * x + y * y);

    currentPosition1 += QPointF((x / length) * CROSSOVER_SPEED, (y / length) * CROSSOVER_SPEED);

    if (abs(currentPosition1.x() - endPoint1.x()) < CROSSOVER_SPEED &&
        abs(currentPosition1.y() - endPoint1.y()) < CROSSOVER_SPEED)
    {
        currentPosition1 = endPoint1;
        animationTimer1.stop();

        if (!animationTimer2.isActive() && !endTimer.isActive())
            endTimer.start();
    }

    update();
}

void CrossoverWidget::crossoverAnimation2()
{
    float x = endPoint2.x() - startPoint2.x();
    float y = endPoint2.y() - startPoint2.y();
    float length = sqrt(x * x + y * y);

    currentPosition2 += QPointF((x / length) * CROSSOVER_SPEED, (y / length) * CROSSOVER_SPEED);

    if (abs(currentPosition2.x() - endPoint2.x()) < CROSSOVER_SPEED &&
        abs(currentPosition2.y() - endPoint2.y()) < CROSSOVER_SPEED)
    {
        currentPosition2 = endPoint2;
        animationTimer2.stop();

        if (!animationTimer1.isActive() && !endTimer.isActive())
            endTimer.start();
    }

    update();
}
