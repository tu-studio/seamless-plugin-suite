# Make a variable with directory in PARENT_SCOPE
set(COMMON_DIR  ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/pluginConnection
                ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/ui/lookAndFeel PARENT_SCOPE)

# Make a variable in the PARENT_SCOPE with the common files to add
set(COMMON_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/SeamLess.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/pluginConnection/MainServer.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/pluginConnection/MainServer.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/pluginConnection/PluginConnection.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/pluginConnection/PluginConnection.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/ui/lookAndFeel/SliderLookAndFeel.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/ui/lookAndFeel/SliderLookAndFeel.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/ui/lookAndFeel/LabelLookAndFeel.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/ui/lookAndFeel/LabelLookAndFeel.cpp PARENT_SCOPE)