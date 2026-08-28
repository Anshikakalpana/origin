;port is a specific number assigned to each hardware 
;outb and inb are functions/instructions to allow communication between hardware and cpu
;outb function/instruction is used to send data to a specific port

global outb
outb:
    mov dx, [esp+4]  ; port number
    mov al, [esp+8]  ; data byte
    out dx, al
    ret

;inb function/instruction is used to recieve data from a specific port

global inb
inb:
    mov dx, [esp+4]  ; port number
    in al, dx
    ret