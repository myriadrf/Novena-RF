//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frBoard2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//Comands
//I2C FPGA
#define CFG_ADDR 0xAA
#define CMD_CFG_I2C_WR 0x14
#define CMD_CFG_I2C_RD 0x15

//LMS6002D
#define CMD_LMS_WR 0x16
#define CMD_LMS_RD 0x17

//I2C Si5356A
#define FSN_ADDR 0xE0
#define CMD_FSN_I2C_WR 0x24
#define CMD_FSN_I2C_RD 0x25

#define SI5338_DELAY 12 //12ms
//#define LOCK_MASK 0x15
//#define LOS_MASK 0x04
#define LOCK_MASK 0x19
#define LOS_MASK 0x08

TfrmBoard2 *m_frmBoard2;
//---------------------------------------------------------------------------
__fastcall TfrmBoard2::TfrmBoard2(TComponent* Owner)
        : TFrame(Owner)
{
        InCtrEndPt = NULL;
        OutCtrEndPt = NULL;
        initialized = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard2::btnConfigureSi5356AClick(TObject *Sender)
{
        
  unsigned char out[64];
  unsigned char in[64];
  LONG length = 64;

  if(!OutCtrEndPt || !InCtrEndPt) return;
/*
  memset(out, 0x00, length);

  //Write data
  out[0] = CMD_CFG_I2C_RD;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 9;//0x00;

//  out[5] = 0x01;
//  out[6] = 0x02;
//  out[7] = 0x03;
//  out[8] = 0x04;
//  out[9] = 0x05;
//  out[10] = 0x06;
//  out[11] = 0x07;

  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);

  Sleep(300);
*/



  Reg_Data curr;
  char curr_chip_val, clear_curr_val, clear_new_val, combined, reg;


  //I2C_ByteWrite(230, 0x10); //OEB_ALL = 1
  //I2C_ByteWrite(241, 0xE5); //DIS_LOL = 1
  out[0] = CMD_CFG_I2C_WR;
  out[1] = FSN_ADDR;
  out[2] = 2;
  //
  out[4] = 230;
  out[5] = 0x10;
  out[6] = 241;
  out[7] = 0xE5; //0xE5;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);

  //for all the register values in the Reg_Store array
  //get each value and mask and apply it to the Si5338  for(int i=0; i<NUM_REGS_MAX; i++)
  for(int i=0; i<NUM_REGS_MAX; i++)
  {
    curr = Reg_Store[i];

    memset(out, 0x00, length);
    memset(in, 0x00, length);

    if(curr.Reg_Mask != 0x00)
    {
      if(curr.Reg_Mask == 0xFF)
      {
        // do a write transaction only
        // since the mask is all ones
        //Write data
        out[0] = CMD_CFG_I2C_WR;
        out[1] = FSN_ADDR;
        out[2] = 1;
        //
        out[4] = curr.Reg_Addr;
        out[5] = curr.Reg_Val;

        OutCtrEndPt->XferData(out, length);
        InCtrEndPt->XferData(in, length);
        //I2C_ByteWrite(curr.Reg_Addr, curr.Reg_Val);
      }
      else
      {
        //do a read-modify-write
        //Write data
        out[0] = CMD_CFG_I2C_RD;
        out[1] = FSN_ADDR;
        out[2] = 1;
        //
        out[4] = curr.Reg_Addr;

        OutCtrEndPt->XferData(out, length);
        InCtrEndPt->XferData(in, length);

        curr_chip_val = in[0];

        //curr_chip_val = 0xFF; //I2C_ByteRead(curr.Reg_Addr);
        clear_curr_val = curr_chip_val & ~curr.Reg_Mask;
        clear_new_val = curr.Reg_Val & curr.Reg_Mask;
        combined = clear_new_val | clear_curr_val;

        //I2C_ByteWrite(curr.Reg_Addr, combined);
        //Write data
        out[0] = CMD_CFG_I2C_WR;
        out[1] = FSN_ADDR;
        out[2] = 1;
        //
        out[4] = curr.Reg_Addr;
        out[5] = combined;

        OutCtrEndPt->XferData(out, length);
        InCtrEndPt->XferData(in, length);

      }
    }
  };


//////////////////////
  //I2C_ByteWrite(246, 2); //soft reset
  memset(out, 0x00, length);
  memset(in, 0x00, length);
  //Write data
  out[0] = CMD_CFG_I2C_WR;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 246;
  out[5] = 2;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);

  
  //I2C_ByteWrite(230, 0x00); // OEB_ALL = 0
  memset(out, 0x00, length);
  memset(in, 0x00, length);
  //Write data
  out[0] = CMD_CFG_I2C_WR;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 230;
  out[5] = 0x00;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);
