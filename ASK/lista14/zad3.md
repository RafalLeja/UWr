- 14-bit virtual addresses
- 12-bit physical address
- Page size = 64 bytes

# 1. 0x027c 
= 000010|01|111100 - virtual address \
TLBI:0x1 TLBT:0x02 PPN:17 V:1 \
Z tablicy stron PPN:17 -> VPN:09

| TLBI | TLBT |	PPN	| V	| TLB |	VPN |
|------|------|-----|---|-----|-----|
| 0x1  | 0x02 | 0x17| 1 | hit | 0x09| 

010111|1111|00 - physical address \
2 nisze bity to CO(cache offset) \
następne 4 bity CI(cache index) \
wysze 6 bitów CT(cache tag) 

| CO | CI| CT |
|----|---|----|
0x0 | 0x0F | 0x17 | miss


# 2. 0x03a9 
 = 000011|10|101001

| TLBI | TLBT |	 V	| TLB |
|------|------|-----|---|
| 0x2  | 0x03 | 0   | miss | 

Sprawdzamy czy jest wpis w tablice stron.
VPN = 00001110 = 0x0E -> PPN:11
Dadajemy do TLB wpis tag:0x03 PPN:11 V:1

| TLBI | TLBT |	PPN	| V	|
|------|------|-----|---|
| 0x2  | 0x03 | 0x11 | 1

10001|1010|01 - physical address

| CO | CI| CT | cache |
|----|---|----|-------|
0x1	 | 0x0A | 	0x11|	miss

# 3. 0x0040 
= 000000|01|000000
TLBI:0x1 TLBT:0x00 TLB:miss
VPN = 00000001 = 0x01

| TLBI | TLBT | TLB |	VPN |
|------|------|-----|-----|
| 0x1  | 0x00 | 0x01| miss| 