#include <benchmark/benchmark.h>
#include "../SeamLess_Main/source/PluginEditor.h"

// static void BM_processor_main(benchmark::State& state) {
//   // Perform setup here
//     auto gui = juce::ScopedJuceInitialiser_GUI {};
//   for (auto _ : state) {
//     // This code gets timed
//     AudioPluginAudioProcessor processor;
//   }
// }
// // Register the function as a benchmark
// BENCHMARK(BM_processor_main);

// static void BM_editor_main(benchmark::State& state) {
//   // Perform setup here
//     auto gui = juce::ScopedJuceInitialiser_GUI {};
//     AudioPluginAudioProcessor plugin;
//   for (auto _ : state) {
//     // This code gets timed
//     auto editor = plugin.createEditor();
//     plugin.editorBeingDeleted (editor);
//     delete editor;
//   }
// }
// // Register the function as a benchmark
// BENCHMARK(BM_editor_main);