///////////////////////


  return;

  // check LOS alarm for the xtal input
  // on IN1 and IN2 (and IN3 if necessary) -
  // change this mask if using inputs on IN4, IN5, IN6
  do
  {
    memset(out, 0x00, length);
    memset(in, 0x00, length);

    //Read data
    out[0] = CMD_CFG_I2C_RD;
    out[1] = FSN_ADDR;
    out[2] = 1;
    //
    out[4] = 218;
    OutCtrEndPt->XferData(out, length);
    InCtrEndPt->XferData(in, length);
    reg = in[0] & LOS_MASK;
  }
  while(reg != 0);


  //I2C_ByteWrite(49, I2C_ByteRead(49) & 0x7F); //FCAL_OVRD_EN = 0
  memset(out, 0x00, length);
  memset(in, 0x00, length);
  //Read data
  out[0] = CMD_CFG_I2C_RD;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 49;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);
  //Write data
  out[0] = CMD_CFG_I2C_WR;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 49;
  out[5] = in[0] & 0x7F;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);


  //I2C_ByteWrite(246, 2); //soft reset
  memset(out, 0x00, length);
  memset(in, 0x00, length);
  //Write data
  out[0] = CMD_CFG_I2C_WR;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 246;
  out[5] = 2;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);


  //I2C_ByteWrite(241, 0x65); //DIS_LOL = 0
  memset(out, 0x00, length);
  memset(in, 0x00, length);
  //Write data
  out[0] = CMD_CFG_I2C_WR;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 241;
  out[5] = 0x65;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);

  // wait for Si5338 to be ready after calibration (ie, soft reset)
  //counter = 0;
  //while(counter < SI5338_DELAY) { counter++; }
  Sleep(SI5338_DELAY);
  
  //counter = 0;
  //while(counter < SI5338_DELAY) { counter++; }
  Sleep(SI5338_DELAY);



  //make sure the device locked by checking PLL_LOL and SYS_CAL
