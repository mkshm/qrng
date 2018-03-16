
qrng:     file format elf32-avr


Disassembly of section .mmcu:

00910000 <_AVR_MMCU_TAG_VCD_PERIOD23>:
  910000:	0d 04 40 42 0f 00                                   ..@B..

00910006 <_AVR_MMCU_TAG_VCD_FILENAME>:
  910006:	0c 40 6c 61 73 65 72 2e 76 63 64 00 00 00 00 00     .@laser.vcd.....
	...

00910048 <_AVR_MMCU_TAG_AREF22>:
  910048:	05 04 05 00 00 00                                   ......

0091004e <_AVR_MMCU_TAG_AVCC22>:
  91004e:	04 04 05 00 00 00                                   ......

00910054 <_AVR_MMCU_TAG_VCC22>:
  910054:	03 04 05 00 00 00                                   ......

0091005a <_mmcu>:
	...

0091005c <_AVR_MMCU_TAG_FREQUENCY20>:
  91005c:	02 04 00 24 f4 00                                   ...$..

00910062 <_AVR_MMCU_TAG_NAME>:
  910062:	01 40 61 74 6d 65 67 61 33 32 38 70 00 00 00 00     .@atmega328p....
	...

Disassembly of section .text:

00000000 <__vectors>:
   0:	33 c0       	rjmp	.+102    	; 0x68 <__ctors_end>
   2:	00 00       	nop
   4:	41 c0       	rjmp	.+130    	; 0x88 <__bad_interrupt>
   6:	00 00       	nop
   8:	3f c0       	rjmp	.+126    	; 0x88 <__bad_interrupt>
   a:	00 00       	nop
   c:	3d c0       	rjmp	.+122    	; 0x88 <__bad_interrupt>
   e:	00 00       	nop
  10:	3b c0       	rjmp	.+118    	; 0x88 <__bad_interrupt>
  12:	00 00       	nop
  14:	39 c0       	rjmp	.+114    	; 0x88 <__bad_interrupt>
  16:	00 00       	nop
  18:	37 c0       	rjmp	.+110    	; 0x88 <__bad_interrupt>
  1a:	00 00       	nop
  1c:	35 c0       	rjmp	.+106    	; 0x88 <__bad_interrupt>
  1e:	00 00       	nop
  20:	33 c0       	rjmp	.+102    	; 0x88 <__bad_interrupt>
  22:	00 00       	nop
  24:	31 c0       	rjmp	.+98     	; 0x88 <__bad_interrupt>
  26:	00 00       	nop
  28:	47 c0       	rjmp	.+142    	; 0xb8 <__vector_10>
  2a:	00 00       	nop
  2c:	2d c0       	rjmp	.+90     	; 0x88 <__bad_interrupt>
  2e:	00 00       	nop
  30:	2b c0       	rjmp	.+86     	; 0x88 <__bad_interrupt>
  32:	00 00       	nop
  34:	2a c0       	rjmp	.+84     	; 0x8a <__vector_13>
  36:	00 00       	nop
  38:	27 c0       	rjmp	.+78     	; 0x88 <__bad_interrupt>
  3a:	00 00       	nop
  3c:	25 c0       	rjmp	.+74     	; 0x88 <__bad_interrupt>
  3e:	00 00       	nop
  40:	23 c0       	rjmp	.+70     	; 0x88 <__bad_interrupt>
  42:	00 00       	nop
  44:	21 c0       	rjmp	.+66     	; 0x88 <__bad_interrupt>
  46:	00 00       	nop
  48:	1f c0       	rjmp	.+62     	; 0x88 <__bad_interrupt>
  4a:	00 00       	nop
  4c:	1d c0       	rjmp	.+58     	; 0x88 <__bad_interrupt>
  4e:	00 00       	nop
  50:	1b c0       	rjmp	.+54     	; 0x88 <__bad_interrupt>
  52:	00 00       	nop
  54:	19 c0       	rjmp	.+50     	; 0x88 <__bad_interrupt>
  56:	00 00       	nop
  58:	17 c0       	rjmp	.+46     	; 0x88 <__bad_interrupt>
  5a:	00 00       	nop
  5c:	15 c0       	rjmp	.+42     	; 0x88 <__bad_interrupt>
  5e:	00 00       	nop
  60:	13 c0       	rjmp	.+38     	; 0x88 <__bad_interrupt>
  62:	00 00       	nop
  64:	11 c0       	rjmp	.+34     	; 0x88 <__bad_interrupt>
	...

