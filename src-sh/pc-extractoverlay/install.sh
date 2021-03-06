#!/bin/sh

DEFAULT="/usr/local"

if [ -z "$1" ] ; then
        LB="${DEFAULT}"
else
        LB="${1}"
fi

cp pc-extractoverlay ${LB}/bin/pc-extractoverlay
if [ $? -ne 0 ] ; then
  exit 1
fi
chmod 755 ${LB}/bin/pc-extractoverlay
if [ $? -ne 0 ] ; then
  exit 1
fi

if [ ! -d "${LB}/share/pcbsd/conf" ] ; then
  mkdir -p ${LB}/share/pcbsd/conf
fi
if [ ! -d "${LB}/share/pcbsd/distfiles" ] ; then
  mkdir -p ${LB}/share/pcbsd/distfiles
fi

# Copy port prune list
cp prune-port-files ${LB}/share/pcbsd/conf
if [ $? -ne 0 ] ; then
  exit 1
fi

# Copy exclude list
cp port-excludes ${LB}/share/pcbsd/conf
if [ $? -ne 0 ] ; then
  exit 1
fi
cp desktop-excludes ${LB}/share/pcbsd/conf
if [ $? -ne 0 ] ; then
  exit 1
fi
cp server-excludes ${LB}/share/pcbsd/conf
if [ $? -ne 0 ] ; then
  exit 1
fi

# Now create overlay.txz file
tar cvJ --uname "root" --gname "wheel" -f ${LB}/share/pcbsd/distfiles/port-overlay.txz -C ports-overlay .
if [ $? -ne 0 ] ; then
  exit 1
fi

# Now create desktop-overlay.txz file
tar cvJ --uname "root" --gname "wheel" -f ${LB}/share/pcbsd/distfiles/desktop-overlay.txz -C desktop-overlay .
if [ $? -ne 0 ] ; then
  exit 1
fi

# Now create server-overlay.txz file
tar cvJ --uname "root" --gname "wheel" -f ${LB}/share/pcbsd/distfiles/server-overlay.txz -C server-overlay .
if [ $? -ne 0 ] ; then
  exit 1
fi

exit 0
