#include <iostream>
#include "matrixmul.h"

void gen_matrix_ab(mat_a_t a[MAT_DIM][MAT_DIM],mat_b_t b[MAT_DIM][MAT_DIM]);
void gen_sw_matmult(mat_a_t a[MAT_DIM][MAT_DIM], mat_b_t b[MAT_DIM][MAT_DIM],result_t sw_res[MAT_DIM][MAT_DIM]);
void check_matmult_result( result_t hw_res[MAT_DIM][MAT_DIM], result_t sw_res[MAT_DIM][MAT_DIM], int &err_cnt);

using namespace std;

//----------------------------------------------------
// Test the streaming interface.
int test_matrix_mul_core()
{
   mat_a_t in_mat_a[MAT_DIM][MAT_DIM];
   mat_b_t in_mat_b[MAT_DIM][MAT_DIM];
   result_t hw_result[MAT_DIM][MAT_DIM], sw_result[MAT_DIM][MAT_DIM];
   int i, j, err_cnt = 0;
   hls::stream<AXI_VALUE> in_stream_0;
   hls::stream<AXI_VALUE> in_stream_1;
   hls::stream<AXI_VALUE> out_stream;
   AXI_VALUE aValue;


   gen_matrix_ab(in_mat_a, in_mat_b);
   gen_sw_matmult(in_mat_a, in_mat_b, sw_result);

   //convert matrix in input stream
	for(i = 0; i < MAT_DIM; i++) {
		for(j = 0; j < MAT_DIM; j++) {
			union {	unsigned int oval; mat_a_t ival; } converter;
			converter.ival = in_mat_a[i][j];
			aValue.data = converter.oval;
		  in_stream_0.write(aValue);
		}
	}

	for(i = 0; i < MAT_DIM; i++) {
		for(j = 0; j < MAT_DIM; j++) {
			union {	unsigned int oval; mat_b_t ival; } converter;
			converter.ival = in_mat_b[i][j];
			aValue.data = converter.oval;
		  in_stream_1.write(aValue);
		}
	}


   // Run the Vivado-HLS matrix multiply block
	func_hls_core(in_stream_0, in_stream_1, out_stream);

   //convert  output stream in matrix
	for(i = 0; i < MAT_DIM; i++) {
		for(j = 0; j < MAT_DIM; j++) {
			out_stream.read(aValue);
			union {	unsigned int ival; result_t oval; } converter;
			converter.ival = aValue.data;
			hw_result[i][j] = converter.oval;
		}
	}


   cout << "Result by HW" << endl;
   check_matmult_result(hw_result, sw_result, err_cnt);

   if (err_cnt)
      cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
   else
      cout << "Test passed. No errors" << endl;

   return err_cnt;
}

//----------------------------------------------------
void gen_matrix_ab(
    mat_a_t a[MAT_DIM][MAT_DIM],
    mat_b_t b[MAT_DIM][MAT_DIM])
{
	for(int i = 0; i < MAT_DIM; i++) {
		  for(int j = 0; j < MAT_DIM; j++) {
		  a[i][j] = i;
		  b[i][j] = j;
		  cout << "a: " << a[i][j] << endl;
		  cout << "b: " << b[i][j] << endl;
	   }
	}
}

//----------------------------------------------------
void gen_sw_matmult(
    mat_a_t a[MAT_DIM][MAT_DIM],
    mat_b_t b[MAT_DIM][MAT_DIM],
    result_t sw_res[MAT_DIM][MAT_DIM])
{
	// Generate the expected result
	// Iterate over the rows of the A matrix
	for(int i = 0; i < MAT_DIM; i++) {
	   // Iterate over the columns of the B matrix
		  for(int j = 0; j < MAT_DIM; j++) {
		  sw_res[i][j] = 0;
		  // Do the inner product of a row of A and col of B
		  for(int k = 0; k < MAT_DIM; k++) {
			 sw_res[i][j] += a[i][k] * b[k][j];
		  }
	   }
	}
}
//----------------------------------------------------
void check_matmult_result(
    result_t hw_res[MAT_DIM][MAT_DIM],
    result_t sw_res[MAT_DIM][MAT_DIM],
    int &err_cnt)
{
// Print result matrix
cout << "{" << endl;
for (int i = 0; i < MAT_DIM; i++) {
   cout << "{";
   for (int j = 0; j < MAT_DIM; j++) {
      cout << hw_res[i][j];
      // Check HW result against SW
      if (hw_res[i][j] != sw_res[i][j]) {
         err_cnt++;
         cout << "*";
      }
      if (j == MAT_DIM - 1)
         cout << "}" << endl;
      else
         cout << ",";
   }
}
cout << "}" << endl;
}

//----------------------------------------------------
int main(int argc, char **argv)
{
	int err_cnt;

	//err_cnt = test_matrix_mul();
    err_cnt = test_matrix_mul_core();

	return err_cnt;
}

