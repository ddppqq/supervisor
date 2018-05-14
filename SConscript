#!python
import sys, os, os.path, platform
import SCons.Util, SCons.Node

def cpplintCheck(rootDir='..'):
    cpplint = '../tools/cpplint.py --quiet '
    listDirs = os.walk(rootDir)
    for root, dirs, files in listDirs:
        for f in files:
            filename = os.path.join(root, f)
            if filename.find("thirdparty") >= 0 or filename.find("protocol") >= 0:
                continue
            if filename.endswith(".h") or filename.endswith(".cpp") :
                x = os.system(cpplint + filename)
                if (x != 0):
                    sys.exit()

cpplintCheck()

env = Environment(tools = ['default', 'protoc'])
env.Append(CCFLAGS = ['-std=c++11', '-g'])
env.AppendUnique(CPPPATH=['.',
                          'thirdparty/include/googletest/',
                          ]
)

# env.Append(LIBPATH = ['thirdparty/lib/'])

env.Install('protocol/', Glob('../protocol/*.proto'))

os.system('protoc -I protocol/ --grpc_out=./protocol/ --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` protocol/*.proto')

#envProtoc = env.Clone()
#envProtoc.Append(GRPC_OUT = '--grpc_out')
#envProtoc.Append(PLUGIN = '--plugin')
#supervisor_grpc_files = envProtoc.Protoc(
#    [Glob('protocol/*.proto')],
#    GRPC_OUT = 'protocol/',
#    PLUGIN = 'protoc-gen-grpc=`which grpc_cpp_plugin`',
#    LIBS = ['grpc++', 'grpc', 'grpc++_reflection', 'dl'],
#)

supervisor_proto_files = env.Protoc(
    [Glob('protocol/*.proto')],
    PROTOC_PATH='protocol/',
    PROTOC_CCOUT='protocol/',
)

supervisor = env.Program(
    target = 'supervisor',
    source = [Glob('framework/supervisor/*.cpp'),
              Glob('framework/common/*.cpp'),
              Glob('framework/nodemanager/*.cpp'),
              Glob('protocol/*.pb.cc'),
              ],
    LIBS = ['protobuf', 'grpc++', 'grpc', 'grpc++_reflection', 'dl', 'pthread'],
)

subprocess = env.Program(
    target = 'subprocess',
    source = [Glob('framework/subprocess/*.cpp'),
              'protocol/common.pb.o',
              ],
    LIBS = ['protobuf', 'grpc++', 'grpc', 'grpc++_reflection', 'dl'],
)

local_filesystem_ut = env.Program(
    target = 'local_filesystem_ut',
    source = ['unittest/local_filesystem_ut.cpp',
               Glob('framework/common/*.o'),
              'thirdparty/lib/gtest_main.a',
              'thirdparty/lib/gmock_main.a'],
        )

local_resource_loader_ut = env.Program(
    target = 'local_resource_loader_ut',
    source = ['unittest/local_resource_loader_ut.cpp',
              Glob('framework/common/local_filesystem.o'),
              Glob('framework/nodemanager/local_resource_loader.cpp'),
              Glob('protocol/common.pb.o'),
              'thirdparty/lib/gtest_main.a',
              'thirdparty/lib/gmock_main.a'],
    LIBS = ['protobuf'],
        )

binary_subprocess_ut = env.Program(
    target = 'binary_subprocess_ut',
    source = ['unittest/binary_subprocess_ut.cpp',
              'thirdparty/lib/gtest_main.a',
              'thirdparty/lib/gmock_main.a'],
        )

env.Install('../bin/', supervisor)
env.Install('../bin/', subprocess)
env.Install('../bin/', local_filesystem_ut)
env.Install('../bin/', local_resource_loader_ut)
env.Install('../bin/', binary_subprocess_ut)