00000068 <__ctors_end>:
  68:	11 24       	eor	r1, r1
  6a:	1f be       	out	0x3f, r1	; 63
  6c:	cf ef       	ldi	r28, 0xFF	; 255
  6e:	d8 e0       	ldi	r29, 0x08	; 8
  70:	de bf       	out	0x3e, r29	; 62
  72:	cd bf       	out	0x3d, r28	; 61

00000074 <__do_clear_bss>:
  74:	22 e0       	ldi	r18, 0x02	; 2
  76:	a0 e0       	ldi	r26, 0x00	; 0
  78:	b1 e0       	ldi	r27, 0x01	; 1
  7a:	01 c0       	rjmp	.+2      	; 0x7e <.do_clear_bss_start>

0000007c <.do_clear_bss_loop>:
  7c:	1d 92       	st	X+, r1

0000007e <.do_clear_bss_start>:
  7e:	aa 31       	cpi	r26, 0x1A	; 26
  80:	b2 07       	cpc	r27, r18
  82:	e1 f7       	brne	.-8      	; 0x7c <.do_clear_bss_loop>
  84:	04 d1       	rcall	.+520    	; 0x28e <main>
  86:	53 c1       	rjmp	.+678    	; 0x32e <_exit>

00000088 <__bad_interrupt>:
  88:	bb cf       	rjmp	.-138    	; 0x0 <__vectors>

0000008a <__vector_13>:
  8a:	1f 92       	push	r1
  8c:	0f 92       	push	r0
  8e:	0f b6       	in	r0, 0x3f	; 63
  90:	0f 92       	push	r0
  92:	11 24       	eor	r1, r1
  94:	8f 93       	push	r24
  96:	9f 93       	push	r25
  98:	80 91 18 02 	lds	r24, 0x0218	; 0x800218 <high>
  9c:	90 91 19 02 	lds	r25, 0x0219	; 0x800219 <high+0x1>
  a0:	01 96       	adiw	r24, 0x01	; 1
  a2:	90 93 19 02 	sts	0x0219, r25	; 0x800219 <high+0x1>
  a6:	80 93 18 02 	sts	0x0218, r24	; 0x800218 <high>
  aa:	9f 91       	pop	r25
  ac:	8f 91       	pop	r24
  ae:	0f 90       	pop	r0
  b0:	0f be       	out	0x3f, r0	; 63
  b2:	0f 90       	pop	r0
  b4:	1f 90       	pop	r1
  b6:	18 95       	reti

