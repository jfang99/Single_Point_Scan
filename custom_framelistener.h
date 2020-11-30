#pragma once
#include <MVGraph_SimpleAPI/framedata/FrameMeshExtractor.h>
#include <MVGraphAPI/frameaccess/Frame.h>
#include <MVGraphAPI/MVGraphAPI.h>
#include <MVGraph_SimpleAPI/mesh/MeshData.h>
#include <MVGraphAPI/core/Graph.h>
#include <MVGraphAPI/core/SourceInfo.h>
#include <MVGraph_SimpleAPI/SimpleDataLayersGuids.h>
#include <MVGraphAPI/core/ManualGraphBuilder.h>
#include <MVGraphAPI/frameaccess/AsyncFrameAccessGraphNode.h>
#include <MVGraph_SimpleAPI/graphnodes/Mvx2FileReaderGraphNode.h>
#include <MVGraph_SimpleAPI/graphnodes/AutoDecompressorGraphNode.h>
#include <MVGraphAPI/runners/AutoSequentialGraphRunner.h>
#include <MVGraphAPI/frameaccess/IFrameListener.h>
#include <MVGraphAPI/utils/PluginsLoader.h>
#include <MVGraphAPI/utils/Utils.h>
#include <functional>
#include <iostream>
#include <iomanip>
#include <memory>

typedef std::function<void(float*, unsigned char*, float*, int, int, int)> CallBackPtr;

//class interface of "custom framelistener"
class AutoSequentialGraphRunner_CustomFrameListener : public MVGraphAPI::IFrameListener
{
public:
    //callback function to get data from the frame
    virtual void OnFrameProcessed(MVGraphAPI::Frame* pFrame) override;

    void SetCallBack(CallBackPtr callback);

private:
    int _processedUpdatesCount = 0;

    CallBackPtr m_callback;
};