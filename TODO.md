# TODO

- [ ] fix bug that ableton live does not recall the state of the plugin with notautomatable parameters
- [ ] Limitation, that every source index can only exist once.
- [ ] Tooltips!
- [x] Send interval OSC limitation Main
- [x] Main Connection Status in beginning Client Bug
- [x] Main Connection osc send when the main starts second
- [ ] getPropertyAsValue -> getProperty
- [x] void Component::internalRepaintUnchecked (Rectangle<int> area, bool isEntireComponent)
      // if component methods are being called from threads other than the message
      // thread, you'll need to use a MessageManagerLock object to make sure it's thread-safe.
      JUCE_ASSERT_MESSAGE_MANAGER_IS_LOCKED
      fix this
- [ ] think about allowed ports for OSC
- [x] receive OSC Message blink
- [ ] better resizing
- [ ] Attributes for slider
- [ ] incorporate Value::listeners when only listening to single variables
- [x] Get OSC receiver running
- [ ] Send current state whenever connecting to an osc-kreuz
- [ ] Change Message format to allow single position values, then ditch the 99.f placeholder
- [ ] Change structure of gains to allow addressing them by index, and not needing 4 different enum elements for them
- [ ] when changing the source_index of a plugin check if in the sources there is another source with the same index but without a pluginconnection, if there is take it over
- [ ] check why aed coordinate conversions happen so often
