#
# This script obtains the sources for and builds a cross compiler
# for the i686-elf target.
# Place this script in the directory where you would like the cross
# compiler built and installed. You will need to set the path to 
# the cross compiler bin directory once the build is complete.
#

# Obtain the sources.
wget http://ftpmirror.gnu.org/binutils/binutils-2.24.tar.gz
wget http://ftpmirror.gnu.org/gcc/gcc-4.9.2/gcc-4.9.2.tar.gz
wget http://ftpmirror.gnu.org/glibc/glibc-2.20.tar.xz
wget http://ftpmirror.gnu.org/mpfr/mpfr-3.1.2.tar.xz
wget http://ftpmirror.gnu.org/gmp/gmp-6.0.0a.tar.xz
wget http://ftpmirror.gnu.org/mpc/mpc-1.0.2.tar.gz
wget ftp://gcc.gnu.org/pub/gcc/infrastructure/isl-0.12.2.tar.bz2
wget ftp://gcc.gnu.org/pub/gcc/infrastructure/cloog-0.18.1.tar.gz

# Extract sources.
for f in *.tar*; do tar xf $f; done

# Create symbolic links from the bin utils directory to the sources.
cd binutils-2.24
ln -s ../isl-0.12.2 isl
ln -s ../cloog-0.18.1 cloog
cd ..

# Create symbolic links from the gcc directory to the sources.
cd gcc-4.9.2
ln -s ../mpfr-3.1.2 mpfr
ln -s ../gmp-6.0.0 gmp
ln -s ../mpc-1.0.2 mpc
ln -s ../isl-0.12.2 isl
ln -s ../cloog-0.18.1 cloog
cd ..

# Set the environment.
export PREFIX=$(pwd)
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
echo "PREFIX: $PREFIX"
echo "TARGET: $TARGET"
echo "  PATH: $PATH"

# Build and install binutils.
mkdir build-binutils
cd build-binutils
../binutils-2.24/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

# Build and install gcc.
mkdir build-gcc
cd build-gcc
../gcc-4.9.2/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
cd ..
