One, download the source code
  Open the virtual machine, enter the terminal and enter the following command:
    microcreat@microcreat:/workdir$ git clone https://github.com/microcreat/cortexm_uclinux.git
  And then into download mode, the following is the process of downloading:
    microcreat@microcreat:/workdir$ git clone https://github.com/microcreat/cortexm_uclinux.git
    Cloning into cortexm_uclinux...
    remote: Counting objects: 45201, done.
    remote: Compressing objects: 100% (37476/37476), done.
    remote: Total 45201 (delta 8745), reused 43510 (delta 7054)
    Receiving objects: 100% (45201/45201), 206.37 MiB | 24 KiB/s, done.
    Resolving deltas: 100% (8745/8745), done.

Second, compile code package	
  sudo make 
  ......
  Image Name:   Linux-2.6.33-arm1
  Created:      Sun Jul 28 21:52:05 2013
  Image Type:   ARM Linux Kernel Image (uncompressed)
  Data Size:    1314960 Bytes = 1284.14 kB = 1.25 MB
  Load Address: a0008000
  Entry Point:  a0008001
  Image arch/arm/boot/uImage is ready
  make[1]: Leaving directory `/workdir/cortexm_uclinux/kernel/linux-2.6.33'
  sudo rm -rf /bin/mkimage
  cp -af /workdir/cortexm_uclinux/kernel/linux-2.6.33/arch/arm/boot/uImage /workdir/cortexm_uclinux/out
  
Three, compiled help
  microcreat@microcreat:/workdir/cortexm_uclinux$ make help
  ----------------------------------------
    You can use the following command    
  compile the uboot:
    make uboot; make uboot_clean;
  compile the kernel:
    make kernel; make kernel_clean;
  compile the rootfs:
    make rootfs; make rootfs_clean;
  clean the target:
    make clean;
----------------------------------------
