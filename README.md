# Seamless Plugin Suite

<!-- TODO: link to seamless docs -->

Suite of VST-Plugins and Standalone Applications to easily control the Seamless system using OSC-Messages.

## Usage

Put the Main Plugin on the Master Bus of your DAW, set ip and port to the receiver (usually an OSC-Kreuz instance). Then add Client Plugins to all tracks that should be spatialized.

![Seamless Plugins Signal Flow](./docs/graphics/seamless-plugin-suite_signal-flow.png)

## Development

Clone the repo

update submodules with

```bash
git submodule update --init --recursive
```
