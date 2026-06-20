/*
=====================================================================

PluginHeader.cpp
Created: 20 Jun 2026
Author:  Fares Schulz

=====================================================================
*/

#include "PluginHeader.h"

namespace {
    const juce::String kRepoUrl  = "https://github.com/tu-studio/seamless-plugin-suite";
    const juce::String kAuthors  = "Fares Schulz, Maximilian Weidauer, Henrik von Coler";
    const juce::String kAffiliation = "TU Studio - Audio Communication Group, TU Berlin";
    const juce::String kCopyright   = juce::CharPointer_UTF8("\xc2\xa9 2026 TU Studio");
}

//==================================================================
// AboutPanel
//==================================================================
AboutPanel::AboutPanel(const juce::String& pluginName)
{
    auto styleLabel = [this](juce::Label& label, const juce::String& text,
                             juce::Justification just, bool bold) {
        label.setText(text, juce::dontSendNotification);
        label.setColour(juce::Label::textColourId, juce::Colours::white);
        label.setJustificationType(just);
        auto font = label.getFont().withHeight(bold ? 18.0f : 14.0f);
        label.setFont(bold ? font.boldened() : font);
        addAndMakeVisible(label);
    };

    styleLabel(titleLabel, pluginName, juce::Justification::centred, true);
    styleLabel(versionLabel, "Version " + juce::String(SEAMLESS_VERSION),
               juce::Justification::centred, false);
    styleLabel(authorsLabel, kAuthors, juce::Justification::centred, false);
    styleLabel(affiliationLabel, kAffiliation, juce::Justification::centred, false);
    styleLabel(copyrightLabel, kCopyright, juce::Justification::centred, false);

    repoLink.setButtonText(kRepoUrl);
    repoLink.setURL(juce::URL(kRepoUrl));
    repoLink.setColour(juce::HyperlinkButton::textColourId, tuStudioLightLavender);
    repoLink.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(repoLink);

    setSize(320, 200);
}

void AboutPanel::paint(juce::Graphics& g)
{
    g.fillAll(tuStudioNight);
    g.setColour(tuStudioPurple);
    g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(1.0f), 10.0f, 2.0f);
}

void AboutPanel::resized()
{
    auto area = getLocalBounds().reduced(15);
    auto spacing = 6;

    titleLabel.setBounds(area.removeFromTop(28));
    area.removeFromTop(spacing);
    versionLabel.setBounds(area.removeFromTop(22));
    area.removeFromTop(spacing * 2);
    authorsLabel.setBounds(area.removeFromTop(22));
    area.removeFromTop(spacing);
    affiliationLabel.setBounds(area.removeFromTop(22));
    area.removeFromTop(spacing * 2);
    repoLink.setBounds(area.removeFromTop(22));
    area.removeFromTop(spacing);
    copyrightLabel.setBounds(area.removeFromTop(22));
}

//==================================================================
// PluginHeader
//==================================================================
PluginHeader::PluginHeader(juce::String pluginNameToUse)
    : pluginName(std::move(pluginNameToUse))
{
    titleLabel.setText(pluginName, juce::dontSendNotification);
    titleLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    titleLabel.setJustificationType(juce::Justification::centredLeft);
    titleLabel.setFont(titleLabel.getFont().withHeight(18.0f).boldened());
    addAndMakeVisible(titleLabel);

    aboutButton.setColour(juce::TextButton::buttonColourId, tuStudioPurple);
    aboutButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    aboutButton.setTooltip("About this plugin");
    aboutButton.onClick = [this] { showAbout(); };
    addAndMakeVisible(aboutButton);
}

void PluginHeader::paint(juce::Graphics& g)
{
    g.setColour(tuStudioPurple);
    g.fillRoundedRectangle(0.f, 0.f, (float) getWidth(), (float) getHeight(), 30.f);

    g.setColour(tuStudioNight);
    g.fillRoundedRectangle(5.f, 5.f, (float) getWidth() - 10.f, (float) getHeight() - 10.f, 25.f);
}

void PluginHeader::resized()
{
    auto area = getLocalBounds();
    area = area.reduced(area.getHeight() / 4);

    // square About button on the right
    auto buttonSize = area.getHeight();
    aboutButton.setBounds(area.removeFromRight(buttonSize));
    area.removeFromRight(area.getHeight() / 2);

    titleLabel.setBounds(area);
}

void PluginHeader::showAbout()
{
    auto panel = std::make_unique<AboutPanel>(pluginName);
    auto& box = juce::CallOutBox::launchAsynchronously(
        std::move(panel),
        aboutButton.getScreenBounds(),
        nullptr);
    juce::ignoreUnused(box);
}
