//Christopher Zhu
//UID: 104455996
// 3.56

/* A. The register %esi contains x from the code movl 8(%ebp), %esi since 
	x is at %ebp + 8. The register %ebx contains n as seen from the second line
	movl 12(%ebp), %ebx since n is at %ebp + 12. The register %edi contains result since it 
	is copied to %eax at the very end of the function as the return value. Therefore,
	the register %edx must be the register with the variable mask as seen in line 4.

	B. The initial value of %edi is -1 and %edx is intialized to 1 as seen in lines 3-4.
	
	C. The test condition for mask is that mask is not equal to zero as seen in line 12 jne .L2.
	
	D. Mask gets updated on line 10,  %cl, %edx, which changes mask to be mask << n.
	
	E. Result gets updated on lines 6 through 8 which make result become result ^ (x & mask).
	
	F. See below for original code.
	
*/
int loop(int x, int n)
{
	int result = -1;
	int mask;
	for(mask = 0x1; mask != 0; mask = mask << n)
	{
		result ^= (x & mask);
	}
	return result;
}