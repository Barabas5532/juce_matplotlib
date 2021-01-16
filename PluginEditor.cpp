#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "matplotlibcpp.h"

#include <juce_graphics/juce_graphics.h>
#include <juce_core/juce_core.h>

#define WIDTH 400
#define HEIGHT 300
#define FILENAME "/tmp/figure.png"

namespace plt = matplotlibcpp;

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    plt::figure_size(WIDTH, HEIGHT);
    plt::plot({1, 3, 2, 4});
    plt::save(FILENAME);

    juce::File figureFile(FILENAME);
    figureComponent.setImage(juce::ImageFileFormat::loadFrom(figureFile));

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(figureComponent);
    setSize(WIDTH, HEIGHT);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    figureComponent.setBounds(getLocalBounds());
}
