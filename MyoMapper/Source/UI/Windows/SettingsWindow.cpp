#include "../JuceLibraryCode/JuceHeader.h"
#include "SettingsWindow.h"
#include "../../Application.h"

bool SettingsWindow::startButtonClicked;
bool SettingsWindow::featureButtonClicked;

SettingsWindow::SettingsWindow()
:
hostAddress("127.0.0.1")
{
    mainOscSendLabel.setJustificationType (Justification::horizontallyCentred);
    mainOscSendLabel.setText ("Main OSC Sender", dontSendNotification);
    addAndMakeVisible (mainOscSendLabel);
    
    mainOscSenderSlider.addListener (this);
    mainOscSenderSlider.setRange (1, 9999, 1);
    mainOscSenderSlider.setValue (Application::getApp().getOscSettingsTree().getChildWithName("SendPort").getProperty ("senderPort"));
    mainOscSenderSlider.setSliderStyle (Slider::IncDecButtons);
    mainOscSenderSlider.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
    addAndMakeVisible (mainOscSenderSlider);
    
    mainOscSendPortLabel.setLookAndFeel (&laf);
    mainOscSendPortLabel.setJustificationType (Justification::left);
    mainOscSendPortLabel.setText ("Port:", dontSendNotification);
    mainOscSendPortLabel.setTooltip("Main OSC sender port number.");
    addAndMakeVisible (mainOscSendPortLabel);
    
    
    mlOscSendLabel.setJustificationType (Justification::horizontallyCentred);
    mlOscSendLabel.setText ("ML OSC Sender", dontSendNotification);
    addAndMakeVisible (mlOscSendLabel);
    
    mlOscSenderSlider.addListener (this);
    mlOscSenderSlider.setRange (1, 9999, 1);
    mlOscSenderSlider.setValue (6448);
    mlOscSenderSlider.setSliderStyle (Slider::IncDecButtons);
    mlOscSenderSlider.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
    addAndMakeVisible (mlOscSenderSlider);
    
    mlOscSendPortLabel.setLookAndFeel (&laf);
    mlOscSendPortLabel.setJustificationType (Justification::left);
    mlOscSendPortLabel.setText ("Port:", dontSendNotification);
    mlOscSendPortLabel.setTooltip("ML OSC sender port number.");
    addAndMakeVisible (mlOscSendPortLabel);
    
    oscReceiveLabel.setJustificationType (Justification::horizontallyCentred);
    oscReceiveLabel.setText ("OSC Receiver", dontSendNotification);
    addAndMakeVisible (oscReceiveLabel);
    
    oscReceivePortLabel.setLookAndFeel (&laf);
    oscReceivePortLabel.setJustificationType (Justification::left);
    oscReceivePortLabel.setText ("Port:", dontSendNotification);
    oscReceivePortLabel.setTooltip("Main OSC receiver port number.");
    addAndMakeVisible (oscReceivePortLabel);
    
    oscReceiverSlider.setRange (1, 9999, 1);
    oscReceiverSlider.setValue (Application::getApp().getOscSettingsTree().getChildWithName("ReceivePort").getProperty ("receiverPort"));
    oscReceiverSlider.setSliderStyle (Slider::IncDecButtons);
    oscReceiverSlider.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
    oscReceiverSlider.setTooltip("Myo Mapper's OSC receiver port number.");
    oscReceiverSlider.addListener (this);
    addAndMakeVisible (oscReceiverSlider);
    
    hostAddressTitleLabel.setJustificationType (Justification::left);
    hostAddressTitleLabel.setText ("IP Address:", dontSendNotification);
    hostAddressTitleLabel.setTooltip("IP address of the device receiving Myo Mapper's OSC messages.");
    addAndMakeVisible(hostAddressTitleLabel);
    
    setHostAddressLabel.setJustificationType (Justification::centred);
    setHostAddressLabel.setText(Application::getApp().getOscSettingsTree().getChildWithName("HostAddress").getProperty ("hostAddress")
                                , dontSendNotification);    setHostAddressLabel.setEditable(true);
    setHostAddressLabel.setColour (Label::backgroundColourId, Colours::white);
    setHostAddressLabel.setColour (Label::textColourId, Colour::fromRGB (84, 101, 126));
    setHostAddressLabel.setColour (Label::outlineColourId, Colour::fromRGB (0, 129, 213));
    setHostAddressLabel.setTooltip("IP address of the device receiving Myo Mapper's OSC messages.");
    addAndMakeVisible(setHostAddressLabel);
    setHostAddressLabel.addListener(this);
    
    
    ////////
    mlHostAddressTitleLabel.setJustificationType (Justification::left);
    mlHostAddressTitleLabel.setText ("IP Address:", dontSendNotification);
    mlHostAddressTitleLabel.setTooltip("IP address of the device receiving Myo Mapper's OSC messages.");
    addAndMakeVisible(mlHostAddressTitleLabel);
    
    mlSetHostAddressLabel.setJustificationType (Justification::centred);
    mlSetHostAddressLabel.setText(Application::getApp().getOscSettingsTree().getChildWithName("HostAddress").getProperty ("hostAddress")
                                , dontSendNotification);    setHostAddressLabel.setEditable(true);
    mlSetHostAddressLabel.setColour (Label::backgroundColourId, Colours::white);
    mlSetHostAddressLabel.setColour (Label::textColourId, Colour::fromRGB (84, 101, 126));
    mlSetHostAddressLabel.setColour (Label::outlineColourId, Colour::fromRGB (0, 129, 213));
    mlSetHostAddressLabel.setTooltip("IP address of the interactive machine learning.");
    addAndMakeVisible(mlSetHostAddressLabel);
    mlSetHostAddressLabel.addListener(this);
    ///////
    
    myoSelectorLabel.setLookAndFeel (&laf);
    myoSelectorLabel.setJustificationType (Justification::left);
    myoSelectorLabel.setText ("Selected Myo:", dontSendNotification);
    myoSelectorLabel.setTooltip("Select the Myo armband which data have to be mapped into OSC messages.");
    addAndMakeVisible (myoSelectorLabel);
    
    myoSelectorSetter.setRange (1, 20, 1);
    myoSelectorSetter.setValue (Application::getApp().getOscSettingsTree().getChildWithName("SelectedMyo").getProperty ("myoId"));
    myoSelectorSetter.setSliderStyle (Slider::IncDecButtons);
    myoSelectorSetter.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
    myoSelectorSetter.addListener (this);
    addAndMakeVisible (myoSelectorSetter);
    
    featuresButton.setButtonText ("FEATURES");
    featuresButton.addListener (this);
    featuresButton.setTooltip("Select Myo features to stream via OSC.");
    addAndMakeVisible (featuresButton);
    
    startButton.setButtonText ("START");
    startButton.setTooltip("Start streaming Myo data via OSC.");
    startButton.addListener (this);
    addAndMakeVisible (startButton);
}

