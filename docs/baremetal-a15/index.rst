Baremetal A15
=====================================

参考资料：

| QEMU virt 平台：
|  https://qemu-project.gitlab.io/qemu/system/arm/virt.html
|  DDI0406C_d_armv7ar_arm.pdf
|  DDI0388I_cortex_a9_r4p1_trm.pdf (A15 arm doc没找到，只有A9、A32可以参考)

| ARM 手册：
|  DDI0406C_d_armv7ar_arm.pdf
|  DDI0388I_cortex_a9_r4p1_trm.pdf (A15 arm doc没找到，只有A9、A32可以参考)

| QEMU:
|   qemu-6.0.0
|   hw/arm/virt.c （硬件相关实现参考代码）

Toolchain:
   gcc-arm-10.3-2021.07-x86_64-arm-none-eabi

ARM 参考代码：
   https://github.com/ARM-software/CMSIS_5/tree/develop/Device/ARM/ARMCA9

代码：
   https://github.com/thomas-coding/baremetal

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   begin.rst


