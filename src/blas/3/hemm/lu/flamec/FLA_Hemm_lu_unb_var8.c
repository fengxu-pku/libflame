
#include "FLAME.h"

#ifdef FLA_ENABLE_NON_CRITICAL_CODE

FLA_Error FLA_Hemm_lu_unb_var8( FLA_Obj alpha, FLA_Obj A, FLA_Obj B, FLA_Obj beta, FLA_Obj C )
{
  FLA_Obj ATL,   ATR,      A00,  a01,     A02, 
          ABL,   ABR,      a10t, alpha11, a12t,
                           A20,  a21,     A22;

  FLA_Obj BT,              B0,
          BB,              b1t,
                           B2;

  FLA_Obj CT,              C0,
          CB,              c1t,
                           C2;

  FLA_Scal_external( beta, C );

  FLA_Part_2x2( A,    &ATL, &ATR,
                      &ABL, &ABR,     0, 0, FLA_BR );

  FLA_Part_2x1( B,    &BT, 
                      &BB,            0, FLA_BOTTOM );

  FLA_Part_2x1( C,    &CT, 
                      &CB,            0, FLA_BOTTOM );

  while ( FLA_Obj_length( ABR ) < FLA_Obj_length( A ) ){

    FLA_Repart_2x2_to_3x3( ATL, /**/ ATR,       &A00,  &a01,     /**/ &A02,
                                                &a10t, &alpha11, /**/ &a12t,
                        /* ************* */   /* ************************** */
                           ABL, /**/ ABR,       &A20,  &a21,     /**/ &A22,
                           1, 1, FLA_TL );

    FLA_Repart_2x1_to_3x1( BT,                &B0, 
                                              &b1t, 
                        /* ** */            /* ** */
                           BB,                &B2,        1, FLA_TOP );

    FLA_Repart_2x1_to_3x1( CT,                &C0, 
                                              &c1t, 
                        /* ** */            /* ** */
                           CB,                &C2,        1, FLA_TOP );

    /*------------------------------------------------------------*/

    /* C0 = C0 + a01 * b1t */
    FLA_Ger_external( alpha, a01, b1t, C0 );

    /* c1t = c1t + alpha11 * b1t */
    FLA_Axpys_external( alpha, alpha11, b1t, FLA_ONE, c1t );

    /* C2 = C2 + a12t' * b1t */
    FLA_Gerc_external( FLA_CONJUGATE, FLA_NO_CONJUGATE, alpha, a12t, b1t, C2 );

    /*------------------------------------------------------------*/

    FLA_Cont_with_3x3_to_2x2( &ATL, /**/ &ATR,       A00,  /**/ a01, A02,
                            /* ************** */  /* ************************ */
                                                     a10t, /**/ alpha11, a12t,
                              &ABL, /**/ &ABR,       A20,  /**/ a21, A22,
                              FLA_BR );

    FLA_Cont_with_3x1_to_2x1( &BT,                B0, 
                            /* ** */           /* ** */
                                                  b1t, 
                              &BB,                B2,     FLA_BOTTOM );

    FLA_Cont_with_3x1_to_2x1( &CT,                C0, 
                            /* ** */           /* ** */
                                                  c1t, 
                              &CB,                C2,     FLA_BOTTOM );

  }

  return FLA_SUCCESS;
}

#endif