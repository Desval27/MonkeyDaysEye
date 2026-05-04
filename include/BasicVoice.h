/* SPDX-License-Identifier: CC0-1.0 */
/**
 * @file BasicVoice.h
 * @brief
 * @author pfburdette <paul.f.burdette@gmail.com>
 *
 * @copyright This work is dedicated to the public domain under CC0 1.0.
 * To the extent possible under law, the author(s) have waived all copyright
 * and related or neighboring rights to this software.
 * See <http://creativecommons.org>
 */
#pragma once

#include <daisy.h>
#include <daisysp.h>

#include <Envelopes.h>
#include <Monkey.h>
#include <Music/Music.h>

const char *WAVEFORM_LABELS[] = {
    "SIN",    "TRI",      "SAW",      "RAMP",
    "SQUARE", "POLY TRI", "POLY SAW", "POLY SQUARE",
};

// template <std::size_t OSCILLATOR_COUNT = 1>
class BasicVoice {
public:
  struct BasicVoiceConfig 
  {
    BasicVoiceConfig(int period, int waveForm)
      : period(Music::MIN_PERIOD, Music::MAX_PERIOD, period, 1, 1, "", false),
        waveForm(WAVEFORM_LABELS, ArrayLen(WAVEFORM_LABELS), waveForm),
        volume(0.0f, 1.0f, 1.0f, daisy::MappedFloatValue::Mapping::lin, "", 2, false),
        balance(-1.0f, 1.0f, 0.0f, daisy::MappedFloatValue::Mapping::lin, "", 2, true),
        fltFreq(0.0f, 16000.0f, 1000.0f, daisy::MappedFloatValue::Mapping::lin,
                "Hz", 0, false),
        fltRes(0.0f, 1.0f, 0.0f, daisy::MappedFloatValue::Mapping::lin, "", 2,
               false),
        fltEnvelope(0.2f, 0.5f, 1.0f),
        ampLevel(-1.0f, 1.0f, 0.0f, daisy::MappedFloatValue::Mapping::lin, "",
                 2, true),
        ampEnvelope(0.1f, 0.5f, 1.0f)
  // ampEnvelope(0.1f, 0.2f, 0.60f, 0.5f)
      {}

    daisy::MappedIntValue period;
    daisy::MappedStringListValue waveForm;
    daisy::MappedFloatValue volume;
    daisy::MappedFloatValue balance;
    daisy::MappedFloatValue fltFreq;
    daisy::MappedFloatValue fltRes;
    ADEnvelope fltEnvelope;
    daisy::MappedFloatValue ampLevel;
    ADEnvelope ampEnvelope;
    // ADSREnvelope ampEnvelope;
  };

  BasicVoiceConfig config_;

  BasicVoice()
      : config_(4, daisysp::Oscillator::WAVE_TRI)
  {}

  void Init(float sample_rate) {
    osc_.Init(sample_rate);
    //noise_.Init();

    flt_.Init(sample_rate);

    fltEnv_.Init(sample_rate);
    fltEnv_.SetMin(0.0f);
    fltEnv_.SetCurve(0); // linear

    ampEnv_.Init(sample_rate);
    ampEnv_.SetMin(0.0f);
    ampEnv_.SetCurve(0); // linear
  }

  std::tuple<float, float> Process() {
  
    // For now...

    // sigL = sigR = osc_.Process();
//    osc_.SetAmp(envOut);

//    float envOut = ampEnv_.Process();
    // float sigL = flt_.Low();
    // float sigR = flt_.High();
    // noise_.SetAmp(config_.volume);
    osc_.SetAmp(config_.volume);
    flt_.Process(osc_.Process());
    float sig = flt_.Low();

    // Get balance coeffecients and apply
    const float rCoeff = (config_.balance.Get() + 1.0f) / 2.0f;
    const float lCoeff = 1.0f - rCoeff;

    return {sig * lCoeff, sig * rCoeff};
  }

  void Update(uint32_t nowMS) 
  {
    osc_.SetWaveform(config_.waveForm);

    flt_.SetFreq(config_.fltFreq);
    flt_.SetRes(config_.fltRes);

    fltEnv_.SetMax(config_.fltEnvelope.amount);
    fltEnv_.SetTime(daisysp::ADENV_SEG_ATTACK, config_.fltEnvelope.attack);
    fltEnv_.SetTime(daisysp::ADENV_SEG_DECAY, config_.fltEnvelope.decay);

    ampEnv_.SetMax(config_.ampEnvelope.amount);
    ampEnv_.SetTime(daisysp::ADENV_SEG_ATTACK, config_.ampEnvelope.attack);
    ampEnv_.SetTime(daisysp::ADENV_SEG_DECAY, config_.ampEnvelope.decay);

    // ampEnv_.SetAttackTime(config_.ampEnvelope.attack);
    // ampEnv_.SetDecayTime(config_.ampEnvelope.decay);
    // ampEnv_.SetSustainLevel(config_.ampEnvelope.sustain);
    // ampEnv_.SetReleaseTime(config_.ampEnvelope.release);
  }

  void SetFreq(float value)
  {
    osc_.SetFreq(value);
  }

private:
  daisysp::Oscillator osc_;
  // daisysp::WhiteNoise noise_;
  daisysp::Svf   flt_;
  daisysp::AdEnv fltEnv_;
  daisysp::AdEnv ampEnv_;
  // daisysp::Adsr ampEnv_;
};
