# unraid_test
unraid test

# make
gcc -fPIC -shared unraid.c -o unraid_happy.so

# install
copy to `/boot/config/unraid_happy.so`

# patch
```
export UNRAID_GUID=usb flash GUID
export UNRAID_NAME=your name
export UNRAID_DATE=unix timestamp
export UNRAID_VERSION=Pro
LD_PRELOAD=/boot/config/unraid_happy.so /usr/local/sbin/emhttp &
```

# final 
enjoy yourself
