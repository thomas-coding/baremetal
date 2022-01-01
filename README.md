# baremetal
目的是学习 arm cpu 硬件相关知识以及qemu相关知识，计划如下：
1、写一个 Cortex-M3（armv7m） 的 baremetal code, 硬件平台为 ARM MPS2 AN385 开发版（QEMU虚拟）
Done - 2021/12/26
https://github.com/thomas-coding/baremetal.git 中baremetal-m3 部分，
完成arch相关功能学习验证，出于学习目的，没有使用libc，也没有使用CMSIS，内容包括启动代码、汇编、SCB、Exception、NVIC、Systick、MPU等

2、写一个 QEMU 的 platform（自己搭一个虚拟板子）， 跑 Cortex-M3 的 baremetal code
Done - 2021/12/31
https://github.com/thomas-coding/qemu
参考MPS2，新建machine（thomas-m3），跑setp1写的baremetal代码，了解QOM相关概念和使用，了解TCG过程

3、写一个 Cortex-M33（armv8m） 的 baremetal code, 硬件平台为 ARM MPS2 AN385 开发版（QEMU虚拟）
5% - 2022/1/1

Docs:
    https://baremetal.readthedocs.io/en/latest/
