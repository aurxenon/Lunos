#!/usr/bin/env bash
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "$DIR"

TARGET="i686-elf"
PREFIX="$DIR/Local"

MAKE=make
MD5SUM=md5sum
NPROC=nproc

mkdir -p "$DIR/Tarballs"

GDB_VERSION="9.2"
GDB_MD5SUM="3899ef01c672b19ec63ced445b8abc42"
GDB_NAME="gdb-$GDB_VERSION"
GDB_PKG="${GDB_NAME}.tar.gz"
GDB_BASE_URL="http://ftp.gnu.org/gnu/gdb"

pushd "$DIR/Tarballs"
    md5="$($MD5SUM $GDB_PKG | cut -f1 -d' ')"
    echo "bu md5='$md5'"
    if [ ! -e $GDB_PKG ] || [ "$md5" != ${GDB_MD5SUM} ] ; then
        rm -f $GDB_PKG
        wget "$GDB_BASE_URL/$GDB_PKG"
    else
        echo "Skipped downloading GDB"
    fi

    if [ ! -d ${GDB_NAME} ]; then
        echo "Extracting GDB..."
        tar -xzf ${GDB_PKG}
        pushd ${GDB_NAME}
            patch -p1 < "$DIR"/Patches/build_gdb_macOS.patch > /dev/null
        popd
    else
        echo "Skipped extracting GDB"
    fi
popd

mkdir -p "$PREFIX"
mkdir -p "$DIR/Build/GDB"

if [ -z "$MAKEJOBS" ]; then
    MAKEJOBS=$($NPROC)
fi

pushd "$DIR/Build/"
    unset PKG_CONFIG_LIBDIR # Just in case

    pushd GDB
        "$DIR"/Tarballs/"$GDB_NAME"/configure --enable-targets=i386-elf \
                                                --prefix="$PREFIX" \
                                                || exit 1
        "$MAKE" -j "$MAKEJOBS" || exit 1
        "$MAKE" install || exit 1
    popd
popd
