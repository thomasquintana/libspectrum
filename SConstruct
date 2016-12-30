# Intel IPP Paths.
IPP_INCLUDEPATH = '/var/lib/intel/compilers_and_libraries_2017.0.098' \
                  '/linux/ipp/include/'
IPP_LIBPATH = '/var/lib/intel/compilers_and_libraries_2017.0.098' \
              '/linux/ipp/lib/intel64'

# Create a production environment.
ENV = Environment(
  CCFLAGS=['-O2', '-Wall', '-Werror'],
  CPPFLAGS=['-Wall', '-Werror'],
  CPPPATH=[IPP_INCLUDEPATH],
  LIBPATH=[IPP_LIBPATH, '.']
)

# Build the library.
ENV.Object('src/spectrograph.c')
ENV.Object('src/vector.c')
ENV.Library(
  'spectrograph',
  [
    'src/spectrograph.o',
    'src/vector.o'
  ],
  LIBS=['ippcore', 'ipps']
)

# Build and run the unit tests.
ENV.Object('tests/spectrograph_tests.cpp')
ENV.Object('tests/test_runner.cpp')
ENV.Object('tests/vector_tests.cpp')
ENV.Program(
  [
    'tests/test_runner.o',
    'tests/spectrograph_tests.o',
    'tests/vector_tests.o'
  ],
  LIBS=['gtest', 'pthread', 'spectrograph', 'ipps', 'ippcore']
)
