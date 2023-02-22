#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    renderer = factory.getRenderer(state.renderer_type);
    format_manager.registerBasicFormats();
    setAudioChannels(0, 2);
    transport_source.setGain(double(state.volunm) / 100);
    setSize (1000, 600);
    auto color = juce::Colours::transparentWhite;
    // set buttons' image
    button_back.setImages(true, true, true, R.get(BACK), 0.8F, color, R.get(BACK), 1.0F, color, R.get(BACK), 0.6F, color);
    button_close.setImages(true, true, true, R.get(CLOSE), 0.8F, color, R.get(CLOSE), 1.0F, color, R.get(CLOSE), 0.6F, color);
    button_forward.setImages(true, true, true, R.get(FORWARD), 0.8F, color, R.get(FORWARD), 1.0F, color, R.get(FORWARD), 0.6F, color);
    button_goto.setImages(true, true, true, R.get(GOTO), 0.8F, color, R.get(GOTO), 1.0F, color, R.get(GOTO), 0.6F, color);
    button_info.setImages(true, true, true, R.get(INFO), 0.8F, color, R.get(INFO), 1.0F, color, R.get(INFO), 0.6F, color);
    button_open.setImages(true, true, true, R.get(OPEN), 0.8F, color, R.get(OPEN), 1.0F, color, R.get(OPEN), 0.6F, color);
    button_pause.setImages(true, true, true, R.get(PLAY), 0.8F, color, R.get(PLAY), 1.0F, color, R.get(PLAY), 0.6F, color);
    button_repeat.setImages(true, true, true, R.get(REPEAT), 0.8F, color, R.get(REPEAT), 1.0F, color, R.get(REPEAT), 0.6F, color);
    button_settings.setImages(true, true, true, R.get(SETTINGS), 0.8F, color, R.get(SETTINGS), 1.0F, color, R.get(SETTINGS), 0.6F, color);
    button_stop.setImages(true, true, true, R.get(STOP), 0.8F, color, R.get(STOP), 1.0F, color, R.get(STOP), 0.6F, color);
    button_volume.setImages(true, true, true, R.get(VOLUME_H), 0.8F, color, R.get(VOLUME_H), 1.0F, color, R.get(VOLUME_H), 0.6F, color);
    // button callbacks
    button_pause.onClick = [this] {
        is_playing = !is_playing;
        pauseSet(is_playing);
    };
    button_stop.onClick = [this] {
        setCurrentTime(0);
        transport_source.setPosition(0);
        pauseSet(false);
    };
    button_forward.onClick = [this] {
        setCurrentTime(transport_source.getCurrentPosition() + state.step);
    };
    button_back.onClick = [this] {
        setCurrentTime(transport_source.getCurrentPosition() - state.step);
    };
    button_repeat.onClick = [this] {
        setCurrentTime(0);
        pauseSet(true);
    };
    button_open.onClick = [this] {
        file_chooser = std::make_unique<juce::FileChooser>("Open File",
            getDir(), "*", false, true, nullptr);
        file_chooser->launchAsync(juce::FileBrowserComponent::FileChooserFlags::openMode | juce::FileBrowserComponent::FileChooserFlags::canSelectFiles,
            [this](const juce::FileChooser& c) {
                auto f = c.getResult();
                if (f != juce::File()) {
                    auto* reader = format_manager.createReaderFor(f);
                    if (reader == nullptr) {
                        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon,
                            "WARNING",
                            "Cannot read file as audio file.");
                        return;
                    }
                    current_file = f.getFullPathName();
                    auto new_source = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
                    transport_source.setSource(new_source.get(), 0, nullptr, reader->sampleRate);
                    reader_source.reset(new_source.release());
                    transport_source.setPosition(0);
                    pauseSet(false);
                    setCurrentTime(0);
                    setTotalTime();
                    info << "File : " << current_file << "\r\n";
                    info << "Length : " << transport_source.getLengthInSeconds() << "\r\n";
                    info << "Format : " << reader->getFormatName() << "\r\n";
                    info << "Channel : " << reader->numChannels << "\r\n";
                    info << "Sample Rate : " << reader->sampleRate << "\r\n";
                    info << "Total Sample : " << reader->lengthInSamples << "\r\n";
                    info << "Bit Per Sample : " << reader->bitsPerSample << "\r\n";
                    info << "Use Float Point : " << ((reader->usesFloatingPointData) ? "true" : "false") << "\r\n";
                    info << "MetaData : {" << "\r\n";
                    for (auto i : reader->metadataValues.getAllKeys()) {
                        info << "    " << i << " : " << (reader->metadataValues)[i] << "\r\n";
                    }
                    info << "}\r\n";
                }
            });
    };
    button_close.onClick = [this] {
        pauseSet(false);
        transport_source.setSource(nullptr);
        reader_source.reset(nullptr);
        transport_source.setPosition(0);
        setCurrentTime(0);
        slider_time.setRange(0, 0.00001);
        current_file.clear();
        info.clear();
    };
    button_goto.onClick = [this,color] {
         auto comp = new JumpComponent([this](double time_jmp,bool confirm) {
        if (confirm) {
            setCurrentTime(time_jmp);
        }
            });
        juce::DialogWindow::LaunchOptions opt;
        opt.dialogTitle = "GOTO";
        opt.dialogBackgroundColour = color;
        opt.content = juce::OptionalScopedPointer<juce::Component>(comp,true);
        opt.useNativeTitleBar = false;
        opt.launchAsync(); 
    };
    button_info.onClick = [this, color] {
        if (current_file.isEmpty()) {
            juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon, "WARNING", "No file.");
            return;
        }
        
        auto comp = new AnalyzeComponent(info);
        juce::DialogWindow::LaunchOptions opt;
        opt.dialogTitle = "INFO";
        opt.dialogBackgroundColour = color;
        opt.content = juce::OptionalScopedPointer<juce::Component>(comp, true);
        opt.useNativeTitleBar = false;
        opt.launchAsync();
    };
    button_settings.onClick = [this, color] {
        auto comp = new SettingsComponent(&state);
        juce::DialogWindow::LaunchOptions opt;
        opt.dialogTitle = "SETTINGS";
        opt.dialogBackgroundColour = color;
        opt.content = juce::OptionalScopedPointer<juce::Component>(comp, true);
        opt.useNativeTitleBar = false;
        opt.launchAsync();
    };
    // set label
    text_time.setText("0:00/0:00", juce::dontSendNotification);

    // set sliders
    slider_volumn.setSliderStyle(juce::Slider::LinearBar);
    slider_volumn.setNormalisableRange(juce::NormalisableRange<double>(0, 100, 0.1));
    slider_volumn.setColour(juce::Slider::trackColourId, juce::Colours::grey);
    slider_volumn.setValue(state.volunm);
    slider_time.setSliderStyle(juce::Slider::LinearHorizontal);
    slider_time.setColour(juce::Slider::trackColourId, juce::Colours::dimgrey);
    slider_time.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    slider_time.setRange(0, 0.00001);
    // sliders callbacks
    volume_callback.reset(new Listener([this](double value) {
        state.volunm = value;
        transport_source.setGain(value / 100);
        }));
    slider_volumn.addListener(volume_callback.get());
    time_callback.reset(new Listener([this](double value) {
        setCurrentTime(value);
        }));
    slider_time.addListener(time_callback.get());
    
    // add buttons
    addAndMakeVisible(button_back);
    addAndMakeVisible(button_close);
    addAndMakeVisible(button_forward);
    addAndMakeVisible(button_goto);
    addAndMakeVisible(button_info);
    addAndMakeVisible(button_open);
    addAndMakeVisible(button_pause);
    addAndMakeVisible(button_repeat);
    addAndMakeVisible(button_settings);
    addAndMakeVisible(button_stop);
    addAndMakeVisible(button_volume);

    // add sliders
    addAndMakeVisible(slider_volumn);
    addAndMakeVisible(slider_time);

    // add labels
    addAndMakeVisible(text_time);


    
    
}

