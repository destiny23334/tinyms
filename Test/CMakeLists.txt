aux_source_directory(./ SOURCE_FILE)
add_executable(test ${SOURCE_FILE})
target_link_libraries(test tinyms)