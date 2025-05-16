#include "bq796xx.h"
#include "sys_common.h"
#include "datatypes.h"
#include "system.h"
#include "gio.h"
#include "sci.h"
#include "rti.h"
#include "sys_vim.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

typedef union{
   struct 
   {
      BYTE fault_oc_b1:1;
      BYTE fault_adc_cc_b1:1;
      BYTE rsvd_b1:2;
      BYTE fault_sys_b1:1;
      BYTE fault_otp_b1:1;
      BYTE fault_comm_b1:1;
      BYTE fault_pwr_b1:1;
   }fs;
   BYTE fault_summary;
}fault_summary_t;

typedef union{
   struct 
   {
      BYTE pwrbist_fail_b1:1;
      BYTE vss_open_b1:1;
      BYTE tsref_osc_b1:1;
      BYTE tsref_uv_b1:1;
      BYTE tsref_ov_b1:1;
      BYTE dvdd_ov_b1:1;
      BYTE avdd_osc_b1:1;
      BYTE avdd_ov_b1:1;
   }fs;
   BYTE fault_pwr1;
}fault_pwr1_t;

typedef union{
   struct 
   {
      BYTE rsvd1:5;
      BYTE cp_ov_b1:1;
      BYTE cp_uv_b1:1;
      BYTE rsvd2:1;
   }fs;
   BYTE fault_pwr2;
}fault_pwr2_t;


typedef union{
   struct 
   {
      BYTE fcomm_det_b1:1;
      BYTE ftone_det_b1:1;
      BYTE hb_fail_b1:1;
      BYTE coml_b1:1;
      BYTE comh_b1:1;
      BYTE uart_frame_b1:1;
      BYTE comm_clr_det_b1:1;
      BYTE stop_det_b1:1;
   }fs;
   BYTE fault_comm1;
}fault_comm1_t;

typedef union{
   struct 
   {
      BYTE rsvd:6;
      BYTE vif_dis_b1:1;
      BYTE spi_b1:1;
   }fs;
   BYTE fault_comm2;
}fault_comm2_t;

typedef union{
   struct 
   {
      BYTE rsvd:2;
      BYTE ded_det_b1:1;
      BYTE sec_det_b1:1;
      BYTE cust_crc_b1:1;
      BYTE fact_crc_b1:1;
      BYTE load_err_b1:1;
      BYTE gblov_err_b1:1;
   }fs;
   BYTE fault_otp;
}fault_otp_t;

typedef union{
   struct 
   {
      BYTE gpio_b1:1;
      BYTE rsvd1_b1:1;
      BYTE i2c_low_b1:1;
      BYTE i2c_nack_b1:1;
      BYTE lfo_b1:1;
      BYTE drst_b1:1;
      BYTE tshut_b1:1;
      BYTE rsvd2_b1:1;
   }fs;
   BYTE fault_sys1;
}fault_sys1_t;

typedef union{
   struct 
   {
      BYTE rsvd:5;
      BYTE i2c_busy_b1:1;
      BYTE mspi_busy_b1:1;
      BYTE mspi_ss_b1:1;
   }fs;
   BYTE fault_sys2;
}fault_sys2_t;

typedef union{
   struct 
   {
      BYTE rsvd_b1:1;
      BYTE cc_ovf_b1:1;
      BYTE adc_pfail_b1:1;
      BYTE diag_meas_pfail_b1:1;
      BYTE diag_ana_pfail_b1:1;
      BYTE diag_ana_abort_b1:1;
   }fs;
   BYTE fault_adc_misc;
}fault_adc_misc_t;


typedef union{
   struct 
   {
      BYTE rsvd_b1:1;
      BYTE gpio15_afail_b1:1;
      BYTE gpio14_afail_b1:1;
      BYTE gpio13_afail_b1:1;
      BYTE gpio12_afail_b1:1;
      BYTE gpio11_afail_b1:1;
      BYTE gpio10_afail_b1:1;
      BYTE gpio9_afail_b1:1;
   }fs;
   BYTE fault_adc_gpio1;
}fault_adc_gpio1_t;

typedef union{
   struct 
   {
      BYTE gpio8_afail_b1:1;
      BYTE gpio7_afail_b1:1;
      BYTE gpio6_afail_b1:1;
      BYTE gpio5_afail_b1:1;
      BYTE gpio4_afail_b1:1;
      BYTE gpio3_afail_b1:1;
      BYTE gpio2_afail_b1:1;
      BYTE gpio1_afail_b1:1;
   }fs;
   BYTE fault_adc_gpio2;
}fault_adc_gpio2_t;

typedef union{
   struct 
   {
      BYTE rsvd_b1:6;
      BYTE vf2_afail_b1:1;
      BYTE vf1_afail_b1:1;
   }fs;
   BYTE fault_adc_vf;
}fault_adc_vf_t;

typedef union{
   struct 
   {
      BYTE rsvd1_b1:4;
      BYTE gp3_dfail_b1:1;
      BYTE gp1_dfail_b1:1;
      BYTE rsvd2_b1:2;
   }fs;
   BYTE fault_adc_dig1;
}fault_adc_dig1_t;

typedef union{
   struct 
   {
      BYTE rsvd_b1:6;
      BYTE vf1_dfail_b1:1;
      BYTE vf2_dfail_b1:1;
   }fs;
   BYTE fault_adc_dig2;
}fault_adc_dig2_t;

typedef union{
   struct 
   {
      BYTE diag_oc_abort_b1:1;
      BYTE occ2_b1:1;
      BYTE ocd2_b1:1;
      BYTE oc_pfail_b1:1;
      BYTE occ1_b1:1;
      BYTE ocd1_b1:1;
      BYTE rsvd:2;
   }fs;
   BYTE fault_oc;
}fault_oc_t;
void ReadDebugRegisters(BYTE *response_frame);

