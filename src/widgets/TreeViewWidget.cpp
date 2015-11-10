#include <QStack>
#include "TreeViewWidget.h"
#include "../gp/Node.h"
#include "../gp/Scenario.h"
#include "../DrawTreeBuilder.h"
#include "../common.h"
#include "../glUtil.h"

using std::max;

TreeViewWidget::TreeViewWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    individual = NULL;
    tree = NULL;

    offsetX = 0;
    offsetY = 0;
    lastX = 0;
    lastY = 0;
    zoom = 1.0f;

    LINE_THICKNESS = 1.0f;
    NODE_WIDTH = 50.0f;
    NODE_HEIGHT = 20.0f;
    LABEL_SIZE = 10.0f;
    ZOOM_MIN = 0.2f;
    ZOOM_MAX = 10.0f;
    MAX_WIDTH = 700.0f;
    MAX_HEIGHT = 500.0f;

    nodeFont = new QFont("Arial", LABEL_SIZE, QFont::Bold);

    drawTreeBuilder = new DrawTreeBuilder(NODE_WIDTH * 1.7f, NODE_HEIGHT * 1.7f);

    setCursor(QCursor(Qt::OpenHandCursor));
}

TreeViewWidget::~TreeViewWidget()
{
    safeDelete(tree);
    safeDelete(nodeFont);
    safeDelete(drawTreeBuilder);
}

void TreeViewWidget::setIndividual(Individual *individual)
{
    if (this->individual)
        safeDelete(this->individual);

    this->individual = individual;

    tree = drawTreeBuilder->build(individual->getRootNode());

    // Zoom out if tree is too wide to fit in the maximum size window
    if (tree->getWidth() > MAX_WIDTH)
    {
        zoom = MAX_WIDTH / tree->getWidth();
        setMinimumWidth(MAX_WIDTH + (zoom * NODE_WIDTH * 2.0f));
        setMinimumHeight(zoom * (tree->getHeight() + NODE_HEIGHT * 2.0f));
    }

    // Zoom out if tree is too high to fit in the maximum size window
    if (zoom * tree->getHeight() > MAX_HEIGHT)
    {
        zoom = zoom * (MAX_HEIGHT / (tree->getHeight() * zoom));
        setMinimumWidth(zoom * (tree->getWidth() + NODE_WIDTH * 2.0f));
        setMinimumHeight(zoom * (tree->getHeight() + NODE_HEIGHT * 2.0f));
    }

    // Tree will fit in window at normal zoom
    if (minimumWidth() == 0 && minimumHeight() == 0)
    {
        setMinimumWidth(tree->getWidth() + NODE_WIDTH * 2.0f);
        setMinimumHeight(tree->getHeight() + NODE_HEIGHT * 2.0f);
    }
}

void TreeViewWidget::initializeGL()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}

void TreeViewWidget::paintGL()
{
    Q_ASSERT(individual);

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    {
        glScalef(zoom, zoom, 1.0f);
        glTranslatef(-(tree->getBoundsH().x() + (tree->getWidth() / 2.0f)), NODE_HEIGHT, 0.0f);
        glTranslatef(offsetX, offsetY, 0.0f);

        drawLine(tree, 0);
        drawNode(tree, 0);
        drawLabel(tree, 0);
    }
    glPopMatrix();
}

void TreeViewWidget::resizeGL(int width, int height)
{
    zoom = findIdealZoom(width, height);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2, width / 2, height, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void TreeViewWidget::mousePressEvent(QMouseEvent *event)
{
    lastX = event->x();
    lastY = event->y();
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void TreeViewWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(QCursor(Qt::OpenHandCursor));
}

void TreeViewWidget::mouseMoveEvent(QMouseEvent *event)
{
    // Calculate amount to move the camera, scale back if zoomed in so
    // it doesn't move as much
    offsetX += (event->x() - lastX) * (1.0f / zoom);
    offsetY += (event->y() - lastY) * (1.0f / zoom);

    // Remember the last mouse position to calculate offset next time
    lastX = event->x();
    lastY = event->y();

    update();
}

void TreeViewWidget::wheelEvent(QWheelEvent *event)
{
    zoom += event->delta() / 1000.0f;

    if (zoom < ZOOM_MIN)
        zoom = ZOOM_MIN;
    else if (zoom > ZOOM_MAX)
        zoom = ZOOM_MAX;

    update();
}

void TreeViewWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    offsetX = 0;
    offsetY = 0;
    zoom = findIdealZoom(this->width(), this->height());

    update();
}

void TreeViewWidget::drawLine(DrawNode *node, int depth)
{
    foreach (DrawNode *child, node->getChildren())
    {
        glBegin(GL_QUADS);
        {
            glColor3f(0.0f, 0.0f, 0.0f);
            glUtil::drawLine(node->getX(), node->getY(), child->getX(), child->getY(), LINE_THICKNESS);
        }
        glEnd();

        drawLine(child, depth + 1);
    }
}

void TreeViewWidget::drawNode(DrawNode *node, int depth)
{
    glPushMatrix();
    {
        glTranslatef(node->getX(), node->getY(), 0.0f);
        glScalef(NODE_WIDTH, NODE_HEIGHT, 0.0f);

        glBegin(GL_QUADS);
        {
            if (node->getNode()->getArity() != 0)
                glColor3f(1.0f, 1.0f, 0.0f);
            else
                glColor3f(1.0f, 1.0f, 1.0f);

            glUtil::drawUnitSquare();
        }
        glEnd();
    }
    glPopMatrix();

    foreach (DrawNode *child, node->getChildren())
        drawNode(child, depth + 1);
}

void TreeViewWidget::drawLabel(DrawNode *node, int depth)
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
    if (LABEL_SIZE * factor * zoom >= 6.0f)
    {
        nodeFont->setPointSizeF(LABEL_SIZE * factor * zoom);
        glColor3f(0.0f, 0.0f, 0.0f);
        renderText(node->getX() - strWidth * 0.5f, node->getY() + strHeight * 0.5f,
                   0.0f, node->getNode()->getName(), *nodeFont);
    }

    // Draw children labels
    foreach (DrawNode *child, node->getChildren())
        drawLabel(child, depth + 1);
}

float TreeViewWidget::findIdealZoom(int width, int height)
{
    float zoom = (float) width / (tree->getWidth() + NODE_WIDTH * 2.0f);

    if (zoom * (tree->getHeight() + NODE_HEIGHT * 2.0F) > height)
        zoom = zoom * ((float) height / ((tree->getHeight() + NODE_HEIGHT * 2.0F) * zoom));

    return zoom;
}
