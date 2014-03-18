
#include "FLAME.h"

FLA_Error FLA_LQ_UT_solve_check( FLA_Obj A, FLA_Obj T, FLA_Obj B, FLA_Obj X )
{
  FLA_Error e_val;

  e_val = FLA_Check_floating_object( A );
  FLA_Check_error_code( e_val );

  e_val = FLA_Check_nonconstant_object( A );
  FLA_Check_error_code( e_val );

  e_val = FLA_Check_identical_object_datatype( A, T );
  FLA_Check_error_code( e_val );

  e_val = FLA_Check_identical_object_datatype( A, B );
  FLA_Check_error_code( e_val );

  e_val = FLA_Check_identical_object_datatype( A, X );
  FLA_Check_error_code( e_val );

  e_val = FLA_Check_object_width_equals( T, FLA_Obj_min_dim( A ) );
  FLA_Check_error_code( e_val );

  e_val = FLA_Check_matrix_matrix_dims( FLA_NO_TRANSPOSE, FLA_NO_TRANSPOSE, A, X, B );
  FLA_Check_error_code( e_val );

  return FLA_SUCCESS;
}

