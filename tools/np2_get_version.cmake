include_guard()

# version.sh port
function(np2_get_version)
    cmake_parse_arguments(VER "" "VERSION;HEAD;BASE;BASE_VERSION;BRANCH;FULL;HAS_LOCAL_CHANGES" "" ${ARGN})
    set(svnrev  760)
    set(svnhash "0cd53aab71b006820233224bbf14c2b18b2caca6")

    set(ver "?")
    set(head "?")
    set(base "?")
    set(base_ver "?")
    set(branch "no branch")
    set(ver_full)
    set(has_local_changes 0)

    find_package(Git)
    if (GIT_FOUND)
        function(run_git) # OUTPUT=output_variable;RESULT=result_variable
            cmake_parse_arguments(RUN "" "OUTPUT;ERROR;RESULT" "ARGS" ${ARGN})
            execute_process(
                COMMAND ${GIT_EXECUTABLE} ${RUN_ARGS}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                RESULT_VARIABLE result
                OUTPUT_VARIABLE output
                ERROR_VARIABLE error
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
            if (RUN_OUTPUT)
                set(${RUN_OUTPUT} ${output} PARENT_SCOPE)
            endif()
            if (RUN_ERROR)
                set(${RUN_ERROR} ${error} PARENT_SCOPE)
            endif()
            if (RUN_RESULT)
                set(${RUN_RESULT} ${result} PARENT_SCOPE)
            elseif(NOT result EQUAL 0)
                message(FATAL_ERROR "run_git: ${error}")
            endif()
        endfunction()

        # Get the current branch name
        run_git(OUTPUT branch RESULT result ARGS symbolic-ref -q HEAD)
        if (result EQUAL 0)
            if (branch MATCHES "refs/heads/(.*)")
                set(branch ${CMAKE_MATCH_1})
            endif()

            # If we are on another branch that isn't master, we want extra info like on
            # which commit from master it is based on and what its hash is. This assumes we
            # won't ever branch from a changeset from before the move to git
            if (NOT branch STREQUAL "master")
                set(${BRANCH} "${branch}" PARENT_SCOPE)
                run_git(RESULT result ARGS show-ref --verify --quiet refs/heads/master)
                if (result EQUAL 0)
                    # Get where the branch is based on master
                    run_git(OUTPUT base ARGS merge-base master HEAD)
                    run_git(OUTPUT base_ver ARGS rev-list --count ${svnhash}..${base})
                    math(EXPR base_ver "${base_ver} + ${svnrev}")
                    set(ver_full " (${branch}) (master@${base_ver})")
                else()
                    set(ver_full " (${branch})")
                endif()
            endif()

            # Count how many changesets we have since the last svn changeset
            run_git(OUTPUT ver ARGS rev-list --count ${svnhash}..HEAD)
            # Now add it with to last svn revision number
            math(EXPR ver "${ver} + ${svnrev}")

            # Get the abbreviated hash of the current changeset
            run_git(OUTPUT head ARGS rev-parse --short HEAD)
        endif()

        # Check if repository has local changes
        run_git(RESULT has_local_changes ARGS diff-index --quiet HEAD)
    endif()

    set(ver_full "${ver} (${head})${ver_full}")

    if (VER_VERSION)
        set(${VER_VERSION} ${ver} PARENT_SCOPE)
    endif()
    if (VER_HEAD)
        set(${VER_HEAD} ${head} PARENT_SCOPE)
    endif()
    if (VER_BASE)
        set(${VER_BASE} ${base} PARENT_SCOPE)
    endif()
    if (VER_BASE_VERSION)
        set(${VER_BASE_VERSION} ${base_ver} PARENT_SCOPE)
    endif()
    if (VER_BRANCH)
        set(${VER_BRANCH} ${branch} PARENT_SCOPE)
    endif()
    if (VER_FULL)
        set(${VER_FULL} ${ver_full} PARENT_SCOPE)
    endif()
    if (VER_HAS_LOCAL_CHANGES)
        set(${VER_HAS_LOCAL_CHANGES} ${has_local_changes} PARENT_SCOPE)
    endif()
endfunction()