/*
  reg = I2C_ByteRead(218) & LOCK_MASK;
  while(reg != 0)
  {
    reg = I2C_ByteRead(218) & LOCK_MASK;
  }
*/
  do
  {
    memset(out, 0x00, length);
    memset(in, 0x00, length);

    //Read data
    out[0] = CMD_CFG_I2C_RD;
    out[1] = FSN_ADDR;
    out[2] = 1;
    //
    out[4] = 218;
    OutCtrEndPt->XferData(out, length);
    InCtrEndPt->XferData(in, length);
    reg = in[0] & LOCK_MASK;
  }
  while(reg != 0);


  //copy FCAL values
  //I2C_ByteWrite(45, I2C_ByteRead(235));
  //I2C_ByteWrite(46, I2C_ByteRead(236));
  memset(out, 0x00, length);
  memset(in, 0x00, length);

  //Read data
  out[0] = CMD_CFG_I2C_RD;
  out[1] = FSN_ADDR;
  out[2] = 2;
  //
  out[4] = 235;
  out[5] = 236;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);

  //Write data
  out[0] = CMD_CFG_I2C_WR;
  out[1] = FSN_ADDR;
  out[2] = 2;
  //
  out[4] = 45;
  out[5] = in[0];
  out[6] = 46;
  out[7] = in[1];
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);


  

  // clear bits 0 and 1 from 47 and
  // combine with bits 0 and 1 from 237
  //reg = (I2C_ByteRead(47) & 0xFC) | (I2C_ByteRead(237) & 3);
  //I2C_ByteWrite(47, reg);
  memset(out, 0x00, length);
  memset(in, 0x00, length);
  //Read data
  out[0] = CMD_CFG_I2C_RD;
  out[1] = FSN_ADDR;
  out[2] = 2;
  //
  out[4] = 47;
  out[5] = 237;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);

  //Write data
  out[0] = CMD_CFG_I2C_WR;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 47;
  out[5] = (in[0] & 0xFC) | (in[1] & 3);
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);


  //I2C_ByteWrite(49, I2C_ByteRead(49) | 0x80); // FCAL_OVRD_EN = 1
  memset(out, 0x00, length);
  memset(in, 0x00, length);
  //Read data
  out[0] = CMD_CFG_I2C_RD;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 49;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);

  //Write data
  out[0] = CMD_CFG_I2C_WR;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 49;
  out[5] = in[0] | 0x80;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);


  //I2C_ByteWrite(230, 0x00); // OEB_ALL = 0
  memset(out, 0x00, length);
  memset(in, 0x00, length);
  //Write data
  out[0] = CMD_CFG_I2C_WR;
  out[1] = FSN_ADDR;
  out[2] = 1;
  //
  out[4] = 230;
  out[5] = 0x00;
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmBoard2::btnLmsRdClick(TObject *Sender)
{
    //     int iVal;
	unsigned char out[64];
	unsigned char in[64];
  LONG length = 64;

  if(!OutCtrEndPt || !InCtrEndPt) return;
  if(!m_bAllowSend) return;

  //iVal = cmbOvs->ItemIndex;

  //Read data from address 0x04
  memset(out, 0x00, length);
  //Write data
  out[0] = CMD_LMS_RD;
  out[1] = CFG_ADDR;
  out[2] = 1;
  //
  out[4] = 0x04;  //SPI Instruction
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);


  //Write 0x0F to address 0x07
  memset(out, 0x00, length);
  //Write data
  out[0] = CMD_LMS_WR;
  out[1] = CFG_ADDR;
  out[2] = 1;
  //
  out[4] = 0x87;  //SPI Instruction
  out[5] = 0x0F;  //SPI Data
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);

  //Read data from address 0x07
  memset(out, 0x00, length);
  //Write data
  out[0] = CMD_LMS_RD;
  out[1] = CFG_ADDR;
  out[2] = 1;
  //
  out[4] = 0x07;  //SPI Instruction
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);


/*
  memset(out, 0x00, length);
  //Write data
  //out[0] = CMD_CFG_I2C_WR;
  out[0] = CMD_CFG_I2C_RD;
  out[1] = CFG_ADDR;
  out[2] = 1;
  //
  out[4] = 0x00;  //SPI Instruction

  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);
*/
        
}
//---------------------------------------------------------------------------

