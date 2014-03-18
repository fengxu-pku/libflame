
#include "FLAME.h"

FLA_Error FLA_Scal_elemwise( FLA_Trans trans, FLA_Obj A, FLA_Obj B )
{
  FLA_Datatype datatype;
  int          m_B, n_B;
  int          rs_A, cs_A;
  int          rs_B, cs_B;
  trans1_t      blis_trans;

  if ( FLA_Check_error_level() == FLA_FULL_ERROR_CHECKING ) 
    FLA_Scal_elemwise_check( trans, A, B );

  if ( FLA_Obj_has_zero_dim( A ) ) return FLA_SUCCESS;

  datatype = FLA_Obj_datatype( A );

  rs_A     = FLA_Obj_row_stride( A );
  cs_A     = FLA_Obj_col_stride( A );

  m_B      = FLA_Obj_length( B );
  n_B      = FLA_Obj_width( B );
  rs_B     = FLA_Obj_row_stride( B );
  cs_B     = FLA_Obj_col_stride( B );

  FLA_Param_map_flame_to_blis_trans( trans, &blis_trans );

  switch ( datatype ){

  case FLA_FLOAT:
  {
    float *buff_A     = ( float * ) FLA_FLOAT_PTR( A );
    float *buff_B     = ( float * ) FLA_FLOAT_PTR( B );

    bl1_sewscalmt( blis_trans,
                   m_B,
                   n_B,
                   buff_A, rs_A, cs_A,
                   buff_B, rs_B, cs_B );

    break;
  }

  case FLA_DOUBLE:
  {
    double *buff_A     = ( double * ) FLA_DOUBLE_PTR( A );
    double *buff_B     = ( double * ) FLA_DOUBLE_PTR( B );

    bl1_dewscalmt( blis_trans,
                   m_B,
                   n_B,
                   buff_A, rs_A, cs_A,
                   buff_B, rs_B, cs_B );

    break;
  }

  case FLA_COMPLEX:
  {
    scomplex *buff_A =     ( scomplex * ) FLA_COMPLEX_PTR( A );
    scomplex *buff_B =     ( scomplex * ) FLA_COMPLEX_PTR( B );

    bl1_cewscalmt( blis_trans,
                   m_B,
                   n_B,
                   buff_A, rs_A, cs_A,
                   buff_B, rs_B, cs_B );

    break;
  }

  case FLA_DOUBLE_COMPLEX:
  {
    dcomplex *buff_A     = ( dcomplex * ) FLA_DOUBLE_COMPLEX_PTR( A );
    dcomplex *buff_B     = ( dcomplex * ) FLA_DOUBLE_COMPLEX_PTR( B );

    bl1_zewscalmt( blis_trans,
                   m_B,
                   n_B,
                   buff_A, rs_A, cs_A,
                   buff_B, rs_B, cs_B );

    break;
  }

  }
  
  return FLA_SUCCESS;
}
