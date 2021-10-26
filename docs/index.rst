.. Baremetal documentation master file, created by
   sphinx-quickstart on Sat Oct 23 13:22:31 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to Baremetal's documentation!
=====================================

| 目的是学习 arm cpu 硬件相关知识以及qemu相关知识，计划如下：
| 1、写一个 Cortex-M3 的 baremetal code, 硬件平台为 ARM MPS2 AN385 开发版（QEMU虚拟）
| 2、写一个 QEMU 的 platform（自己搭一个虚拟板子）， 跑 Cortex-M3 的 baremetal code
| 3、学习其他core及外设，完善自己的 qemu platform

一入QEMU深似海，预期第二个任务会比较难

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   baremetal-m3/index.rst
   baremetal-a15/index.rst


