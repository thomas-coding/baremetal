7、函数调用
==========================================

| 这一小节我们来看下arm函数调用处理流程
| 参考文档：
| IHI0042J_2020Q2_aapcs32.pdf


7.1 函数调用代码 
-------------------------------------------
最简单情况，main函数中调用一个空的test函数

.. code-block:: c

    void test(void)
    {

    }

    int main(void)
    {
        test();
        return 0;
    }

对应汇编：

::

	00000024 <test>:
	24:	b480      	push	{r7}
	26:	af00      	add	r7, sp, #0
	28:	bf00      	nop
	2a:	46bd      	mov	sp, r7
	2c:	bc80      	pop	{r7}
	2e:	4770      	bx	lr

	0000008c <main>:
	8c:	b580      	push	{r7, lr}
	8e:	af00      	add	r7, sp, #0
	90:	f7ff ffc8 	bl	24 <test>
	94:	2300      	movs	r3, #0
	96:	4618      	mov	r0, r3
	98:	bd80      	pop	{r7, pc}
	9a:	bf00      	nop


.. note::
	| 1. 0x90行bl执行跳转指令，这时候core会把下一条指令地址0x94赋值给lr，然后把test函数的地址0x24赋值给pc。
	| 2. r0-r3 4个寄存器用于传递参数，子程序需要负责保护的寄存器：r4-r8, r10, r11 and SP，子程序返回后这些寄存器不能变化。
	| 3. 看我们这里的test子程序，入口先把r7保存到栈上，接下来把sp保存到r7，然后执行程序本身（因为是空函数，所以只有一条nop指令）。 
	| 4. 返回时先把r7赋值给sp，其实就是恢复入口时的sp，然后把r7从栈上取出来恢复。这样这个程序用到的sp、r7做了保存恢复工作，如果需要用到其他寄存器，处理方法一样的。
	| 5. 最后执行bx lr，之前bl跳到子程序时，core已经帮我们把程序返回后下一条要执行的指令（0x94）赋值给lr了，所以这里bx lr，即跳转到0x94去执行，实现了函数返回。


7.2 传参和返回值  
-------------------------------------------

.. code-block:: c

	int test(int a)
	{
		return 100;
	}

	int main(void)
	{
		int ret;

		ret = test(10);
		return 0;
	}

.. code-block::
	:emphasize-lines: 7,8,17

	00000024 <test>:
	24:	b480      	push	{r7}
	26:	b083      	sub	sp, #12
	28:	af00      	add	r7, sp, #0
	2a:	6078      	str	r0, [r7, #4]
	2c:	2364      	movs	r3, #100	; 0x64
	2e:	4618      	mov	r0, r3
	30:	370c      	adds	r7, #12
	32:	46bd      	mov	sp, r7
	34:	bc80      	pop	{r7}
	36:	4770      	bx	lr

	00000094 <main>:
	94:	b580      	push	{r7, lr}
	96:	b082      	sub	sp, #8
	98:	af00      	add	r7, sp, #0
	9a:	200a      	movs	r0, #10
	9c:	f7ff ffc2 	bl	24 <test>
	a0:	6078      	str	r0, [r7, #4]
	a2:	2300      	movs	r3, #0
	a4:	4618      	mov	r0, r3
	a6:	3708      	adds	r7, #8
	a8:	46bd      	mov	sp, r7
	aa:	bd80      	pop	{r7, pc}

.. note::
	相对上一个程序，多了入参和返回，main函数中0x9a地址的指令，把入参10赋值给了r0，子程序中0x2c地址的指令把返回值100赋值给了r3，0x2e地址的指令把r3赋值给了r0，最终100放在了r0中返回给main函数。



7.3 栈的使用
-------------------------------------------

代码如下：在入口函数中增加一个Assemble_learn函数的调用，在子函数中通过push和pop操作栈

.. code-block::

		.thumb_func
	Assemble_learn:
		push	{r0-r7}						/* Save registers to stack , thumbe only support r0-r7*/
		add     r7, sp, #0					/* Save sp to r7 */

		mov		r0, #0
		mov		r1, #0
		mov		r2, #0
		mov		r3, #0
		mov		r4, #0
		mov		r5, #0
		mov		r6, #0

		mov     sp, r7						/* Restore sp*/
		pop		{r0-r7}						/* Restore registers*/
		bx		lr							/* Return*/

		.thumb_func
		.globl   Reset_Handler
	Reset_Handler:
		mov		r0, #0
		mov		r1, #1
		mov		r2, #2
		mov		r3, #3
		mov		r4, #4
		mov		r5, #5
		mov		r6, #6
		mov		r7, #7
		bl		Assemble_learn
		mov		r7, #6
		bl		main
		mov		r3, #4
		b		.
		mov		r2, #4


1.进入Assemble_learn之前打印sp内容：
sp             0x400000            0x400000

.. code-block::

	(gdb) x/16xw 0x400000-16*4
	0x3fffc0:       0x00000000      0x00000000      0x00000000      0x00000000
	0x3fffd0:       0x00000000      0x00000000      0x00000000      0x00000000
	0x3fffe0:       0x00000000      0x00000000      0x00000000      0x00000000
	0x3ffff0:       0x00000000      0x00000000      0x00000000      0x00000000

当前sp指向 0x400000， 在栈顶，栈里面的内容都是0


2.接下来跑完 push	{r0-r7}	 指令后再看现场：

sp             0x3fffe0            0x3fffe0

.. code-block::

	(gdb) x/16xw 0x400000-16*4
	0x3fffc0:       0x00000000      0x00000000      0x00000000      0x00000000
	0x3fffd0:       0x00000000      0x00000000      0x00000000      0x00000000
	0x3fffe0:       0x00000000      0x00000001      0x00000002      0x00000003
	0x3ffff0:       0x00000004      0x00000005      0x00000006      0x00000007

可以看到sp指针指向了0x3fffe0，stack中最后8个4字节保存了r0-r7，其中r7最先保存


3.接下来看跑完pop		{r0-r7}	指令后，现场情况

sp             0x400000            0x400000

.. code-block::

	(gdb)  x/16xw 0x400000-16*4
	0x3fffc0:       0x00000000      0x00000000      0x00000000      0x00000000
	0x3fffd0:       0x00000000      0x00000000      0x00000000      0x00000000
	0x3fffe0:       0x00000000      0x00000001      0x00000002      0x00000003
	0x3ffff0:       0x00000004      0x00000005      0x00000006      0x00000007

栈顶回到了0x400000，栈中数据还在（因为没人清），但是这部分数据不会再有人用了，当下次执行push指令时，会覆盖掉

.. note::
	| 总结下函数调用：
	| 1、执行BL跳转指令时，硬件把下一条要执行的指令放入LR，然后把子函数地址赋值给pc后执行子函数。
	| 2、字函数执行完成后，BX lr 即可执行主函数中下一条指令，即实现了函数返回。
	| 3、c程序入参和返回通过r0-r4来传递（超过了会使用sp），编译器会处理。
	| 4、栈从高地址向低地址增长，通过push指令把寄存器值保存到栈上，通过pop指令恢复。