000000b8 <__vector_10>:
  b8:	1f 92       	push	r1
  ba:	0f 92       	push	r0
  bc:	0f b6       	in	r0, 0x3f	; 63
  be:	0f 92       	push	r0
  c0:	11 24       	eor	r1, r1
  c2:	8f 92       	push	r8
  c4:	9f 92       	push	r9
  c6:	af 92       	push	r10
  c8:	bf 92       	push	r11
  ca:	cf 92       	push	r12
  cc:	df 92       	push	r13
  ce:	ef 92       	push	r14
  d0:	ff 92       	push	r15
  d2:	0f 93       	push	r16
  d4:	1f 93       	push	r17
  d6:	2f 93       	push	r18
  d8:	3f 93       	push	r19
  da:	4f 93       	push	r20
  dc:	5f 93       	push	r21
  de:	6f 93       	push	r22
  e0:	7f 93       	push	r23
  e2:	8f 93       	push	r24
  e4:	9f 93       	push	r25
  e6:	af 93       	push	r26
  e8:	bf 93       	push	r27
  ea:	ef 93       	push	r30
  ec:	ff 93       	push	r31
  ee:	20 91 86 00 	lds	r18, 0x0086	; 0x800086 <__TEXT_REGION_LENGTH__+0x7e0086>
  f2:	30 91 87 00 	lds	r19, 0x0087	; 0x800087 <__TEXT_REGION_LENGTH__+0x7e0087>
  f6:	c9 01       	movw	r24, r18
  f8:	20 91 18 02 	lds	r18, 0x0218	; 0x800218 <high>
  fc:	30 91 19 02 	lds	r19, 0x0219	; 0x800219 <high+0x1>
 100:	d9 01       	movw	r26, r18
 102:	20 91 11 01 	lds	r18, 0x0111	; 0x800111 <hit.2476>
 106:	32 2f       	mov	r19, r18
 108:	33 70       	andi	r19, 0x03	; 3
 10a:	e3 2f       	mov	r30, r19
 10c:	f0 e0       	ldi	r31, 0x00	; 0
 10e:	ee 0f       	add	r30, r30
 110:	ff 1f       	adc	r31, r31
 112:	ee 0f       	add	r30, r30
 114:	ff 1f       	adc	r31, r31
 116:	ef 5f       	subi	r30, 0xFF	; 255
 118:	fe 4f       	sbci	r31, 0xFE	; 254
 11a:	40 91 12 01 	lds	r20, 0x0112	; 0x800112 <prev.2477>
 11e:	50 91 13 01 	lds	r21, 0x0113	; 0x800113 <prev.2477+0x1>
 122:	60 91 14 01 	lds	r22, 0x0114	; 0x800114 <prev.2477+0x2>
 126:	70 91 15 01 	lds	r23, 0x0115	; 0x800115 <prev.2477+0x3>
 12a:	7c 01       	movw	r14, r24
 12c:	8d 01       	movw	r16, r26
 12e:	e4 1a       	sub	r14, r20
 130:	f5 0a       	sbc	r15, r21
 132:	06 0b       	sbc	r16, r22
 134:	17 0b       	sbc	r17, r23
 136:	b8 01       	movw	r22, r16
 138:	a7 01       	movw	r20, r14
 13a:	40 83       	st	Z, r20
 13c:	51 83       	std	Z+1, r21	; 0x01
 13e:	62 83       	std	Z+2, r22	; 0x02
 140:	73 83       	std	Z+3, r23	; 0x03
 142:	2f 5f       	subi	r18, 0xFF	; 255
 144:	20 93 11 01 	sts	0x0111, r18	; 0x800111 <hit.2476>
 148:	40 91 00 01 	lds	r20, 0x0100	; 0x800100 <_edata>
 14c:	21 e0       	ldi	r18, 0x01	; 1
 14e:	24 0f       	add	r18, r20
 150:	47 70       	andi	r20, 0x07	; 7
 152:	61 e0       	ldi	r22, 0x01	; 1
 154:	70 e0       	ldi	r23, 0x00	; 0
 156:	32 30       	cpi	r19, 0x02	; 2
 158:	09 f4       	brne	.+2      	; 0x15c <__vector_10+0xa4>
 15a:	82 c0       	rjmp	.+260    	; 0x260 <__vector_10+0x1a8>
 15c:	33 30       	cpi	r19, 0x03	; 3
 15e:	09 f4       	brne	.+2      	; 0x162 <__vector_10+0xaa>
 160:	50 c0       	rjmp	.+160    	; 0x202 <__vector_10+0x14a>
 162:	31 30       	cpi	r19, 0x01	; 1
 164:	09 f4       	brne	.+2      	; 0x168 <__vector_10+0xb0>
 166:	65 c0       	rjmp	.+202    	; 0x232 <__vector_10+0x17a>
 168:	80 90 01 01 	lds	r8, 0x0101	; 0x800101 <dt.2478>
 16c:	90 90 02 01 	lds	r9, 0x0102	; 0x800102 <dt.2478+0x1>
 170:	a0 90 03 01 	lds	r10, 0x0103	; 0x800103 <dt.2478+0x2>
 174:	b0 90 04 01 	lds	r11, 0x0104	; 0x800104 <dt.2478+0x3>
 178:	c0 90 09 01 	lds	r12, 0x0109	; 0x800109 <dt.2478+0x8>
 17c:	d0 90 0a 01 	lds	r13, 0x010A	; 0x80010a <dt.2478+0x9>
 180:	e0 90 0b 01 	lds	r14, 0x010B	; 0x80010b <dt.2478+0xa>
 184:	f0 90 0c 01 	lds	r15, 0x010C	; 0x80010c <dt.2478+0xb>
 188:	c8 14       	cp	r12, r8
 18a:	d9 04       	cpc	r13, r9
 18c:	ea 04       	cpc	r14, r10
 18e:	fb 04       	cpc	r15, r11
 190:	08 f0       	brcs	.+2      	; 0x194 <__vector_10+0xdc>
 192:	4d c0       	rjmp	.+154    	; 0x22e <__vector_10+0x176>
 194:	20 93 00 01 	sts	0x0100, r18	; 0x800100 <_edata>
 198:	e0 91 17 01 	lds	r30, 0x0117	; 0x800117 <head>
 19c:	f0 e0       	ldi	r31, 0x00	; 0
 19e:	01 c0       	rjmp	.+2      	; 0x1a2 <__vector_10+0xea>
 1a0:	66 0f       	add	r22, r22
 1a2:	4a 95       	dec	r20
 1a4:	ea f7       	brpl	.-6      	; 0x1a0 <__vector_10+0xe8>
 1a6:	e8 5e       	subi	r30, 0xE8	; 232
 1a8:	fe 4f       	sbci	r31, 0xFE	; 254
 1aa:	60 83       	st	Z, r22
 1ac:	30 91 17 01 	lds	r19, 0x0117	; 0x800117 <head>
 1b0:	23 fb       	bst	r18, 3
 1b2:	22 27       	eor	r18, r18
 1b4:	20 f9       	bld	r18, 0
 1b6:	23 0f       	add	r18, r19
 1b8:	20 93 17 01 	sts	0x0117, r18	; 0x800117 <head>
 1bc:	80 93 12 01 	sts	0x0112, r24	; 0x800112 <prev.2477>
 1c0:	90 93 13 01 	sts	0x0113, r25	; 0x800113 <prev.2477+0x1>
 1c4:	a0 93 14 01 	sts	0x0114, r26	; 0x800114 <prev.2477+0x2>
 1c8:	b0 93 15 01 	sts	0x0115, r27	; 0x800115 <prev.2477+0x3>
 1cc:	ff 91       	pop	r31
 1ce:	ef 91       	pop	r30
 1d0:	bf 91       	pop	r27
 1d2:	af 91       	pop	r26
 1d4:	9f 91       	pop	r25
 1d6:	8f 91       	pop	r24
 1d8:	7f 91       	pop	r23
 1da:	6f 91       	pop	r22
 1dc:	5f 91       	pop	r21
 1de:	4f 91       	pop	r20
 1e0:	3f 91       	pop	r19
 1e2:	2f 91       	pop	r18
 1e4:	1f 91       	pop	r17
 1e6:	0f 91       	pop	r16
 1e8:	ff 90       	pop	r15
 1ea:	ef 90       	pop	r14
 1ec:	df 90       	pop	r13
 1ee:	cf 90       	pop	r12
 1f0:	bf 90       	pop	r11
 1f2:	af 90       	pop	r10
 1f4:	9f 90       	pop	r9
 1f6:	8f 90       	pop	r8
 1f8:	0f 90       	pop	r0
 1fa:	0f be       	out	0x3f, r0	; 63
 1fc:	0f 90       	pop	r0
 1fe:	1f 90       	pop	r1
 200:	18 95       	reti
 202:	80 90 0d 01 	lds	r8, 0x010D	; 0x80010d <dt.2478+0xc>
 206:	90 90 0e 01 	lds	r9, 0x010E	; 0x80010e <dt.2478+0xd>
 20a:	a0 90 0f 01 	lds	r10, 0x010F	; 0x80010f <dt.2478+0xe>
 20e:	b0 90 10 01 	lds	r11, 0x0110	; 0x800110 <dt.2478+0xf>
 212:	c0 90 05 01 	lds	r12, 0x0105	; 0x800105 <dt.2478+0x4>
 216:	d0 90 06 01 	lds	r13, 0x0106	; 0x800106 <dt.2478+0x5>
 21a:	e0 90 07 01 	lds	r14, 0x0107	; 0x800107 <dt.2478+0x6>
 21e:	f0 90 08 01 	lds	r15, 0x0108	; 0x800108 <dt.2478+0x7>
 222:	c8 14       	cp	r12, r8
 224:	d9 04       	cpc	r13, r9
 226:	ea 04       	cpc	r14, r10
 228:	fb 04       	cpc	r15, r11
 22a:	08 f4       	brcc	.+2      	; 0x22e <__vector_10+0x176>
 22c:	b3 cf       	rjmp	.-154    	; 0x194 <__vector_10+0xdc>
 22e:	60 e0       	ldi	r22, 0x00	; 0
 230:	b1 cf       	rjmp	.-158    	; 0x194 <__vector_10+0xdc>
 232:	80 90 05 01 	lds	r8, 0x0105	; 0x800105 <dt.2478+0x4>
 236:	90 90 06 01 	lds	r9, 0x0106	; 0x800106 <dt.2478+0x5>
 23a:	a0 90 07 01 	lds	r10, 0x0107	; 0x800107 <dt.2478+0x6>
 23e:	b0 90 08 01 	lds	r11, 0x0108	; 0x800108 <dt.2478+0x7>
 242:	c0 90 0d 01 	lds	r12, 0x010D	; 0x80010d <dt.2478+0xc>
 246:	d0 90 0e 01 	lds	r13, 0x010E	; 0x80010e <dt.2478+0xd>
 24a:	e0 90 0f 01 	lds	r14, 0x010F	; 0x80010f <dt.2478+0xe>
 24e:	f0 90 10 01 	lds	r15, 0x0110	; 0x800110 <dt.2478+0xf>
 252:	c8 14       	cp	r12, r8
 254:	d9 04       	cpc	r13, r9
 256:	ea 04       	cpc	r14, r10
 258:	fb 04       	cpc	r15, r11
 25a:	08 f4       	brcc	.+2      	; 0x25e <__vector_10+0x1a6>
 25c:	9b cf       	rjmp	.-202    	; 0x194 <__vector_10+0xdc>
 25e:	e7 cf       	rjmp	.-50     	; 0x22e <__vector_10+0x176>
 260:	80 90 09 01 	lds	r8, 0x0109	; 0x800109 <dt.2478+0x8>
 264:	90 90 0a 01 	lds	r9, 0x010A	; 0x80010a <dt.2478+0x9>
 268:	a0 90 0b 01 	lds	r10, 0x010B	; 0x80010b <dt.2478+0xa>
 26c:	b0 90 0c 01 	lds	r11, 0x010C	; 0x80010c <dt.2478+0xb>
 270:	c0 90 01 01 	lds	r12, 0x0101	; 0x800101 <dt.2478>
 274:	d0 90 02 01 	lds	r13, 0x0102	; 0x800102 <dt.2478+0x1>
 278:	e0 90 03 01 	lds	r14, 0x0103	; 0x800103 <dt.2478+0x2>
 27c:	f0 90 04 01 	lds	r15, 0x0104	; 0x800104 <dt.2478+0x3>
 280:	c8 14       	cp	r12, r8
 282:	d9 04       	cpc	r13, r9
 284:	ea 04       	cpc	r14, r10
 286:	fb 04       	cpc	r15, r11
 288:	08 f4       	brcc	.+2      	; 0x28c <__vector_10+0x1d4>
 28a:	84 cf       	rjmp	.-248    	; 0x194 <__vector_10+0xdc>
 28c:	d0 cf       	rjmp	.-96     	; 0x22e <__vector_10+0x176>

