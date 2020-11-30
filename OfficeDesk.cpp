#include "OfficeDesk.h"
#include "custom_framelistener.h"

OfficeDesk::OfficeDesk(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setGeometry(400, 400, 640, 480);
    m_fScale = 0.0f;
    m_matModelView = glm::mat4(
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

OfficeDesk::~OfficeDesk()
{
}

void OfficeDesk::initializeGL()
{
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
}

void OfficeDesk::paintGL()
{
    lock.lock();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glm::vec4 vecX = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * m_matModelView;
    glm::vec4 vecY = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) * m_matModelView;

    m_matModelView = glm::rotate(m_matModelView, m_fRotateX * 0.1f, glm::vec3(vecX.x, vecX.y, vecX.z));
    m_matModelView = glm::rotate(m_matModelView, m_fRotateY * 0.1f, glm::vec3(vecY.x, vecY.y, vecY.z));

    glm::vec4 view(0, 0, 1000 + m_fScale, 1.0);
    view = view * m_matModelView;

    glm::vec4 up(0, 1, 0, 1.0);
    up = up * m_matModelView;

    gluLookAt(view.x, view.y, view.z, 0, 0, 0, up.x, up.y, up.z);

    m_fRotateX = 0.0f;
    m_fRotateY = 0.0f;

    glBegin(GL_POINTS);
    for (int i = 0; i < vec_vertex.size(); i = i + 3)
    {
        glColor3f(vec_color[i], vec_color[i + 1], vec_color[i + 2]);
        glNormal3f(vec_normal[i], vec_normal[i + 1], vec_normal[i + 2]);
        glVertex3f(vec_vertex[i], vec_vertex[i + 1], vec_vertex[i + 2]);
    }
    glEnd();

    lock.unlock();
}

void OfficeDesk::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0f, (float)width / (float)height, 1, 2000);
}

void OfficeDesk::set_vec_vertex(std::vector<float> input)
{
    vec_vertex = input;
}

void OfficeDesk::set_vec_color(std::vector<float> input)
{
    vec_color = input;
}

void OfficeDesk::set_vec_normal(std::vector<float> input)
{
    vec_normal = input;
}

//use mouse move event to rotate
void OfficeDesk::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_fIniX = event->globalX();
        m_fIniY = event->globalY();
        m_fDx = 0.0f;
        m_fDy = 0.0f;
    }

    update();
}

void OfficeDesk::mouseMoveEvent(QMouseEvent *event)
{
    m_fDx = event->globalX() - m_fIniX;
    m_fDy = event->globalY() - m_fIniY;

    if (event->buttons() == Qt::LeftButton)
    {
        m_fRotateX = 0.2 * m_fDy;
        m_fRotateY = 0.2 * m_fDx;
        update();
        m_fIniX = event->globalX();
        m_fIniY = event->globalY();
    }

    update();
}