SettingsWindow::~SettingsWindow()
{
    oscReceivePortLabel.setLookAndFeel (nullptr);
    mainOscSendPortLabel.setLookAndFeel (nullptr);
    mlOscSendPortLabel.setLookAndFeel (nullptr);
    myoSelectorLabel.setLookAndFeel (nullptr);
}

void SettingsWindow::paint (Graphics& g)
{
    g.fillAll (Colour::fromRGB (245, 245, 245));
    
    auto area = getBounds().toFloat();
    auto windowSize = area;
    area.removeFromTop (windowSize.proportionOfHeight(0.078));
    
    auto mainOscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.3)).reduced (windowSize.proportionOfWidth (0.078), 0);
    auto mainOscHostRegion = area.removeFromTop(windowSize.proportionOfHeight (0.1)).reduced (windowSize.proportionOfWidth (0.078), 0);
    
    auto mlOscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.3)).reduced (windowSize.proportionOfWidth (0.078), 0);
    
    auto oscRectangleWidth = windowSize.proportionOfWidth (0.375);
    auto mainOscSendRegion = mainOscRegion.removeFromLeft (oscRectangleWidth);
    auto oscReceiveRegion = mainOscRegion.removeFromRight (oscRectangleWidth);
    auto mlOscSendRegion = mlOscRegion.removeFromLeft (oscRectangleWidth);

    g.setColour (Colour::fromRGB (0, 129, 213));
    auto rectangleCorner = windowSize.getHeight() * 0.02;
    auto lineThickness = windowSize.getHeight() * 0.006;
    
    Path oscSendRectangle;
    oscSendRectangle.addRoundedRectangle (mainOscSendRegion, rectangleCorner);
    g.strokePath (oscSendRectangle, PathStrokeType (lineThickness));
    
    Path oscReceiveRectangle;
    oscReceiveRectangle.addRoundedRectangle (oscReceiveRegion, rectangleCorner);
    g.strokePath (oscReceiveRectangle, PathStrokeType (lineThickness));
    
    Path mlSendRectangle;
    mlSendRectangle.addRoundedRectangle (mlOscSendRegion, rectangleCorner);
    g.strokePath (mlSendRectangle, PathStrokeType (lineThickness));
}

