#pragma once

#include <JuceHeader.h>
#include "Render/Interface.h"
#include "Render/Factory.h"
#include "Utils/AppState.h"
#include "Utils/Resources.h"
#include "JumpComponent.h"
#include "AnalyzeComponent.h"
#include "SettingsComponent.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    AppState state;
    void setuprender();
private:
    //==============================================================================
    // Your private member variables go here...

    juce::ImageButton button_repeat;
    juce::ImageButton button_back;
    juce::ImageButton button_pause;
    juce::ImageButton button_stop;
    juce::ImageButton button_forward;
    juce::ImageButton button_info;
    juce::ImageButton button_goto;
    juce::ImageButton button_open;
    juce::ImageButton button_close;
    juce::ImageButton button_settings;
    juce::ImageButton button_volume;
    juce::Slider slider_time;
    juce::Slider slider_volumn;
    juce::Label text_time;
    std::unique_ptr<IRenderer> renderer;
    bool is_playing = false;
    juce::String current_file;
    juce::String info;
    // callbacks
    void pauseSet(bool play);
    void setCurrentTime(double time);
    void setTotalTime();
    class Listener : public juce::Slider::Listener {
    public:
        Listener(std::function<void (double)> callback);
        virtual void sliderValueChanged(juce::Slider* slider) override;
    private:
        std::function<void (int)> _f;
    };
    std::unique_ptr<Listener> volume_callback;
    std::unique_ptr<Listener> time_callback;
    std::unique_ptr<juce::FileChooser> file_chooser;
    juce::AudioFormatManager format_manager;
    std::unique_ptr<juce::AudioFormatReaderSource> reader_source;
    juce::AudioTransportSource transport_source;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
