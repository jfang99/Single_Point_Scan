#include "custom_framelistener.h"

//receive data from each frame
void AutoSequentialGraphRunner_CustomFrameListener::OnFrameProcessed(MVGraphAPI::Frame * pFrame)
{
    float* vertex = nullptr;
    unsigned char* color = nullptr;
    float* normal = nullptr;

    int vertex_count = 0;
    int color_count = 0;
    int normal_count = 0;

    std::cout << "\nUpdate " << std::setw(2) << std::setfill('0') << (++_processedUpdatesCount) << ":" << std::endl;

    uint32_t numStreams = pFrame->GetNumStreams();

    for (uint32_t streamIndex = 0; streamIndex < numStreams; ++streamIndex)
    {
        pFrame->ActivateStreamWithIndex(streamIndex);

        std::shared_ptr<MVGraphAPI::MeshData> spFrameMesh(MVGraphAPI::FrameMeshExtractor::GetMeshData(pFrame));

        vertex = (float*)(spFrameMesh->GetVertices());
        vertex_count = (int)(spFrameMesh->GetNumVertices());

        color = (unsigned char*)(spFrameMesh->GetColorsRGB());
        color_count = (int)(spFrameMesh->GetNumColors());

        normal = (float*)spFrameMesh->GetNormals();
        normal_count = (int)(spFrameMesh->GetNumNormals());
    }

    m_callback(vertex, color, normal, vertex_count, color_count, normal_count);

    delete pFrame;
}

void AutoSequentialGraphRunner_CustomFrameListener::SetCallBack(CallBackPtr callback)
{
    m_callback = callback;
}