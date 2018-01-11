#include "../JuceLibraryCode/JuceHeader.h"
#include "SettingsWindow.h"
#include "../../Application.h"

bool SettingsWindow::startButtonClicked;
bool SettingsWindow::featureButtonClicked;

SettingsWindow::SettingsWindow()
:
hostAddress("127.0.0.1")
{
    oscSendLabel.setJustificationType (Justification::horizontallyCentred);
    oscSendLabel.setText ("OSC Sender", dontSendNotification);
    addAndMakeVisible (oscSendLabel);
    
    oscSenderSlider.addListener (this);
    oscSenderSlider.setRange (1, 9999, 1);
    oscSenderSlider.setValue (Application::getApp().getOscSettingsTree().getChildWithName("SendPort").getProperty ("senderPort"));
    oscSenderSlider.setSliderStyle (Slider::IncDecButtons);
    oscSenderSlider.setIncDecButtonsMode (Slider::incDecButtonsNotDraggable);
    addAndMakeVisible (oscSenderSlider);
    
    oscSendPortLabel.setLookAndFeel (&laf);
    oscSendPortLabel.setJustificationType (Justification::left);
    oscSendPortLabel.setText ("Port:", dontSendNotification);
    oscSendPortLabel.setTooltip("Myo Mapper's OSC sender port number.");
    addAndMakeVisible (oscSendPortLabel);
    
    oscReceiveLabel.setJustificationType (Justification::horizontallyCentred);
    oscReceiveLabel.setText ("OSC Receiver", dontSendNotification);
    addAndMakeVisible (oscReceiveLabel);
    
    oscReceivePortLabel.setLookAndFeel (&laf);
    oscReceivePortLabel.setJustificationType (Justification::left);
    oscReceivePortLabel.setText ("Port:", dontSendNotification);
    oscReceivePortLabel.setTooltip("Myo Mapper's OSC receiver port number.");
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
    oscSendPortLabel.setLookAndFeel (nullptr);
    myoSelectorLabel.setLookAndFeel (nullptr);
}

void SettingsWindow::paint (Graphics& g)
{
    g.fillAll (Colour::fromRGB (245, 245, 245));
    
    auto area = getBounds().toFloat();
    auto windowSize = area;
    area.removeFromTop (windowSize.proportionOfHeight(0.078));
    auto oscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.429)).reduced (windowSize.proportionOfWidth (0.078), 0);
    auto oscHostRegion = area.removeFromTop(windowSize.proportionOfHeight (0.1)).reduced (windowSize.proportionOfWidth (0.078), 0);

    auto oscRectangleWidth = windowSize.proportionOfWidth (0.375);
    auto oscSendRegion = oscRegion.removeFromLeft (oscRectangleWidth);
    auto oscReceiveRegion = oscRegion.removeFromRight (oscRectangleWidth);
    
    g.setColour (Colour::fromRGB (0, 129, 213));
    auto rectangleCorner = windowSize.getHeight() * 0.02;
    auto lineThickness = windowSize.getHeight() * 0.006;
    
    Path oscSendRectangle;
    oscSendRectangle.addRoundedRectangle (oscSendRegion, rectangleCorner);
    g.strokePath (oscSendRectangle, PathStrokeType (lineThickness));
    Path oscReceiveRectangle;
    oscReceiveRectangle.addRoundedRectangle (oscReceiveRegion, rectangleCorner);
    g.strokePath (oscReceiveRectangle, PathStrokeType (lineThickness));
}

void SettingsWindow::resized()
{
    auto area = getBounds();
    auto windowSize = area;
    auto windowSizeWidth = area;
    area.removeFromTop (windowSize.proportionOfHeight (0.078));
    auto oscRegion = area.removeFromTop (windowSize.proportionOfHeight (0.429))
    .reduced (windowSizeWidth.proportionOfWidth (0.078), 0);
    auto oscRectangleWidth = windowSizeWidth.proportionOfWidth (0.375);
    auto oscSendRegion = oscRegion.removeFromLeft (oscRectangleWidth);
    auto oscReceiveRegion = oscRegion.removeFromRight (oscRectangleWidth);
    area.removeFromTop (windowSize.proportionOfHeight (0.07));
    auto myoSelectorRegion = area.removeFromTop (windowSize.proportionOfHeight (0.118))
    .reduced (windowSizeWidth.proportionOfWidth (0.13), 0);
    area.removeFromTop (windowSize.proportionOfHeight (0.07));
    auto buttonRegion = area.removeFromTop (windowSize.proportionOfHeight (0.14))
    .reduced (windowSizeWidth.proportionOfWidth (0.0315), 0);
    
    // Set send region bounds
    oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.03));
    oscSendLabel.setBounds (oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.118))
                            .reduced (windowSizeWidth.proportionOfWidth (0.029), 0));
    oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.018));
    auto sendPortRegion = oscSendRegion.removeFromTop (proportionOfHeight (0.1))
                          .reduced (oscSendRegion.proportionOfWidth (0.04), 0);
    oscSendPortLabel.setBounds (sendPortRegion.removeFromLeft (sendPortRegion.proportionOfWidth (0.3)));
    oscSenderSlider.setBounds (sendPortRegion.reduced (oscSendRegion.proportionOfWidth (0.02), sendPortRegion.proportionOfHeight (0.05)));
    oscSendRegion.removeFromTop (windowSize.proportionOfHeight (0.038));
    auto hostRegion = oscSendRegion.removeFromTop (proportionOfHeight (0.1))
                      .reduced (oscSendRegion.proportionOfWidth (0.04), 0);
    hostAddressTitleLabel.setBounds (hostRegion.removeFromLeft (hostRegion.proportionOfWidth (0.4)));
    setHostAddressLabel.setBounds (hostRegion
                                   .reduced (oscSendRegion.proportionOfWidth (0.03), hostRegion.proportionOfHeight (0.05)));
    
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
    if (slider == &oscSenderSlider)
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
