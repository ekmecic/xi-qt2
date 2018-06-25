project('xi-qt', 'cpp', default_options : 'cpp_std=c++17')

if get_option('buildtype').startswith('debug')
  add_project_arguments('-DXI_QT_DEBUG', language : 'cpp')
endif

qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Widgets'])


inc = include_directories('src')

flags = [
  '-Wall',
  '-Wextra',
  '-Werror',
  '-pedantic',
  '-Wredundant-decls',
  '-Wcast-align',
  '-Wmissing-declarations',
  '-Wmissing-include-dirs',
  '-Wswitch-enum',
  '-Winvalid-pch',
  '-Wredundant-decls',
  '-Wformat=2',
  '-Wmissing-format-attribute',
  '-Wformat-nonliteral',
  '-Wodr',
  '-flto',
]

src = [
  'src/main.cpp',
  'src/editor.cpp',
  'src/rpc_handler.cpp',
  'src/json_types.cpp',
  'src/view.cpp',
]

normal_headers = [
  'src/json_types.hpp',
  'src/global_types.hpp',
  'src/view.hpp',
]

moc_headers = [
  'src/editor.hpp',
  'src/rpc_handler.hpp',
]

processed = qt5.preprocess(
  moc_headers : moc_headers,
  include_directories: inc,
  qresources  : 'assets/resources.qrc',
)

add_project_arguments(flags, language: 'cpp')

executable('xi-qt2', src, normal_headers, processed,
           include_directories: inc,
           dependencies : qt5_dep)
