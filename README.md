# HelloDAW

*HelloDAW* is a collection of boilerplate audio plugins for multiple formats, implementing a single low-level standard, built with Makefiles and the terminal.

It's like the "Hello, world!" of DAW plugins.
Actually, it's like [TodoMVC](http://todomvc.com/), except with audio plugin formats instead of JavaScript frameworks.

Most importantly, this project attempts to reduce the time to build your first plugin from hours of frustration to hopefully 1 minute (`git clone ...`, `cd <project>`, read README, `make`).


### Includes

- VST2


### Wanted

- VST3
- AU (Audio Unit)
- AAX
- LV2

Pull-requests are welcome and will be merged if I can follow your instructions and build the plugin with `make`.


## The standard

Each plugin project is very simple and does nothing whatsoever.

The plugin should be loadable in a plugin host (e.g. DAW) capable of loading its format. The plugin should feature

- 8 inputs (4 stereo inputs) if possible, otherwise 2 inputs
- 8 outputs (4 stereo outputs) if possible, otherwise 2 outputs
- 8 automation parameters if possible
- No GUI. Use the host's automation parameters if possible.

When running, the plugin should implement the following I/O.

- print incoming MIDI message bytes to `stdout`
- print the state of automation parameters (whenever they change, or upon each audio block)
- In a double `for` loop for each frame and channel, apply a gain of 0.5 to the input buffer and set it to the output buffer.


The project should have a single `Makefile` and should be built by running `make` in the project directory.
No IDEs like Xcode or Visual Studio should be used.

Instructions should be provided in a `README.md` file for setting up the development environment and acquiring relevant SDK files.


## Using

Each *HelloDAW* project attempts to obtain a standard unified low-level API using each plugin's SDK.

This is great for forking and writing your own plugin if you prefer *simple* and *low-level* to *complex* and *convenient*.

Some things you will need to do
- process the 3-byte MIDI messages yourself
- handle your own polyphony by managing multiple MIDI notes and voices

If you enjoy that kind of thing, these boilerplate projects are for you!


## License

All code and documentation in this repository is released into the public domain ([CC0](https://creativecommons.org/publicdomain/zero/1.0/)).
No credit is needed, but it would be nice to hear if you've released a plugin with help from this project.

However, note that plugin SDKs typically have more restrictive licenses.
They are not included in this repository.
