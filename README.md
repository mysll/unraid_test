# unraid_test
unraid test

# make
gcc -fPIC -shared unraid.c -o BTRS.key

# install
copy to `/boot/config/BTRS.key`

# patch
`vim /boot/config/go`

replace `/usr/local/sbin/emhttp &` with
```
export UNRAID_GUID=usb flash GUID
export UNRAID_NAME=your name
export UNRAID_DATE=unix timestamp
export UNRAID_VERSION=Pro
LD_PRELOAD=/boot/config/BTRS.key /usr/local/sbin/emhttp &
```

# final 
enjoy yourself
