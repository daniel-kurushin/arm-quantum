byte b;
int rs = 0;
int r_sys, r_cmd, e_sys, e_cmd;
int first_byte_x, second_byte_x, x;

void setup()
{
  Serial.begin(9600);
}

void log()
{
  Serial.println("\nb\trs\tr_sys\tr_cmd\te_sys\te_cmd\n");
  Serial.print(b);  Serial.print("\t");
  Serial.print(rs);  Serial.print("\t");
  Serial.print(r_sys);  Serial.print("\t");
  Serial.print(r_cmd);  Serial.print("\t");
  Serial.print(e_sys);  Serial.print("\t");
  Serial.print(e_cmd);  Serial.print("\t");

  Serial.print("\n");
}

void loop()
{

  if (Serial.available() > 0)
  {
    b = Serial.read();
       
    switch (rs)
    {
      case 0:
        if (b == 48) rs++;
        else Serial.println("-+-+-+-\tnot first synchro\t-+-+-+-");
        break;
      case 1:
        if (b == 48) rs++;
        else
        {
          rs = 0;
          Serial.println("-+-+-+-\tnot second synchro\t-+-+-+-");
        }
        break;
      case 2:
        r_sys = b;
        rs++;
        break;   
      case 3:
        r_cmd = b;
        rs++;
        break;
      case 4:
        switch (r_sys)
        {
          case 49://engines system
            switch (r_cmd)
            {
              case 49:
                
                break;
              case 50://position x, y, z
                /*switch (rs)
                {
                  case 5:
                    first_byte_x = b;
                    rs++;
                    break;
                  case 6:
                    second_byte_x = b;
                    x = first_byte_x;
                    x = x << 8;
                    x = x | second_byte_x;
                    rs=0;                    
                    break;
//                  case 7:
//                    first_byte_y = b;
//                    rs++;
//                    break;
//                  case 8:
//                    second_byte_y = b;
//                    rs++;
//                    break;
//                  case 9:
//                    first_byte_z = b;
//                    rs++;
//                    break;
//                  case 10:
//                    second_byte_z = b;
//                    rs++;
//                    break;
//                  case 11:
//                    
//                    rs++;
//                    break;
//                  case 12:
//                    y = first_byte_y;
//                    y = y << 8;
//                    y = y | second_byte_y;
//                    rs++;
//                    break;
//                  case 13:
//                    z = first_byte_z;
//                    z = z << 8;
//                    z = z | second_byte_z;
//                    rs++;
//                    break;
                }*/
              default:
                Serial.println("-+-+-+-\tnumber command  not found\t-+-+-+-");
            }
            break;
            
          default:
            Serial.println("-+-+-+-\tnumber system  not found\t-+-+-+-");
        }
        rs++;
        break;
      case 5:
        if (b == 102) rs++;
        else
        {
          rs = 0;
          Serial.println("-+-+-+-\tnot first end synchro\t-+-+-+-");
        }
        break;
      case 6:
        rs = 0;
        if (b == 102) 
        {
          Serial.println("qqq");
          e_sys = r_sys;
          e_cmd = r_cmd;
          Serial.println("-+-+-+-\tcommand successful recive\t-+-+-+-");
        }
        else  Serial.println("-+-+-+-\tnot second end synchro\t-+-+-+-");
        break;
    }
    log();
    
  }
  else
  {

    //еще нужно деление на выполненную и в процессе

    switch(e_sys)
    {
      case 49:
        switch(e_cmd)
        {
          case 49:
            Serial.println("inicialization");
            e_cmd = 0;//not now
            break;

          default:
            Serial.println("command not selected");
            delay(3000);
        }
        break;
        
      default:
        Serial.println("system not selected");
        delay(3000);
    }
  }

}
