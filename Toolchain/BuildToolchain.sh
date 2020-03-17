#!/usr/bin/env bash
set -e
# This file is ripped right from https://github.com/SerenityOS/serenity
# Thank you to all of the SerenityOS contributors who helped create this file
# This file will need to be run in bash, for now.


# === CONFIGURATION AND SETUP ===

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "$DIR"

TARGET="i686-elf"
PREFIX="$DIR/Local"

MAKE=make
MD5SUM=md5sum
NPROC=nproc

echo PREFIX is "$PREFIX"

mkdir -p "$DIR/Tarballs"

BINUTILS_VERSION="2.33.1"
BINUTILS_MD5SUM="1a6b16bcc926e312633fcc3fae14ba0a"
BINUTILS_NAME="binutils-$BINUTILS_VERSION"
BINUTILS_PKG="${BINUTILS_NAME}.tar.gz"
BINUTILS_BASE_URL="http://ftp.gnu.org/gnu/binutils"

GCC_VERSION="9.2.0"
GCC_MD5SUM="e03739b042a14376d727ddcfd05a9bc3"
GCC_NAME="gcc-$GCC_VERSION"
GCC_PKG="${GCC_NAME}.tar.gz"
GCC_BASE_URL="http://ftp.gnu.org/gnu/gcc"

# === DOWNLOAD AND PATCH ===

pushd "$DIR/Tarballs"
    md5="$($MD5SUM $BINUTILS_PKG | cut -f1 -d' ')"
    echo "bu md5='$md5'"
    if [ ! -e $BINUTILS_PKG ] || [ "$md5" != ${BINUTILS_MD5SUM} ] ; then
        rm -f $BINUTILS_PKG
        wget "$BINUTILS_BASE_URL/$BINUTILS_PKG"
    else
        echo "Skipped downloading binutils"
    fi

    md5="$($MD5SUM ${GCC_PKG} | cut -f1 -d' ')"
    echo "gc md5='$md5'"
    if [ ! -e $GCC_PKG ] || [ "$md5" != ${GCC_MD5SUM} ] ; then
        rm -f $GCC_PKG
        wget "$GCC_BASE_URL/$GCC_NAME/$GCC_PKG"
    else
        echo "Skipped downloading gcc"
    fi

    if [ ! -d ${BINUTILS_NAME} ]; then
        echo "Extracting binutils..."
        tar -xzf ${BINUTILS_PKG}
    else
        echo "Skipped extracting binutils"
    fi

    if [ ! -d $GCC_NAME ]; then
        echo "Extracting gcc..."
        tar -xzf $GCC_PKG
    else
        echo "Skipped extracting gcc"
    fi

    if [ "$(uname)" = "Darwin" ]; then
        pushd "gcc-${GCC_VERSION}"
        ./contrib/download_prerequisites
        popd
    fi
popd


# === COMPILE AND INSTALL ===

mkdir -p "$PREFIX"
mkdir -p "$DIR/Build/binutils"
mkdir -p "$DIR/Build/gcc"

if [ -z "$MAKEJOBS" ]; then
    MAKEJOBS=$($NPROC)
fi

pushd "$DIR/Build/"
    unset PKG_CONFIG_LIBDIR # Just in case

    pushd binutils
        "$DIR"/Tarballs/binutils-2.33.1/configure --target=$TARGET \
                                                --prefix="$PREFIX" \
                                                --with-sysroot \
                                                --disable-nls \
                                                --disable-werror \
                                                || exit 1
        if [ "$(uname)" = "Darwin" ]; then
            # under macOS generated makefiles are not resolving the "intl"
            # dependency properly to allow linking its own copy of
            # libintl when building with --enable-shared.
            "$MAKE" -j "$MAKEJOBS" || true
            pushd intl
            "$MAKE" all-yes
            popd
        fi
        "$MAKE" -j "$MAKEJOBS" || exit 1
        "$MAKE" install || exit 1
    popd

    pushd gcc
        "$DIR"/Tarballs/gcc-9.2.0/configure --target=$TARGET \
                                                --prefix="$PREFIX" \
                                                --disable-nls \
                                                --enable-languages=objc,obj-c++,c,c++ \
                                                --without-headers \
                                                || exit 1

        echo "XXX build gcc and libgcc"
        "$MAKE" -j "$MAKEJOBS" all-gcc all-target-libgcc || exit 1
        echo "XXX install gcc and libgcc"
        "$MAKE" install-gcc install-target-libgcc || exit 1
    popd
popd