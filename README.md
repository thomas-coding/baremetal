# baremetal
目的是学习 arm cpu 硬件相关知识以及qemu相关知识，记录如下：<br />
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
https://github.com/thomas-coding/baremetal.git 中baremetal-m33 部分，<br />
完成Trustzone相关功能验证，出于学习目的，没有使用libc，也没有使用CMSIS，内容包括S和NS两个image，S侧SAU、PPC、MPC配置，S->NS，NS->NSC->S， BXNS、SG指令验证<br />

<br />
4、写一个 Cortex-A15（armv7） 的 baremetal code, 硬件平台为 ARM Virt A15 开发版（QEMU虚拟）<br />
Done - 2022/1/22<br />
完成启动代码，完成如下模块：串口，mmu，cache，gic，generic timer，完成异常处理，模式切换usr-svc，完成smc两个世界切换验证<br />

<br />
5、Qemu thomas-m3 machine + Freerots thomas-m3 demo<br />
Done - 2022/4/17<br />
学习Qemu arm cortex-m3 相关代码，包括cpu、memory、中断、device等，完成qemu thomas-m3 machine 搭建，在这个machine上跑Freertos（新建THOMAS_M3_QEMU demo工程）<br />
相关代码提交：<br />
https://github.com/thomas-coding/FreeRTOS<br />
https://github.com/thomas-coding/qemu<br />

<br />
6、Qemu thomas-m33 machine, 跑 TFM + Freerots<br />
Done - 2022/4/24<br />
6.1 Qemu 搭建 thomas-m33 machine，只包含基本的m33 core（带sau）<br />
6.2 TFM 中针对这个qemu board 新建platform <br />
6.3 FreeRTOS 中针对这个qemu board 新建 Demo <br />
TFM 和 freerots 可以在这个qemu board上正常跑起来，后续还要加下MPC、PPC，tfm中加个sp，更完整些 <br />
相关代码提交：<br />
https://github.com/thomas-coding/FreeRTOS<br />
https://github.com/thomas-coding/qemu<br />
https://github.com/thomas-coding/trusted-firmware-m<br />

<br />
7、Qemu搭建 thomas-a15 machine,  跑 baremetal <br />
Done - 2022/5/8<br />
7.1 Qemu 搭建 thomas-a15 machine   <br />
7.2 Baremetal 新建工程qemu-bm-thomas-a15，跑在qemu machine thomas-a15 上 <br />

相关代码提交：<br />
https://github.com/thomas-coding/baremetal.git 中 qemu-bm-thomas-a15 部分，<br />
https://github.com/thomas-coding/qemu<br />

<br />
8、Qemu thomas-a15 machine,  跑 freertos <br />
Done - 2022/7/30<br />
8.1 FreeRTOS 中针对这个qemu board 新建 Demo, task可以正常调度运行 <br />
接下来要在这个board上实现freertos的smp功能

相关代码提交：<br />
https://github.com/thomas-coding/FreeRTOS<br />

<br />
9、Qemu thomas-riscv32 machine,  跑 baremetal 和 freertos <br />
Done - 2022/9/30<br />
9.1 Baremetal 跑riscv基本start 代码，clint，plinc 中断相关代码 <br />
9.2 FreeRTOS 中针对这个qemu board 新建 Demo, task可以正常调度运行 <br />

相关代码提交：<br />
https://github.com/thomas-coding/FreeRTOS<br />


<br />
Docs:<br />
    https://baremetal.readthedocs.io/en/latest/
