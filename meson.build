project('xi-qt', 'cpp', default_options : 'cpp_std=c++17')

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
  '-Wswitch-default',
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
  'src/mainwindow.cpp',
  'src/editor.cpp',
]

headers = [
  'src/mainwindow.h',
  'src/editor.h',
]

processed = qt5.preprocess(
  moc_headers : headers,
  include_directories: inc,
)

add_project_arguments(flags, language: 'cpp')

executable('xi-qt', src, processed,
           include_directories: inc,
           dependencies : qt5_dep)
