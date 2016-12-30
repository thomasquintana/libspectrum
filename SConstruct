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
ENV.Object('src/dsp.c')
ENV.Object('src/spectrograph.c')
ENV.Library(
  'spectrograph',
  [
    'src/dsp.o',
    'src/spectrograph.o'
  ],
  LIBS=['ippcore', 'ipps']
)

# Build and run the unit tests.
ENV.Object('tests/dsp_tests.cpp')
ENV.Object('tests/spectrograph_tests.cpp')
ENV.Object('tests/test_runner.cpp')
ENV.Program(
  [
    'tests/test_runner.o',
    'tests/dsp_tests.o',
    'tests/spectrograph_tests.o'
  ],
  LIBS=['gtest', 'pthread', 'spectrograph', 'ipps', 'ippcore']
)

#ENV.Execute('tests/spectrograph_tests')
