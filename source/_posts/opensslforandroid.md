---
title: Android 编译 openssl 的注意事项
date: 2022-07-21 10:01:47
tags: [openssl,ndk,Android]
categories:
- [ndk]
- [openssl]
---

<!--more-->


以下载链接https://www.openssl.org/source/openssl-1.1.1o.tar.gz为例<br>
下载解压之后，查看根目录的 NOTES.ANDROID，其中有

```asm

export ANDROID_NDK_HOME=/home/whoever/Android/android-sdk/ndk/20.0.5594570
PATH=$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin:$ANDROID_NDK_HOME/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin:$PATH
./Configure android-arm64 -D__ANDROID_API__=29
make

```

这里就是最直接的编译方式了。但是这样编译之后，会有一个坑<br>

```asm

lrwxrwxrwx  1 ubuntu ubuntu      16 Jun  9 21:23 libcrypto.so -> libcrypto.so.1.1
-rwxrwxr-x  1 ubuntu ubuntu 2754216 Jun  9 21:23 libcrypto.so.1.1
lrwxrwxrwx  1 ubuntu ubuntu      13 Jun  9 21:23 libssl.so -> libssl.so.1.1
-rwxrwxr-x  1 ubuntu ubuntu  596600 Jun  9 21:23 libssl.so.1.1

```

编译时尝试链接 libssl.so ，实际上会链接到 libssl.so.1.1 ，但是当你尝试将 libssl.so.1.1 集成到 Android studio 工程内时，会发现 libssl.so.1.1 这种命名格式so，Android studio 是不会自动将其打包到 apk 内的，即使将 libssl.so.1.1 改名为 libssl.so 可以集成到 apk ，app运行时仍然会去找 libssl.so.1.1。因为 so 内部有其文件名信息

```asm

$objdump -p libssl.so | grep SONAME
  SONAME               libssl.so.1.1

```

对于Android来说，我们更希望，编译之后，so 本身名字就叫 libssl.so。
具体做法是解压 openssl-1.1.1o.tar.gz 之后，修改 15-android.conf
大概 193 行

```asm

my %targets = (
    "android" => {
        inherit_from     => [ "linux-generic32" ],
        template         => 1,
        ################################################################
        # Special note about -pie. The underlying reason is that
        # Lollipop refuses to run non-PIE. But what about older systems
        # and NDKs? -fPIC was never problem, so the only concern is -pie.
        # Older toolchains, e.g. r4, appear to handle it and binaries
        # turn out mostly functional. "Mostly" means that oldest
        # Androids, such as Froyo, fail to handle executable, but newer
        # systems are perfectly capable of executing binaries targeting
        # Froyo. Keep in mind that in the nutshell Android builds are
        # about JNI, i.e. shared libraries, not applications.
        cflags           => add(sub { android_ndk()->{cflags} }),
        cppflags         => add(sub { android_ndk()->{cppflags} }),
        cxxflags         => add(sub { android_ndk()->{cflags} }),
        bn_ops           => sub { android_ndk()->{bn_ops} },
        bin_cflags       => "-pie",
        enable           => [ ],
        shared_extension => ".so",  ### 这一行是新加的
    },
    
```

这样可以编译出来不带版本后缀的 libssl.so 和 libcrypto.so

可以参考下边的懒人脚本来自行编译

```asm

#!/bin/bash

function buildopenssl()
{
    androidarch=$1
    toolchain=$2
    if [ ! -f openssl-1.1.1o.tar.gz ]; then
        wget https://www.openssl.org/source/openssl-1.1.1o.tar.gz
    fi
    if [ !-d openssl-1.1.1o ]; then
        tar -xf openssl-1.1.1o.tar.gz
    fi
    if [ -z $ANDROID_NDK_HOME ]; then
        echo "missing ANDROID_NDK_HOME"
        exit
    fi
    pushd openssl-1.1.1o
    PATH=$ANDROID_NDK_HOME/toolchains/llvm/prebuilt/linux-x86_64/bin:$ANDROID_NDK_HOME/toolchains/${toolchain}-linux-androideabi-4.9/prebuilt/linux-x86_64/bin:$PATH
    ./Configure android-$androidarch -D__ANDROID_API__=26
    make clean
    make
    popd
}

buildopenssl arm64 aarch64
#buildopenssl arm arm
#buildopenssl x86 x86
#buildopenssl x86_64 x86_64


```

使用时，将 NDK_HOME传入，例如，脚本保存为 build.sh，则执行命令

```asm
ANDROID_NDK_HOME=/home/whoever/android-ndk-r21e ./build_android_openssl.sh


```

想为 Android (arm/x86/x86_64)编译时，修改脚本末尾的 buildopenssl 注释

[友情链接](https://www.cnblogs.com/SupperMary/p/16361303.html?share_token=D86811DE-FA19-49BF-A4AB-B50D1D50C467&tt_from=copy_link&utm_source=copy_link&utm_medium=toutiao_ios&utm_campaign=client_share)