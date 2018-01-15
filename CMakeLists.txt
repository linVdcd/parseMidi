cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project (JDKSMIDI)

include_directories( ${JDKSMIDI_SOURCE_DIR}/include )

add_library (jdksmidi src/jdksmidi_advancedsequencer.cpp src/jdksmidi_driver.cpp src/jdksmidi_driverdump.cpp src/jdksmidi_edittrack.cpp src/jdksmidi_file.cpp src/jdksmidi_fileread.cpp src/jdksmidi_filereadmultitrack.cpp src/jdksmidi_fileshow.cpp src/jdksmidi_filewrite.cpp src/jdksmidi_filewritemultitrack.cpp src/jdksmidi_keysig.cpp src/jdksmidi_manager.cpp src/jdksmidi_matrix.cpp src/jdksmidi_midi.cpp src/jdksmidi_msg.cpp src/jdksmidi_multitrack.cpp src/jdksmidi_parser.cpp src/jdksmidi_process.cpp src/jdksmidi_queue.cpp src/jdksmidi_sequencer.cpp src/jdksmidi_showcontrol.cpp src/jdksmidi_showcontrolhandler.cpp src/jdksmidi_smpte.cpp src/jdksmidi_sysex.cpp src/jdksmidi_tempo.cpp src/jdksmidi_tick.cpp src/jdksmidi_track.cpp src/jdksmidi_utils.cpp)

link_directories( ${JDKSMIDI_BINARY_DIR} )



add_executable(parse_midi examples/main.cpp examples/parseMIDI.cpp)
target_link_libraries(parse_midi jdksmidi)


