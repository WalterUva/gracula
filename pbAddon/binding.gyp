{
  "targets": [
    {
      "target_name": "pb",

      "sources": [ "pb.cc" ],

      "include_dirs": [

        "<!(node -e \"require('nan')\")",
        "gcc-linaro-5.2-2015.11-2-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/usr/include/",
        # "gcc-linaro-5.2-2015.11-2-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc/usr/include/asm"
        # "gcc-linaro-5.2-2015.11-2-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/5.2.1/include",
        # "gcc-linaro-5.2-2015.11-2-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/5.2.1/include-fixed"
      ]
    }
  ]
}
