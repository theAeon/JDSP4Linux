#ifndef PIPEWIREAUDIOSERVICE_H
#define PIPEWIREAUDIOSERVICE_H

#include "PwPipelineManager.h"
#include "FilterContainer.h"
#include "PwAppManager.h"
#include "IAudioService.h"

#include "IOutputDevice.h"

#include <memory>
#include <QObject>

class PwJamesDspPlugin;

class PipewireAudioService : public IAudioService
{
    Q_OBJECT
    Q_INTERFACES(IAudioService)

public:
    PipewireAudioService();
    ~PipewireAudioService();

public slots:
    void onAppConfigUpdated(const AppConfig::Key& key, const QVariant& value);

    void update(DspConfig* config) override;
    void reloadService() override;

    DspHost* host() override;
    IAppManager* appManager() override;
    std::vector<IOutputDevice> sinkDevices() override;
    DspStatus status() override;

private:
    const std::string log_tag = "PipewireAudioService: ";

    std::unique_ptr<PwPipelineManager> mgr;
    std::unique_ptr<PwAppManager> appMgr;
    std::unique_ptr<FilterContainer> effects;
    PwJamesDspPlugin* plugin;

};

#endif // PIPEWIREAUDIOSERVICE_H
