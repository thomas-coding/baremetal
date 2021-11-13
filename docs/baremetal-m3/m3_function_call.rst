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





