// Compute vector sum h_C = h_A+h_B
void vecAdd(float* h_A, float* h_B, float* h_C, int n)
{
	for (i = 0; i < n; i++) 
		h_C[i] = h_A[i] + h_B[i];
}
int main()
{
	// Memory allocation for h_A, h_B, and h_C
	// I/O to read h_A and h_B, N elements each
	…
	vecAdd(h_A, h_B, h_C, N);
}