#include <QQueue>
#include "MutationWidget.h"
#include "../glUtil.h"
#include "../common.h"

using std::min;
using std::max;

MutationWidget::MutationWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    this->parent = NULL;
    child = NULL;
    mutation = NULL;
    mutationPoint = 0;
    drawParent = NULL;
    drawChild = NULL;

    zoom = 1.0f;

    LINE_THICKNESS = 1.0f;
    NODE_WIDTH = 40.0f;
    NODE_HEIGHT = 20.0f;
    LABEL_SIZE = 10.0f;
    MAX_WIDTH = 300.0f;
    MAX_HEIGHT = 150.0f;

    nodeFont = new QFont("Arial", LABEL_SIZE, QFont::Bold);

    drawTreeBuilder = new DrawTreeBuilder(NODE_WIDTH * 1.7f, NODE_HEIGHT * 1.7f);

    setMinimumSize(MAX_WIDTH, MAX_HEIGHT * 2);

    startTimer.setInterval(2000);
    connect(&startTimer, SIGNAL(timeout()), this, SIGNAL(finished()));
}

MutationWidget::~MutationWidget()
{
    safeDelete(drawTreeBuilder);
    safeDelete(drawParent);
    safeDelete(drawChild);
    safeDelete(nodeFont);
}

void MutationWidget::setTrees(Node *parent, Node *child, int mutationPoint)
{
    // Store trees
    this->parent = parent;
    this->child = child;
    this->mutationPoint = mutationPoint;

    // Build draw trees
    drawParent = drawTreeBuilder->build(parent);
    drawChild = drawTreeBuilder->build(child);

    // Calculate the required zooms for both trees to fit in window
    float zoom1 = calculateZoom(drawParent);
    float zoom2 = calculateZoom(drawChild);

    // Choose the smallest zom so both trees fit and ar the same size
    zoom = min(zoom1, zoom2);

    // Get mutation node
    mutation = child->getNode(mutationPoint);

    startTimer.start();
}

void MutationWidget::initializeGL()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
}

void MutationWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Parent
    glPushMatrix();
    {
        glTranslatef(0.0f, -MAX_HEIGHT / 2.0f, 0.0f);
        glScalef(zoom, zoom, 1.0f);
        glTranslatef(-(drawParent->getBoundsH().x() + (drawParent->getWidth() / 2.0f)),
                     -(drawParent->getBoundsV().x() + (drawParent->getHeight() / 2.0f)), 0.0f);

        drawLine(drawParent, 0);
        drawNode(drawParent, 0);
        drawLabel(drawParent, 0);
    }
    glPopMatrix();

    // Child
    glPushMatrix();
    {
        glTranslatef(0.0f, MAX_HEIGHT / 2.0f, 0.0f);
        glScalef(zoom, zoom, 1.0f);
        glTranslatef(-(drawChild->getBoundsH().x() + (drawChild->getWidth() / 2.0f)),
                     -(drawChild->getBoundsV().x() + (drawChild->getHeight() / 2.0f)), 0.0f);

        drawLine(drawChild, 0);
        drawNode(drawChild, 0);
        drawLabel(drawChild, 0);
    }
    glPopMatrix();

    // Headings
    nodeFont->setPointSizeF(16);
    glColor3f(0.0f, 0.0f, 0.0f);
    renderText(5.0, 20.0, "Parent", *nodeFont);
    renderText(5.0, MAX_HEIGHT + 20.0, "Child", *nodeFont);
}

void MutationWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2.0f, width / 2.0f, height / 2.0f, -height / 2.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void MutationWidget::drawLine(DrawNode *node, int depth)
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

void MutationWidget::drawNode(DrawNode *node, int depth)
{
    glPushMatrix();
    {
        glTranslatef(node->getX(), node->getY(), 0.0f);
        glScalef(NODE_WIDTH, NODE_HEIGHT, 0.0f);

        glBegin(GL_QUADS);
        {
            // Highlight mutation node on child - TODO a nicer way of doing this?
            if (node->getNode() == mutation)
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
        drawNode(child, depth + 1);
}

void MutationWidget::drawLabel(DrawNode *node, int depth)
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

float MutationWidget::calculateZoom(DrawNode *tree)
{
    float zoom = 1.0f;

    if (tree->getWidth() + NODE_WIDTH * 2.0f > MAX_WIDTH)
        zoom = MAX_WIDTH / (tree->getWidth() + NODE_WIDTH * 2.0f);

    if (zoom * tree->getHeight() > MAX_HEIGHT)
        zoom = zoom * (MAX_HEIGHT / (tree->getHeight() * zoom));

    return zoom;
}
