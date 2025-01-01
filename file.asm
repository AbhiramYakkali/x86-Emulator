mov eax, 100 ; test immediate -> register
mov byte [10], 75 ; test immediate -> memory
mov dword ebx, [7] ; test memory -> register
mov dword [eax], ebx ; test register -> memory
mov dword ecx, [eax] ; test memory (indirect addressing) -> register
;
xchg ecx, edx ; test xchg register <-> register
mov dword [ecx], 200
xchg dword ecx, [ecx] ; test xchg register <-> memory