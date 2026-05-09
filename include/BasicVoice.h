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
#include <monkey.hpp>
#include <music/music.hpp>

///////////////////////////////////////////////////////////////////////////
/// @brief
struct BasicVoiceConfig
{
  BasicVoiceConfig()
    : volume(0.0f,
             1.0f,
             1.0f,
             daisy::MappedFloatValue::Mapping::lin,
             "",
             4,
             false)
    , balance(-1.0f,
              1.0f,
              0.0f,
              daisy::MappedFloatValue::Mapping::lin,
              "",
              4,
              true)
  {
  }

  daisy::MappedFloatValue volume;
  daisy::MappedFloatValue balance;
};

///////////////////////////////////////////////////////////////////////////////
/// @brief
// template <std::size_t OSCILLATOR_COUNT = 1>
template<typename VOICE_CONFIG = BasicVoiceConfig>
class BasicVoice
{
public:
  VOICE_CONFIG config_;

  ///////////////////////////////////////////////////////////////////////////
  /// @brief
  BasicVoice()
    : gate_(false)
    , trigger_(false)
  {
  }

  ///////////////////////////////////////////////////////////////////////////
  /// @brief
  /// @param sample_rate
  virtual void init(float sample_rate) {}

  ///////////////////////////////////////////////////////////////////////////
  /// @brief
  /// @return
  virtual std::tuple<float, float> process(bool trigger = false)
  {
    return { 0.0F, 0.0F };
  }

  ///////////////////////////////////////////////////////////////////////////
  /// @brief
  /// @param nowMS
  virtual void update(uint32_t nowMS) {}

  ///////////////////////////////////////////////////////////////////////////
  /// @brief
  bool get_gate() const { return gate_; }

  ///////////////////////////////////////////////////////////////////////////
  /// @brief
  /// @param value
  void set_gate(bool value) { gate_ = value; }

  ///////////////////////////////////////////////////////////////////////////
  /// @brief
  /// @return
  bool get_trigger() const { return trigger_; }

  ///////////////////////////////////////////////////////////////////////////
  /// @brief
  /// @param value
  void set_trigger(bool value) { trigger_ = value; }

protected:
  ///////////////////////////////////////////////////////////////////////////
  /// @brief
  /// @param sig
  /// @return
  std::tuple<float, float> balance_signal(float sig)
  {
    const float rCoeff = (config_.balance.Get() + 1.0F) / 2.0F;
    const float lCoeff = 1.0F - rCoeff;
    return { sig * lCoeff, sig * rCoeff };
  }

private:
  bool gate_;
  bool trigger_;
};