MainComponent::~MainComponent()
{
    volume_callback = nullptr;
    time_callback = nullptr;
    file_chooser = nullptr;
    shutdownAudio();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    auto f = getBounds();
    // draw components
    constexpr int bw = 40;
    constexpr int bh = 40;
    // The buttons are all 40*40

    // bottom of the ui
    button_pause.setBounds(0, f.getHeight() - bh, bw, bh);
    button_stop.setBounds(bw, f.getHeight() - bh, bw, bh);
    button_back.setBounds(bw * 2, f.getHeight() - bh, bw, bh);
    button_forward.setBounds(bw * 3, f.getHeight() - bh, bw, bh);
    button_repeat.setBounds(bw * 4, f.getHeight() - bh, bw, bh);
    constexpr int slider_length = 200;
    constexpr int slider_height = 20;
    constexpr int slider_offset = 20;
    constexpr int slider_blank = 10;
    button_volume.setBounds(f.getWidth() - slider_length - slider_offset - slider_blank - bw, f.getHeight() - bh, bw, bh);
    slider_volumn.setBounds(f.getWidth() - slider_length - slider_offset, f.getHeight() - bh / 2 - slider_height / 2, slider_length, slider_height);
    // top of the ui
    button_open.setBounds(0, 0, bw, bh);
    button_close.setBounds(bw, 0, bw, bh);
    button_goto.setBounds(2 * bw, 0, bw, bh);
    button_settings.setBounds(f.getWidth() - bw, 0, bw, bh);
    button_info.setBounds(f.getWidth() - 2 * bw, 0, bw, bh);
    // main part
    constexpr int margin = 5;
    constexpr int text_width = 100;
    slider_time.setBounds(margin, f.getHeight() - bh - margin - slider_height, f.getWidth() - 3 * margin - text_width , slider_height);
    text_time.setBounds(f.getWidth() - 2 * margin - text_width, f.getHeight() - bh - margin - slider_height, text_width, slider_height);
    renderer.get()->setBounds(0, bh, f.getWidth(), f.getHeight() - bh * 2 - 2 * margin - slider_height);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (reader_source.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }

    transport_source.getNextAudioBlock(bufferToFill);
    juce::AudioSampleBuffer data;
    data.makeCopyOf(*bufferToFill.buffer, false);
    juce::MessageManager::callAsync([this, data]() {
        setCurrentTime(transport_source.getCurrentPosition());
    if (is_playing) {
        renderer.get()->setSample(data);
    }
        });
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transport_source.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::releaseResources()
{
    transport_source.releaseResources();
}

void MainComponent::setuprender()
{
    // add renderer
    juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon,
        "WARNING",
        "The program may crash if your audio device is not open.",
        juce::String(), nullptr,
        juce::ModalCallbackFunction::create([this](int) {
            addAndMakeVisible(renderer.get());
            }));
}

