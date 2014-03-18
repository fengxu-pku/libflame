
#include "FLAME.h"

extern fla_uddateut_t* flash_uddateut_cntl;
extern fla_apqudut_t*  flash_apqudut_cntl;

fla_uddateutinc_t*     flash_uddateutinc_cntl;
fla_blocksize_t*       flash_uddateutinc_var1_bsize;

void FLASH_UDdate_UT_inc_cntl_init()
{
	// Set blocksizes for hierarchical storage.
	flash_uddateutinc_var1_bsize = FLA_Blocksize_create( 1, 1, 1, 1 );

	// Create a control tree to invoke variant 1.
	flash_uddateutinc_cntl = FLA_Cntl_uddateutinc_obj_create( FLA_HIER,
	                                                          FLA_BLOCKED_VARIANT1, 
	                                                          flash_uddateutinc_var1_bsize,
	                                                          flash_uddateut_cntl,
	                                                          flash_apqudut_cntl );
}

void FLASH_UDdate_UT_inc_cntl_finalize()
{
	FLA_Cntl_obj_free( flash_uddateutinc_cntl );

	FLA_Blocksize_free( flash_uddateutinc_var1_bsize );
}
