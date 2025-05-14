BITS 16
ORG 0x7C00

start:
	tutaj zaczynamy program
	mov si, menu

.menu_loop:
	call print_string 	; Rysujemy menu
	call read_char		; Czekamy na wejscie
	cmp al, '1'
	je show_licence		; jesli user wybral 1 pokazujemy licencje
	cpm al, '2'
	je reboot					; jesli 2 to reboot
	jmp .menu_loop		; wpp. wracamy do menu

show_licence:
	; konstruujemy przerwanie biosu
	mov ah, 0x02		; typ przerwania: odczyt sektorow
	mov al, 0x01		; liczba sektorow
	mov ch, 0x00		; cylider
	mov cl, 0x02 		; sektor: 2 = LBA 1
	mov dh, 0x00		; glowica
	mov dl, 0x00		; numer dysku
	mov es, 0x0500		; adres docelowy
	mov bx, 0x0000
	int 0x13		; wywolanie przerwania
	mov si, 0x0500		; wypisz licencje

.print_loop:
	lodsb			; al = si++	
	cmp al, 0x00		; koniec lancucha
	je .menu_loop
	mov ah, 0x0E		; funkcja: wyswietl znak
	call print_char		; 
	jmp .print_loop		; powrot do petli

reboot:
	jmp 0xffff:0x0000

print_string:
.next_char:
	lodsb
	cmp al, 0x00
	je .done
	call print_char
	jmp .next_char
.done:
	ret

print_char:
	mov ah, 0x0E		; write character
	mov bh, 0x00		; numer strony
	mov bl, 0x04		; kolor - czerwony
	int 0x10		; interupt
	ret

read_char:
	mov ah, 0x00		; read character
	int 0x16		; keyboard interrupt
	ret

msg db "1) Licence", 13, 10, "2) Reboot", 13, 10, 0