void MainComponent::pauseSet(bool play)
{
    auto color = juce::Colours::transparentWhite;
    if (current_file.isEmpty()) {
        is_playing = false;
        return;
    }
    auto r = play ? PAUSE : PLAY;
    button_pause.setImages(true, true, true, R.get(r), 0.8F, color, R.get(r), 1.0F, color, R.get(r), 0.6F, color);
    is_playing = play;
    if (is_playing) {
        transport_source.start();
    }
    else {
        transport_source.stop();
    }
}

void MainComponent::setCurrentTime(double time)
{
    if (time >= transport_source.getLengthInSeconds()) {
        pauseSet(false);
        transport_source.setPosition(0);
        slider_time.setValue(0, juce::dontSendNotification);
        text_time.setText(timeSFormat(0, transport_source.getLengthInSeconds()),juce::dontSendNotification);
        return;
    }
    if (time < 0) {
        transport_source.setPosition(0);
        slider_time.setValue(0, juce::dontSendNotification);
        text_time.setText(timeSFormat(0, transport_source.getLengthInSeconds()), juce::dontSendNotification);
        return;
    }
    if (abs(time - transport_source.getCurrentPosition()) > 0.001) {
        transport_source.setPosition(time);
    }
    slider_time.setValue(time, juce::dontSendNotification);
    text_time.setText(timeSFormat(time, transport_source.getLengthInSeconds()), juce::dontSendNotification);
}

void MainComponent::setTotalTime()
{
    slider_time.setRange(0, transport_source.getLengthInSeconds());
}

MainComponent::Listener::Listener(std::function<void(double)> callback)
{
    _f = callback;
}

void MainComponent::Listener::sliderValueChanged(juce::Slider* slider)
{
    _f(slider->getValue());
}
