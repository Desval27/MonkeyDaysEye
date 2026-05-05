/* SPDX-License-Identifier: CC0-1.0 */
/**
 * @file BasicApp.h
 * @brief
 * @author pfburdette <paul.f.burdette@gmail.com>
 *
 * @copyright This work is dedicated to the public domain under CC0 1.0.
 * To the extent possible under law, the author(s) have waived all copyright
 * and related or neighboring rights to this software.
 * See <http://creativecommons.org>
 */
#pragma once

#include <array>
#include <utility>

#include <Music/Gnome.h>
#include <Music/EventSetManager.h>
#include <BasicVoice.h>


///////////////////////////////////////////////////////////////////////////////
/// @brief
/// @tparam VOICE_COUNT
template <std::size_t VOICE_COUNT, std::size_t MAX_DEGREES = Music::DEF_MAX_DEGREES, std::size_t SCALE_DEGREES = Music::DEF_SCALE_DEGREES>
class BasicApp
{
    static_assert(VOICE_COUNT > 0, "BasicApp needs at least one voice.");
    
    using AppSetup = Music::Setup<MAX_DEGREES, SCALE_DEGREES>;

  private:
    const uint32_t VOICE_REFRESH_MS = 100;

  public:

    /////////////////////////////////////////////////////////////////////////////
    /// @brief Singleton Instance
    /// @return The Instance
    static BasicApp &instance()
    {
        static BasicApp s;
        return s;
    }

    static constexpr std::size_t VoiceCount = VOICE_COUNT;

    /////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes app infrastructure including all voices based on the
    /// given sample rate
    /// @param sample_rate
    void Init(float sample_rate)
    {
        for(BasicVoice &v : voices)
        {
            v.Init(sample_rate);
            v.Update(0UL); // Initial state
        }

        // For giggles at the moment.
        voices[0].SetFreq(110.0f);
        if constexpr(VOICE_COUNT > 1)
            voices[1].SetFreq(220.0f);
        if constexpr(VOICE_COUNT > 2)
            voices[2].SetFreq(440.0f);
        if constexpr(VOICE_COUNT > 3)
            voices[3].SetFreq(880.0f);
    }

    /////////////////////////////////////////////////////////////////////////////
    /// @brief Processes the audio stream for all voices mixed into separate left
    /// & right values.
    /// @return left & right floating point values.
    std::tuple<float, float> Process()
    {
        const float evenMix = 1.0 / VOICE_COUNT;
        float       mixL    = 0.0f;
        float       mixR    = 0.0f;
        for(BasicVoice &v : voices)
        {
            auto [sigL, sigR] = v.Process();
            mixL              = mixL + (sigL * evenMix);
            mixR              = mixR + (sigR * evenMix);
        }
        return {mixL, mixR};
    }

    /////////////////////////////////////////////////////////////////////////////
    /// @brief Updates the status of all components including voices based on
    /// possible configuration or setup changes.
    /// @param nowMS
    void Update(uint32_t nowMS)
    {
        uint32_t delta = nowMS - lastRefreshMS_;
        if(delta >= VOICE_REFRESH_MS)
        {
            lastRefreshMS_ = nowMS - (delta % VOICE_REFRESH_MS);

            for(BasicVoice &v : voices)
                v.Update(nowMS);
        }
    }

    /////////////////////////////////////////////////////////////////////////////
    /// @brief
    /// @param index
    /// @return
    BasicVoice *GetVoicePtr(std::size_t index) { return &voices[index]; }


  private:
    AppSetup     setup_;
    Music::Gnome gnome_;
    uint32_t     lastRefreshMS_;

    std::array<BasicVoice, VOICE_COUNT>        voices;
    std::array<EventSetManager<>, VOICE_COUNT> voiceEvents;

    /////////////////////////////////////////////////////////////////////////////
    /// @brief
    BasicApp()
    : setup_(4, Music::NoteValue::Quarter, 12, 2.0f),
      gnome_(setup_.timeSignature, setup_.bars),
      lastRefreshMS_(0UL)
    {
    }
};