void SettingsWindow::resized()
{
    auto area = getBounds();
    auto windowSize = area;
    auto windowSizeWidth = area;
    area.removeFromTop (windowSize.proportionOfHeight (0.05));
    
    auto mainOscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.35))
    .reduced (windowSizeWidth.proportionOfWidth (0.078), 0);
    
    area.removeFromTop (windowSize.proportionOfHeight (0.1));
    
    auto mlOscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.35))
    .reduced (windowSizeWidth.proportionOfWidth (0.078), 0);
    
    auto oscRectangleWidth = windowSizeWidth.proportionOfWidth (0.375);
    
    auto mainOscSendRegion = mainOscRegion.removeFromLeft (oscRectangleWidth);
    auto oscReceiveRegion = mainOscRegion.removeFromRight (oscRectangleWidth);
    area.removeFromTop (windowSize.proportionOfHeight (0.07));
    
    auto mlOscSendRegion = mlOscRegion.removeFromLeft (oscRectangleWidth);

    
    auto myoSelectorRegion = area.removeFromTop (windowSize.proportionOfHeight (0.118))
    .reduced (windowSizeWidth.proportionOfWidth (0.13), 0);
    area.removeFromTop (windowSize.proportionOfHeight (0.07));
    
    auto buttonRegion = area.removeFromTop (windowSize.proportionOfHeight (0.14))
    .reduced (windowSizeWidth.proportionOfWidth (0.0315), 0);
    
    // Set send region bounds
    mainOscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.03));
    mainOscSendLabel.setBounds (mainOscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.09))
                            .reduced (windowSizeWidth.proportionOfWidth (0.029), 0));
    
    mainOscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.01));
    
    auto sendPortRegion = mainOscSendRegion.removeFromTop (proportionOfHeight (0.07))
                          .reduced (mainOscSendRegion.proportionOfWidth (0.04), 0);
    mainOscSendPortLabel.setBounds (sendPortRegion.removeFromLeft (sendPortRegion.proportionOfWidth (0.3)));
    mainOscSenderSlider.setBounds (sendPortRegion.reduced (mainOscSendRegion.proportionOfWidth (0.01), sendPortRegion.proportionOfHeight (0.05)));
    
    mainOscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.03));
    
    auto hostRegion = mainOscSendRegion.removeFromTop (proportionOfHeight (0.08))
                      .reduced (mainOscSendRegion.proportionOfWidth (0.04), 0);
    hostAddressTitleLabel.setBounds (hostRegion.removeFromLeft (hostRegion.proportionOfWidth (0.5)));
    setHostAddressLabel.setBounds (hostRegion
                                   .reduced (mainOscSendRegion.proportionOfWidth (0.03), hostRegion.proportionOfHeight (0.05)));
    
    
    // Set receive region bounds
    oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.03));
    oscReceiveLabel.setBounds (oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.118))
                               .reduced (windowSizeWidth.proportionOfWidth (0.019), 0));
    oscReceiveRegion.removeFromTop (windowSize.proportionOfHeight (0.018));
    
    auto ReceivePortRegion = oscReceiveRegion.removeFromTop (proportionOfHeight (0.1))
    .reduced (oscReceiveRegion.proportionOfWidth (0.04), 0);
    oscReceivePortLabel.setBounds (ReceivePortRegion.removeFromLeft (ReceivePortRegion.proportionOfWidth (0.3)));
    oscReceiverSlider.setBounds (ReceivePortRegion.reduced (oscReceiveRegion.proportionOfWidth (0.02), ReceivePortRegion.proportionOfHeight (0.05)));
    
    // Set myo selector region bounds
    myoSelectorLabel.setBounds (myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.287)));
    myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.033));
    myoSelectorSetter.setBounds (myoSelectorRegion.removeFromLeft (windowSize.proportionOfWidth (0.401))
                                 .reduced (0, windowSize.proportionOfHeight (0.01)));
    buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.2));
    featuresButton.setBounds (buttonRegion.removeFromLeft (windowSize.proportionOfWidth (0.222)));
    buttonRegion.removeFromRight (windowSize.proportionOfWidth (0.2));
    startButton.setBounds (buttonRegion.removeFromRight (windowSize.proportionOfWidth (0.174)));
    
    
    // Set ml region bounds
    mlOscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.03));
    mlOscSendLabel.setBounds (mlOscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.09))
                                .reduced (windowSizeWidth.proportionOfWidth (0.029), 0));
    
    mlOscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.01));
    
    auto mlSendPortRegion = mlOscSendRegion.removeFromTop (proportionOfHeight (0.07))
    .reduced (mlOscSendRegion.proportionOfWidth (0.04), 0);
    mlOscSendPortLabel.setBounds (mlSendPortRegion.removeFromLeft (mlSendPortRegion.proportionOfWidth (0.3)));
    mlOscSenderSlider.setBounds (mlSendPortRegion.reduced (mlOscSendRegion.proportionOfWidth (0.01), mlSendPortRegion.proportionOfHeight (0.05)));
    
    mlOscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.03));
    
    auto mlHostRegion = mlOscSendRegion.removeFromTop (proportionOfHeight (0.08))
    .reduced (mlOscSendRegion.proportionOfWidth (0.04), 0);
    mlHostAddressTitleLabel.setBounds (mlHostRegion.removeFromLeft (mlHostRegion.proportionOfWidth (0.5)));
    mlSetHostAddressLabel.setBounds (mlHostRegion
                                   .reduced (mlOscSendRegion.proportionOfWidth (0.03), mlHostRegion.proportionOfHeight (0.05)));
}

