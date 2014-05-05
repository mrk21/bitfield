include_directories(${PROJECT_SOURCE_DIR}/test)
include_directories(${PROJECT_SOURCE_DIR}/vendor/bandit)

file(GLOB_RECURSE SRCS "spec/*_spec.cpp")
add_executable(spec spec.cpp ${SRCS})