void TfrmBoard2::Initialize(CCyUSBEndPoint *pInEndPt, CCyUSBEndPoint *pOutEndPt,
                                CCyUSBEndPoint *pInCtrEndPt, CCyUSBEndPoint *pOutCtrEndPt)
{
//end points are set in dlgSerPort
/*
        USBDevice = new CCyUSBDevice();
        USBDevice->Open(0);
        if(USBDevice)
        {
  	        USBDevice->Open(0);
                OutCtrEndPt = USBDevice->BulkOutEndPt;
                InCtrEndPt = USBDevice->BulkInEndPt;
        }
        //InCtrEndPt = pInEndPt;
        //OutCtrEndPt = pOutEndPt;

        int eptCount = USBDevice->EndPointCount();
    for(int i=0; i<eptCount; i++)
    {
      //cccnt = USBDevice->EndPoints[i]->Address;
      if(USBDevice->EndPoints[i]->Address == 0x86)
      {
        InEndPt = USBDevice->EndPoints[i];
      }

      if(USBDevice->EndPoints[i]->Address == 0x02)
      {
        OutEndPt = USBDevice->EndPoints[i];
      }

      if(USBDevice->EndPoints[i]->Address == 0x01)
      {
        OutCtrEndPt = USBDevice->EndPoints[i];
      }

      if(USBDevice->EndPoints[i]->Address == 0x81)
      {
        InCtrEndPt = USBDevice->EndPoints[i];
      }
    }

        if(InCtrEndPt && OutCtrEndPt)
        {
                m_bAllowSend = true;
                initialized = true;
        }
        else
        {
                m_bAllowSend = false;
                initialized = false;
        }
        USBDevice->Close();
*/
        InCtrEndPt = pInCtrEndPt;
        OutCtrEndPt = pOutCtrEndPt;
        InEndPt = pInEndPt;
        OutEndPt = pOutEndPt;

        if(InCtrEndPt && OutCtrEndPt)
        {
                m_bAllowSend = true;
                initialized = true;
        }
        else
        {
                m_bAllowSend = false;
                initialized = false;
        }
        
}
void __fastcall TfrmBoard2::btnLoadFileClick(TObject *Sender)
{
  char drive[MAXDRIVE] = "";
  char dir[MAXDIR] = "";
  char file[MAXFILE] = "";
  char ext[MAXEXT] = "";
  char s[MAX_PATH] = "";

  memset(s, '\0', sizeof(s));
  memcpy(s, Application->ExeName.c_str(), Application->ExeName.Length());
  fnsplit(s, drive, dir, file, ext);
  dlgOpen->DefaultExt = "h";
  //dlgOpen->FileName = "*.vco";
//  dlgOpen->Filter = "Register Files (*.h)|*.h";
  dlgOpen->Filter = "Register Files (*.h)|*.h|Text files (*.txt)|*.TXT";
  dlgOpen->InitialDir = drive;
  dlgOpen->InitialDir = dlgOpen->InitialDir + dir;
  if(dlgOpen->Execute())
  {
    LoadRegValuesFromFile(dlgOpen->FileName);
  };
}

void TfrmBoard2::LoadRegValuesFromFile(String FName)
{
  FILE *in;
  char inStr[128];
  int iEntry = 0;
  int Rez;

  int iReg_Addr;
  int iReg_Val;
  int iReg_Mask;

  if((in = fopen(FName.c_str(), "rt")) == NULL)
  {
    ShowMessage("Cannot open input file.");
    return;
  };

  //while( fscanf( in, "%[^\n]", inStr )!=EOF )
  //while( fscanf( in, "%s\n", inStr )!=EOF )
  while(!feof(in))
  {
    fgets(inStr, 127, in);
    if(inStr[0] == '{')
    {
      Rez = sscanf(&inStr[1], "%d,%i,%i", &iReg_Addr, &iReg_Val, &iReg_Mask);
      if(Rez == 3)
      {
        Reg_Store[iEntry].Reg_Addr = iReg_Addr;
        Reg_Store[iEntry].Reg_Val = iReg_Val;
        Reg_Store[iEntry].Reg_Mask = iReg_Mask;
      };
      iEntry++;
    };
  };

  fclose(in);
};


//---------------------------------------------------------------------------

void __fastcall TfrmBoard2::btnRdMemClick(TObject *Sender)
{
  int iVal;
	unsigned char out[64];
	unsigned char in[64];
  LONG length = 64;

  if(!OutCtrEndPt || !InCtrEndPt) return;
  if(!m_bAllowSend) return;

  memset(out, 0x00, length);
  //Write data
  out[0] = CMD_CFG_I2C_RD;
  out[1] = CFG_ADDR;
  out[2] = 16;
  //
  for(int i=0; i<16; i++)
  {
    out[4+i] = i;
  }
  OutCtrEndPt->XferData(out, length);
  InCtrEndPt->XferData(in, length);
}
//---------------------------------------------------------------------------

