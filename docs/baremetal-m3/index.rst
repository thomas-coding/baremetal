Baremetal M3
=====================================

参考资料：

| MPS2 平台：
|  https://developer.arm.com/tools-and-software/development-boards/fpga-prototyping-boards/mps2
|  DAI0385D_cortex_m3_on_v2m_mps2.pdf
|  DDI0479D_m_class_processor_system_r1p1_trm.pdf

ARM m3 手册：
   DUI0552A_cortex_m3_dgug.pdf

QEMU:
   qemu-6.0.0

Toolchain:
   gcc-arm-none-eabi-10-2020-q4-major

ARM 参考代码：
   https://github.com/ARM-software/CMSIS_5/tree/develop/Device/ARM/ARMCM3

代码：
   https://github.com/thomas-coding/baremetal

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   begin.rst
   m3_start.rst
   m3_add_makefile_and_lds.rst
   m3_add_main_function.rst
   m3_add_log.rst
   m3_ld.rst
   m3_function_call.rst
   m3_exception.rst


