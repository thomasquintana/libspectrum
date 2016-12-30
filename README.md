# libspectrum

A library to generate partial and/or complete log power spectrums of an input signal in C. The library makes a couple of assumptions listed below which have been hard-coded into the source code.

* The windowing function is the hann function.
* The window size is 128.

### Installing Dependencies

#### Install Linux Dependencies (Ubuntu)

```
sudo apt-get install -y build-essential binutils g++ gcc scons
```

#### Install Intel Performance Primitives Library

The libspectrum library uses the [Intel Performance Primitives Library](https://software.intel.com/en-us/intel-ipp). When installing this library make sure the install path is changed to `/var/lib/intel`. If the library is installed to a different location then the `IPP_INCLUDEPATH` and `IPP_LIBPATH` variables have to be updated in the `SConstruct` file located in the the project's root folder.

After the installation is complete create a new file `/etc/ld.so.conf.d/intel_ipp.conf` and paste the following into it:

```
/var/lib/intel/compilers_and_libraries_2017.0.098/linux/ipp/lib/intel64
``` 

*Keep in mind if the library was installed to a different path then the path should be updated in the `/etc/ld.so.conf.d/intel_ipp.conf` file as well.*

Finally, inform the dynamic loader of our new libraries by running the following command:

```
$] sudo ldconfig
```

### Compiling libspectrum (Static Library)

```
$] git clone https://github.com/thomasquintana/libspectrum.git
$] cd libspectrum
$] scons
```

Once, `libspectrum` is compiled run the unit tests.

```
$] tests/test_runner
```
