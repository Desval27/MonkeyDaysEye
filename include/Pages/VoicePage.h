#pragma once

#include <BasicVoice.h>
#include <Pages/FullScreenVerticalMenu.h>

class VoicePage : public FullScreenVerticalMenu<>
{
  public:
    VoicePage() {}

    void Init(BasicVoice* voice)
    {
        voice_ = voice;

        menuConfig_[0].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[0].text = s_PERIOD;
        menuConfig_[0].asMappedValueItem.valueToModify = &voice->config_.period;

        menuConfig_[1].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[1].text = s_SHAPE;
        menuConfig_[1].asMappedValueItem.valueToModify = &voice->config_.waveForm;

        menuConfig_[2].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[2].text = s_VOLUME;
        menuConfig_[2].asMappedValueItem.valueToModify = &voice->config_.volume;

        menuConfig_[3].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[3].text = s_BALANCE;
        menuConfig_[3].asMappedValueItem.valueToModify = &voice->config_.balance;

        menuConfig_[4].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[4].text = s_FLT_FREQ;
        menuConfig_[4].asMappedValueItem.valueToModify = &voice->config_.fltFreq;

        menuConfig_[5].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[5].text = s_FLT_RES;
        menuConfig_[5].asMappedValueItem.valueToModify = &voice->config_.fltRes;

        menuConfig_[6].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[6].text = s_FLT_ATTACK;
        menuConfig_[6].asMappedValueItem.valueToModify
            = &voice->config_.fltEnvelope.attack;

        menuConfig_[7].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[7].text = s_FLT_DECAY;
        menuConfig_[7].asMappedValueItem.valueToModify
            = &voice->config_.fltEnvelope.decay;

        menuConfig_[8].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[8].text = s_AMP_LEVEL;
        menuConfig_[8].asMappedValueItem.valueToModify
            = &voice->config_.ampLevel;

        menuConfig_[9].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[9].text = s_AMP_ATTACK;
        menuConfig_[9].asMappedValueItem.valueToModify
            = &voice->config_.ampEnvelope.attack;

        menuConfig_[10].type = daisy::AbstractMenu::ItemType::valueItem;
        menuConfig_[10].text = s_AMP_DECAY;
        menuConfig_[10].asMappedValueItem.valueToModify
            = &voice->config_.ampEnvelope.decay;

        // menuConfig_[11].type = daisy::AbstractMenu::ItemType::valueItem;
        // menuConfig_[11].text = s_AMP_SUSTAIN;
        // menuConfig_[11].asMappedValueItem.valueToModify
        //     = &voice->config_.ampEnvelope.sustain;

        // menuConfig_[12].type = daisy::AbstractMenu::ItemType::valueItem;
        // menuConfig_[12].text = s_AMP_RELEASE;
        // menuConfig_[12].asMappedValueItem.valueToModify
        //     = &voice->config_.ampEnvelope.release;

        FullScreenVerticalMenu<>::Init(
            menuConfig_.data(),
            menuConfig_.size(),
            daisy::AbstractMenu::Orientation::leftRightSelectUpDownModify,
            true);
    }

  private:
    BasicVoice* voice_;

    std::array<daisy::AbstractMenu::ItemConfig, 11> menuConfig_;

    static inline const char* s_PERIOD      = "PERIOD";
    static inline const char* s_SHAPE       = "SHAPE";
    static inline const char* s_VOLUME      = "VOLUME";
    static inline const char* s_BALANCE     = "BALANCE";
    static inline const char* s_FLT_FREQ    = "FLT FREQ";
    static inline const char* s_FLT_RES     = "FLT RES";
    static inline const char* s_FLT_ATTACK  = "FLT ATTACK";
    static inline const char* s_FLT_DECAY   = "FLT DECAY";
    static inline const char* s_AMP_LEVEL   = "AMP LEVEL";
    static inline const char* s_AMP_ATTACK  = "AMP ATTACK";
    static inline const char* s_AMP_DECAY   = "AMP DECAY";
    static inline const char* s_AMP_SUSTAIN = "AMP SUSTAIN";
    static inline const char* s_AMP_RELEASE = "AMP RELEASE";
};
