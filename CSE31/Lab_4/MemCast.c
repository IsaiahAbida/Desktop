#include <stdio.h>

int main() {
	int i;
	int four_ints[4];
	char* four_c;

	for(i = 0; i < 4; i++)
        four_ints[i] = 2;

	printf("%x\n", four_ints[0]);
	
    four_c = (char*)four_ints;

    for(i = 0; i < 4; i++)
        four_c[i] = 'A' + i; // ASCII 0x41-0x44

    // question 3: 
    // printf("four_ints[0] after writing via four_c: %x\n", four_ints[0]);

	// question 5:
	//printf("four_ints: %p\n", (void*)four_ints);
	//printf("four_c: %p\n", (void*)four_c);

	// question 6:
	//for (i = 0; i < 4; i++)
   // printf("&four_ints[%d] = %p, value = %x\n", i, (void*)&four_ints[i], four_ints[i]);
	
   //question 8
   for(i = 0; i < 16; i++) {
    printf("&four_c[%d] = %p, value = %x\n", i, (void*)&four_c[i], four_c[i]);
}

    return 0;
}
