cmake_minimum_required(VERSION 3.1)
include(CSProj)

set(OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(FLATBUFFERS_DLL "${OUTPUT_PATH}/FlatBuffers.dll")
set(FLATBUFFERS_MDB "${FLATBUFFERS_DLL}.mdb")

get_filename_component(FLATBUFFERS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../flatbuffers/net/FlatBuffers/" ABSOLUTE)
set(SOURCES
    "${FLATBUFFERS_ROOT}/ByteBuffer.cs"
    "${FLATBUFFERS_ROOT}/FlatBufferBuilder.cs"
    "${FLATBUFFERS_ROOT}/FlatBufferConstants.cs"
    "${FLATBUFFERS_ROOT}/Offset.cs"
    "${FLATBUFFERS_ROOT}/Properties/AssemblyInfo.cs"
    "${FLATBUFFERS_ROOT}/Struct.cs"
    "${FLATBUFFERS_ROOT}/Table.cs")

make_csproj(
  TARGET flatbuffers-net
  ASSEMBLY_NAME FlatBuffers
  ROOT_NAMESPACE FlatBuffers
  SOURCES ${SOURCES}
  FRAMEWORK v3.5
  REFERENCES System System.Core
)

get_target_property(FLATBUFFERS_NET_DLL flatbuffers-net DLL)

install(
        FILES "${FLATBUFFERS_NET_DLL}"
        DESTINATION client
        PERMISSIONS
          OWNER_READ OWNER_WRITE OWNER_EXECUTE
          GROUP_READ
          WORLD_READ
    )
