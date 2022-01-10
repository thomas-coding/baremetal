# baremetal
目的是学习 arm cpu 硬件相关知识以及qemu相关知识，计划如下：<br />
<br />
1、写一个 Cortex-M3（armv7m） 的 baremetal code, 硬件平台为 ARM MPS2 AN385 开发版（QEMU虚拟）<br />
Done - 2021/12/26<br />
https://github.com/thomas-coding/baremetal.git 中baremetal-m3 部分，<br />
完成arch相关功能学习验证，出于学习目的，没有使用libc，也没有使用CMSIS，内容包括启动代码、汇编、SCB、Exception、NVIC、Systick、MPU等<br />

2、写一个 QEMU 的 platform（自己搭一个虚拟板子）， 跑 Cortex-M3 的 baremetal code<br />
Done - 2021/12/31<br />
https://github.com/thomas-coding/qemu<br />
参考MPS2，新建machine（thomas-m3），跑setp1写的baremetal代码，了解QOM相关概念和使用，了解TCG过程<br />
<br />
3、写一个 Cortex-M33（armv8m） 的 baremetal code, 硬件平台为 ARM MPS2 AN385 开发版（QEMU虚拟）<br />
Done - 2022/1/10<br />
<br />
4、写一个 Cortex-A15（armv7） 的 baremetal code, 硬件平台为 ARM Virt A15 开发版（QEMU虚拟）<br />
5% - 2022/1/10<br />
安全状态跑到main函数<br />
安全状态串口<br />
安全状态mmu<br />
安全状态cache<br />
安全状态gic<br />
安全状态usr mode以及svc<br />
非安全状态main函数<br />
非安全状态mmu、cache、gic<br />
<br />

<br />
Docs:<br />
    https://baremetal.readthedocs.io/en/latest/
