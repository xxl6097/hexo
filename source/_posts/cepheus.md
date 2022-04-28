---
title: 小米9基于PixelExperience源码编译步骤
date: 2022-04-28 23:05:47
tags: [cepheus,proxy,android]
---

# Pixel Experience #

### Sync ###

```bash

# Initialize local repository
repo init -u https://github.com/PixelExperience/manifest -b twelve

# Sync
repo sync -c -j$(nproc --all) --force-sync --no-clone-bundle --no-tags
```

### Build ###

```bash

# Set up environment
$ . build/envsetup.sh

# Choose a target
$ lunch aosp_$device-userdebug

# Build the code
$ mka bacon -jX
```

### Submitting Patches ###

Patches are always welcome! Please submit your patches to our Gerrit.

[Gerrit push guide](https://wiki.pixelexperience.org/help/submit-patch/)