void SettingsWindow::resetStartButtonPressed()
{
    SettingsWindow::startButtonClicked = false;
}

void SettingsWindow::resetFeatureButtonPressed()
{
    SettingsWindow::featureButtonClicked = false;
}

void SettingsWindow::buttonClicked (Button* button)
{
    if (button == &startButton)
    {
        startButtonClicked = true;
        sendChangeMessage(); // Close the settings window, start the program and open the visualiser
    }
    if (button == &featuresButton)
    {
        
        featureButtonClicked = true;
        sendChangeMessage();
    }
}


void SettingsWindow::labelTextChanged(juce::Label *labelThatHasChanged)
{
    if (labelThatHasChanged == &setHostAddressLabel)
    {
        Application::getApp().getOscSettingsTree().getChildWithName("HostAddress").setProperty ("hostAddress", setHostAddressLabel.getText(), 0);
    }
}

String SettingsWindow::getHostAddress()
{
    return hostAddress;
}


void SettingsWindow::sliderValueChanged (Slider* slider)
{
    auto value = slider->getValue();
    if (slider == &mainOscSenderSlider)
    {
        Application::getApp().getOscSettingsTree().getChildWithName("SendPort").setProperty ("portNumber", value, 0);
    }
    if (slider == &oscReceiverSlider)
    {
        Application::getApp().getOscSettingsTree().getChildWithName("ReceivePort").setProperty ("portNumber", value, 0);
    }
    if (slider == &myoSelectorSetter)
    {
        Application::getApp().getOscSettingsTree().getChildWithName ("SelectedMyo").setProperty ("myoId", value, 0);
    }
}
