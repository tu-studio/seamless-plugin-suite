# TODO

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
- [x] incorporate Value::listeners when only listening to single variables
- [x] Get OSC receiver running
- [x] Send current state whenever port or ip get changed
- [x] Change Message format to allow single position values, then ditch the 99.f placeholder
- [x] Change structure of gains to allow addressing them by index, and not needing 4 different enum elements for them
- [x] when changing the source_index of a plugin check if in the sources there is another source with the same index but without a pluginconnection, if there is take it over
- [x] fix aed->xyz conv (when moving a source using mouse, radius is correctly between 0 and 1.73 (when it goes into a corner), but when directly changin aed, it is in the old range)
- [x] fix xyz->aed conversions:
      when moving in the xy-pad, x and y are updated seperately. This also triggers two seperate calls to `SphericalSliderBox::updateSphericalCoordinates()`, one with the new x and the old y, and one with the new y and old x. only the second update is used to actually update the values, so when just clicking anywhere on the xy-pad once, it often leads to discontinuities.
      **Solution**: bundle updates together, or only update single coordinates at a time, or internally keep track of state
- [ ] move cartesian-coordinate-limit from sphericalsliderbox to a global setting
- [ ] listen to spherical coordinates via OSC
