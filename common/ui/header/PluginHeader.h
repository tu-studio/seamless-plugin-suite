/*
=====================================================================

PluginHeader.h
Created: 20 Jun 2026
Author:  Fares Schulz

Shared header bar for the SeamLess plugins. Shows the plugin name on the
left and an About button on the right which opens a CallOutBox with the
build version, authors and project information.

=====================================================================
*/

#ifndef SM_PLUGINHEADER_H
#define SM_PLUGINHEADER_H

#include "JuceHeader.h"
#include "SeamLess.h"

// Full build version, injected from CMake (git describe --dirty).
// Fallback keeps the file compilable if the define is ever missing.
#ifndef SEAMLESS_VERSION
#define SEAMLESS_VERSION "dev"
#endif

//==================================================================
// Content shown inside the About CallOutBox.
//==================================================================
class AboutPanel : public juce::Component
{
public:
    explicit AboutPanel(const juce::String& pluginName);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::Label titleLabel;
    juce::Label versionLabel;
    juce::Label authorsLabel;
    juce::Label affiliationLabel;
    juce::Label copyrightLabel;
    juce::HyperlinkButton repoLink;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AboutPanel)
};

//==================================================================
// Header bar: plugin name (left) + About button (right).
//==================================================================
class PluginHeader : public juce::Component
{
public:
    explicit PluginHeader(juce::String pluginName);

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void showAbout();

    juce::String pluginName;
    juce::Label titleLabel;
    juce::TextButton aboutButton {"?"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginHeader)
};

#endif //SM_PLUGINHEADER_H
