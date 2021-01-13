function(create_symlink target_name symlink_dir)
    add_custom_target(${target_name}-symlink ALL
                      DEPENDS ${grammar_tester}
                      COMMAND ${CMAKE_COMMAND} -E make_directory "${symlink_dir}"
                      COMMAND ${CMAKE_COMMAND} -E create_symlink "$<TARGET_FILE:${target_name}>" "${symlink_dir}/$<TARGET_FILE_NAME:${target_name}>")
endfunction()