0000028e <main>:
 28e:	f8 94       	cli
 290:	2f ef       	ldi	r18, 0xFF	; 255
 292:	80 e7       	ldi	r24, 0x70	; 112
 294:	92 e0       	ldi	r25, 0x02	; 2
 296:	21 50       	subi	r18, 0x01	; 1
 298:	80 40       	sbci	r24, 0x00	; 0
 29a:	90 40       	sbci	r25, 0x00	; 0
 29c:	e1 f7       	brne	.-8      	; 0x296 <main+0x8>
 29e:	00 c0       	rjmp	.+0      	; 0x2a0 <main+0x12>
 2a0:	00 00       	nop
 2a2:	81 e0       	ldi	r24, 0x01	; 1
 2a4:	90 e0       	ldi	r25, 0x00	; 0
 2a6:	90 93 c5 00 	sts	0x00C5, r25	; 0x8000c5 <__TEXT_REGION_LENGTH__+0x7e00c5>
 2aa:	80 93 c4 00 	sts	0x00C4, r24	; 0x8000c4 <__TEXT_REGION_LENGTH__+0x7e00c4>
 2ae:	80 91 c0 00 	lds	r24, 0x00C0	; 0x8000c0 <__TEXT_REGION_LENGTH__+0x7e00c0>
 2b2:	82 60       	ori	r24, 0x02	; 2
 2b4:	80 93 c0 00 	sts	0x00C0, r24	; 0x8000c0 <__TEXT_REGION_LENGTH__+0x7e00c0>
 2b8:	80 91 c2 00 	lds	r24, 0x00C2	; 0x8000c2 <__TEXT_REGION_LENGTH__+0x7e00c2>
 2bc:	8e 60       	ori	r24, 0x0E	; 14
 2be:	80 93 c2 00 	sts	0x00C2, r24	; 0x8000c2 <__TEXT_REGION_LENGTH__+0x7e00c2>
 2c2:	80 91 c1 00 	lds	r24, 0x00C1	; 0x8000c1 <__TEXT_REGION_LENGTH__+0x7e00c1>
 2c6:	88 60       	ori	r24, 0x08	; 8
 2c8:	80 93 c1 00 	sts	0x00C1, r24	; 0x8000c1 <__TEXT_REGION_LENGTH__+0x7e00c1>
 2cc:	10 92 85 00 	sts	0x0085, r1	; 0x800085 <__TEXT_REGION_LENGTH__+0x7e0085>
 2d0:	10 92 84 00 	sts	0x0084, r1	; 0x800084 <__TEXT_REGION_LENGTH__+0x7e0084>
 2d4:	80 91 81 00 	lds	r24, 0x0081	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
 2d8:	81 60       	ori	r24, 0x01	; 1
 2da:	80 93 81 00 	sts	0x0081, r24	; 0x800081 <__TEXT_REGION_LENGTH__+0x7e0081>
 2de:	80 91 6f 00 	lds	r24, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
 2e2:	81 60       	ori	r24, 0x01	; 1
 2e4:	80 93 6f 00 	sts	0x006F, r24	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
 2e8:	80 91 6f 00 	lds	r24, 0x006F	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
 2ec:	80 62       	ori	r24, 0x20	; 32
 2ee:	80 93 6f 00 	sts	0x006F, r24	; 0x80006f <__TEXT_REGION_LENGTH__+0x7e006f>
 2f2:	78 94       	sei
 2f4:	90 91 16 01 	lds	r25, 0x0116	; 0x800116 <tail>
 2f8:	80 91 17 01 	lds	r24, 0x0117	; 0x800117 <head>
 2fc:	98 17       	cp	r25, r24
 2fe:	d1 f3       	breq	.-12     	; 0x2f4 <main+0x66>
 300:	80 91 c0 00 	lds	r24, 0x00C0	; 0x8000c0 <__TEXT_REGION_LENGTH__+0x7e00c0>
 304:	85 ff       	sbrs	r24, 5
 306:	f6 cf       	rjmp	.-20     	; 0x2f4 <main+0x66>
 308:	e0 91 16 01 	lds	r30, 0x0116	; 0x800116 <tail>
 30c:	81 e0       	ldi	r24, 0x01	; 1
 30e:	8e 0f       	add	r24, r30
 310:	80 93 16 01 	sts	0x0116, r24	; 0x800116 <tail>
 314:	f0 e0       	ldi	r31, 0x00	; 0
 316:	e8 5e       	subi	r30, 0xE8	; 232
 318:	fe 4f       	sbci	r31, 0xFE	; 254
 31a:	80 81       	ld	r24, Z
 31c:	80 93 c6 00 	sts	0x00C6, r24	; 0x8000c6 <__TEXT_REGION_LENGTH__+0x7e00c6>
 320:	90 91 16 01 	lds	r25, 0x0116	; 0x800116 <tail>
 324:	80 91 17 01 	lds	r24, 0x0117	; 0x800117 <head>
 328:	98 13       	cpse	r25, r24
 32a:	ea cf       	rjmp	.-44     	; 0x300 <main+0x72>
 32c:	e3 cf       	rjmp	.-58     	; 0x2f4 <main+0x66>

0000032e <_exit>:
 32e:	f8 94       	cli

00000330 <__stop_program>:
 330:	ff cf       	rjmp	.-2      	; 0x330 <__stop_program>

Disassembly of section .bss:

00800100 <__bss_start>:
	...

00800101 <dt.2478>:
	...

00800111 <hit.2476>:
	...

00800112 <prev.2477>:
  800112:	00 00 00 00                                         ....

00800116 <tail>:
	...

00800117 <head>:
	...

00800118 <buff>:
	...

00800218 <high>:
	...
