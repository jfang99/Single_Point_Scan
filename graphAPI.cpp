#include "graphAPI.h"
#include "custom_framelistener.h"

//read MVX file
void graphAPI::readMvx(OfficeDesk* InputDesk)
{
    MVGraphAPI::PluginsLoader::LoadPluginsInFolder(MVGraphAPI::Utils::GetAppExeDirectory(), false, false);

    auto spFrameListener = std::make_shared<AutoSequentialGraphRunner_CustomFrameListener>();

    //define the callback function that sends data to OpenGL and paints
    spFrameListener->SetCallBack(
        std::bind(
        &graphAPI::paint, this, InputDesk,
        std::placeholders::_1, std::placeholders::_2,
        std::placeholders::_3, std::placeholders::_4,
        std::placeholders::_5, std::placeholders::_6));

    MVGraphAPI::AsyncFrameAccessGraphNode frameAccess(spFrameListener.get());

    MVGraphAPI::ManualGraphBuilder graphBuilder;
    graphBuilder
        << MVGraphAPI::Mvx2FileReaderGraphNode("C:/Users/jeffe/Documents/Visual Studio 2015/Projects/OfficeDesk/record.mvx")
        << MVGraphAPI::AutoDecompressorGraphNode()
        << frameAccess;

    std::shared_ptr<MVGraphAPI::Graph> spGraph = std::shared_ptr<MVGraphAPI::Graph>(graphBuilder.CompileGraphAndReset());

    auto spGraphRunner = std::make_shared<MVGraphAPI::AutoSequentialGraphRunner>(spGraph.get());
    spGraphRunner->Play(MVGraphAPI::RunnerPlaybackMode::RPM_FORWARD_LOOP, true);
}

void graphAPI::paint(OfficeDesk* target, float* vertex, unsigned char* color, float* normal, int vertex_count, int color_count, int normal_count)
{
    (*target).lock.lock();

    Sleep(30);

    //send data to OfficeDesk(OpenGL)
    m_vertex = vertex;
    m_color = color;
    m_normal = normal;

    m_vertex_count = vertex_count;
    m_color_count = color_count;
    m_normal_count = normal_count;

    std::vector<float> vec_vertex;
    std::vector<float> vec_color;
    std::vector<float> vec_normal;

    vec_vertex.resize(m_vertex_count * 3);
    for (int i = 0; i < (m_vertex_count * 3); i++)
    {
        vec_vertex[i] = (*(m_vertex + i));
    }

    vec_color.resize(m_color_count * 3);
    for (int i = 0; i < (m_color_count * 3); i++)
    {
        vec_color[i] = (*(m_color + i)) / 255.0f;
    }

    vec_normal.resize(m_normal_count * 3);
    for (int i = 0; i < (m_normal_count * 3); i++)
    {
        vec_normal[i] = (*(m_normal + i));
    }

    //relocate to center
    float fx = 0;
    float fy = 0;
    float fz = 0;

    for (int i = 0; i < vec_vertex.size(); i = i + 3)
    {
        fx += vec_vertex[i];
        fy += vec_vertex[i + 1];
        fz += vec_vertex[i + 2];
    }

    fx /= vec_vertex.size() / 3;
    fy /= vec_vertex.size() / 3;
    fz /= vec_vertex.size() / 3;

    for (int i = 0; i < vec_vertex.size(); i = i + 3)
    {
        vec_vertex[i] -= fx;
        vec_vertex[i + 1] -= fy;
        vec_vertex[i + 2] -= fz;
    }

    (*target).set_vec_vertex(vec_vertex);
    (*target).set_vec_color(vec_color);
    (*target).set_vec_normal(vec_normal);

    (*target).lock.unlock();

    //paint
    (*target).update();
}